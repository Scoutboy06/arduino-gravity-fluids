#include "oled.h"

#include "globals.h"

void Oled::init(uint8_t switchvcc, uint8_t i2caddr) {
  m_svcc = switchvcc;
  m_i2caddr = i2caddr;

  // I2C Init
  Wire.setClock(400000);  // fast mode
  Wire.begin();

  // Init sequence
  writeCommand(SSD1306_CMD_DISPLAYOFF);          // 0xAE
  writeCommand(SSD1306_CMD_SETDISPLAYCLOCKDIV);  // 0xD5
  writeCommand(0x80);                            // the suggested ratio 0x80

  writeCommand(SSD1306_CMD_SETMULTIPLEX);  // 0xA8
  writeCommand(SCREEN_HEIGHT - 1);

  writeCommand(SSD1306_CMD_SETDISPLAYOFFSET);    // 0xD3
  writeCommand(0x0);                             // no offset
  writeCommand(SSD1306_CMD_SETSTARTLINE | 0x0);  // line #0
  writeCommand(SSD1306_CMD_CHARGEPUMP);          // 0x8D
  if (m_svcc == SSD1306_CMD_EXTERNALVCC)
    writeCommand(0x10);
  else
    writeCommand(0x14);
  writeCommand(SSD1306_CMD_MEMORYMODE);  // 0x20
  writeCommand(0x00);                    // 0x0 act like ks0108
  writeCommand(SSD1306_CMD_SEGREMAP | 0x1);
  writeCommand(SSD1306_CMD_COMSCANDEC);

  // 128x64
  writeCommand(SSD1306_CMD_SETCOMPINS);  // 0xDA
  writeCommand(0x12);
  writeCommand(SSD1306_CMD_SETCONTRAST);  // 0x81
  if (m_svcc == SSD1306_CMD_EXTERNALVCC)
    writeCommand(0x9F);
  else
    writeCommand(0xCF);

  writeCommand(SSD1306_CMD_SETPRECHARGE);  // 0xd9
  if (m_svcc == SSD1306_CMD_EXTERNALVCC)
    writeCommand(0x22);
  else
    writeCommand(0xF1);
  writeCommand(SSD1306_CMD_SETVCOMDETECT);  // 0xDB
  writeCommand(0x40);
  writeCommand(SSD1306_CMD_DISPLAYALLON_RESUME);  // 0xA4
  writeCommand(SSD1306_CMD_NORMALDISPLAY);        // 0xA6

  writeCommand(SSD1306_CMD_DEACTIVATE_SCROLL);

  writeCommand(SSD1306_CMD_DISPLAYON);  //--turn on oled panel

  // clear
  clear();
}

void Oled::writeCommand(uint8_t c) {
  Wire.beginTransmission(m_i2caddr);
  Wire.write(0x00);  // control
  Wire.write(c);
  Wire.endTransmission();
}

void Oled::setPos(uint8_t x, uint8_t y) {
  // set column
  writeCommand(SSD1306_CMD_COLUMNADDR);
  writeCommand(x);                 // Column start address (0 = reset)
  writeCommand(SCREEN_WIDTH - 1);  // Column end address (127 = reset)
  // set line
  writeCommand(SSD1306_CMD_PAGEADDR);
  writeCommand(y);                      // Page start address (0 = reset)
  writeCommand(SCREEN_HEIGHT / 8 - 1);  // Page end address
}

void Oled::draw(const uint8_t* bitmap) {
  setPos(0, 0);

  for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT / 8; i++) {
    Wire.beginTransmission(m_i2caddr);
    Wire.write(0x40);  // Write to GDDRAM
    Wire.write(bitmap[i]);
    Wire.endTransmission();
  }
}

void Oled::clear() {
  setPos(0, 0);

  for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT / 8; i++) {
    Wire.beginTransmission(m_i2caddr);
    Wire.write(0x40);
    Wire.write(0x0);
    Wire.endTransmission();
  }
}