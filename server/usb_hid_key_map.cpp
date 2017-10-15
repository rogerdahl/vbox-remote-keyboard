// Key Name, HID Usage, Page HID, Usage ID, PS/2 Set 1 Make, PS/2 Set 1 Break,
// PS/2 Set 2 Make }, PS/2 Set 2 Break

#include "usb_hid_key_map.h"

#include <complex>
#include <map>
#include <string>


std::vector <UsbHidKeyMap> usbHidKeyMapVec{
  {{0x01, 0x81}, {0, 0xE0, 0x5E}, {0, 0xE0, 0xDE}, {0, 0xE0, 0x37},
    {0xE0, 0xF0, 0x37}}, // System Power
   {{0x01, 0x82}, {0, 0xE0, 0x5F}, {0, 0xE0, 0xDF}, {0, 0xE0, 0x3F},
    {0xE0, 0xF0, 0x3F}}, // System Sleep
   {{0x01, 0x81}, {0xE0, 0x5E}, {0xE0, 0xDE}, {0xE0, 0x37},
    {0xE0, 0xF0, 0x37}}, // System Power
   {{0x01, 0x82}, {0xE0, 0x5F}, {0xE0, 0xDF}, {0xE0, 0x3F},
    {0xE0, 0xF0, 0x3F}}, // System Sleep
   {{0x01, 0x83}, {0xE0, 0x63}, {0xE0, 0xE3}, {0xE0, 0x5E},
    {0xE0, 0xF0, 0x5E}}, // System Wake
   {{0x07, 0x04}, {0x1E}, {0x9E}, {0x1C}, {0xF0, 0x1C}}, // a A
   {{0x07, 0x05}, {0x30}, {0xB0}, {0x32}, {0xF0, 0x32}}, // b B
   {{0x07, 0x06}, {0x2E}, {0xAE}, {0x21}, {0xF0, 0x21}}, // c C
   {{0x07, 0x07}, {0x20}, {0xA0}, {0x23}, {0xF0, 0x23}}, // d D
   {{0x07, 0x08}, {0x12}, {0x92}, {0x24}, {0xF0, 0x24}}, // e E
   {{0x07, 0x09}, {0x21}, {0xA1}, {0x2B}, {0xF0, 0x2B}}, // f F
   {{0x07, 0x0A}, {0x22}, {0xA2}, {0x34}, {0xF0, 0x34}}, // g G
   {{0x07, 0x0B}, {0x23}, {0xA3}, {0x33}, {0xF0, 0x33}}, // h H
   {{0x07, 0x0C}, {0x17}, {0x97}, {0x43}, {0xF0, 0x43}}, // i I
   {{0x07, 0x0D}, {0x24}, {0xA4}, {0x3B}, {0xF0, 0x3B}}, // j J
   {{0x07, 0x0E}, {0x25}, {0xA5}, {0x42}, {0xF0, 0x42}}, // k K
   {{0x07, 0x0F}, {0x26}, {0xA6}, {0x4B}, {0xF0, 0x4B}}, // l L
   {{0x07, 0x10}, {0x32}, {0xB2}, {0x3A}, {0xF0, 0x3A}}, // m M
   {{0x07, 0x11}, {0x31}, {0xB1}, {0x31}, {0xF0, 0x31}}, // n N
   {{0x07, 0x12}, {0x18}, {0x98}, {0x44}, {0xF0, 0x44}}, // o O
   {{0x07, 0x13}, {0x19}, {0x99}, {0x4D}, {0xF0, 0x4D}}, // p P
   {{0x07, 0x14}, {0x10}, {0x90}, {0x15}, {0xF0, 0x15}}, // q Q
   {{0x07, 0x15}, {0x13}, {0x93}, {0x2D}, {0xF0, 0x2D}}, // r R
   {{0x07, 0x16}, {0x1F}, {0x9F}, {0x1B}, {0xF0, 0x1B}}, // s S
   {{0x07, 0x17}, {0x14}, {0x94}, {0x2C}, {0xF0, 0x2C}}, // t T
   {{0x07, 0x18}, {0x16}, {0x96}, {0x3C}, {0xF0, 0x3C}}, // u U
   {{0x07, 0x19}, {0x2F}, {0xAF}, {0x2A}, {0xF0, 0x2A}}, // v V
   {{0x07, 0x1A}, {0x11}, {0x91}, {0x1D}, {0xF0, 0x1D}}, // w W
   {{0x07, 0x1B}, {0x2D}, {0xAD}, {0x22}, {0xF0, 0x22}}, // x X
   {{0x07, 0x1C}, {0x15}, {0x95}, {0x35}, {0xF0, 0x35}}, // y Y
   {{0x07, 0x1D}, {0x2C}, {0xAC}, {0x1A}, {0xF0, 0x1A}}, // z Z
   {{0x07, 0x1E}, {0x02}, {0x82}, {0x16}, {0xF0, 0x16}}, // 1 !
   {{0x07, 0x1F}, {0x03}, {0x83}, {0x1E}, {0xF0, 0x1E}}, // 2 @
   {{0x07, 0x20}, {0x04}, {0x84}, {0x26}, {0xF0, 0x26}}, // 3 #
   {{0x07, 0x21}, {0x05}, {0x85}, {0x25}, {0xF0, 0x25}}, // 4 $
   {{0x07, 0x22}, {0x06}, {0x86}, {0x2E}, {0xF0, 0x2E}}, // 5 %
   {{0x07, 0x23}, {0x07}, {0x87}, {0x36}, {0xF0, 0x36}}, // 6 ^
   {{0x07, 0x24}, {0x08}, {0x88}, {0x3D}, {0xF0, 0x3D}}, // 7 &
   {{0x07, 0x25}, {0x09}, {0x89}, {0x3E}, {0xF0, 0x3E}}, // 8 *
   {{0x07, 0x26}, {0x0A}, {0x8A}, {0x46}, {0xF0, 0x46}}, // 9 (
   {{0x07, 0x27}, {0x0B}, {0x8B}, {0x45}, {0xF0, 0x45}}, // 0 )
   {{0x07, 0x28}, {0x1C}, {0x9C}, {0x5A}, {0xF0, 0x5A}}, // Return
   {{0x07, 0x29}, {0x01}, {0x81}, {0x76}, {0xF0, 0x76}}, // Escape
   {{0x07, 0x2A}, {0x0E}, {0x8E}, {0x66}, {0xF0, 0x66}}, // Backspace
   {{0x07, 0x2B}, {0x0F}, {0x8F}, {0x0D}, {0xF0, 0x0D}}, // Tab
   {{0x07, 0x2C}, {0x39}, {0xB9}, {0x29}, {0xF0, 0x29}}, // Space
   {{0x07, 0x2D}, {0x0C}, {0x8C}, {0x4E}, {0xF0, 0x4E}}, // - _
   {{0x07, 0x2E}, {0x0D}, {0x8D}, {0x55}, {0xF0, 0x55}}, // = +
   {{0x07, 0x2F}, {0x1A}, {0x9A}, {0x54}, {0xF0, 0x54}}, // [ {
   {{0x07, 0x30}, {0x1B}, {0x9B}, {0x5B}, {0xF0, 0x5B}}, // ] }
   {{0x07, 0x31}, {0x2B}, {0xAB}, {0x5D}, {0xF0, 0x5D}}, // \ |
   {{0x07, 0x33}, {0x27}, {0xA7}, {0x4C}, {0xF0, 0x4C}}, // ; :
   {{0x07, 0x34}, {0x28}, {0xA8}, {0x52}, {0xF0, 0x52}}, // ' "
   {{0x07, 0x35}, {0x29}, {0xA9}, {0x0E}, {0xF0, 0x0E}}, // ` ~ <
   {{0x07, 0x36}, {0x33}, {0xB3}, {0x41}, {0xF0, 0x41}}, //
   {{0x07, 0x37}, {0x34}, {0xB4}, {0x49}, {0xF0, 0x49}}, // . >
   {{0x07, 0x38}, {0x35}, {0xB5}, {0x4A}, {0xF0, 0x4A}}, // / ?
   {{0x07, 0x39}, {0x3A}, {0xBA}, {0x58}, {0xF0, 0x58}}, // Caps Lock
   {{0x07, 0x3A}, {0x3B}, {0xBB}, {0x05}, {0xF0, 0x05}}, // F1
   {{0x07, 0x3B}, {0x3C}, {0xBC}, {0x06}, {0xF0, 0x06}}, // F2
   {{0x07, 0x3C}, {0x3D}, {0xBD}, {0x04}, {0xF0, 0x04}}, // F3
   {{0x07, 0x3D}, {0x3E}, {0xBE}, {0x0C}, {0xF0, 0x0C}}, // F4
   {{0x07, 0x3E}, {0x3F}, {0xBF}, {0x03}, {0xF0, 0x03}}, // F5
   {{0x07, 0x3F}, {0x40}, {0xC0}, {0x0B}, {0xF0, 0x0B}}, // F6
   {{0x07, 0x40}, {0x41}, {0xC1}, {0x83}, {0xF0, 0x83}}, // F7
   {{0x07, 0x41}, {0x42}, {0xC2}, {0x0A}, {0xF0, 0x0A}}, // F8
   {{0x07, 0x42}, {0x43}, {0xC3}, {0x01}, {0xF0, 0x01}}, // F9
   {{0x07, 0x43}, {0x44}, {0xC4}, {0x09}, {0xF0, 0x09}}, // F10
   {{0x07, 0x44}, {0x57}, {0xD7}, {0x78}, {0xF0, 0x78}}, // F11
   {{0x07, 0x45}, {0x58}, {0xD8}, {0x07}, {0xF0, 0x07}}, // F12
   {{0x07, 0x46}, {0xE0, 0x37}, {0xE0, 0xB7}, {0xE0, 0x7C},
    {0xE0, 0xF0, 0x7C}}, // Print Screen
   {{0x07, 0x47}, {0x46}, {0xC6}, {0x7E}, {0xF0, 0x7E}}, // Scroll Lock
   {{0x07, 0x48}, {0xE0, 0x46}, {0xE0, 0xC6}, {0xE0, 0x7E},
    {0xE0, 0xF0, 0x7E}}, // Break Pause
    // { { 0x07, 0x48 }, 0xE1, 0x1D, 0x45, 0xE1, 0x9D, 0xC5, 0xE1, 0x14, 0x77,
    // 0xE1, 0xF0, 0x14, 0xF0, 0x77, // Pause
   {{0x07, 0x49}, {0xE0, 0x52}, {0xE0, 0xD2}, {0xE0, 0x70},
    {0xE0, 0xF0, 0x70}}, // Insert
   {{0x07, 0x4A}, {0xE0, 0x47}, {0xE0, 0xC7}, {0xE0, 0x6C},
    {0xE0, 0xF0, 0x6C}}, // Home
   {{0x07, 0x4B}, {0xE0, 0x49}, {0xE0, 0xC9}, {0xE0, 0x7D},
    {0xE0, 0xF0, 0x7D}}, // Page Up
   {{0x07, 0x4C}, {0xE0, 0x53}, {0xE0, 0xD3}, {0xE0, 0x71},
    {0xE0, 0xF0, 0x71}}, // Delete
   {{0x07, 0x4D}, {0xE0, 0x4F}, {0xE0, 0xCF}, {0xE0, 0x69},
    {0xE0, 0xF0, 0x69}}, // End
   {{0x07, 0x4E}, {0xE0, 0x51}, {0xE0, 0xD1}, {0xE0, 0x7A},
    {0xE0, 0xF0, 0x7A}}, // Page Down
   {{0x07, 0x4F}, {0xE0, 0x4D}, {0xE0, 0xCD}, {0xE0, 0x74},
    {0xE0, 0xF0, 0x74}}, // Right Arrow
   {{0x07, 0x50}, {0xE0, 0x4B}, {0xE0, 0xCB}, {0xE0, 0x6B},
    {0xE0, 0xF0, 0x6B}}, // Left Arrow
   {{0x07, 0x51}, {0xE0, 0x50}, {0xE0, 0xD0}, {0xE0, 0x72},
    {0xE0, 0xF0, 0x72}}, // Down Arrow
   {{0x07, 0x52}, {0xE0, 0x48}, {0xE0, 0xC8}, {0xE0, 0x75},
    {0xE0, 0xF0, 0x75}}, // Up Arrow
   {{0x07, 0x53}, {0x45}, {0xC5}, {0x77}, {0xF0, 0x77}}, // Num Lock
   {{0x07, 0x54}, {0xE0, 0x35}, {0xE0, 0xB5}, {0xE0, 0x4A},
    {0xE0, 0xF0, 0x4A}}, // Keypad /
   {{0x07, 0x55}, {0x37}, {0xB7}, {0x7C}, {0xF0, 0x7C}}, // Keypad *
   {{0x07, 0x56}, {0x4A}, {0xCA}, {0x7B}, {0xF0, 0x7B}}, // Keypad -
   {{0x07, 0x57}, {0x4E}, {0xCE}, {0x79}, {0xF0, 0x79}}, // Keypad +
   {{0x07, 0x58}, {0xE0, 0x1C}, {0xE0, 0x9C}, {0xE0, 0x5A},
    {0xE0, 0xF0, 0x5A}}, // Keypad Enter
   {{0x07, 0x59}, {0x4F}, {0xCF}, {0x69}, {0xF0, 0x69}}, // Keypad 1 End
   {{0x07, 0x5A}, {0x50}, {0xD0}, {0x72}, {0xF0, 0x72}}, // Keypad 2 Down
   {{0x07, 0x5B}, {0x51}, {0xD1}, {0x7A}, {0xF0, 0x7A}}, // Keypad 3 PageDn
   {{0x07, 0x5C}, {0x4B}, {0xCB}, {0x6B}, {0xF0, 0x6B}}, // Keypad 4 Left
   {{0x07, 0x5D}, {0x4C}, {0xCC}, {0x73}, {0xF0, 0x73}}, // Keypad 5 Right
   {{0x07, 0x5E}, {0x4D}, {0xCD}, {0x74}, {0xF0, 0x74}}, // Keypad 6 Home
   {{0x07, 0x5F}, {0x47}, {0xC7}, {0x6C}, {0xF0, 0x6C}}, // Keypad 7 Up
   {{0x07, 0x60}, {0x48}, {0xC8}, {0x75}, {0xF0, 0x75}}, // Keypad 8 PageUp
   {{0x07, 0x61}, {0x49}, {0xC9}, {0x7D}, {0xF0, 0x7D}}, // Keypad 9 Insert
   {{0x07, 0x62}, {0x52}, {0xD2}, {0x70}, {0xF0, 0x70}}, // Keypad 0 Delete
   {{0x07, 0x63}, {0x53}, {0xD3}, {0x71}, {0xF0, 0x71}}, // Keypad .
   {{0x07, 0x65}, {0xE0, 0x5D}, {0xE0, 0xDD}, {0xE0, 0x2F}, {0xE0, 0xF0, 0x2F}}, // App
   {{0x07, 0x67}, {0x59}, {0xD9}, {0x0F}, {0xF0, 0x0F}}, // Keypad =
   {{0x07, 0x68}, {0x5D}, {0xDD}, {0x2F}, {0xF0, 0x2F}}, // F13
   {{0x07, 0x69}, {0x5E}, {0xDE}, {0x37}, {0xF0, 0x37}}, // F14
   {{0x07, 0x6A}, {0x5F}, {0xDF}, {0x3F}, {0xF0, 0x3F}}, // F15
   {{0x07, 0xE0}, {0x1D}, {0x9D}, {0x14}, {0xF0, 0x14}}, //  Left Control
   {{0x07, 0xE1}, {0x2A}, {0xAA}, {0x12}, {0xF0, 0x12}}, //  Left Shift
   {{0x07, 0xE2}, {0x38}, {0xB8}, {0x11}, {0xF0, 0x11}}, //  Left Alt
   {{0x07, 0xE3}, {0xE0, 0x5B }, { 0xE0, 0xDB }, { 0xE0, 0x1F }, { 0xE0, 0xF0, 0x1F}}, //  Left GUI
   {{0x07, 0xE4}, {0xE0, 0x1D }, { 0xE0, 0x9D }, { 0xE0, 0x14 }, { 0xE0, 0xF0, 0x14}}, //  Right Control
   {{0x07, 0xE5}, {0x36}, {0xB6}, {0x59}, {0xF0, 0x59}}, //  Right Shift
   {{0x07, 0xE6}, {0xE0, 0x38}, {0xE0, 0xB8}, {0xE0, 0x11}, {0xE0, 0xF0, 0x11}}, //  Right Alt
   {{0x07, 0xE7}, {0xE0, 0x5C}, {0xE0, 0xDC}, {0xE0, 0x27}, {0xE0, 0xF0, 0x27}}, //  Right GUI

//   {{0x0C, 0x00, 0xB6}, {0xE0, 0x10}, {0xE0, 0x90}, {0xE0, 0x15}, {0xE0, 0xF0, 0x15}}, //  Scan Previous Track
//   {{0x0C, 0x00, 0xB5}, {0xE0, 0x19}, {0xE0, 0x99}, {0xE0, 0x4D}, {0xE0, 0xF0, 0x4D}}, //  Scan Next Track
//   {{0x0C, 0x00, 0xB7}, {0xE0, 0x24}, {0xE0, 0xA4}, {0xE0, 0x3B}, {0xE0, 0xF0, 0x3B}}, //  Stop
//   {{0x0C, 0x00, 0xCD}, {0xE0, 0x22}, {0xE0, 0xA2}, {0xE0, 0x34}, {0xE0, 0xF0, 0x34}}, //  Play/ Pause
//   {{0x0C, 0x00, 0xE2}, {0xE0, 0x20}, {0xE0, 0xA0}, {0xE0, 0x23}, {0xE0, 0xF0, 0x23}}, //  Mute
//   {{0x0C, 0x00, 0xE9}, {0xE0, 0x30}, {0xE0, 0xB0}, {0xE0, 0x32}, {0xE0, 0xF0, 0x32}}, //  Volume Up
//   {{0x0C, 0x00, 0xEA}, {0xE0, 0x2E}, {0xE0, 0xAE}, {0xE0, 0x21}, {0xE0, 0xF0, 0x21}}, //  Volume Down
//   {{0x0C, 0x01, 0x83}, {0xE0, 0x6D}, {0xE0, 0xED}, {0xE0, 0x50}, {0xE0, 0xF0, 0x50}}, //  Media Select
//   {{0x0C, 0x01, 0x8A}, {0xE0, 0x6C}, {0xE0, 0xEC}, {0xE0, 0x48}, {0xE0, 0xF0, 0x48}}, //  Mail
//   {{0x0C, 0x01, 0x92}, {0xE0, 0x21}, {0xE0, 0xA1}, {0xE0, 0x2B}, {0xE0, 0xF0, 0x2B}}, //  Calculator
//   {{0x0C, 0x01, 0x94}, {0xE0, 0x6B}, {0xE0, 0xEB}, {0xE0, 0x40}, {0xE0, 0xF0, 0x40}}, //  My Computer
  };
