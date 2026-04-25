
#define RSI_PIN 9
#define SDA_PIN 10
#define MOSI_PIN 11
#define MISO_PIN 12
#define SCK_PIN 13

void setup() {
    pinMode(MOSI_PIN, OUTPUT);
    pinMode(MISO_PIN, INPUT);
    pinMode(SCK_PIN, OUTPUT);
    pinMode(SDA_PIN, OUTPUT);
    pinMode(RSI_PIN, INPUT);
}

void loop() {

}
