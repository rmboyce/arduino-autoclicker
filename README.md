# arduino-autoclicker

This is code for the Clickotron board, a shield for the Arduino Leonardo which extends the capabilities of a normal mouse. The Clickotron-5000 autoclicking device uses a Leonardo, a USB Host Shield board, and the Clickotron board on top, with this code loaded on the Arduino.

Note: for the scroll wheel to work properly you will have to make an edit to the USB Host Shield Library. (On windows) you will have to go to Documents > Arduino > libraries > USB_Host_Shield_Library_2.0 > hiduniversal.h and add "virtual" on line 60 before the BuffersIdentical function so that it reads "virtual bool BuffersIdentical".

See details at my website [here](https://www.ramseyboyce.com/bigger_projects/arduino_autoclicker.html).
