/*
 *  KeedConfigWiFi.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "KeedConfig.h"

KeedWiFi::KeedWiFi()
        : server(80) {
}

KeedWiFi::KeedWiFi(const char *ssid, const char *password) {
    createWiFIAP(ssid, password);
}

int KeedWiFi::createWiFIAP(const char *ssid, const char *password) {
    Serial.print("| Setting AP (Access Point)… ");
    WiFi.softAP(ssid, password);
    IP = WiFi.softAPIP();
    return IP;
}

void KeedWiFi::beginServer() {
    server.begin();
    // core.createCore(1, [](void *pvParameter) [[TASK_FUNCTION]] -> void {
    //   KeedWiFi server("Auto Light AP");
    //   server.beginServer();
    //   server.showServerInfo();
    //   for (;;) {
    //     server.runServer();
    //     vTaskDelay(20 / portTICK_PERIOD_MS);
    //   }
    // });
}

void KeedWiFi::showServerInfo() {
    Serial.print("| AP IP address: ");
    Serial.println(IP);
}

void KeedWiFi::runServer() {
    WiFiClient client = server.available();
    if (client) {
        String currentLine = "";
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                header += c;
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        if (header.indexOf("GET /mode") >= 0) {
                            auto setMode = [&]() -> size_t {
                                for (int i = 10; i >= 1; --i) {
                                    String modePath = "/mode/" + String(i);
                                    if (header.indexOf("GET " + modePath) >= 0) {
                                        return writeMEM(25, (i == 8 || i == 9) ? "0" : (i == 10) ? "8" : String(i));
                                    }
                                }
                                return 0;
                            };
                            setMode();
                        }
                        if (header.indexOf("GET /delay/set?value=") >= 0) {
                            int valueStart = header.indexOf("value=") + 6;
                            int valueEnd = header.indexOf(" ", valueStart);
                            String valueString = header.substring(valueStart, valueEnd);
                            int value = valueString.toInt();
                            writeMEM(30, String(value));
                        }

                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<link rel=\"icon\" href=\"data:,\">");
                        client.println("<style>html { font-family: \"Verdana\", \"Arial\", sans-serif; display: inline-block; margin: 0px auto; text-align: center;}");
                        client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; border-radius: 10px;");
                        client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                        client.println(".button2 {background-color: #555555; border-radius: 10px;}</style></head>");
                        client.println("<body><h1>KEED Auto Light</h1>");

                        client.println("<div style=\"display: flex; justify-content: space-evenly;\">");

                        client.println("<form action=\"/delay/set\" method=\"get\">");
                        client.println("<p>Value for <b>Delay(ms)</b> </p>");
                        client.println("<input type=\"number\" name=\"value\" min=\"30\" max=\"1000\" step=\"1\" placeholder=\"value\">");
                        client.println("<input type=\"submit\" value=\"Set\">");
                        client.println("</form>");

                        client.println("<form action=\"/anything/set\" method=\"get\">");
                        client.println("<p>Value for <b>Anything</b> </p>");
                        client.println("<input type=\"number\" name=\"value\" min=\"0\" max=\"5000\" step=\"1\" placeholder=\"value\">");
                        client.println("<input type=\"submit\" value=\"Set\">");
                        client.println("</form>");

                        client.println("</div>");

                        [&]() -> void {
                            int sequence = readMEM(25).toInt();
                            sequence = (sequence == 0) ? 9 : (sequence == 8) ? 10 : sequence;
                            auto displayMode = [&](const String &mode, const String &value, bool isActive) -> void {
                                if (isActive) client.println("<a href=\"/mode/" + value + "\"><button class=\"button\">" + mode + "</button></a>");
                                else client.println("<a href=\"/mode/" + value + "\"><button class=\"button button2\">" + mode + "</button></a>");
                            };
                            client.println("<div style=\"display: flex; justify-content: space-evenly;\">");
                            client.println("<p> AUTO LIGHT MODE </p>");
                            String modes[] = {"MODE 1", "MODE 2", "MODE 3", "MODE 4", "MODE 5", "MODE 6", "MODE 7", "MODE X", "MODE OFF", "MODE ON"};
                            String values[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
                            bool isActive[] = {false, false, false, false, false, false, false, false, false, false};
                            isActive[sequence - 1] = true;
                            for (int i = 0; i < 5; ++i) {
                                client.println("</div>");
                                client.println("<div style=\"display: flex; justify-content: space-evenly;\">");
                                displayMode(modes[2 * i], values[2 * i], isActive[2 * i]);
                                displayMode(modes[2 * i + 1], values[2 * i + 1], isActive[2 * i + 1]);
                            }
                        }();
                        client.println("</body></html>");
                        client.println();
                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }
            }
        }
        header = "";
        client.stop();
    }
}
