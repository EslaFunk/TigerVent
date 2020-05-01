# TigerVent #
## A Ventilator design inspired by Rice University's ApolloBMV with added Alarming and Pressure Sensing

Custom Enhancements from base ApolloBMV Design:
* Honeywell NSCDRRN001PDUNV Pressure Sensor integrated with driver (still available pressure sensor)
* Assist control mode that triggers the ventilator when negative pressure (a breath) is initiated
* Alarm/Buzzer and code to handle alarms based on pressure (WIP)
* Schematic and Board files for printed circuit board designed in EAGLE (confirmed tested and working)
* updated CAD file of chassis to fit PCB and CAD file of PCB
* alternate LCD driver implementation for more available 2004 LCD Screen
* Powershell script to automate updating library in seperate folder while also maintaining git capability

![alt text][renderedpcb]


Special thanks to the team at Rice University for the base design. Hopefully these enhancements can provide more functionality and safety to others looking to implement these ventilators.
















[renderedpcb]: https://github.com/kebroad/TigerVent/blob/master/PrintedCircuitBoard/RenderedImage.png 

