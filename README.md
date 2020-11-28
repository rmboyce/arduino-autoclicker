# arduino-autoclicker

This is code for the Clickotron board, a shield for the Arduino Leonardo which extends the capabilities of a normal mouse. The Clickotron-5000 autoclicking device uses a Leonardo, a USB Host Shield board, and the Clickotron board on top, with this code loaded on the Arduino.

This code should work with normal USB mice, but some functions may or may not work depending on the exact mouse you use. If you use a more complicated mouse that reports input differently, you will have to change the code so that the HID report the Clickotron device sends to your computer is correct.

Note that if your scroll wheel only works if you scroll while moving the mouse, making an edit to the USB Host Shield library will fix it. On Windows you will have to go to Documents > Arduino > libraries > USB_Host_Shield_Library_2.0 > hiduniversal.h and add "virtual" on line 60 before the BuffersIdentical function so that it reads "virtual bool BuffersIdentical". For other operating systems you will have to figure out where the USB Host Shield Library is stored and make the same change to the code.

See details at my website [here](https://www.ramseyboyce.com/bigger_projects/arduino_autoclicker.html).
