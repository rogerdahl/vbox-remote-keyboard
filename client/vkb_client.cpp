#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/kd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#include <chrono>
#include <thread>

#include "int_types.h"

int connect();
void disconnect(int sock);
void send_int(int sock, int v);

int open_tty();
void close_tty(int tty_dev);

int open_keyboard();
void close_keyboard(int keyboard_dev);

void get_exclusive_access(int keyboard_dev);
void release_exclusive_access(int keyboard_dev);

struct termios save_terminal_attr(int tty_dev);
void restore_terminal_attr(int tty_dev, termios &t);
void set_keyboard_mode(int tty_dev, int mode_idx);
void set_leds(int keyboard_dev, int led_idx, int led_state);

int get_mapping(int tty_dev, int table_idx, int key_idx);
void set_mapping(int tty_dev, int table_idx, int key_idx, int new_keycode);

void intHandler(int dummy);
void set_terminal_attr_raw(int tty_dev);

// Configuration

const char* SERVER_ADDR = "192.168.1.10";
const int SERVER_PORT = 19613;
//const char *KEYBOARD_DEV = "/dev/input/event0";
const char *KEYBOARD_DEV = "/dev/input/event6";

const char *TTY_DEV = "/dev/console";
//const char *TTY_DEV = "/dev/tty";
//const char *TTY_DEV = "/dev/tty1";
//const char *TTY_DEV = "/dev/tty2";
//const char* TTY_DEV = "/dev/pts/0";
const int MSG_LEN = 12;


int main(void)
{
  // If keyboard is opened too soon, the Enter press that was used for launching
  // the program becomes stuck and causes continuous printing of newlines.
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  int socket = connect();
  
  signal(SIGINT, intHandler);

//  int tty_dev = open_tty();
//  struct termios old_term_attr = save_terminal_attr(tty_dev);
//  set_terminal_attr_raw(tty_dev);
//  set_keyboard_mode(tty_dev, K_RAW);
  int keyboard_dev = open_keyboard();
  get_exclusive_access(keyboard_dev);
  set_leds(keyboard_dev, LED_SCROLLL, 1);

  printf("Forwarding keys. Press Ctrl+Shift+F1 to exit\n");

  bool isShiftPressed = false;
  bool isCtrlPressed = false;
  bool isKeyRelease = false;
  u32 curHidValue = 0;

  while (true) {
    ssize_t n;
    struct input_event ev;

    n = read(keyboard_dev, &ev, sizeof ev);
    printf("type=%x code=%x value=%x\n", ev.type, ev.code, ev.value);

//    printf("n=%d\n", n);

    if (n != sizeof ev) {
      perror("Read error");
      break;
    }

    if (ev.type == EV_MSC && ev.code == 4) {
      curHidValue = ev.value;
      continue;
    }

    if (ev.type != EV_KEY) {
      continue;
    }

    isKeyRelease = !ev.value;

    if ((ev.code == KEY_LEFTSHIFT || ev.code == KEY_RIGHTSHIFT)) {
      isShiftPressed = !isKeyRelease;
    }
    if ((ev.code == KEY_LEFTCTRL || ev.code == KEY_RIGHTCTRL)) {
      isCtrlPressed = !isKeyRelease;
    }
    if (ev.code == KEY_F1 && isShiftPressed && isCtrlPressed) {
      printf("Ctrl+Shift+F1 pressed. Exiting\n");
      break;
    }

    u32 hidUsageKey = curHidValue;
    if (isKeyRelease) {
      hidUsageKey |= 0x80000000;
    }

    printf("Sending: %x\n", hidUsageKey);
    send_int(socket, hidUsageKey);
  }

//  set_keyboard_mode(tty_dev, K_XLATE);
  set_leds(keyboard_dev, LED_SCROLLL, 0);
//  poll(keyboard_dev);
  release_exclusive_access(keyboard_dev);
  close_keyboard(keyboard_dev);
//  restore_terminal_attr(tty_dev, old_term_attr);
//  close_tty(tty_dev);
//  disconnect(socket);

  return 0;
}

int open_tty()
{
  int tty_dev = open(TTY_DEV, O_RDWR);
  if (tty_dev < 0) {
    fprintf(stderr,
            "Cannot open TTY. dev=%s err=%s\n",
            TTY_DEV,
            strerror(errno));
    exit(1);
  }
  return tty_dev;
}

void close_tty(int tty_dev)
{
  if (close(tty_dev)) {
    perror("Close TTY");
    exit(1);
  }
}

int open_keyboard()
{
  int keyboard_dev = open(KEYBOARD_DEV, O_RDWR);
  if (keyboard_dev == -1) {
    fprintf(stderr, "Cannot open %s: %s.\n", KEYBOARD_DEV, strerror(errno));
    exit(1);
  }
  return keyboard_dev;
}

void close_keyboard(int keyboard_dev)
{
  if (close(keyboard_dev)) {
    perror("Close keyboard");
    exit(1);
  }
}

void get_exclusive_access(int keyboard_dev)
{
  if (ioctl(keyboard_dev, EVIOCGRAB, 1) < 0) {
    perror("EVIOCGRAB - get exclusive");
    exit(1);
  }
}

void release_exclusive_access(int keyboard_dev)
{
  if (ioctl(keyboard_dev, EVIOCGRAB, 0) < 0) {
    perror("EVIOCGRAB - release exclusive");
    exit(1);
  }
}

struct termios save_terminal_attr(int tty_dev)
{
  struct termios t;
  if (tcgetattr(tty_dev, &t)) {
    perror("tcgetattr");
    exit(1);
  }
  return t;
}

void restore_terminal_attr(int tty_dev, termios &t)
{
  if (tcsetattr(tty_dev, TCSANOW, &t)) {
    perror("tcsetattr");
    exit(1);
  }
}

void set_terminal_attr_raw(int tty_dev)
{
  termios t;
  t.c_iflag = ~(ISTRIP | INLCR | ICRNL | IGNCR | IXON | IXOFF);
  t.c_lflag = ~(ECHO | ICANON | ISIG);
  if (tcsetattr(tty_dev, TCSANOW, &t)) {
    perror("tcsetattr");
    exit(1);
  }
}

// mode_idx = K_RAW, X_LATE
void set_keyboard_mode(int tty_dev, int mode_idx)
{
  if (ioctl(tty_dev, KDSKBMODE, mode_idx) < 0) {
    perror("KDSKBMODE");
    exit(1);
  }
}

// led_idx = LED_CAPSL | LED_SCROLLL | LED_NUML
void set_leds(int keyboard_dev, int led_idx, int led_state)
{
  input_event ev;
  ev.type = EV_LED;
  ev.code = led_idx;
  ev.value = led_state;
  if (write(keyboard_dev, &ev, sizeof ev) < 0) {
    perror("LED write");
    exit(1);
  }
}

// table_idx = K_NORMTAB,
// key_idx = KEY_LEFT,
// return: current keycode
int get_mapping(int tty_dev, int table_idx, int key_idx)
{
  kbentry kbe;
  kbe.kb_table = table_idx;
  kbe.kb_index = key_idx;
  kbe.kb_value = -1;

  if (ioctl(tty_dev, KDGKBENT, &kbe) < 0) {
    perror("KDGKBENT");
    exit(1);
  }

  return kbe.kb_value;
}

// table_idx = K_NORMTAB,
// key_idx = KEY_LEFT,
// new_keycode = val
void set_mapping(int tty_dev, int table_idx, int key_idx, int new_keycode)
{
  kbentry kbe;
  kbe.kb_table = table_idx;
  kbe.kb_index = key_idx;
  kbe.kb_value = new_keycode;

  if (ioctl(tty_dev, KDSKBENT, &kbe) < 0) {
    perror("KDSKBENT");
    exit(1);
  }
}

void intHandler(int dummy)
{
  // Catch and ignore Ctrl-C, so that it can be transmitted.
  // Can only quit with the multi-key sequence.
}

int connect()
{
  struct sockaddr_in server;

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    perror("Could not create socket");
    exit(1);
  }

  server.sin_addr.s_addr = inet_addr(SERVER_ADDR);
  server.sin_family = AF_INET;
  server.sin_port = htons(SERVER_PORT);

  if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
    perror("Could not connect");
    exit(1);
  }

  printf("Connected\n");

  return sock;
}

void disconnect(int sock)
{
  close(sock);
}

void send_int(int sock, int v)
{
  char msg[MSG_LEN];
  sprintf(msg, "%x", v);
  if (send(sock, msg, MSG_LEN, 0) < 0) {
    printf("Send failed\n");
    exit(1);
  }
}
