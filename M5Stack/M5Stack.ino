#include <M5Stack.h>

#include "MAX30105.h"
#include "heartRate.h"
#include "spo2_algorithm.h"

#define NONE         0
#define PLOT_IRVALUE 1
#define SPO2         2
#define HRV          3


#define MAX_BRIGHTNESS 255

MAX30105 particleSensor;

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

int state = NONE;
int oldState = -1;

int val;
int oldVal = 0;
int cont = 0;
int minimo = -1, massimo = -1;
int currentMinimo, currentMassimo;
int problem = 0;
long hrTime = 0;

uint32_t irBuffer[100]; //infrared LED sensor data
uint32_t redBuffer[100];  //red LED sensor data
int32_t bufferLength; //data length
int32_t spo2; //SPO2 value
int8_t validSPO2; //indicator to show if the SPO2 calculation is valid
int32_t heartRate; //heart rate value
int8_t validHeartRate; //indicator to show if the heart rate calculation is valid

long irValue;

void setup()
{
  Serial.begin(115200);
  Serial.println("Initializing...");

  M5.begin();
  M5.Power.begin();
  M5.Lcd.fillScreen(BLACK);
  drawMenu();
  particleSensor.begin(Wire, I2C_SPEED_FAST);
}

void loop()
{
  M5.update();
  if (M5.BtnA.wasPressed()) {
    if (state == 1)
      state = 0;
    else
      state = 1;
  }
  if (M5.BtnB.wasPressed()) {
    if (state == 1)
      state = 0;
    else
      state = 2;
  }
  if (M5.BtnC.wasPressed()) {
    M5.powerOFF();
  }

  if (oldState != state) {
    M5.Lcd.fillScreen(BLACK);
    drawMenu();
    oldState = state;
    //Configure
    switch (state) {
      case NONE:
        M5.Lcd.setCursor(50, 100);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.setTextSize(2);
        M5.Lcd.printf("Select an option");
        break;

      case PLOT_IRVALUE:
        particleSensor.setup(); //Configure sensor with default settings
        particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
        particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
        minimo = -1;
        currentMinimo = minimo;
        massimo = -1;
        currentMassimo = massimo;
        break;

      case SPO2:
        byte ledBrightness = 60; //Options: 0=Off to 255=50mA
        byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
        byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
        byte sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
        int pulseWidth = 411; //Options: 69, 118, 215, 411
        int adcRange = 4096; //Options: 2048, 4096, 8192, 16384

        particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings

        M5.Lcd.setCursor(100, 100);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.setTextSize(2);
        M5.Lcd.printf("Init");

        bufferLength = 100;

        //read the first 100 samples, and determine the signal range
        for (byte i = 0 ; i < bufferLength ; i++)
        {
          if (M5.BtnB.wasPressed()) {
            if (state == 1)
              state = 0;
            else
              state = 2;
          }
          if (M5.BtnC.wasPressed()) {
            M5.powerOFF();
          }
          while (particleSensor.available() == false) //do we have new data?
            particleSensor.check(); //Check the sensor for new data

          redBuffer[i] = particleSensor.getRed();
          irBuffer[i] = particleSensor.getIR();
          particleSensor.nextSample(); //We're finished with this sample so move to next sample
        }
        //calculate heart rate and SpO2 after first 100 samples (first 4 seconds of samples)
        maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
        M5.Lcd.fillScreen(BLACK);
        drawMenu();
        break;
    }
  }

  switch (state) {
    case NONE:
      break;

    case PLOT_IRVALUE:
      irValue = particleSensor.getIR();
      if (checkForBeat(irValue) == true)
      {
        //We sensed a beat!
        long delta = millis() - lastBeat;
        lastBeat = millis();

        beatsPerMinute = 60 / (delta / 1000.0);

        if (beatsPerMinute < 255 && beatsPerMinute > 20)
        {
          rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
          rateSpot %= RATE_SIZE; //Wrap variable

          //Take average of readings
          beatAvg = 0;
          for (byte x = 0 ; x < RATE_SIZE ; x++)
            beatAvg += rates[x];
          beatAvg /= RATE_SIZE;
        }
      }


      if (irValue < 50000) {
        problem = 1;
        M5.Lcd.setCursor(10, 100);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.setTextSize(2);
        M5.Lcd.printf("Place finger on sensor");
      }
      else
      {
        if (problem == 1) {
          M5.Lcd.fillScreen(BLACK);
          drawMenu();
          problem = 0;
        }

        val = map(irValue, currentMinimo, currentMassimo, 0, 160);
        if (val > 160)
          val = 160;
        if ((minimo == -1) || (irValue < minimo))
          minimo = irValue;
        if ((massimo == -1) || (irValue > massimo))
          massimo = irValue;
        M5.Lcd.drawLine(cont, oldVal, cont + 1, val, RED);
        cont = cont + 2;
        if (cont >= 320) {
          currentMinimo = minimo - 100;
          currentMassimo = massimo + 100;
          minimo = -1;
          massimo = -1;
          cont = 0;
          M5.Lcd.fillRect(0, 0, 320, 180, BLACK);
          drawMenu();
        }
        oldVal = val;
        if (millis() - hrTime > 500) {
          hrTime = millis();
          if (beatsPerMinute < 255 && beatsPerMinute > 20) {
            M5.Lcd.fillRect(0, 180, 320, 200, BLACK);
            drawMenu();
            M5.Lcd.setCursor(10, 180);
            M5.Lcd.setTextColor(WHITE);
            char bpm[50];
            sprintf(bpm, "HR = %.0f   AVG_HR = %d", beatsPerMinute, beatAvg);
            M5.Lcd.printf(bpm);
          }
        }
      }
      break;

    case SPO2:
      //dumping the first 25 sets of samples in the memory and shift the last 75 sets of samples to the top
      for (byte i = 25; i < 100; i++)
      {
        redBuffer[i - 25] = redBuffer[i];
        irBuffer[i - 25] = irBuffer[i];
      }

      //take 25 sets of samples before calculating the heart rate.
      for (byte i = 75; i < 100; i++)
      {
        if (M5.BtnB.wasPressed()) {
          if (state == 1)
            state = 0;
          else
            state = 2;
        }
        if (M5.BtnC.wasPressed()) {
          M5.powerOFF();
        }
        while (particleSensor.available() == false) //do we have new data?
          particleSensor.check(); //Check the sensor for new data

        redBuffer[i] = particleSensor.getRed();
        irBuffer[i] = particleSensor.getIR();

        particleSensor.nextSample(); //We're finished with this sample so move to next sample

        if (millis() - hrTime > 1000)
        {
          hrTime = millis();
          M5.Lcd.fillRect(0, 0, 320, 200, BLACK);
          drawMenu();
          M5.Lcd.setTextSize(3);
          char ox[15];
          
          if (validSPO2 == 1){
            M5.Lcd.setTextColor(GREEN);
            sprintf(ox, "SpO2 = -");
          }
          else{
            M5.Lcd.setTextColor(RED);
            sprintf(ox, "SpO2 = %d", spo2);
          }
          M5.Lcd.setCursor(50, 75);
          M5.Lcd.printf(ox);
          /*
            sprintf(ox, "HR = %d",heartRate);
            M5.Lcd.setCursor(50, 125);
            if (validHeartRate == 1)
            M5.Lcd.setTextColor(GREEN);
            else
            M5.Lcd.setTextColor(RED);
            M5.Lcd.printf(ox);
          */
        }

      }

      //After gathering 25 new samples recalculate HR and SP02
      maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
      break;


  }
}

void drawMenu() {

  M5.Lcd.fillRect(0, 210, 320, 240, BLUE);
  M5.Lcd.setCursor(50, 220);
  if (state != 1)
    M5.Lcd.setTextColor(WHITE);
  else
    M5.Lcd.setTextColor(RED);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("HR");
  M5.Lcd.setCursor(140, 220);
  if (state != 2)
    M5.Lcd.setTextColor(WHITE);
  else
    M5.Lcd.setTextColor(RED);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("SpO2");
  M5.Lcd.setCursor(240, 220);
  if (state != 3)
    M5.Lcd.setTextColor(WHITE);
  else
    M5.Lcd.setTextColor(RED);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("OFF");
}
