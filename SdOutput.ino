/* This file is part of HydroStation Package
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
 */
 
int SdPin = 10;
SdFat sd;
SdFile file;

void setup_Sd(){
  //Setup SD Card
  if(!sd.begin(SdPin, SPI_FULL_SPEED)) sd.initErrorHalt();
  
  //open file, at this state, there is only one file
  if(!file.open("data.csv", O_RDWR | O_CREAT)){
    sd.errorHalt("opening data.csv failed!");
  }
  file.println("Date;Sensor 0;Sensor 1;Sensor 2;Sensor 3;Sensor 4;");
  file.close();
}

void printSdData(){
  /* To make the SD card removable, the SD Stream is ended
   * and therefore has to be started every time
   */
   sd.begin(SdPin, SPI_FULL_SPEED);
   
   //open file
   if(!file.open("data.csv", O_RDWR | O_CREAT | O_AT_END)){
    sd.errorHalt("opening data.csv for writing failed!");
  }
  
  //print Time to csv
  file.print(now.year(), DEC);
  file.print('/');
  file.print(now.month(), DEC);
  file.print('/');
  file.print(now.day(), DEC);
  file.print(' ');
  file.print(now.hour(), DEC);
  file.print(':');
  file.print(now.minute(), DEC);
  file.print(':');
  file.print(now.second(), DEC);
  file.print(';');
  
  //write the values to csv
  for (int i = 0; i < len; i++){
    file.print(Data[i]);
    file.print(";");
  }
  file.println();
  file.close();

}
