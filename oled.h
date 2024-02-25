#pragma once

#include <Arduino.h>
#include <Wire.h>

// define I2C address
#define SSD1306_ADDRESS 0x3C

// define colors
#define BLACK 0
#define WHITE 1
#define INVERSE 2
#define TRANSPARENT 0xff

// define level 1 commands
#define SSD1306_CMD_SETCONTRAST 0x81
#define SSD1306_CMD_DISPLAYALLON_RESUME 0xA4
#define SSD1306_CMD_DISPLAYALLON 0xA5
#define SSD1306_CMD_NORMALDISPLAY 0xA6
#define SSD1306_CMD_INVERTDISPLAY 0xA7
#define SSD1306_CMD_DISPLAYOFF 0xAE
#define SSD1306_CMD_DISPLAYON 0xAF

#define SSD1306_CMD_SETDISPLAYOFFSET 0xD3
#define SSD1306_CMD_SETCOMPINS 0xDA

#define SSD1306_CMD_SETVCOMDETECT 0xDB

#define SSD1306_CMD_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_CMD_SETPRECHARGE 0xD9

#define SSD1306_CMD_SETMULTIPLEX 0xA8

#define SSD1306_CMD_SETLOWCOLUMN 0x00
#define SSD1306_CMD_SETHIGHCOLUMN 0x10

#define SSD1306_CMD_SETSTARTLINE 0x40

#define SSD1306_CMD_MEMORYMODE 0x20
#define SSD1306_CMD_COLUMNADDR 0x21
#define SSD1306_CMD_PAGEADDR 0x22

#define SSD1306_CMD_COMSCANINC 0xC0
#define SSD1306_CMD_COMSCANDEC 0xC8

#define SSD1306_CMD_SEGREMAP 0xA0

#define SSD1306_CMD_CHARGEPUMP 0x8D

#define SSD1306_CMD_EXTERNALVCC 0x1
#define SSD1306_CMD_SWITCHCAPVCC 0x2

// level 2
#define SSD1306_CMD_ACTIVATE_SCROLL 0x2F
#define SSD1306_CMD_DEACTIVATE_SCROLL 0x2E

class Oled {
  uint8_t m_svcc;
  uint8_t m_i2caddr;

 private:
  void writeCommand(uint8_t c);
  void setPos(uint8_t x, uint8_t y);

 public:
  void init(uint8_t switchvcc = SSD1306_CMD_SWITCHCAPVCC,
            uint8_t i2caddr = SSD1306_ADDRESS);
  void draw(const uint8_t* bitmap);
  void clear();
};