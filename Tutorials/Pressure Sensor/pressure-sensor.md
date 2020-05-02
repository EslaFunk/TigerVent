### Pressure Sensor:

For our pressure sensor, we decided to get the Honeywell NSCDRRN001PDUNV. This pressure sensor has a +-1 PSI range, which is +-70.307cm H2O. This is within range of the generally accepted maximum allowed 40 cm H20. This is a differential pressure sensor with two pressure inputs. The top port (port 1) is connected to the Ambu bag, and the bottom port (port 2) is left open to the atmosphere. This allows for the pressure to always be consistent. 


![alt text][pinout]

The pressure sensor part was created and is available in our eagle PCB library.

Here is our plumbing connection configuration:

![alt text][plumbingconfig]

We want the microcontroller to see the difference in pressure, or **Pressure Port 1 - Pressure Port 2**. This pressure sensor is an **unamplified** sensor, and has a range of about ~65mV. In order to provide an input of ~0-5V analog voltage to the microcontroller, we had to manipulate this signal. We used the INA125 from TI to amplify the change in signal while maintaining its ~0-5V range by using the "psuedoground" of the 2.5V. Note that our actual circuit schematic differs slightly from this application circuit from the IINA125 datasheet.
![alt text][ina125]

From the gain measurements, we decided on a gain resistor (Rg) to be 750 Ohms. We were able to get a voltage range of ~0-4V from the

[pinout]: https://github.com/kebroad/TigerVent/blob/master/Tutorials/Pressure%20Sensor/images/pinout.JPG

[plumbingconfig]: https://github.com/kebroad/TigerVent/blob/master/Tutorials/Pressure%20Sensor/images/plumbingconfig.jpg

[ina125]: https://github.com/kebroad/TigerVent/blob/master/Tutorials/Pressure%20Sensor/images/ina125.JPG