
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


int problem = 0;
long hrTime = 0;

uint32_t irBuffer[100]; //infrared LED sensor data
uint32_t redBuffer[100];  //red LED sensor data
int32_t bufferLength; //data length
int32_t spo2; //SPO2 value
int8_t validSPO2; //indicator to show if the SPO2 calculation is valid
int32_t heartRate; //heart rate value
int8_t validHeartRate; //indicator to show if the heart rate calculation is valid
char c;

long irValue;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");

  particleSensor.begin(Wire, I2C_SPEED_FAST);

}

void loop() {
  if (Serial.available())
  {
    c = Serial.read();
    if (c == 'h') {
      if (state == 1)
        state = 0;
      else
        state = 1;
    }
    else if (c == 's') {
      if (state == 1)
        state = 0;
      else
        state = 2;
    }
  }

  if (oldState != state) {
    oldState = state;
    switch (state) {
      case NONE:
        Serial.println("Select an option: (h=HR, s=SpO2");
        break;

      case PLOT_IRVALUE:
        particleSensor.setup(); //Configure sensor with default settings
        particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
        particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
        break;

      case SPO2:
        byte ledBrightness = 60; //Options: 0=Off to 255=50mA
        byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
        byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
        byte sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
        int pulseWidth = 411; //Options: 69, 118, 215, 411
        int adcRange = 4096; //Options: 2048, 4096, 8192, 16384

        particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings


        Serial.println("Init");

        bufferLength = 100;

        //read the first 100 samples, and determine the signal range
        for (byte i = 0 ; i < bufferLength ; i++)
        {
          while (particleSensor.available() == false) //do we have new data?
            particleSensor.check(); //Check the sensor for new data

          redBuffer[i] = particleSensor.getRed();
          irBuffer[i] = particleSensor.getIR();
          particleSensor.nextSample(); //We're finished with this sample so move to next sample
        }
        //calculate heart rate and SpO2 after first 100 samples (first 4 seconds of samples)
        maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
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
        Serial.println("Place finger on sensor");
      }
      else
      {
        if (problem == 1)
          problem = 0;

        if (millis() - hrTime > 500) {
          hrTime = millis();
          if (beatsPerMinute < 255 && beatsPerMinute > 20) {
            char bpm[50];
            sprintf(bpm, "HR = %.0f   AVG_HR = %d", beatsPerMinute, beatAvg);
            Serial.println(bpm);
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
        while (particleSensor.available() == false) //do we have new data?
          particleSensor.check(); //Check the sensor for new data

        redBuffer[i] = particleSensor.getRed();
        irBuffer[i] = particleSensor.getIR();

        particleSensor.nextSample(); //We're finished with this sample so move to next sample

        if (millis() - hrTime > 1000)
        {
          hrTime = millis();
          char ox[15];

          if (validSPO2 == 1) {
            sprintf(ox, "SpO2 = -");
          }
          else {
            sprintf(ox, "SpO2 = %d", spo2);
          }

          Serial.println(ox);
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
