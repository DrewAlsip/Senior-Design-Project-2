#include <Wire.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <TinyGPSPlus.h>

TinyGPSPlus gps;

#define GPS_BAUDRATE 9600
#define BT_BAUD 9600
#define RXD2 0
#define TXD2 1

Adafruit_ICM20948 imu;

void setup()
{
    Serial.begin(115200);

    // GPS
    Serial1.begin(GPS_BAUDRATE);
    Serial4.begin(BT_BAUD);

    // IMU
    Wire.begin();

    if (!imu.begin_I2C())
    {
        Serial.println("IMU not detected!");

        while (1)
        {
            delay(100);
        }
    }

    Serial.println("System Ready");
}

void loop()
{
    // Update GPS parser
    while (Serial1.available())
    {
        gps.encode(Serial1.read());
    }

    // Read IMU
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;
    sensors_event_t mag;

    imu.getEvent(
        &accel,
        &gyro,
        &temp,
        &mag
    );

    // Only send data if GPS has valid fix
    if (gps.location.isValid())
    {
       
      Serial.print(gps.location.lat(), 6);
      Serial4.print(gps.location.lat(), 6);
      Serial.print(",");
      Serial4.print(",");

      Serial.print(gps.location.lng(), 6);
      Serial4.print(gps.location.lng(), 6);
      Serial.print(",");
      Serial4.print(",");

      Serial.print(gps.altitude.meters());
      Serial4.print(gps.altitude.meters());
      Serial.print(",");
      Serial4.print(",");

      Serial.print(gps.satellites.value());
      Serial4.print(gps.satellites.value());
      Serial.print(",");
      Serial4.print(",");

      Serial.print(accel.acceleration.x);
      Serial4.print(accel.acceleration.x);
      Serial.print(",");
      Serial4.print(",");

      Serial.print(accel.acceleration.y);
      Serial4.print(accel.acceleration.y);
      Serial.print(",");
      Serial4.print(",");

      Serial.print(accel.acceleration.z);
      Serial4.print(accel.acceleration.z);
      Serial.print(",");
      Serial4.print(",");

      Serial.print(gyro.gyro.x);
      Serial4.print(gyro.gyro.x);
      Serial.print(",");
      Serial4.print(",");

      Serial.print(gyro.gyro.y);
      Serial4.print(gyro.gyro.y);
      Serial.print(",");
      Serial4.print(",");

      Serial.print(gyro.gyro.z);
      Serial4.print(gyro.gyro.z);
      Serial.print(",");
      Serial4.print(",");

      Serial.print(mag.magnetic.x);
      Serial4.print(mag.magnetic.x);
      Serial.print(",");
      Serial4.print(",");

      Serial.print(mag.magnetic.y);
      Serial4.print(mag.magnetic.y);
      Serial.print(",");
      Serial4.print(",");

      Serial.println(mag.magnetic.z);
      Serial4.println(mag.magnetic.z);
      delay(2000);
    }

}