#pragma once

#include <nsEventQueueUtils.h>
#include <nsIServiceManager.h>
#include <nsMemory.h>
#include <nsString.h>
#include <nsIExceptionService.h>
/*
 * VirtualBox XPCOM interface. This header is generated
 * from IDL which in turn is generated from a custom XML format.
 */
#include "VirtualBox_XPCOM.h"

nsCOMPtr<IVirtualBox> createVirtualBoxInterface();
void releaseVirtualBoxInterface(nsCOMPtr<IVirtualBox> virtualBox);

nsCOMPtr<IKeyboard> createKeyboard(nsCOMPtr<IVirtualBox> virtualBox,
                                   const PRUnichar* vbox_guest);
void releaseKeys(nsCOMPtr<IKeyboard> keyboard);

void sendKeyScanCode(nsCOMPtr<IKeyboard>, int scancode);
