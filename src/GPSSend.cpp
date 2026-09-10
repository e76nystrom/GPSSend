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
//#include <ESPAsyncWebServer.h>
#endif	/* USE_U8X8 */

#include "esp_timer.h"

#if defined(USE_U8X8)
#include <U8x8lib.h>
#include <Wire.h>
#endif	/* USE_U8X8 */

#if !defined(WIFI_LAN)

// const char* ssid = "router0";
// const char* password = "candle14salt";
//
// #if defined(RTK_SEND)
// AsyncClient* client = nullptr;
// #endif	/* RTK_SEND */
//
// constexpr int port = 8088;

#endif  /* WIFI_LAN */

#define GPS_LIB

#if !defined(GPS_LIB)
#define DBG_PRT
#if defined(DBG_PRT)
int prt;
#endif
#endif

#if !defined(WIFI_LAN)

// #if defined(RTK_SEND)
// // const char* serverIP = "192.168.0.237";
// constexpr char CLIENT_NAME[] = "cli2";
// #define HOST_NAME CLIENT_NAME
// #endif	/* RTK_SEND */
//
// constexpr char SERVER_NAME[] = "srv2";
//
// #if defined(RTK_RECV)
// AsyncServer server(port);
// #define HOST_NAME SERVER_NAME
// #endif	/* RTK_RECV */
//
// char ipAddress[20];

#endif	/* WIFI_LAN */

#include "dbgPin.h"

#if defined(GPS_LIB)

#include "gpsLib.h"

#else
//
// enum RCV_STATE {RCV_IDLE, RCV_GET_LEN, RCV_GET_DATA, RCV_TEXT};
//
// typedef struct S_RTK_DATA
// {
//  RCV_STATE state;
//  unsigned int t0;
//  uint64_t startTime;
//  uint32_t crc;
//  int count;
//  int len;
//  int fil;
//  char buf[1024];
//  unsigned int t0Accum;
//  int rxAccum;
//  int rxCount;
//  int numSv;
//  unsigned int svTmr;
//  int svCount[4];
// } T_RTK_DATA, *P_RTK_DATA;
//
// #define MAX_SIG 4
// #define MAX_SAT 100
//
// typedef struct S_FREQ_INFO
// {
//  char freq;
//  char cno;
// } T_FREQ_INFO, *P_FREQ_INFO;
//
// typedef struct S_SAT_DATA
// {
//  char cons;
//  char sVid;
//  char elv;
//  char az;
//  char freqs;
//  T_FREQ_INFO sig[MAX_SIG];
// } T_SAT_DATA, *P_SAT_DATA;
//
// T_RTK_DATA rtk;
//
// S_SAT_DATA satData[MAX_SAT];
// int satIndex;
//
// char cons[5] = "PLBA";
// const char *names[] = {"GPS", "GLO", "BDS", "GAL"};
//
// #if defined(RTK_SEND)
// bool sendBinary(const uint8_t *data, size_t len);
// #endif	/* RTK_SEND */

#endif	/* NO_GPS_LIB */

#if !defined(GPS_LIB)
//
// inline void dbg0Set()
// {
//  REG_WRITE(GPIO_OUT_W1TS_REG, (1 << DBG0_PIN));
// }
//
// inline void dbg0Clr()
// {
//  REG_WRITE(GPIO_OUT_W1TC_REG, (1 << DBG0_PIN));
// }
//
// inline void dbg1Set()
// {
//  REG_WRITE(GPIO_OUT_W1TS_REG, (1 << DBG1_PIN));
// }
//
// inline void dbg1Clr()
// {
//  REG_WRITE(GPIO_OUT_W1TC_REG, (1 << DBG1_PIN));
// }
//
// void printHex(const uint8_t *data, size_t len);
//
// char *nextArg(char* p0);
// char *getNum(char *p0, int n, int *result);
// int getNum(char **p0, int n);
// int getNum(char **p0);
// int getHex(char **p0);
//
// void buildCRC24qTable();
// inline uint32_t crc24(uint32_t crc, unsigned char c);
// uint32_t crc24qTable[256];
//
// void processRemData(void *data, size_t len);
// void processSerial();
// void gpsLoc();
// void gpsSat();

#endif	/* GPS_LIB */

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

#if !defined(WIFI_LAN)
//
// bool connected;
// unsigned int connectTmr;
//
// // ── Send state tracking ───────────────────────────────────────────────────────
// struct SendContext
// {
//  size_t   bytesSent;
//  uint32_t timestamp;   // millis() at send time
// };
//
// static SendContext lastSend = { 0, 0 };
//
// void onConnect(void *arg, AsyncClient *c)
// {
//  printf("[TCP] Connected to server\n");
//  IPAddress ip = c->remoteIP();
//  Serial.printf("Connected to %s at %s\n", SERVER_NAME, ip.toString().c_str());
//  c->write("Hello from ESP32-S3\n");
//  connected = true;
//  connectTmr = 0;
// }
//
// #if defined(RTK_SEND)
//
// void onData(void *arg, AsyncClient *c, void *data, size_t len)
// {
//  printf("[TCP] Received %u bytes: ", len);
// }
//
// void onAck(void* arg, AsyncClient* c, size_t len, uint32_t time)
// {
//  printf("[TCP] ACK: %u bytes acknowledged, round-trip ~%u ms\n",
//                len, static_cast<unsigned int>(millis() - lastSend.timestamp));
//
//  lastSend.bytesSent -= len;  // track how many bytes are still unacknowledged
//
//  if (lastSend.bytesSent == 0)
//  {
//   printf("[TCP] Send complete: all bytes acknowledged\n");
//  }
// }
//
// void onDisconnect(void *arg, AsyncClient *c)
// {
//  printf("[TCP] Disconnected\n");
//  c->close();
//  client = nullptr;
//
//  connected = false;
//  connectTmr = millis();
// }
//
// void onError(void *arg, AsyncClient *c, int8_t error)
// {
//  printf("[TCP] Error: %s\n", AsyncClient::errorToString(error));
//  c->close();
//  client = nullptr;
// }
//
// void onTimeout(void *arg, AsyncClient *c, uint32_t time)
// {
//  printf("[TCP] Timeout at %u ms, disconnecting\n", static_cast<unsigned int>(time));
//  c->close();
//  client = nullptr;
// }
//
// // ── Connection helper ────────────────────────────────────────────────────────
//
// void connectToServer()
// {
//  if (client)
//   return;			// already alive
//
//  connectTmr = millis();
//
//  client = new AsyncClient();
//  client->onConnect   (onConnect,    nullptr);
//  client->onData      (onData,       nullptr);
//  client->onAck       (onAck,        nullptr);
//  client->onDisconnect(onDisconnect, nullptr);
//  client->onError     (onError,      nullptr);
//  client->onTimeout   (onTimeout,    nullptr);
//  client->setRxTimeout(10);	// seconds before timeout fires
//
//  printf("[TCP] Connecting to %s:%d\n", SERVER_NAME, port);
//  if (!client->connect(SERVER_NAME, port))
//  {
//   printf("[TCP] connect() failed immediately\n");
//   delete client;
//   client = nullptr;
//  }
// }
//
// // ── Send binary data ──────────────────────────────────────────────────────────
//
// bool sendBinary(const uint8_t *data, size_t len)
// {
//  if (!connected)
//  {
//   printf("[TCP] Cannot send: not connected 1\n");
//   return false;
//  }
//
//  if (!client || !client->connected())
//  {
//   printf("[TCP] Cannot send: not connected 2\n");
//   return false;
//  }
//
//  if (!client->canSend())
//  {
//   printf("[TCP] Cannot send: TX buffer full\n");
//   return false;
//  }
//
//  size_t available = client->space();
//  if (available < len)
//  {
//   printf("[TCP] Cannot send: need %u bytes, only %u available in TX buffer\n", len, available);
//   return false;
//  }
//
//  size_t written = client->write(reinterpret_cast<const char *>(data), len);
//  if (written != len)
//  {
//   printf("[TCP] Partial write: sent %u of %u bytes\n", written, len);
//   return false;
//  }
//
//  printf("[TCP] Sent %u bytes\n", written);
//  lastSend.timestamp = millis();
//  return true;
// }
//
// #endif	/* RTK_SEND */
//
// #if defined(RTK_RECV)
//
// static void onClientData(void *arg, AsyncClient *c,
//                          void *data, size_t len)
// {
//  printf("[%s:%u] Received %u byte(s):\n",
//         c->remoteIP().toString().c_str(),
//         c->remotePort(), static_cast<unsigned int>(len));
//
//  processRemData(data, len);
// }
//
// static void onClientError(void *arg, AsyncClient *c, int8_t error)
// {
//  printf("[%s:%u] Error: %s\n",
//         c->remoteIP().toString().c_str(),
//         c->remotePort(),
//         AsyncClient::errorToString(error));
// }
//
// static void onClientTimeout(void *arg, AsyncClient *c, uint32_t time)
// {
//  printf("[%s:%u] Timeout (ACK not received within %u ms)\n",
//         c->remoteIP().toString().c_str(),
//         c->remotePort(), static_cast<unsigned int>(time));
//  c->close();
// }
//
// static void onClientDisconnect(void *arg, AsyncClient *c)
// {
//  printf("[%s:%u] Disconnected\n",
//         c->remoteIP().toString().c_str(),
//         c->remotePort());
//  // AsyncTCP frees the client object after this callback returns.
// }
//
// // ─── New connection callback ──────────────────────────────────────────────────
//
// static void onNewClient(void* arg, AsyncClient* c)
// {
//  Serial.printf("\n[SERVER] New connection from %s:%u\n",
// 	       c->remoteIP().toString().c_str(),
// 	       c->remotePort());
//
//  // Wire up per-c callbacks
//  c->onData    (onClientData,       nullptr);
//  c->onError   (onClientError,      nullptr);
//  c->onTimeout (onClientTimeout,    nullptr);
//  c->onDisconnect(onClientDisconnect, nullptr);
//
//  // Optional: set a 5-second ACK timeout
//  c->setAckTimeout(5000);
//
//  // Optional: send a greeting frame to the client
//  const uint8_t greeting[] = { 0x48, 0x65, 0x6C, 0x6C, 0x6F }; // "Hello"
//  c->write(reinterpret_cast<const char *>(greeting), sizeof(greeting));
// }
//
// #endif	/* RTK_RECV */

#endif	/* WIFI_LAN */

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

#if defined(WIFI_LAN)

 wifiInit();

#else
 //
 // WiFiClass::mode(WIFI_STA);
 // WiFiClass::setHostname(HOST_NAME);
 //
 // Serial.printf("Attempting to set hostname to: %s\n", HOST_NAME);
 // esp_netif_t *netIf = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
 // esp_netif_set_hostname(netIf, HOST_NAME);
 //
 // WiFi.begin(ssid, password);
 // printf("wait for wifi connection\n");
 // while (WiFi.status() != WL_CONNECTED)
 // {
 //  delay(500);
 //  printf("%d ", WiFi.status());
 //  printf(".");
 // }
 // printf("\n");
 //
 // const char *tmpBuf = nullptr;
 // const esp_err_t err = esp_netif_get_hostname(netIf, &tmpBuf);
 // if (err == ESP_OK)
 // {
 //  Serial.printf("Hostname %s\n", tmpBuf);
 // }
 // else
 // {
 //  Serial.printf("hostname lookup error %d\n", err);
 // }
 //
 // strncpy(ipAddress, WiFi.localIP().toString().c_str(), sizeof(ipAddress));
 //
 // printf("WiFi connected IP %s %d\n", ipAddress, WiFi.RSSI());

#endif	/* WIFI_LAN */
  
#if defined(USE_U8X8)
 drawString(0, 0, ipAddress);
 char tmp[2];
 tmp[0] = HOST_NAME[0];
 tmp[1] = 0;
 drawString(15, 0, tmp);
#endif	/* USE_U8X8 */

#if 0
 i0 = 0;
#endif 

#if defined(WIFI_LAN)

 wifiConnect();

#else

// #if defined(RTK_SEND)
//  connectToServer();
// #endif	/* RTK_SEND */
//
// #if defined(RTK_RECV)
//  server.onClient(onNewClient, nullptr);
//  server.begin();
// #endif	/* RTK_RECEIVE */

#endif	/* WWIFI_LAN */

 rtk.state = RCV_IDLE;
 rtk.t0 = millis();

#if defined(DBG_PRT)
 prt = 0;
#endif	/* DBG_PRT */

 printf("exit setup\n");
}

#if 1

void loop()
{
 static unsigned int tmr0;
 unsigned int t0 = millis();
 if ((t0 - tmr0) > 1000)
 {
  tmr0 = t0;

#if defined(WIFI_LAN)
  const signed char rssi = wifiRSSI();
#else
  // const signed char rssi = WiFi.RSSI();
#endif
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

#if defined(GPS_LIB)

 pollSerial();

#else
 //
 // if ((rtk.state == RCV_IDLE) && (rtk.t0Accum != 0) && (t0 - rtk.t0Accum) > 100)
 // {
 //  rtk.t0Accum = 0;
 //  rtk.rxCount = rtk.rxAccum;
 //  rtk.rxAccum = 0;
 // }
 //
 // if (rtk.state != RCV_IDLE)
 // {
 //  if ((millis() - rtk.t0) > 100)
 //  {
 //   rtk.state = RCV_IDLE;
 //   printf("receive timeout\n");
 //  }
 // }
 //
 // if (rtk.svTmr != 0)
 // {
 //  if ((millis() - rtk.svTmr) > 500)
 //  {
 //   printf("***svTmr\n");
 //   rtk.svTmr = 0;
 //
 //   P_SAT_DATA data = satData;
 //   for (int i = 0; i < satIndex; i++)
 //   {
 //    printf("%2d %3s sVid %2d elv %2d az %3d n %d ",
 //           i, names[data->cons], data->sVid, data->elv, data->az, data->freqs);
 //    auto f = data->sig;
 //    for (int j = 0; j < data->freqs; j++)
 //    {
 //     printf("freq %d cno %d ", f->freq, f->cno);
 //     f += 1;
 //    }
 //    printf("\n");
 //    data += 1;
 //   }
 //
 //   int total = 0;
 //   int *p = rtk.svCount;
 //   for (int i = 0; i < 4; i++)
 //   {
 //    total +=  *p;
 //    printf("%2d ", *p);
 //    *p++ = 0;
 //   }
 //   printf("%2d\n", total);
 //  }
 // }

#endif  /* GPS_LIB */

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

#if !defined(GPS_LIB)
//
// void processSerial()
// {
//  while (Serial2.available() > 0)
//  {
//   dbg1Set();
//   unsigned char c = Serial2.read();
//   switch (rtk.state)
//   {
//   case RCV_IDLE:
//    if (c == 0xd3)
//    {
//     dbg0Set();
//     rtk.count = 2;
//     rtk.buf[0] = c;
//     rtk.crc = crc24qTable[c];
//     crcBuf[0] = rtk.crc;
//     rtk.fil = 1;
//     rtk.t0 = millis();
//     rtk.state = RCV_GET_LEN;
//     rtk.startTime = esp_timer_get_time();
//    }
//    else if (c == '$')
//    {
//     rtk.t0 = millis();
//     rtk.state = RCV_TEXT;
//     rtk.buf[0] = c;
//     rtk.fil = 1;
//    }
//    break;
//
//   case RCV_GET_LEN:
//    rtk.crc = ((rtk.crc << 8) ^ crc24qTable[((rtk.crc >> 16) ^ c) & 0xFFu]) & 0xFFFFFFu;
//    crcBuf[rtk.fil] = rtk.crc;
//    rtk.len = (rtk.len << 8) + c;
//    rtk.buf[rtk.fil] = c;
//    rtk.fil += 1;
//    rtk.count -= 1;
//    if (rtk.count == 0)
//    {
//     rtk.state = RCV_GET_DATA;
//     rtk.len &= 0x3ff;
//     // printf("rtkLen %d\n", rtk.len);
// #if defined(DBG_PRT)
//     // if ((prt == 0) && (rtk.len == 19))
//     if (rtk.len == 19)
//     {
//      prt = 1;
//     }
// #endif	/* DBG_PRT */
//     rtk.len += 3;
//    }
//    break;
//
//   case RCV_GET_DATA:
//    rtk.crc = ((rtk.crc << 8) ^ crc24qTable[((rtk.crc >> 16) ^ c) & 0xFFu]) & 0xFFFFFFu;
//    crcBuf[rtk.fil] = rtk.crc;
//    rtk.buf[rtk.fil] = c;
//    rtk.fil += 1;
//    rtk.len -= 1;
//    if (rtk.len == 0)
//    {
//     const auto msgT = static_cast<uint32_t>(esp_timer_get_time() - rtk.startTime);
//     int type = (rtk.buf[3] << 4) | (rtk.buf[4] >> 4);
//     rtk.rxAccum += rtk.fil;
//     printf("rtkLen %4d type %4d rtkCRC %08x %5d %u\n",
//            rtk.fil, type, static_cast<unsigned int>(rtk.crc), rtk.rxAccum,
//            static_cast<unsigned int>(msgT));
//     rtk.t0Accum = millis();
// #if defined(RTK_SEND)
//     sendBinary(reinterpret_cast<const uint8_t *>(rtk.buf), (ssize_t) rtk.fil);
// #endif	/* RTK_SEND */
//
// #if defined(DBG_PRT)
//     if (prt == 1)
//     {
//      printHex(reinterpret_cast<const u_int8_t *>(rtk.buf), rtk.fil);
//      printHex(reinterpret_cast<const u_int8_t *>(crcBuf), rtk.fil << 2);
//      prt = 0;
//     }
// #endif	/* DDBG_PRT */
//     dbg0Clr();
//     rtk.state = RCV_IDLE;
//    }
//    break;
//
//   case RCV_TEXT:
//    if (c == '\n')
//    {
//     if (rtk.buf[rtk.fil - 1] == '\r')
//      rtk.fil -= 1;
//     rtk.buf[rtk.fil] = 0;
//
//     if (rtk.buf[0] == '$')
//     {
//      char *p2 = &rtk.buf[1];
//      char chk = 0;
//      char rcvChk = 0xff;
//      for (int i = 0; i < (rtk.fil - 1); i++)
//      {
//       const char c0 = *p2++;
//       if (c0 == '*')
//       {
//        rcvChk = getHex(&p2);
//        printf("chk %02x tmp %02x\n", chk, rcvChk);
//        break;
//       }
//       chk ^= c0;
//      }
//      if (chk != rcvChk)
//      {
//       printf("checksum error\n");
//       break;
//      }
//      printf("%s\n", static_cast<const char *>(rtk.buf));
//
//      if (strncmp(rtk.buf, "$GNGGA", 6) == 0)
//      {
//       gpsLoc();
//      }
//      else if (rtk.buf[1] == 'G' && strncmp(&rtk.buf[3], "GSV", 3) == 0)
//      {
//       gpsSat();
//      }
//     }
//     rtk.state = RCV_IDLE;
//    }
//    else
//    {
//     rtk.buf[rtk.fil] = c;
//     rtk.fil += 1;
//    }
//    break;
//   }
//   dbg1Clr();
//  }
// }
//
// /* $GNGGA, 091628.00, 3844.78718183,N, 07755.96337656,W, 7,28,0.5,135.9670,M,-33.6653,M,,*44 */
//
// void gpsLoc()
// {
//  char *p = nextArg(rtk.buf);
//
// #if defined(USE_U8X8)
//  char *p0 = p;
//  char buf[20];
//  char *p1 = buf;
//  *p1++ = *p0++;		/* 0 */
//  *p1++ = *p0++;		/* 1 */
//  *p1++ = ':';		/* 2 */
//  *p1++ = *p0++;		/* 3 */
//  *p1++ = *p0++;		/* 4 */
//  *p1++ = ':';		/* 5 */
//  *p1++ = *p0++;		/* 6 */
//  *p1++ = *p0;		/* 7 */
//  *p1++ = ' ';		/* 8 */
//  *p1++ = ' ';		/* 9 */
//  *p1 = 0;
//  drawString(0, 2, buf);
// #endif	/* USE_U8X8 */
//
//  int gpsTime = getNum(&p, 2) * 60;
//  gpsTime += getNum(&p, 2);
//  gpsTime *= 60;
//  gpsTime += getNum(&p, 2);
//
//  p = nextArg(p);
//  int tmp = getNum(&p, 2);
//  const double lat = static_cast<double>(tmp) + strtod(p, &p) / 60.0;
//  p = nextArg(p);
//  p = nextArg(p);
//  tmp = getNum(&p, 3);
//  double lon = (static_cast<double>(tmp) + strtod(p, &p) / 60.0);
//  p = nextArg(p);
//  if (*p == 'W')
//   lon = -lon;
//  p = nextArg(p);
//  int fix = getNum(&p);
//  int sats = getNum(&p);
//  printf("gpsTime %6d lat %-14.10f lon %-14.10f fix %d sats %2d\n",
// 	gpsTime, lat, lon, fix, sats);
//
// #if defined(USE_U8X8)
//  snprintf(buf, sizeof(buf), "%d %2d   ", fix, sats);
//  drawString(9, 2, buf);  // 9 10 11 12 13 14 15
//
//  snprintf(buf, sizeof(buf), " %13.10f", lat);
//  drawString(0, 3, buf);
//  snprintf(buf, sizeof(buf), "%14.10f", lon);
//  drawString(0, 4, buf);
// #endif	/* USE_U8X8 */
// }
//
// void gpsSat()
// {
//  if (rtk.svTmr == 0)
//  {
//   printf("***start svTmr\n");
//   satIndex = 0;
//  }
//  rtk.svTmr = millis();
//
//  char c0 = rtk.buf[2];
//  int satCons = -1;
//  for (int i = 0; i < sizeof(cons) - 1; i++)
//  {
//   if (c0 == cons[i])
//   {
//    satCons = i;
//    break;
//   }
//  }
//
//  if (satCons >= 0)
//  {
//   const char* txtEnd = &rtk.buf[rtk.fil];
//   int freq = -1;
//   for (int i = 0; i < 3; i++)
//   {
//    const char c2 = *--txtEnd;
//    if (c2 == '*')
//    {
//     txtEnd -= 1;
//     puts(txtEnd);
//     freq = *txtEnd - '0';
//     break;
//    }
//   }
//   printf("constellation %d %s freq %d\n", satCons, names[satCons], freq);
//
//   char* p = nextArg(rtk.buf); /* skip name */
//   int numMsg = getNum(&p);
//   int msgNum = getNum(&p);
//   int numSv =  getNum(&p);
//   if (msgNum == 1)
//    rtk.numSv = numSv;
//   printf("numMsg %d msgNum %d numSv %d\n", numMsg, msgNum, numSv);
//   int n = rtk.numSv > 4 ? 4 : rtk.numSv;
//   for (int i = 0; i < n; i++)
//   {
//    int sVid = getNum(&p);
//    int elv = getNum(&p);
//    int az = getNum(&p);
//    int cno = getNum(&p);
//    printf("%2d %2d sVid %2d elv %2d az %3d ", satIndex, rtk.numSv, sVid, elv, az);
//
//    int j;
//    for (j = 0; j <= satIndex; j++)
//    {
//     P_SAT_DATA rec = &satData[j];
//     if (satCons == rec->cons && sVid == rec->sVid)
//     {
//      if (rec->freqs < MAX_SIG)
//      {
//       P_FREQ_INFO f = &rec->sig[rec->freqs];
//       rec->freqs += 1;
//       f->freq = freq;
//       f->cno = cno;
//       printf("n %d freq %d cno %2d\n", rec->freqs, f->freq, f->cno);
//       break;
//      }
//     }
//    }
//
//    if (j > satIndex)
//    {
//     rtk.svCount[satCons] += 1;
//     P_SAT_DATA rec = &satData[satIndex];
//     rec->cons = satCons;
//     rec->sVid = sVid;
//     rec->elv = elv;
//     rec->az = az;
//     rec->freqs = 1;
//     P_FREQ_INFO f = rec->sig;
//     memset(f, 0, sizeof(rec->sig));
//     f->freq = freq;
//     f->cno = cno;
//     if (satIndex < MAX_SAT)
//      satIndex += 1;
//     printf("n %d freq %d cno %2d\n", rec->freqs, f->freq, f->cno);
//    }
//
//    rtk.numSv -= 1;
//   }
//   printf("satCons %d count %d\n", satCons, rtk.svCount[satCons]);
//
//   int total = 0;
//   int *pC = rtk.svCount;
//   for (int i = 0; i < 4; i++)
//   {
//    total += *pC;
//    printf("%2d ", *pC);
//    pC++;
//   }
//   printf("%2d\n", total);
//
//  }
//  printf("\n");
// }
//
// #if defined(RTK_RECV)
//
// void processRemData(void *data, size_t len)
// {
//  const auto *ptr = static_cast<char *>(data);
//  while (len > 0)
//  {
//   len -= 1;
//   const char ch = *ptr++;
//   switch (rtk.state)
//   {
//   case RCV_IDLE:
//    if (ch == 0xd3)
//    {
//     rtk.count = 2;
//     Serial2.write(ch);
//     rtk.buf[0] = ch;
//     rtk.crc = crc24qTable[ch];
//     crcBuf[0] = rtk.crc;
//     rtk.fil = 1;
//     rtk.t0 = millis();
//     rtk.state = RCV_GET_LEN;
//    }
//    else if (ch == '$')
//    {
//     rtk.t0 = millis();
//     rtk.state = RCV_TEXT;
//    }
//    break;
//
//   case RCV_GET_LEN:
//    Serial2.write(ch);
//    rtk.crc = ((rtk.crc << 8) ^ crc24qTable[((rtk.crc >> 16) ^ ch) & 0xFFu]) & 0xFFFFFFu;
//    crcBuf[rtk.fil] = rtk.crc;
//    rtk.len = (rtk.len << 8) + ch;
//    rtk.buf[rtk.fil] = ch;
//    rtk.fil += 1;
//    rtk.count -= 1;
//    if (rtk.count == 0)
//    {
//     rtk.state = RCV_GET_DATA;
//     rtk.len &= 0x3ff;
//     // printf("dLen %d\n", dLen);
// #if defined(DBG_PRT)
//     //if ((prt == 0) && (rtk.len == 19))
//     if (rtk.len == 19)
//     {
//      prt = 1;
//     }
// #endif	/* DBG_PRT */
//     rtk.len += 3;
//    }
//    break;
//
//   case RCV_GET_DATA:
//    Serial2.write(ch);
//    rtk.crc = ((rtk.crc << 8) ^ crc24qTable[((rtk.crc >> 16) ^ ch) & 0xFFu]) & 0xFFFFFFu;
//    crcBuf[rtk.fil] = rtk.crc;
//    rtk.buf[rtk.fil] = ch;
//    rtk.fil += 1;
//    rtk.len -= 1;
//    if (rtk.len == 0)
//    {
//     const int type = (rtk.buf[3] << 4) | (rtk.buf[4] >> 4);
//     printf("len %4d type %4d CRC %08x\n", rtk.fil, type, static_cast<unsigned int>(rtk.crc));
// #if defined(DBG_PRT)
//     if (prt == 1)
//     {
//      printHex(reinterpret_cast<const uint8_t *>(rtk.buf), rtk.fil);
//      printHex(reinterpret_cast<const uint8_t *>(crcBuf), rtk.fil << 2);
//      prt = 0;
//     }
// #endif	/* DBG_PRT */
//     rtk.state = RCV_IDLE;
//    }
//    break;
//
//   case RCV_TEXT:
//    if (ch == '\n')
//    {
//     rtk.state = RCV_IDLE;
//    }
//    else
//    {
//
//    }
//    break;
//   }
//  }
// }
//
// #endif	/* RTK_RECV */

#endif	/* GPS_LIB */

#if 0
#if 0
 unsigned int t = millis();
 if ((t - t0) > 5000)
 {
  t0 = t;
#if 0
  // Connect to TCP server
  if (client.connect(host, port))
  {
   printf("Connected to server %d\n", i0);

   // Send data
   client.printf("Hello Server %d", i0);

   // Close connection
   client.stop();
   printf("Connection closed\n");
  }
  else
  {
   printf("Connection failed\n");
  }
#else
  //uint8_t buf[32];
  //size_t len = sprintf(reinterpret_cast<char *>(buf), "Hello Server %d", i0);
  //sendBinary(buf, len);

#endif
  i0 += 1;
 }
#endif

}
#endif

#else
//
// void loop()
// {
//
//  if (static_cast<unsigned int>(client) == 0)
//  {
//   client = server.available();
//   if (static_cast<unsigned int>(client) != 0)
//    printf("connected %08x\n", static_cast<unsigned int>(client));
//  }
//
//  if (client)
//  {
//   if (client.connected())
//   {
//    if (client.available())
//    {
//     String data = client.readStringUntil('\n');
//     printf("Received: ");
//     printf("%s\n", data.c_str());
//    }
//   }
//   else
//    printf("connection lost\n");
//  }
//
// }

#endif

#if !defined(GPS_LIB)
//
// void printHex(const uint8_t *data, size_t len)
// {
//  int col = 0;
//  for (size_t i = 0; i < len; i++)
//  {
//   if (col == 0)
//   {
//    printf("  %04X: ", static_cast<unsigned int>(i));
//   }
//   printf("%02X ", data[i]);
//   col += 1;
//   if (col == 16)
//   {
//    col = 0;
//    printf("\n");
//   }
//  }
//  if (col != 0)
//   printf("\n");
// }
//
// /* ── CRC-24Q constants ───────────────────────────────────────────────────── */
//
// #define CRC24Q_POLY      0x1864CFBu  /* Generator polynomial                 */
// #define RTCM3_PREAMBLE   0xD3u       /* Mandatory first byte of every frame  */
// #define RTCM3_HDR_LEN    3           /* Preamble + 2 length/reserved bytes   */
// #define RTCM3_CRC_LEN    3           /* 24-bit CRC appended at end           */
// #define RTCM3_MIN_FRAME  (RTCM3_HDR_LEN + RTCM3_CRC_LEN)
//
// /* ── CRC-24Q lookup table (generated once on first use) ─────────────────── */
//
// static void buildCRC24qTable()
// {
//  for (uint32_t i = 0; i < 256; i++)
//  {
//   uint32_t crc = i << 16;
//   for (int j = 0; j < 8; j++)
//   {
//    crc <<= 1;
//    if (crc & 0x1000000u)
//     crc ^= CRC24Q_POLY;
//   }
//   crc24qTable[i] = crc & 0xFFFFFFu;
//  }
// }
//
// inline uint32_t crc24(const uint32_t crc, const unsigned char c)
// {
//  return ((crc << 8) ^ crc24qTable[((crc >> 16) ^ c) & 0xFFu]) & 0xFFFFFFu;
// }
//
// char* nextArg(char* p0)
// {
//  while (true)
//  {
//   const char c0 = *p0;
//   if (c0 == 0)
//    break;
//   p0 += 1;
//   if (c0 == ',')
//   {
//    break;
//   }
//  }
//  return p0;
// }
//
// char *getNum(char *p0, int n, int *result)
// {
//  int val = 0;
//  while (n > 0)
//  {
//   const char c1 = *p0++;
//   val *= 10;
//   val += c1 - '0';
//   n -= 1;
//  }
//  *result = val;
//  return p0;
// }
//
// int getNum(char **p0, int n)
// {
//  char *p1 = *p0;
//  int val = 0;
//  while (n > 0)
//  {
//   const char c1 = *p1++;
//   val *= 10;
//   val += c1 - '0';
//   n -= 1;
//  }
//  *p0 = p1;
//  return val;
// }
//
// int getNum(char **p0)
// {
//  char *p1 = *p0;
//  int val = 0;
//  while (true)
//  {
//   const char c1 = *p1++;
//   if (c1 == ',' || c1 == 0)
//    break;
//   val *= 10;
//   val += c1 - '0';
//  }
//  *p0 = p1;
//  return val;
// }
//
// int getHex(char **p0)
// {
//  char *p1 = *p0;
//  int val = 0;
//  while (true)
//  {
//   char c1 = *p1++;
//   if (c1 <= ' ')
//    break;
//   val <<= 4;
//   c1 -= '0';
//   if (c1 > 9)
//    c1 -= 'A' - ('9' + 1);
//   val += c1;
//  }
//  *p0 = p1;
//  return val;
// }

#endif	/* GPS_LIB */

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
