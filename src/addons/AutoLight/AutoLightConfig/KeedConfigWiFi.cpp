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
        Serial.println("New Client.");  // print a message out in the serial port
        String currentLine = "";        // make a String to hold incoming data from the client
        while (client.connected()) {    // loop while the client's connected
            if (client.available()) {     // if there's bytes to read from the client,
                char c = client.read();     // read a byte, then
                Serial.write(c);            // print it out the serial monitor
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

                        // turns the GPIOs on and off
//                            if (header.indexOf("GET /26/on") >= 0) {
//                                Serial.println("GPIO 26 on");
//                                output26State = "on";
//                                digitalWrite(output26, HIGH);
//                            } else if (header.indexOf("GET /26/off") >= 0) {
//                                Serial.println("GPIO 26 off");
//                                output26State = "off";
//                                digitalWrite(output26, LOW);
//                            } else if (header.indexOf("GET /27/on") >= 0) {
//                                Serial.println("GPIO 27 on");
//                                output27State = "on";
//                                digitalWrite(output27, HIGH);
//                            } else if (header.indexOf("GET /27/off") >= 0) {
//                                Serial.println("GPIO 27 off");
//                                output27State = "off";
//                                digitalWrite(output27, LOW);
//                            }

                        // Display the HTML web page
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<link rel=\"icon\" href=\"data:,\">");
                        client.println("<style>html { font-family: \"Verdana\", \"Arial\", sans-serif; display: inline-block; margin: 0px auto; text-align: center;}");
                        client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
                        client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                        client.println(".button2 {background-color: #555555;}</style></head>");
                        client.println("<body><h1>KEED Auto Light</h1>");

                        client.println("<div style=\"display: flex; justify-content: space-evenly;\">");
                        {
                            client.println("<form action=\"/28/set\" method=\"get\">");
                            client.println("<p>Value for <b>Delay(ms)</b> </p>");

                            client.println("<input type=\"number\" name=\"value\" min=\"0\" max=\"5000\" step=\"1\" placeholder=\"value\">");
                            client.println("<input type=\"submit\" value=\"Set\">");

                            client.println("</form>");
                        }
                        {
                            client.println("<form action=\"/28/set\" method=\"get\">");
                            client.println("<p>Value for <b>Anything</b> </p>");

                            client.println("<input type=\"number\" name=\"value\" min=\"0\" max=\"5000\" step=\"1\" placeholder=\"value\">");
                            client.println("<input type=\"submit\" value=\"Set\">");

                            client.println("</form>");
                        }
                        client.println("</div>");

                        auto modeMenu = [&](String _left, String _right, bool _active_left, bool _active_right) -> void {
                            client.println("<div style=\"display: flex; justify-content: space-evenly;\">");
                            client.println("<p> " + _left + " </p>");
                            client.println("<p> " + _right + " </p>");
                            client.println("</div>");

                            client.println("<div style=\"display: flex; justify-content: space-evenly;\">");
                            {
                                if (_active_left) client.println("<a href=\"/26/on\"><button class=\"button\">ON</button></a>");
                                else client.println("<a href=\"/26/on\"><button class=\"button button2\">ON</button></a>");
                                if (_active_right) client.println("<a href=\"/27/on\"><button class=\"button\">ON</button></a>");
                                else client.println("<a href=\"/27/on\"><button class=\"button button2\">ON</button></a>");
                            }
                            client.println("</div>");
                        };

                        modeMenu("MODE 1", "MODE 2", true, false);
                        modeMenu("MODE 3", "MODE 4", false, false);
                        modeMenu("MODE 5", "MODE 6", false, false);
                        modeMenu("MODE ON", "MODE OFF", false, false);

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
        Serial.println("Client disconnected.");
        Serial.println("");
    }
}
