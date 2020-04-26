#include "panel.h"
#include "Wire.h"
#include "buzzeralarmmanager.h"
#include "nscdrrn001pdunv.h"

// Address of slave.
#define SLAVE_ADDR 8

// Pin definitions.
#define DISPLAY_PIN 3
#define ENC_CLK_PIN 6
#define ENC_DT_PIN 5
#define ENC_BUTTON_PIN 7
#define STOP_BUTTON_PIN 11
#define PRESSURE_SENSOR_PIN A0
#define BUZZER_PIN 2
#define PRESSURE_CONVERSION_MULTIPLIER 0.169618
#define PRESSURE_CONVERSTION_CONSTANT -71.3247129


Buzzer buzzer(BUZZER_PIN);
// Init peripherals.
Nscdrrn001pdunv pressure_sensor(PRESSURE_SENSOR_PIN, PRESSURE_CONVERSION_MULTIPLIER, PRESSURE_CONVERSTION_CONSTANT);
Lcd2004 display(DISPLAY_PIN);
Encoder enc(ENC_DT_PIN, ENC_CLK_PIN);
ButtonManager encoder_button(ENC_BUTTON_PIN, true);
ButtonManager stop_button(STOP_BUTTON_PIN, false);

// Default settings.
VentSettings vs = {'X', 500, 12, 1, 3, 0, 00, 20, 0, 0, 0, false}; 

// Default limits.
VentLimits vl;

// Calibration for TV on Ambu bag SPUR II.
int cal[9] = {950, 1062, 1155, 1238, 1320, 1393, 1465, 1538, 1610};

// String params for splash screens.
String* splash_text = new String[4];
String* warning_text = new String[4];
String* alarm_text = new String[4];

// Init panel pointers.
SplashPanel* splash_ptr;
SplashPanel* warning_ptr;
AlarmPanel* alarm_ptr;
EditPanel* start_ptr;
EditPanel* apply_ptr;
RunningPanel* run_ptr;
PausePanel* pause_ptr;

// Init display panel pointer.
Panel* cur_panel;

void setup()
{

  // Join i2c bus.
  Wire.begin();

  // Start serial debug connection.
//  Serial.begin(9600);

  // Start display.
  display.begin(9600);
  display.clearDisplay();

  // Init slash text.
  splash_text[0] = "    LSU TigerVent   ";
  splash_text[1] = " ";
  splash_text[2] = "    inspired by";
  splash_text[3] = "     ApolloBVM";

  //Init warning text.
  warning_text[0] = "      WARNING: ";
  warning_text[1] = "   USE ADULT SIZED";
  warning_text[2] = "   BAG VALVE MASK";
  warning_text[3] = "";

  //Init alarm text.
  alarm_text[0] = "      ALARM: ";
  alarm_text[1] = "   OVER PRESSURE";
  alarm_text[2] = "   BAG VALVE MASK";
  alarm_text[3] = "";


  // Init panels.
  start_ptr = new EditPanel(&display, &enc, &encoder_button, &stop_button, &vs, &vl, "Confirm & Run?", &run_ptr, 0);
  warning_ptr = new SplashPanel(&display, &enc, &encoder_button, &stop_button, &vs, warning_text, 2000, &start_ptr);
  splash_ptr = new SplashPanel(&display, &enc, &encoder_button, &stop_button, &vs, splash_text, 2000, &warning_ptr);
  alarm_ptr = new AlarmPanel(&display, &enc, &encoder_button, &stop_button, &vs, &pause_ptr, &buzzer) :
  apply_ptr = new EditPanel(&display, &enc, &encoder_button, &stop_button, &vs, &vl, "Apply Changes?", &run_ptr, &pause_ptr);
  run_ptr = new RunningPanel(&display, &enc, &encoder_button, &stop_button, &vs, &apply_ptr, &pause_ptr, &pressure_sensor, alarm_ptr );
  pause_ptr = new PausePanel(&display, &enc, &encoder_button, &stop_button, &vs, &start_ptr, &run_ptr);

  // Delay just cause.
  delay(100);

  // Set current panel to splash.
  cur_panel = splash_ptr;
  cur_panel->start();

}

void loop()
{

  // //if an alarm is on, continue
  // alarmManager.update();
    
  // }
  // if(pressure_sensor.read() > 40){
  //   alarm = HighPressureAlarm;
  // }
  // Poll button status.
  encoder_button.poll();
  stop_button.poll();

  // Update current panel.
  Panel* new_panel = cur_panel->update();

  // If we get a new panel, start and switch to it.
  if (new_panel != 0) {
    cur_panel = new_panel;
    cur_panel->start();
  }

  // Transmit to the device if necessary.
  if (vs.send)
    transmit();
}

void transmit() {

  // Transmit to the slave device.
  Wire.beginTransmission(SLAVE_ADDR);

  // Write the mode first.
  Wire.write(vs.mode);

  // Send settings to controller unit, if we're loading.
  if (vs.mode == 'L') {
    // Calculate setpoint based on calibration.
    int setpoint = cal[(vs.tidal_volume - vl.min_tidal_volume)/vl.delta_tidal_volume];

    // Send the ventilation parameters to slave.
    Wire.write(byte(setpoint >> 8));
    Wire.write(byte(setpoint & 0x00FF));
    Wire.write(byte(vs.respiration_rate));
    Wire.write(byte(vs.inhale));
    Wire.write(byte(vs.exhale));
    Wire.write(byte(vs.hold_seconds));
    Wire.write(byte(vs.hold_decimals));
    Wire.write(byte(vs.delta_time));

    // Set the mode to on as device will start.
    vs.mode = 'O';
  }

  // Send i2c message.
  Wire.endTransmission();

  // Sent settings so disable send.
  vs.send = false;
}

