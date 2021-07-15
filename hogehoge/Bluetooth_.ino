#include <WiFi.h>

const char *ssid = "iphoneはし";
const char *password = "MGAryoma311";
 
void setup() {
  Serial.begin(115200);
  setupWifi();    // Wifi接続
  syncTime();     // 時刻を合わせる
  Serial.println("setup end!");
}
 
void loop() {
  struct tm timeInfo;
  char s[20];

  getLocalTime(&timeInfo); // 時刻を取得

  // 日付と時刻を文字列として取得
  sprintf(s, "%04d/%02d/%02d %02d:%02d:%02d",
          timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday,
          timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);

  // 曜日も含めた書式に変更
  String dayInfo = s;
  dayInfo = dayInfo.substring(0, 10) + " (" + getDayOfWeek(timeInfo.tm_wday) + ")\n" + dayInfo.substring(11);

  Serial.println(dayInfo);
  delay(10);
}

/**
 * Wifiの設定を行う関数
 */
void setupWifi() {
  // WiFiに接続
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Connected to ");
  Serial.println(ssid);
}

/**
 * 時刻合わせを行う関数
 */
void syncTime() {
  configTime(-9 * 3600L, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");
}

/**
 * 引数の数値を曜日に変換する関数
 */
String getDayOfWeek(int dayNum) {
  String result = "";
  switch (dayNum) {
    case 0:
      result = "Sun";
      break;
    case 1:
      result = "Mon";
      break;
    case 2:
      result = "Tue";
      break;
    case 3:
      result = "Wed";
      break;
    case 4:
      result = "Thu";
      break;
    case 5:
      result = "Fri";
      break;
    case 6:
      result = "Sat";
      break;
  }
  return result;
}
