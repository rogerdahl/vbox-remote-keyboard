

#include "vbox.h"

#include <stdlib.h>

char* nsIDToString(nsID* guid);
void printErrorInfo();


nsCOMPtr<IVirtualBox> createVirtualBoxInterface()
{
  nsresult rc;

  /*
   * Check that PRUnichar is equal in size to what compiler composes L""
   * strings from; otherwise NS_LITERAL_STRING macros won't work correctly
   * and we will get a meaningless SIGSEGV. This, of course, must be checked
   * at compile time in xpcom/string/nsTDependentString.h, but XPCOM lacks
   * compile-time assert macros and I'm not going to add them now.
   */
  if (sizeof(PRUnichar) != sizeof(wchar_t)) {
    printf(
        "Error: sizeof(PRUnichar) {%lu} != sizeof(wchar_t) {%lu}!\n"
        "Probably, you forgot the -fshort-wchar compiler option.\n",
        (unsigned long)sizeof(PRUnichar), (unsigned long)sizeof(wchar_t));
    exit(1);
  }

  /*
   * This is the standard XPCOM init procedure.
   * What we do is just follow the required steps to get an instance
   * of our main interface, which is IVirtualBox.
   *
   * Note that we scope all nsCOMPtr variables in order to have all XPCOM
   * objects automatically released before we call NS_ShutdownXPCOM at the
   * end. This is an XPCOM requirement.
   */
  nsCOMPtr<nsIServiceManager> serviceManager;
  rc = NS_InitXPCOM2(getter_AddRefs(serviceManager), nsnull, nsnull);
  if (NS_FAILED(rc)) {
    printf("Error: XPCOM could not be initialized! rc=%#x\n", rc);
    exit(1);
  }

  /*
   * Make sure the main event queue is created. This event queue is
   * responsible for dispatching incoming XPCOM IPC messages. The main
   * thread should run this event queue's loop during lengthy non-XPCOM
   * operations to ensure messages from the VirtualBox server and other
   * XPCOM IPC clients are processed. This use case doesn't perform such
   * operations so it doesn't run the event loop.
   */
  nsCOMPtr<nsIEventQueue> eventQ;
  rc = NS_GetMainEventQ(getter_AddRefs(eventQ));
  if (NS_FAILED(rc)) {
    printf("Error: NS_GetMainEventQ(): rc=%#x\n", rc);
    exit(1);
  }

  /*
   * Now XPCOM is ready and we can start to do real work.
   * IVirtualBox is the root interface of VirtualBox and will be
   * retrieved from the XPCOM component manager. We use the
   * XPCOM provided smart pointer nsCOMPtr for all objects because
   * that's very convenient and removes the need deal with reference
   * counting and freeing.
   */
  nsCOMPtr<nsIComponentManager> manager;
  rc = NS_GetComponentManager(getter_AddRefs(manager));
  if (NS_FAILED(rc)) {
    printf("Error: NS_GetComponentManager(): rc=%#x\n", rc);
    exit(1);
  }

  nsCOMPtr<IVirtualBox> virtualBox;
  rc = manager->CreateInstanceByContractID(
      NS_VIRTUALBOX_CONTRACTID, nsnull, NS_GET_IID(IVirtualBox),
      getter_AddRefs(virtualBox));
  if (NS_FAILED(rc)) {
    printf("Error: CreateInstanceByContractID(): rc=%#x\n", rc);
    exit(1);
  }

  return virtualBox;
}

void releaseVirtualBoxInterface(nsCOMPtr<IVirtualBox> virtualBox)
{
  nsresult rc;

  // Smart pointer magic
  virtualBox = nsnull;

  nsCOMPtr<nsIEventQueue> eventQ;
  rc = NS_GetMainEventQ(getter_AddRefs(eventQ));
  if (NS_FAILED(rc)) {
    printf("Error: NS_GetMainEventQ(): rc=%#x\n", rc);
    exit(1);
  }

  /*
   * Process events that might have queued up in the XPCOM event
   * queue. If we don't process them, the server might hang.
   */
  eventQ->ProcessPendingEvents();

  /*
   * Perform the standard XPCOM shutdown procedure.
   */
  NS_ShutdownXPCOM(nsnull);
}

nsCOMPtr<IKeyboard> createKeyboard(nsCOMPtr<IVirtualBox> virtualBox,
                                   const PRUnichar* vbox_guest)
{
  nsresult rc;

//  const nsAFlatString& q = L"test";

  nsCOMPtr<IMachine> machine;
  rc = virtualBox->FindMachine(
//    NS_LITERAL_STRING("test").get(), getter_AddRefs(machine));
    vbox_guest, getter_AddRefs(machine));
  if (NS_FAILED(rc)) {
    printf("Error: FindMachine(): rc=%#x\n", rc);
    exit(1);
  }

  nsCOMPtr<nsIComponentManager> manager;
  rc = NS_GetComponentManager(getter_AddRefs(manager));
  if (NS_FAILED(rc)) {
    printf("Error: NS_GetComponentManager(): rc=%#x\n", rc);
    exit(1);
  }

  nsCOMPtr<ISession> session;
  rc = manager->CreateInstanceByContractID(
      NS_SESSION_CONTRACTID, nsnull, NS_GET_IID(ISession),
      getter_AddRefs(session));
  if (NS_FAILED(rc)) {
    printf("Error: CreateInstanceByContractID(): rc=%#x\n", rc);
    exit(1);
  }

  rc = machine->LockMachine(session, LockType_Shared);
  if (NS_FAILED(rc)) {
    printf("Error: LockMachine(): rc=%#x\n", rc);
    exit(1);
  }

  nsCOMPtr<IMachine> sessionMachine;
  rc = session->GetMachine(getter_AddRefs(sessionMachine));
  if (NS_FAILED(rc)) {
    printf("Error: GetMachine(): rc=%#x\n", rc);
    exit(1);
  }

  nsCOMPtr<IConsole> console;
  rc = session->GetConsole(getter_AddRefs(console));
  if (NS_FAILED(rc)) {
    printf("Error: GetConsole(): rc=%#x\n", rc);
    exit(1);
  }

  nsCOMPtr<IKeyboard> keyboard;
  rc = console->GetKeyboard(getter_AddRefs(keyboard));
  if (NS_FAILED(rc)) {
    printf("Error: GetKeyboard(): rc=%#x\n", rc);
    exit(1);
  }

  return keyboard;
}

void releaseKeys(nsCOMPtr<IKeyboard> keyboard)
{
  nsresult rc = keyboard->ReleaseKeys();
  if (NS_FAILED(rc)) {
    printf("Error: ReleaseKeys(): rc=%#x\n", rc);
    exit(1);
  }
}

void sendKeyScanCode(nsCOMPtr<IKeyboard> keyboard, int scancode)
{
  nsresult rc = keyboard->PutScancode(scancode);
  if (NS_FAILED(rc)) {
    printf("Error: PutScancode(): rc=%#x\n", rc);
    exit(1);
  }
}

//void sendKeyScanCodeArr(nsCOMPtr<IKeyboard> keyboard, int* scancode)
//{
//  nsresult rc = keyboard->PutScancodes(scancode);
//  if (NS_FAILED(rc)) {
//    printf("Error: PutScancode(): rc=%#x\n", rc);
//    exit(1);
//  }
//}

/**
 * Helper function to convert an nsID into a human readable string
 *
 * @returns result string, allocated. Has to be freed using free()
 * @param   guid Pointer to nsID that will be converted.
 */
char* nsIDToString(nsID* guid)
{
  char* res = (char*)malloc(39);

  if (res != NULL) {
    snprintf(
        res, 39, "{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}", guid->m0,
        (PRUint32)guid->m1, (PRUint32)guid->m2, (PRUint32)guid->m3[0],
        (PRUint32)guid->m3[1], (PRUint32)guid->m3[2], (PRUint32)guid->m3[3],
        (PRUint32)guid->m3[4], (PRUint32)guid->m3[5], (PRUint32)guid->m3[6],
        (PRUint32)guid->m3[7]);
  }
  return res;
}

/**
 * Helper function to print XPCOM exception information set on the current
 * thread after a failed XPCOM method call. This function will also print
 * extended VirtualBox error info if it is available.
 */
void printErrorInfo()
{
  nsresult rc;

  nsCOMPtr<nsIExceptionService> es;
  es = do_GetService(NS_EXCEPTIONSERVICE_CONTRACTID, &rc);
  if (NS_SUCCEEDED(rc)) {
    nsCOMPtr<nsIExceptionManager> em;
    rc = es->GetCurrentExceptionManager(getter_AddRefs(em));
    if (NS_SUCCEEDED(rc)) {
      nsCOMPtr<nsIException> ex;
      rc = em->GetCurrentException(getter_AddRefs(ex));
      if (NS_SUCCEEDED(rc) && ex) {
        nsCOMPtr<IVirtualBoxErrorInfo> info;
        info = do_QueryInterface(ex, &rc);
        if (NS_SUCCEEDED(rc) && info) {
          /* got extended error info */
          printf("Extended error info (IVirtualBoxErrorInfo):\n");
          PRInt32 resultCode = NS_OK;
          info->GetResultCode(&resultCode);
          printf("  resultCode=%08X\n", resultCode);
          nsXPIDLString component;
          info->GetComponent(getter_Copies(component));
          printf("  component=%s\n", NS_ConvertUTF16toUTF8(component).get());
          nsXPIDLString text;
          info->GetText(getter_Copies(text));
          printf("  text=%s\n", NS_ConvertUTF16toUTF8(text).get());
        }
        else {
          /* got basic error info */
          printf("Basic error info (nsIException):\n");
          nsresult resultCode = NS_OK;
          ex->GetResult(&resultCode);
          printf("  resultCode=%08X\n", resultCode);
          nsXPIDLCString message;
          ex->GetMessage(getter_Copies(message));
          printf("  message=%s\n", message.get());
        }

        /* reset the exception to NULL to indicate we've processed it */
        em->SetCurrentException(NULL);

        rc = NS_OK;
      }
    }
  }
}
