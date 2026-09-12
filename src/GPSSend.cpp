#define WIFI_LAN
#define GPS_LIB

#if defined(WIFI_LAN)

#include "cfg.h"
#include "wifi.h"

#else

// #include "esp_netif.h"
//
// #include <WiFi.h>
// #include <AsyncTCP.h>

#endif	/* WIFI_LAN */

#define USE_U8X8

#if defined(RTK_RECV)
#endif	/* USE_U8X8 */

#include "esp_timer.h"

#if defined(USE_U8X8)
#include <U8x8lib.h>
#include <Wire.h>
#endif	/* USE_U8X8 */

#define GPS_LIB

#if !defined(GPS_LIB)
#define DBG_PRT
#if defined(DBG_PRT)
int prt;
#endif
#endif

#include "dbgPin.h"
#include "gpsLib.h"

#if defined(USE_U8X8)

U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset */ U8X8_PIN_NONE); // GPIO 8 SDA, GPIO 9 SCL

void initDisplay();
void newScreen(const char* title);
size_t drawNumber(char x, char y, int val);
size_t drawNumber(char x, char y, unsigned long val);
size_t drawString(char x, char y, const char *str);
size_t drawFloat(char x, char y, float floatNumber, uint8_t dp);
void clearLine(char line);
void erase(char x, char y, char len);

#endif	/* USE_U8X8 */

void setup()
{
 buildCRC24qTable();

 Serial.begin(115200);
 printf("starting\n");

#if defined(USE_U8X8)
 initDisplay();
#endif	/* USE_U8X8 */

 Serial2.setRxBufferSize(1024);
// Serial2.begin(115200, SERIAL_8N1, 18, 17); // 18 rxPin, 17 txPin
 Serial2.begin(115200, SERIAL_8N1, 2, 1); // 2 rxPin, 1 txPin
 printf("UART2 initialized\n");
 Serial2.printf("started\n\r");

 dbgInit();

 wifiInit();
  
#if defined(USE_U8X8)
 drawString(0, 0, ipAddress);
 char tmp[2];
 tmp[0] = HOST_NAME[0];
 tmp[1] = 0;
 drawString(15, 0, tmp);
#endif	/* USE_U8X8 */

 wifiConnect();

 rtk.state = RCV_IDLE;
 rtk.t0 = millis();

#if defined(DBG_PRT)
 prt = 0;
#endif	/* DBG_PRT */

 printf("exit setup\n");
}

void loop()
{
 static unsigned int tmr0;
 unsigned int t0 = millis();
 if ((t0 - tmr0) > 1000)
 {
  tmr0 = t0;

  const signed char rssi = wifiRSSI();
  const float temp = temperatureRead();

#if defined(USE_U8X8)
  char buf[20];
  snprintf(buf, sizeof(buf), "%3d %4.1f %4d ", rssi, temp, rtk.rxCount);
  drawString(0, 1, buf);
#endif	/* USE_U8X8 */

#if defined(RTK_SEND)

  if (!connected)
  {
   if ((millis() - connectTmr) > 5000)
   {
    printf("try to reconnect\n");
    connectTmr = t0;
    connectToServer();
   }
  }

#endif	/* RTK_SEND */
 }

 pollSerial();
 processSerial();

#if defined(USE_U8X8)
 if (gpsInfo.update)
 {
  gpsInfo.update = false;
  char buf[20];
  drawString(0, 2, gpsInfo.timeBuf);
  snprintf(buf, sizeof(buf), "%d %2d   ", gpsInfo.fix, gpsInfo.sats);
  drawString(9, 2, buf);  // 9 10 11 12 13 14 15

  snprintf(buf, sizeof(buf), " %13.10f", gpsInfo.lat);
  drawString(0, 3, buf);
  snprintf(buf, sizeof(buf), "%14.10f", gpsInfo.lon);
  drawString(0, 4, buf);
 }
#endif	/* USE_U8X8 */
}

#if defined(USE_U8X8)

size_t drawString(char x, char y, const char *str)
{
 u8x8.drawString(x, y, str);
#if 0
 printf("x ");
 printf(static_cast<int>(x));
 printf(" y ");
 printf(static_cast<int>(y));
 printf(" \"");
 printf(str);
 printfln("\"");
#endif
 return strlen(str);
}

void newScreen(const char* title)
{
#if 0
 printf("newScreen ");
 printf(title);
 printf("\n");
#endif
 u8x8.clear();
 drawString(0, 0, title);
}

void clearLine(char line)
{
 drawString(0, line, "                ");
#if 0
 printf("clearLine %d", static_cast<int>(line));
#endif
}

void erase(char x, char y, char len)
{
 while (len != 0)
 {
  u8x8.drawString(x, y, " ");
  y += 1;
  len -= 1;
 }
}

size_t drawNumber(char x, char y, int val)
{
 char buf[6];
 itoa(val, buf, 10);
 drawString(x, y, buf);
#if 0
 printf(val);
 printf("\n");
#endif
 return strlen(buf);
}

size_t drawNumber(char x, char y, unsigned long val)
{
 char buf[12];
 ltoa(static_cast<long>(val), buf, 10);
 drawString(x, y, buf);
#if 0
 printf(val);
 printf("\n");
#endif
 return strlen(buf);
}

/***************************************************************************************
** Function name:           drawFloat
** Descriptions:            drawFloat, prints 7 non-zero digits maximum
***************************************************************************************/
// from https://github.com/Bodmer/TFT_ST7735
// Adapted to assemble and print a string, this permits alignment relative to a datum
// looks complicated but much more compact and actually faster than using print class

size_t drawFloat(char x, char y, float floatNumber, uint8_t dp)
{
  char str[14];               // Array to contain decimal string
  uint8_t ptr = 0;            // Initialize pointer for array
  uint8_t  digits = 1;        // Count the digits to avoid array overflow
  float rounding = 0.5;       // Round up down delta

  if (dp > 7)
   dp = 7;			// Limit the size of decimal portion

  // Adjust the rounding value
  for (uint8_t i = 0; i < dp; ++i) rounding /= 10.0;

  if (floatNumber < -rounding)    // add sign, avoid adding - sign to 0.0!
  {
    str[ptr++] = '-';	    // Negative number
    str[ptr] = 0;	    // Put a null in the array as a precaution
    digits = 0;		    // Set digits to 0 to compensate so pointer value can be used later
    floatNumber = -floatNumber; // Make positive
  }

  floatNumber += rounding; // Round up or down

  // For error put ... in string and return (all TFT_ST7735 library fonts contain . character)
  if (floatNumber >= static_cast<float>(2147483647)) {
    strcpy(str, "...");
    return drawString(x, y, str);
  }
  // No chance of overflow from here on

  // Get integer part
  auto temp = static_cast<unsigned long>(floatNumber);

  // Put integer part into array
  ltoa(static_cast<long>(temp), str + ptr, 10);

  // Find out where the null is to get the digit count loaded
  while (static_cast<uint8_t>(str[ptr]) != 0) ptr++; // Move the pointer along
  digits += ptr;                  // Count the digits

  str[ptr++] = '.'; // Add decimal point
  str[ptr] = '0';   // Add a dummy zero
  str[ptr + 1] = 0; // Add a null but don't increment pointer so it can be overwritten

  // Get the decimal portion
  floatNumber = floatNumber - static_cast<float>(temp);

  // Get decimal digits one by one and put in array
  // Limit digit count so we don't get a false sense of resolution
  uint8_t i = 0;
  while ((i < dp) && (digits < 9)) // while (i < dp) for no limit but array size must be increased
  {
    i++;
    floatNumber *= 10;       // for the next decimal
    temp = static_cast<unsigned long>(floatNumber);      // get the decimal
    ltoa(static_cast<long>(temp), str + ptr, 10);
    ptr++;
    digits++;         // Increment pointer and digits count
    floatNumber -= static_cast<float>(temp);     // Remove that digit
  }
  
  // Finally we can plot the string and return pixel length
  return drawString(x, y, str);
}

void initDisplay()
{
 Wire.setPins(8, 9);		// Set SDA to GPIO 8, SCL to GPIO 9
 u8x8.begin();

 u8x8.setFont(u8x8_font_chroma48medium8_r);
 drawString(0, 0, "Starting");
}

#endif	/* USE_U8X8 */
