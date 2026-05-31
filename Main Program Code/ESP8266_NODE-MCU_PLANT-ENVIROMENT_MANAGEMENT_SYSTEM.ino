#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

// Wi-Fi credentials
const char* ssid = "TP Link C64";
const char* password = "Netgear@shihab1209";

// Admin login credentials
const String adminUser = "Admin";
const String adminPass = "1234";

// Relay and buzzer pins
#define RELAY1 D1  // GPIO5
#define RELAY2 D2  // GPIO4
#define RELAY3 D5  // GPIO14
#define RELAY4 D6  // GPIO12
#define BUZZER  D7  // GPIO13

bool relayState[4] = {false, false, false, false};
int relayPins[4] = {RELAY1, RELAY2, RELAY3, RELAY4};

// Buzzer config (ms and Hz)
const int shortBeep = 50;
const int longBeep = 90;
const int wifiBeep = 50;
const int gap = 50;

const int defaultFreq = 1900;
const int loginFreq = 2000;
const int allRelayFreq = 2100;
const int eachRelayFreq = 1900;
const int failFreq = 1800;
const int powerOnFreq = 2100;

AsyncWebServer server(80);

void beep(int duration, int freq) {
  tone(BUZZER, freq);
  delay(duration);
  noTone(BUZZER);
}

void multiBeep(int count, int duration, int gap, int freq) {
  for (int i = 0; i < count; i++) {
    beep(duration, freq);
    delay(gap);
  }
}

void failedBeep() {
  for (int i = 0; i < 6; i++) {
    beep(50, 1800);  // 30ms, 500Hz
    delay(50);
  }
}

void setup() {
  Serial.begin(115200);

  // Set pin modes
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH);
  }
  pinMode(BUZZER, OUTPUT);

  // Startup beep
  multiBeep(3, shortBeep, gap, powerOnFreq);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  multiBeep(3, wifiBeep, gap, wifiBeep);

  // Login endpoint
  server.on("/login", HTTP_GET, [](AsyncWebServerRequest *request) {
    String u = request->getParam("u")->value();
    String p = request->getParam("p")->value();
    if (u == adminUser && p == adminPass) {
      Serial.println("Admin logged in.");
      multiBeep(2, shortBeep, gap, loginFreq);
      request->send(200, "text/plain", "OK");
    } else {
      Serial.println("Login failed.");
      failedBeep();
      request->send(200, "text/plain", "FAIL");
    }
  });

  // Relay control endpoint
  server.on("/relay", HTTP_GET, [](AsyncWebServerRequest *request) {
    int id = request->getParam("id")->value().toInt();
    String action = request->getParam("state")->value();
    String status = "";

    if (id == 0) {
      bool turnOn = (action == "on");
      for (int i = 0; i < 4; i++) {
        relayState[i] = turnOn;
        digitalWrite(relayPins[i], turnOn ? LOW : HIGH);
      }
      status = turnOn ? "All ON" : "All OFF";
      beep(longBeep, allRelayFreq);
    } else if (id >= 1 && id <= 4) {
      int idx = id - 1;
      relayState[idx] = (action == "on");
      digitalWrite(relayPins[idx], relayState[idx] ? LOW : HIGH);
      status = relayState[idx] ? "Relay ON" : "Relay OFF";
      beep(shortBeep, eachRelayFreq);
    }
    Serial.printf("Relay %d set to %s\n", id, status.c_str());
    request->send(200, "text/plain", status);
  });

  // Web UI
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send_P(200, "text/html", R"rawliteral(
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <title>Plant Environment Management System</title>

    <style>
      body {
        font-family: "Segoe UI", sans-serif;
        margin: 0;
        padding: 0;
        text-align: center;
        transition:
          background-color 0.3s,
          color 0.3s;
      }

      body.dark-mode {
        background-color: #121212;
        color: #ffffff;
      }

      body.light-mode {
        background-color: #f0f0f0;
        color: #000000;
      }

      h2 {
        margin-top: 40px;
      }

      #login {
        margin-top: 80px;
      }

      #panel {
        display: none;
        margin-top: 40px;
      }

      button {
        padding: 12px 20px;
        margin: 5px;
        font-size: 16px;
        background-color: #1e1e1e;
        color: #fff;
        border: 1px solid #444;
        border-radius: 6px;
        transition: background-color 0.3s ease;
        cursor: pointer;
      }

      body.light-mode button {
        background-color: #e0e0e0;
        color: #000;
        border: 1px solid #aaa;
      }

      button:hover {
        background-color: #333;
      }

      body.light-mode button:hover {
        background-color: #ccc;
      }

      input {
        padding: 10px;
        margin: 5px;
        font-size: 16px;
        border-radius: 6px;
        border: 1px solid #444;
        background-color: #1e1e1e;
        color: #fff;
      }

      body.light-mode input {
        background-color: #fff;
        color: #000;
        border: 1px solid #aaa;
      }

      /* Floating Input Style */
      .input-box {
        position: relative;
        width: 260px;
        margin: 14px auto;
      }

      .input-box input {
        width: 100%;
        padding: 14px 10px 10px;
        font-size: 16px;
        border-radius: 6px;
        border: 1px solid #444;
        background-color: #1e1e1e;
        color: #fff;
        outline: none;
        box-sizing: border-box;
      }

      body.light-mode .input-box input {
        background-color: #fff;
        color: #000;
        border: 1px solid #aaa;
      }

      .input-box label {
        position: absolute;
        left: 12px;
        top: 13px;
        color: #888
        font-size: 16px;
        pointer-events: none;
        transition: 0.25s ease;
      }

      .input-box input:focus + label,
      .input-box input:not(:placeholder-shown) + label {
        top: -5px;
        left: 10px;
        font-size: 12px;
        padding: 0 4px;
        background-color: #121212;
        color: #00bfff;
      }

      body.light-mode .input-box input:focus + label,
      body.light-mode .input-box input:not(:placeholder-shown) + label {
        background-color:  #f0f0f0;
        color: #0077cc;
      }

      .input-box input:focus {
        border-color: #00bfff;
      }

      .card {
        display: inline-block;
        margin: 10px;
        padding: 15px;
        border-radius: 10px;
        width: 250px;
        background-color: #1e1e1e;
        border: 1px solid #444;
        box-shadow: 0 0 15px rgba(255, 255, 255, 0.05);
      }

      body.light-mode .card {
        background-color: #ffffff;
        border: 1px solid #aaa;
        box-shadow: 0 0 15px rgba(0, 0, 0, 0.05);
      }

      .footer {
        margin-top: 100px;
        padding: 20px;
        font-size: 14px;
        color: #aaa;
      }

      body.light-mode .footer {
        color: #333;
      }

      .footer b {
        color: #fff;
      }

      body.light-mode .footer b {
        color: #000;
      }

      #modeToggle {
        position: fixed;
        top: 10px;
        right: 10px;
        padding: 8px 14px;
        font-size: 14px;
        border-radius: 6px;
        border: 1px solid #444;
        background-color: #1e1e1e;
        color: #fff;
        cursor: pointer;
        transition: background-color 0.3s ease;
        z-index: 9999;
      }

      body.light-mode #modeToggle {
        background-color: #e0e0e0;
        color: #000;
        border: 1px solid #aaa;
      }

      #modeToggle:hover {
        background-color: #333;
      }

      body.light-mode #modeToggle:hover {
        background-color: #ccc;
      }
    </style>
  </head>

  <body>
    <button id="modeToggle" onclick="toggleMode()">🌓</button>

    <div id="login">
      <h2>Plant Environment Management System</h2>

      <div class="input-box">
        <input
          type="text"
          id="user"
          placeholder=" "
          autocomplete="username"
          required
        />
        <label for="user">Username</label>
      </div>

      <div class="input-box">
        <input
          type="password"
          id="pass"
          placeholder=" "
          autocomplete="current-password"
          required
        />
        <label for="pass">Password</label>
      </div>

      <button onclick="auth()">Login</button>
    </div>

    <div id="panel">
      <h2>🍀Environmental Activation System</h2>

      <div class="card">
        <h3>All Functions</h3>
        <button onclick="toggle(0, 'on')">ON</button>
        <button onclick="toggle(0, 'off')">OFF</button>
      </div>

      <div class="card">
        <h3>Plant Light-01</h3>
        <button onclick="toggle(1, 'on')">ON</button>
        <button onclick="toggle(1, 'off')">OFF</button>
      </div>

      <div class="card">
        <h3>Plant Light-02</h3>
        <button onclick="toggle(2, 'on')">ON</button>
        <button onclick="toggle(2, 'off')">OFF</button>
      </div>

      <div class="card">
        <h3>Air Humidifier</h3>
        <button onclick="toggle(3, 'on')">ON</button>
        <button onclick="toggle(3, 'off')">OFF</button>
      </div>

      <div class="card">
        <h3>Water Supply</h3>
        <button onclick="toggle(4, 'on')">ON</button>
        <button onclick="toggle(4, 'off')">OFF</button>
      </div>
    </div>

    <div class="footer">
      <b>🍀iOT Plant Environment Management System [PEMS]</b><br />
      Open Source Prototype Developed and Designed by<br />
      <b>Md. Shihab Sikder</b><br /><br />
      Server : ESP8266 Node Micro Controller Unit | Ver: 3.0<br />
      Route : Home Network | Wi-Fi 2.4Ghz📶<br />
      Access : http://192.168.0.166<br /><br />
      V 1.0
    </div>

    <script>
      function auth() {
        let u = document.getElementById("user").value;
        let p = document.getElementById("pass").value;

        fetch(`/login?u=${u}&p=${p}`)
          .then((res) => res.text())
          .then((txt) => {
            if (txt === "OK") {
              document.getElementById("login").style.display = "none";
              document.getElementById("panel").style.display = "block";
            } else {
              alert("Unauthorized credentials!");
            }
          });
      }

      function toggle(id, state) {
        fetch(`/relay?id=${id}&state=${state}`)
          .then((res) => res.text())
          .then((status) => console.log(`Switch ${id} is now ${status}`));
      }

      function toggleMode() {
        if (document.body.classList.contains("dark-mode")) {
          document.body.classList.remove("dark-mode");
          document.body.classList.add("light-mode");
          localStorage.setItem("theme", "light");
        } else {
          document.body.classList.remove("light-mode");
          document.body.classList.add("dark-mode");
          localStorage.setItem("theme", "dark");
        }
      }

      window.onload = () => {
        const savedTheme = localStorage.getItem("theme") || "dark";
        document.body.classList.add(savedTheme);
      };
    </script>
  </body>
</html>
  )rawliteral");
});


  server.begin();
}

void loop() {
  // Nothing here
}
