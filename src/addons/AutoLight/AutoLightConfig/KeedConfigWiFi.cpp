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
    WiFiClient client = server.available();  // Listen for incoming clients

    if (client) {                     // If a new client connects,
//        Serial.println("New Client.");  // print a message out in the serial port
        String currentLine = "";        // make a String to hold incoming data from the client
        while (client.connected()) {    // loop while the client's connected
            if (client.available()) {     // if there's bytes to read from the client,
                char c = client.read();     // read a byte, then
//                Serial.write(c);            // print it out the serial monitor
                header += c;
                if (c == '\n') {  // if the byte is a newline character
                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (currentLine.length() == 0) {
                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        if (header.indexOf("GET /mode/1") >= 0) {
                            Serial.println("MODE 1");
                        } else if (header.indexOf("GET /mode/2") >= 0) {
                            Serial.println("MODE 2");
                        }

                        if (header.indexOf("GET /delay/set?value=") >= 0) {
                            int valueStart = header.indexOf("value=") + 6;
                            int valueEnd = header.indexOf(" ", valueStart);
                            String valueString = header.substring(valueStart, valueEnd);
                            int value = valueString.toInt();
                            Serial.println("value: " + String(value));
                        }

                        // Display the HTML web page
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
                            auto displayMode = [&](const String &mode, const String &value, bool isActive) -> void {
                                if (isActive) client.println("<a href=\"/mode/" + value + "\"><button class=\"button\">" + mode + "</button></a>");
                                else client.println("<a href=\"/mode/" + value + "\"><button class=\"button button2\">" + mode + "</button></a>");
                            };
                            int random_value = random(1, 11);
                            client.println("<div style=\"display: flex; justify-content: space-evenly;\">");
                            client.println("<p> AUTO LIGHT MODE </p>");
                            String modes[] = {"MODE 1", "MODE 2", "MODE 3", "MODE 4", "MODE 5", "MODE 6", "MODE 7", "MODE X", "MODE ON", "MODE OFF"};
                            String values[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
                            bool isActive[] = {false, false, false, false, false, false, false, false, false, false};
                            isActive[random_value - 1] = true;
                            for (int i = 0; i < 5; ++i) {
                                client.println("</div>");
                                client.println("<div style=\"display: flex; justify-content: space-evenly;\">");
                                displayMode(modes[2 * i], values[2 * i], isActive[2 * i]);
                                displayMode(modes[2 * i + 1], values[2 * i + 1], isActive[2 * i + 1]);
                            }

//                            int random_value = random(1, 11);
//                            client.println("<div style=\"display: flex; justify-content: space-evenly;\">");
//                            client.println("<p> AUTO LIGHT MODE </p>");
//                            auto displayMode = [&](String _first, String _last, String _first_value, String _last_value, bool _first_state, bool _second_state) -> void {
//                                client.println("</div>");
//                                client.println("<div style=\"display: flex; justify-content: space-evenly;\">");
//                                if (_first_state) client.println("<a href=\"/mode/" + _first_value + "\"><button class=\"button\">MODE " + _first + " </button></a>");
//                                else client.println("<a href=\"/mode/" + _first_value + "\"><button class=\"button button2\">MODE " + _first + "</button></a>");
//                                if (_second_state) client.println("<a href=\"/mode/" + _last_value + "\"><button class=\"button\">MODE " + _last + "</button></a>");
//                                else client.println("<a href=\"/mode/" + _last_value + "\"><button class=\"button button2\">MODE " + _last + "</button></a>");
//                                client.println("</div>");
//                            };
//                            if (random_value == 1) {
//                                displayMode("1", "2", "1", "2", true, false);
//                                displayMode("3", "4", "3", "4", false, false);
//                                displayMode("5", "6", "5", "6", false, false);
//                                displayMode("7", "X", "7", "8", false, false);
//                                displayMode("ON", "OFF", "9", "10", false, false);
//                            } else if (random_value == 2) {
//                                displayMode("1", "2", "1", "2", false, true);
//                                displayMode("3", "4", "3", "4", false, false);
//                                displayMode("5", "6", "5", "6", false, false);
//                                displayMode("7", "X", "7", "8", false, false);
//                                displayMode("ON", "OFF", "9", "10", false, false);
//                            } else if (random_value == 3) {
//                                displayMode("1", "2", "1", "2", false, false);
//                                displayMode("3", "4", "3", "4", true, false);
//                                displayMode("5", "6", "5", "6", false, false);
//                                displayMode("7", "X", "7", "8", false, false);
//                                displayMode("ON", "OFF", "9", "10", false, false);
//                            } else if (random_value == 4) {
//                                displayMode("1", "2", "1", "2", false, false);
//                                displayMode("3", "4", "3", "4", false, true);
//                                displayMode("5", "6", "5", "6", false, false);
//                                displayMode("7", "X", "7", "8", false, false);
//                                displayMode("ON", "OFF", "9", "10", false, false);
//                            } else if (random_value == 5) {
//                                displayMode("1", "2", "1", "2", false, false);
//                                displayMode("3", "4", "3", "4", false, false);
//                                displayMode("5", "6", "5", "6", true, false);
//                                displayMode("7", "X", "7", "8", false, false);
//                                displayMode("ON", "OFF", "9", "10", false, false);
//                            } else if (random_value == 6) {
//                                displayMode("1", "2", "1", "2", false, false);
//                                displayMode("3", "4", "3", "4", false, false);
//                                displayMode("5", "6", "5", "6", false, true);
//                                displayMode("7", "X", "7", "8", false, false);
//                                displayMode("ON", "OFF", "9", "10", false, false);
//                            } else if (random_value == 7) {
//                                displayMode("1", "2", "1", "2", false, false);
//                                displayMode("3", "4", "3", "4", false, false);
//                                displayMode("5", "6", "5", "6", false, false);
//                                displayMode("7", "X", "7", "8", true, false);
//                                displayMode("ON", "OFF", "9", "10", false, false);
//                            } else if (random_value == 8) {
//                                displayMode("1", "2", "1", "2", false, false);
//                                displayMode("3", "4", "3", "4", false, false);
//                                displayMode("5", "6", "5", "6", false, false);
//                                displayMode("7", "X", "7", "8", false, true);
//                                displayMode("ON", "OFF", "9", "10", false, false);
//                            } else if (random_value == 9) {
//                                displayMode("1", "2", "1", "2", false, false);
//                                displayMode("3", "4", "3", "4", false, false);
//                                displayMode("5", "6", "5", "6", false, false);
//                                displayMode("7", "X", "7", "8", false, false);
//                                displayMode("ON", "OFF", "9", "10", true, false);
//                            } else if (random_value == 10) {
//                                displayMode("1", "2", "1", "2", false, false);
//                                displayMode("3", "4", "3", "4", false, false);
//                                displayMode("5", "6", "5", "6", false, false);
//                                displayMode("7", "X", "7", "8", false, false);
//                                displayMode("ON", "OFF", "9", "10", false, true);
//                            }
                        }();

//                        auto modeMenu = [&](String _left, String _right, bool _active_left, bool _active_right) -> void {
//                            client.println("<div style=\"display: flex; justify-content: space-evenly;\">");
//                            client.println("<p> " + _left + " </p>");
//                            client.println("<p> " + _right + " </p>");
//                            client.println("</div>");
//
//                            client.println("<div style=\"display: flex; justify-content: space-evenly;\">");
//                            {
//                                if (_active_left) client.println("<a href=\"/26/on\"><button class=\"button\">ON</button></a>");
//                                else client.println("<a href=\"/mode/on\"><button class=\"button button2\">ON</button></a>");
//                                if (_active_right) client.println("<a href=\"/27/on\"><button class=\"button\">ON</button></a>");
//                                else client.println("<a href=\"/mode/on\"><button class=\"button button2\">ON</button></a>");
//                            }
//                            client.println("</div>");
//                        };
//
//                        modeMenu("MODE 1", "MODE 2", true, false);
//                        modeMenu("MODE 3", "MODE 4", false, false);
//                        modeMenu("MODE 5", "MODE 6", false, false);
//                        modeMenu("MODE ON", "MODE OFF", false, false);

                        client.println("</body></html>");
                        client.println();
                        break;
                    } else {  // if you got a newline, then clear currentLine
                        currentLine = "";
                    }
                } else if (c != '\r') {  // if you got anything else but a carriage return character,
                    currentLine += c;      // add it to the end of the currentLine
                }
            }
        }
        header = "";
        client.stop();
//        Serial.println("Client disconnected.");
//        Serial.println("");
    }
}
