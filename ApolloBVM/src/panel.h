#ifndef panel_h
#define panel_h

#include "buttonmanager.h"
#include "encodermanager.h"
#include "lcd2004.h"
#include "nscdrrn001pdunv.h"
#include "buzzer.h"
//#include "nhd_0420d3z.h"
#include "ventsettings.h"
#include "Encoder.h"

class Panel {
  public:

    Panel(Lcd2004* disp_ptr, Encoder* encoder_ptr, ButtonManager* em_button_ptr, ButtonManager* stop_button_ptr, VentSettings* vs_ptr, Nscdrrn001pdunv* pressure_ptr);

    // Virtual methods for each panel to inherit.
    virtual void start() = 0;
    virtual Panel* update() = 0;

  protected:


    // Pointers for settings and input.
    Lcd2004* _disp_ptr;
    Nscdrrn001pdunv* _pressure_ptr;
    //BuzzerAlarmManager* _alarm_manager_ptr;

    Encoder* _encoder_ptr;
    ButtonManager* _em_button_ptr;
    ButtonManager* _stop_button_ptr;
    
    // Pointers for system setting.
    VentSettings* _vs_ptr;


};

class SplashPanel : public Panel {
  public:
    SplashPanel(Lcd2004* disp_ptr, Encoder* encoder_ptr, ButtonManager* em_button_ptr, ButtonManager* stop_button_ptr, VentSettings* vs_ptr, String* text, int display_time, Panel** next_ptr);

    // Panel to display splash text for a specified amout of time.
    void start();
    Panel* update();

  private:
    
    // Number of miliseconds to display text for.
    int _display_time;

    // Pointer to 4 element string array with text to display.
    String* _text;

    // Pointer and double pointer to next panel.
    Panel** _next_d_ptr;
    Panel* _next_ptr;

};

enum AlarmType {HighPressureAlarm, LowPressureAlarm, NoAlarm};

class AlarmPanel : public Panel {
  public:
    AlarmPanel(Lcd2004* disp_ptr, Encoder* encoder_ptr, ButtonManager* em_button_ptr, ButtonManager* stop_button_ptr, VentSettings* vs_ptr, String* text, Panel** next_ptr, Buzzer * buzzer_ptr);

    // Panel to display splash text for a specified amout of time.
    void start();
    Panel* update();
    void setAlarmType(AlarmType alarmType);

  private:
    // Pointer to 4 element string array with text to display.
    String* _text  = new String[4];
    Buzzer * _buzzer_ptr;
    AlarmType _alarmType = NoAlarm;
    // Pointer and double pointer to next panel.
    Panel** _next_d_ptr;
    Panel* _next_ptr;

};

class EditPanel : public Panel {
  public:
    EditPanel(Lcd2004* disp_ptr, Encoder* encoder_ptr, ButtonManager* em_button_ptr, ButtonManager* stop_button_ptr, VentSettings* vs_ptr, VentLimits* vl_ptr, String top_text, Panel** run_panel_ptr, Panel** stop_panel_ptr);


    // Panel to edit ventilator parameters.
    void start();
    Panel* update();

  private:

    // Pointer to encoder manager for this edit panel.
    EncoderManager* _em_ptr;

    // String for the top line of text.
    String _top_text;
    
    // Text to show for tidal volume.
    String _tv_text = "TV:";
    int _tv_text_length = 3;
    String _tv_units = "mL";

    // Text to show for respiratory rate.
    String _rr_text = "RR:";
    int _rr_text_length = 3;
    String _rr_units = "BPM";

    // Text to show for I:E ratio.
    String _i_e_text = "I/E:";
    int _i_e_text_length = 6;

    // Pointers to other panels.
    Panel** _run_panel_d_ptr;
    Panel** _stop_panel_d_ptr;
    Panel* _run_panel_ptr;
    Panel* _stop_panel_ptr;

    // Pointer to ventilator setting limits.
    VentLimits* _vl_ptr;

    // Holds which row is currently being selected.
    int _row = 0;

    // Holds if we are in edit mode or not.
    bool _edit = false;

    // Old selection to detect changes made.
    int _old_selection = 0;

    // Bool to hold if changes were made.
    bool _made_change = false;
};

class RunningPanel : public Panel {
  public:
    RunningPanel(Lcd2004* disp_ptr, Encoder* encoder_ptr, ButtonManager* em_button_ptr, ButtonManager* stop_button_ptr, VentSettings* vs_ptr, Panel** apply_panel_ptr, Panel** stop_panel_ptr, Nscdrrn001pdunv* pressure_ptr, AlarmPanel* alarm_panel_ptr);

    // Panel to display current time counter and current settings.
    void start();
    Panel* update();

    String formatTime();

  private:

    // Pointers to other panels.
    Panel** _apply_panel_d_ptr;
    Panel** _stop_panel_d_ptr;
    //Panel** _alarm_panel_d_ptr;
    Panel* _apply_panel_ptr;
    Panel* _stop_panel_ptr;
    AlarmPanel* _alarm_panel_ptr;
    // String for the top line of text.
    String _top_text = "Run Time: ";
    int _text_length_to_time = 10;

    // Text to show for tidal volume.
    String _tv_text = "TV:";
    String _tv_units = "mL";

    // Text to show for respiratory rate.
    String _rr_text = "RR:";
    String _rr_units = "BPM";

    // Text to show for I:E ratio.
    String _i_e_text = "I/E:";

    int _text_length_to_pressure = 12;
};

class PausePanel : public Panel {
  public:
    PausePanel(Lcd2004* disp_ptr, Encoder* encoder_ptr, ButtonManager* em_button_ptr, ButtonManager* stop_button_ptr, VentSettings* vs_ptr, Panel** apply_panel_ptr, Panel** run_panel_ptr);

    // Panel to display time ventilated and settings during pause.
    void start();
    Panel* update();

  private:

    // Pointer to encoder manager for this edit panel.
    EncoderManager* _em_ptr;

    // Pointers to other panels.
    Panel** _apply_panel_d_ptr;
    Panel** _run_panel_d_ptr;
    Panel* _apply_panel_ptr;
    Panel* _run_panel_ptr;

    // String for top line with time and selection.
    String _top_before_time = "T";
    String _top_after_time = " Run/Edit?";
    int _text_length_to_run = 11;
    int _text_length_to_edit = 15;

    // Text to show for tidal volume.
    String _tv_text = "TV = ";
    String _tv_units = " mL";

    // Text to show for respiratory rate.
    String _rr_text = "RR = ";
    String _rr_units = " BPM";

    // Text to show for I:E ratio.
    String _i_e_text = "I:E = ";

    // Current selection of whether to run or edit.
    int _selection = 0;
};


#endif
