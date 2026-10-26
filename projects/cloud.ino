#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <DHT.h>

// Wi-Fi credentials
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// Firebase project credentials
#define API_KEY "YOUR_FIREBASE_API_KEY"
#define DATABASE_URL "https://YOUR_PROJECT-default-rtdb.firebaseio.com"  // No trailing slash

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// DHT sensor config
#define DHTTYPE DHT11
#define NUM_SENSORS 4
uint8_t dhtPins[NUM_SENSORS] = {15, 4, 16, 17};  
DHT* dhtSensors[NUM_SENSORS];

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Initializing DHT sensors and Wi-Fi...");

  // Initialize DHT sensors
  for (int i = 0; i < NUM_SENSORS; i++) {
    dhtSensors[i] = new DHT(dhtPins[i], DHTTYPE);
    dhtSensors[i]->begin();
  }

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Connected to Wi-Fi!");

  // Set Firebase config
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // Anonymous authentication
  auth.user.email = "";
  auth.user.password = "";

  // Sign up anonymously
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("✅ Firebase anonymous sign-up successful.");
  } else {
    Serial.printf("❌ Firebase sign-up failed: %s\n", config.signer.signupError.message.c_str());
  }

  // Initialize Firebase
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("✅ Firebase initialized.");
}

void loop() {
  Serial.println("🔄 Reading DHT sensors...");

  for (int i = 0; i < NUM_SENSORS; i++) {
    float temp = dhtSensors[i]->readTemperature();
    float hum = dhtSensors[i]->readHumidity();

    String basePath = "/sensor" + String(i + 1);

    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(" - Temp: ");
    Serial.print(temp);
    Serial.print(" °C, Humidity: ");
    Serial.print(hum);
    Serial.println(" %");

    if (isnan(temp) || isnan(hum)) {
      Serial.println("❌ Failed to read from DHT" + String(i + 1));
      continue;
    }

    // Send temperature
    if (Firebase.RTDB.setFloat(&fbdo, basePath + "/temperature", temp)) {
      Serial.println("✅ Temperature sent to Firebase");
    } else {
      Serial.print("❌ Failed to send temperature: ");
      Serial.println(fbdo.errorReason());
    }

    // Send humidity
    if (Firebase.RTDB.setFloat(&fbdo, basePath + "/humidity", hum)) {
      Serial.println("✅ Humidity sent to Firebase");
    } else {
      Serial.print("❌ Failed to send humidity: ");
      Serial.println(fbdo.errorReason());
    }

    Serial.println("-----------------------------------");
  }

  delay(5000);  // Delay before next read
}
