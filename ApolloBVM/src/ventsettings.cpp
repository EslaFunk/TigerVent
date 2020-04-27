#include "ventsettings.h"

char* abbreviatedOperationMode(OperatingMode operatingMode){
  switch(operatingMode){
    case VolumeControl:{
      return "VS";
    }
    case AssistControl:{
      return "AC";
    }
    case SynchronizedIntermittentMandatoryVentilation:{
      return "SIMV";
    }
  }
}
