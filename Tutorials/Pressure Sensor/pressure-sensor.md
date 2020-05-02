### Pressure Sensor:

For our pressure sensor, we decided to get the Honeywell NSCDRRN001PDUNV. This pressure sensor has a +-1 PSI range, which is +-70.307cm H2O. This is within range of the generally accepted maximum allowed 40 cm H20. This is a differential pressure sensor with two pressure inputs. The top port (port 1) is connected to the Ambu bag, and the bottom port (port 2) is left open to the atmosphere. This allows for the pressure to always be consistent. 


![alt text][pinout]

The pressure sensor part was created and is available in our eagle PCB library.

Here is our plumbing connection configuration:

![alt text][plumbingconfig]

We want the microcontroller to see the difference in pressure, or **Pressure Port 1 - Pressure Port 2**. This pressure sensor is an **unamplified** sensor, and outputs 0-~65mV differenat 5V input. 


[pinout]: https://github.com/kebroad/TigerVent/blob/master/Tutorials/Pressure%20Sensor/images/pinout.JPG

[plumbingconfig]: https://github.com/kebroad/TigerVent/blob/master/Tutorials/Pressure%20Sensor/images/pinout.JPG
