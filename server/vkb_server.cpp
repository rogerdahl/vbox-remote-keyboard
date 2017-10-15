#include <arpa/inet.h> //inet_addr
#include <arpa/inet.h>
#include <chrono>
#include <errno.h>
#include <fcntl.h>
#include <iconv.h>
#include <linux/input.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>

#include "vbox.h"
#include "int_types.h"
#include "usb_hid_key_map.h"

#include <string>

void error(char* msg);
void forwardScanCodes(nsCOMPtr<IKeyboard> keyboard);
void intHandler(int dummy);
void send_scan_codes(nsCOMPtr<IKeyboard> keyboard, const std::vector<u8>& scanArr);

// Configuration

const int SERVER_PORT = 19613;
const PRUnichar* VBOX_GUEST = reinterpret_cast<const u16*>(L"my-vbox-guest");
const int MSG_LEN = 12;

extern std::vector<UsbHidKeyMap> usbHidKeyMapVec;
bool sigIntReceived = false;


int main()
{
  printf("Starting...\n");

  signal(SIGINT, intHandler);

  nsCOMPtr<IVirtualBox> virtualBox = createVirtualBoxInterface();
  nsCOMPtr<IKeyboard> keyboard = createKeyboard(virtualBox, VBOX_GUEST);

  forwardScanCodes(keyboard);

  releaseKeys(keyboard);
  releaseVirtualBoxInterface(virtualBox);

  return 0;
}

void forwardScanCodes(nsCOMPtr<IKeyboard> keyboard)
{
//  printf("forwardScanCodes()...\n");

  struct sockaddr_in server;
  struct sockaddr_in client;
  char msg[MSG_LEN];

  // Create socket
//  printf("create...\n");
  int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_desc == -1) {
    perror("socket()");
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(SERVER_PORT);

  if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) {
    perror("bind()");
    exit(1);
  }

  while (!sigIntReceived) {
    releaseKeys(keyboard);

    printf("Listening on all interfaces. port=%d\n", SERVER_PORT);
    listen(socket_desc, 3);

    int c = sizeof(struct sockaddr_in);
    int client_sock =
      accept(socket_desc, (struct sockaddr *) &client, (socklen_t * ) & c);
    if (client_sock < 0) {
      perror("accept()");
      exit(1);
    }

    printf("Client connected\n");

    while (!sigIntReceived) {
      int read_size = recv(client_sock, msg, MSG_LEN, 0);

      printf("read_size=%d\n", read_size);

      if (read_size == -1) {
        perror("recv()");
        exit(1);
      }

      if (read_size == 0) {
        printf("Client disconnected\n");
        fflush(stdout);
        break;
      }

      if (read_size != MSG_LEN) {
        printf("Ignoring broken msg: %s\n", msg);
        continue;
      }

      u32 scancode;
      sscanf(msg, "%x", &scancode);
//    printf("%d\n", scancode);

      bool isKeyRelease = scancode & 0x80000000;
      scancode &= 0x7fffffff;
      u8 hidUsagePage = (scancode >> 16) & 0xff;
      u8 hidUsageId = scancode & 0xff;
      
      printf("Search: %x %x\n", hidUsagePage, hidUsageId);

      bool isFound = false;
      for (const auto& map : usbHidKeyMapVec) {
        if (map.hidUsageKey.hidUsagePage == hidUsagePage
          && map.hidUsageKey.hidUsageId == hidUsageId)
        {
          printf("2\n");
          send_scan_codes(
            keyboard,
            !isKeyRelease ? map.ps2Set1make : map.ps2Set1brk
          );
          isFound = true;
        }
//
//          printf("Found: %x %x\n", hidUsagePage, hidUsageId);
//        }
      }
      printf("found: %d\n", isFound);
    }
  }
}

void send_scan_codes(nsCOMPtr<IKeyboard> keyboard, const std::vector<u8>& scanArr)
{
  for (const auto& v : scanArr) {
    printf("send_scan_codes(): %x\n", v);
    sendKeyScanCode(keyboard, v);
  }
}

void error(char* msg)
{
  perror(msg);
  exit(1);
}

void intHandler(int dummy)
{
  sigIntReceived = true;
}
