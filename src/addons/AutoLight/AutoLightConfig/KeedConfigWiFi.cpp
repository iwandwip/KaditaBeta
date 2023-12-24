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

int KeedWiFi::createWiFIAP(const char *_ssid, const char *_password) {
    Serial.print("| Setting AP (Access Point) … ");
    String ssid_mem = readMEM(SSID_ADDRESS);
    String password_mem = readMEM(PASSWORD_ADDRESS);
    if (ssid_mem.isEmpty()) {
        WiFi.softAP(_ssid, _password);
        Serial.println("| WiFi set to Default");
    } else {
        WiFi.softAP(ssid_mem.c_str(), password_mem.isEmpty() ? nullptr : password_mem.c_str());
        Serial.print("| WiFi set to SSID: ");
        Serial.print(ssid_mem);
        Serial.print("| PASSWORD: ");
        Serial.print(password_mem.isEmpty() ? "NONE" : password_mem);
        Serial.println();
    }
    IP = WiFi.softAPIP();
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    return IP;
}

void KeedWiFi::beginServer() {
    server.begin();
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
                                        return writeMEM(MODE_ADDRESS, (i == 8 || i == 9) ? "0" : (i == 10) ? "8" : String(i));
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
                            if (value) writeMEM(DELAY_ADDRESS, String(value));
                        }

                        if (header.indexOf("GET /ap/set?ssid=") >= 0) {
                            auto parseSSIDAndPassword = [&](const String &request) {
                                int ssidStart = request.indexOf("ssid=") + 5;
                                int ssidEnd = request.indexOf("&", ssidStart);
                                int passwordStart = request.indexOf("password=") + 9;
                                int passwordEnd = request.indexOf(" ", passwordStart);
                                String ssid = request.substring(ssidStart, ssidEnd);
                                String password = request.substring(passwordStart, passwordEnd);
                                while (ssid.indexOf('+') != -1) {
                                    ssid.replace("+", " ");
                                }
                                writeMEM(SSID_ADDRESS, ssid);
//                                writeMEM(PASSWORD_ADDRESS, password);
                                ESP.restart();
                            };
                            parseSSIDAndPassword(header);
                        }

                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<link rel=\"icon\" href=\"data:,\">");
                        client.println("<style>html { font-family: \"Verdana\", \"Arial\", sans-serif; display: inline-block; margin: 0px auto; text-align: center;}");
                        client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; border-radius: 10px;");
                        client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                        client.println(".button2 {background-color: #555555; border-radius: 10px;}</style></head>");
                        client.println("<body><h2>KEED Auto Light</h2>");

                        client.println("<div style=\"display: flex; justify-content: space-evenly;\">");

                        client.println("<form action=\"/delay/set\" method=\"get\">");
                        client.println("<p><b>Delay(ms): " + String(readMEM(DELAY_ADDRESS)) + "</b> </p>");
                        client.println("<input type=\"number\" name=\"value\" min=\"10\" max=\"1000\" step=\"1\" placeholder=\"value\">");
                        client.println("<input type=\"submit\" value=\"Set\">");
                        client.println("</form>");

                        client.println("<form action=\"/anything/set\" method=\"get\">");
                        client.println("<p><b>Anything</b> </p>");
                        client.println("<input type=\"number\" name=\"value\" min=\"0\" max=\"5000\" step=\"1\" placeholder=\"value\">");
                        client.println("<input type=\"submit\" value=\"Set\">");
                        client.println("</form>");

                        client.println("</div>");

                        [&]() -> void {
                            int sequence = readMEM(MODE_ADDRESS).toInt();
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
                                client.println("</div>");
                            }
                        }();

                        client.println("<div style=\"display: flex; justify-content: space-evenly;\">");

                        client.println("<form action=\"/ap/set\" method=\"get\">");
                        client.println("<p>" + readMEM(SSID_ADDRESS) + " | " + (readMEM(PASSWORD_ADDRESS).isEmpty() ? "NONE" : readMEM(PASSWORD_ADDRESS)) + "</p>");
                        client.println("<input type=\"text\" name=\"ssid\" placeholder=\"SSID\" maxlength=\"30\" required>");
                        client.println("<input type=\"text\" name=\"password\" placeholder=\"PASSWORD\"  minlength=\"8\" maxlength=\"10\" required>");
                        client.println("<br><br>");
                        client.println("<input type=\"submit\" value=\"Set AP\">");
                        client.println("</form>");

                        client.println("</div>");

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
