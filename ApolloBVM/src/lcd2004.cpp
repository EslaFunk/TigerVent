#include "Arduino.h"
#include "lcd2004.h"

Lcd2004::Lcd2004(byte pin) :

                             _row(0),
                             _col(0)
{
  _lcd = new LiquidCrystal(8, 9, 10, 0, 12, 13);
  //_serial_ptr = new SoftwareSerial(2, pin);
}

void Lcd2004::begin(int baud)
{
  //_serial_ptr->begin(9600);
  //_lcd = new LiquidCrystal(8, 9, 10, 0, 12, 13);
  _lcd->begin(20, 4);
}

void Lcd2004::print(String st)
{
  //_serial_ptr->print(st);
  _lcd->print(st);
}

void Lcd2004::print(int val)
{
  _lcd->print(String(val));
  //_serial_ptr->print(String(val));
}

void Lcd2004::println(String st)
{
  //_serial_ptr->println(st);
  _lcd->print(st);
}

void Lcd2004::setBacklight(byte brightness)
{
  //_serial_ptr->write(0xFE);  // send the special command
  //_serial_ptr->write(0x53);  // send the backlight command
  //_serial_ptr->write(brightness);  // send the brightness value
}

void Lcd2004::clearDisplay()
{
  //_serial_ptr->write(0xFE);  // send the special command
  //_serial_ptr->write(0x51);  // send the clear screen command
  _lcd->clear();
}

void Lcd2004::setCursor(byte cursor_position, byte line)
{
  _lcd->setCursor(cursor_position, line);
  _row = line;
  _col = cursor_position;
}

void Lcd2004::underlineOn()
{
}

void Lcd2004::underlineOff()
{
}

void Lcd2004::blinkingOn()
{
  _lcd->blink(); // send the clear screen command
}

void Lcd2004::blinkingOff()
{
  _lcd->noBlink();
}

void Lcd2004::moveCursorRight()
{
  if (_col % 19 == 0 && _row % 3 == 0)
  {
    _col = _row = 0;
  }
  else if (_col % 20 == 0)
  {
    _row++;
    _col = 0;
  }
  else
  {
    _col++;
  }
  _lcd->setCursor(_col, _row);
}

void Lcd2004::moveCursorLeft()
{
  if (_col == _row == 0)
  {
    _col = 19;
    _row = 3;
  }
  else if (_col == 0)
  {
    _row--;
    _col = 19;
  }
  else
  {
    _col++;
  }
  _lcd->setCursor(_col, _row); // send the clear screen command
}

void Lcd2004::backspace()
{
  _lcd->write(" ");
  this->moveCursorLeft();
}

void Lcd2004::remove()
{
  _lcd->write(" ");
  _lcd->setCursor(_row, _col);
}

String Lcd2004::zeroPad(int in)
{
  char digit[2];
  sprintf(digit, "%02d", in);
  return String(digit);
}
