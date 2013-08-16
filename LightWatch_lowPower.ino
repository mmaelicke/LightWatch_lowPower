/* LightWatch_lowPower Arduino - Sketch
 * Main sketch to run HydroStation hydrological measuring device
 *  - Light intensity configuration - 
 * Upload to your Arduino - based Station
 * More information under http:openhydro.org
 *
 * This file is part of LightWatch Package, 
 * containing files of HydroStation Package 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * author: Mirko Maelicke
 *
 * This software includes several other libaries or files, which may not be
 * published under GPL 3.0. All rights belong to their respective owners.
 * This applies to: "LowPower.h", "RTClib.h", "SdFat.h"
 */

/*include libaries*/ 
#include <Wire.h>
#include "LowPower.h"
#include "RTClib.h"

#include <SdFat.h>

int const len = 5;
int Data[len];
/* 0 -5 are the connected Light Sensors */

RTC_DS1307 RTC;
DateTime now;

long timestep = 60;    //in seconds
long duration = 0;

void setup(){
  Wire.begin();
 
  for (int i = 0; i < len; i++){
    Data[i] = 0;
  }
  
  setup_RTC();
  setup_Sd();
}

void loop(){
  delay(10);
  now = RTC.now();
  for (int i = 0; i < len; i++){
    Data[i] = analogRead(i);
  }
  
  printSdData();
  
  while(duration < timestep){
    LowPower.powerDown(SLEEP_8S,ADC_OFF,BOD_OFF);
    duration += 8;
  }
  duration = 0;
}




