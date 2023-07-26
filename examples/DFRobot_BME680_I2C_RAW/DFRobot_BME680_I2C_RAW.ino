#include "DFRobot_BME680_I2C.h"
#include "Wire.h"

// helper functions declarations
void printCalibrationData(void);

/* use an accurate altitude to calibrate sea level air pressure */
//#define CALIBRATE_PRESSURE

DFRobot_BME680_I2C bme(0x77);  //0x77 I2C address

float seaLevel;


void setup()
{
  uint8_t rslt = 1;
  Serial.begin(9600);
  while(!Serial);
  delay(1000);
  Serial.println();
  while(rslt != 0) {
    rslt = bme.begin();
    if(rslt != 0) {
      Serial.println("bme begin failure");
      delay(2000);
    }
  }
  Serial.println("bme begin successful");
  #ifdef CALIBRATE_PRESSURE
  bme.startConvert();
  delay(1000);
  bme.update();
  /*You can use an accurate altitude to calibrate sea level air pressure. 
   *And then use this calibrated sea level pressure as a reference to obtain the calibrated altitude.
   *In this case,525.0m is chendu accurate altitude.
   */
  seaLevel = bme.readSeaLevel(525.0);
  Serial.print("seaLevel :");
  Serial.println(seaLevel);
  #endif

  printCalibrationData();
}


void loop()
{
  bme.startConvert();
  delay(10000);
  bme.update();

  Serial.println();
  Serial.print("temperature(RAW / C) : ");
  Serial.print(bme.readTemperatureRAW());
  Serial.print(" : ");
  Serial.println(bme.readTemperature() / 100, 2);

  Serial.print("pressure(RAW / Pa) : ");
  Serial.print(bme.readPressureRAW());
  Serial.print(" : ");
  Serial.println(bme.readPressure());

  Serial.print("humidity(RAW / %rh) : ");
  Serial.print(bme.readHumidityRAW());
  Serial.print(" : ");
  Serial.println(bme.readHumidity() / 1000, 2);

  Serial.print("gas_resistance(RAW / ohm) : ");
  Serial.print(bme.readGasResistanceRAW());
  Serial.print(" : " );
  Serial.println(bme.readGasResistance());

  Serial.print("gas_range : ");
  Serial.println(bme.readGasRange());



  #ifdef CALIBRATE_PRESSURE
  Serial.print("altitude(m) :");
  Serial.println(bme.readAltitude());
  Serial.print("calibrated altitude(m) :");
  Serial.println(bme.readCalibratedAltitude(seaLevel));
  #endif
}


// helper function definitions
void printCalibrationData(void)
{
  bme680_calib_data calib_data;

  calib_data = bme.getCalibrationData();

  Serial.println();
  Serial.println("Calibration data ...");

  Serial.println("Temperature calibration data:");
  Serial.print("Temperature (par_t1) : ");
  Serial.println(calib_data.par_t1);
	Serial.print("Temperature (par_t2) : ");
  Serial.println(calib_data.par_t2);
  Serial.print("Temperature (par_t3) : ");
  Serial.println(calib_data.par_t3);

  Serial.println("Pressure calibration data:");
  Serial.print("Pressure (par_p1) : ");
  Serial.println(calib_data.par_p1);
  Serial.print("Pressure (par_p2) : ");
  Serial.println(calib_data.par_p2);
  Serial.print("Pressure (par_p3) : ");
  Serial.println(calib_data.par_p3);
  Serial.print("Pressure (par_p4) : ");
  Serial.println(calib_data.par_p4);
  Serial.print("Pressure (par_p5) : ");
  Serial.println(calib_data.par_p5);
  Serial.print("Pressure (par_p6) : ");
  Serial.println(calib_data.par_p6);
  Serial.print("Pressure (par_p7) : ");
  Serial.println(calib_data.par_p7);
  Serial.print("Pressure (par_p8) : ");
  Serial.println(calib_data.par_p8);
  Serial.print("Pressure (par_p9) : ");
  Serial.println(calib_data.par_p9);
  Serial.print("Pressure (par_p10) : ");
  Serial.println(calib_data.par_p10);

  Serial.println("Humidity calibration data:");
  Serial.print("Pressure (par_h1) : ");
  Serial.println(calib_data.par_h1);
  Serial.print("Pressure (par_h2) : ");
  Serial.println(calib_data.par_h2);
  Serial.print("Pressure (par_h3) : ");
  Serial.println(calib_data.par_h3);
  Serial.print("Pressure (par_h4) : ");
  Serial.println(calib_data.par_h4);
  Serial.print("Pressure (par_h5) : ");
  Serial.println(calib_data.par_h5);
  Serial.print("Pressure (par_h6) : ");
  Serial.println(calib_data.par_h6);
  Serial.print("Pressure (par_h7) : ");
  Serial.println(calib_data.par_h7);

  Serial.println("Gas calibration data:");
  Serial.print("Pressure (par_gh1) : ");
  Serial.println(calib_data.par_gh1);
  Serial.print("Pressure (par_gh2) : ");
  Serial.println(calib_data.par_gh2);
  Serial.print("Pressure (par_gh3) : ");
  Serial.println(calib_data.par_gh3);

  Serial.println("Misc calibration data:");
  Serial.print("Fine size (t_fine) : ");
  Serial.println(calib_data.t_fine);
  Serial.print("Heater resistance range (res_heat_range) : ");
  Serial.println(calib_data.res_heat_range);
  Serial.print("Heater resistance value (res_heat_val) : ");
  Serial.println(calib_data.res_heat_val);
  Serial.print("Error range (range_sw_err) : ");
  Serial.println(calib_data.range_sw_err);
}
