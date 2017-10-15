#pragma once

#include <vector>

typedef unsigned char u8;

class HidUsageKey
{
public:
  u8 hidUsagePage;
  u8 hidUsageId;
};

class UsbHidKeyMap
{
public:
  HidUsageKey hidUsageKey;
  std::vector<u8> ps2Set1make;
  std::vector<u8> ps2Set1brk;
  std::vector<u8> ps2Set2make;
  std::vector<u8> ps2Set2brk;
};
