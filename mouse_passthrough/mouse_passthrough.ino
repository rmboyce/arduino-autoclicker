//USB host mouse from USB Host Shield Library. Install using Library Manager
#include <hiduniversal.h>

//USB device mouse library included with Arduino IDE 1.8.5
#include <Mouse.h>

//Satisfy the IDE, which needs to see the include statment in the ino too
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

//Variables
bool autoClickMode = false;

const PROGMEM uint8_t clickTimesArray[] = { 
  104, 127, 126, 108, 117, 109, 110, 89, 103, 132, 125, 105, 118, 109, 119, 102, 119, 109, 109, 105, 106, 101, 106, 87, 95, 110, 99, 108, 116, 104, 115, 99, 115, 122, 100, 101, 118, 80, 107, 119, 133, 112, 108, 103, 95, 95, 89, 106, 107, 115, 78, 107, 97, 109, 109, 109, 101, 116, 97, 109, 99, 115, 126, 92, 97, 96, 80, 96, 105, 102, 105, 90, 124, 103, 129, 104, 99, 90, 116, 107, 126, 115, 90, 105, 131, 108, 120, 99, 128, 106, 111, 117, 127, 103, 105, 91, 134, 126, 116, 110, 93, 103, 113, 116, 83, 115, 113, 119, 112, 102, 111, 105, 114, 112, 104, 102, 85, 92, 106, 111, 112, 113, 113, 113, 108, 99, 105, 121, 97, 94, 99, 103, 104, 100, 98, 94, 110, 107, 107, 104, 100, 121, 104, 109, 114, 115, 103, 106, 99, 111, 116, 94, 102, 113, 110, 104, 119, 99, 95, 105, 119, 120, 124, 105, 88, 115, 90, 117, 115, 91, 109, 106, 89, 112, 100, 101, 78, 90, 122, 96, 111, 132, 117, 127, 93, 106, 107, 102, 114, 110, 105, 114, 98, 112, 104, 114, 99, 101, 98, 75, 109, 104, 116, 111, 103, 107, 98, 109, 93, 95, 122, 103, 120, 92, 97, 86, 101, 129, 101, 121, 97, 115, 107, 103, 129, 114, 106, 109, 113, 95, 120, 112, 122, 96, 105, 96, 102, 114, 113, 85, 108, 107, 110, 87, 107, 116, 112, 127, 112, 123, 123, 105, 94, 120, 90, 116, 101, 89, 117, 95, 115, 107, 114, 102, 95, 105, 108, 106, 122, 93, 75, 110, 124, 113, 107, 112, 116, 105, 103, 111, 98, 101, 106, 111, 97, 99, 104, 104, 92, 112, 108, 96, 116, 107, 114, 99, 89, 110, 102, 89, 112, 106, 79, 121, 101, 99, 109, 96, 103, 89, 108, 82, 107, 105, 111, 78, 102, 95, 121, 91, 104, 87, 99, 110, 103, 113, 110, 103, 109, 113, 108, 104, 103, 114, 120, 102, 108, 110, 100, 101, 88, 107, 115, 79, 111, 111, 109, 118, 108, 117, 111, 123, 117, 112, 106, 113, 103, 88, 103, 90, 96, 96, 126, 108, 114, 123, 95, 89, 112, 107, 129, 105, 99, 93, 108, 98, 109, 118, 96, 106, 122, 118, 109, 114, 113, 125, 112, 113, 104, 120, 102, 121, 96, 97, 101, 140, 98, 122, 105, 108, 116, 118, 123, 128, 100, 95, 127, 100, 100, 89, 106, 97, 75, 102, 109, 133, 104, 117, 103, 108, 114, 102, 88, 105, 91, 96, 101, 110, 99, 107, 104, 86, 114, 117, 103, 100, 93, 114, 131, 91, 103, 96, 76, 95, 108, 118, 126, 104, 113, 102, 105, 86, 91, 96, 123, 114, 104, 101, 109, 115, 115, 103, 128, 86, 88, 87, 121, 111, 102, 112, 117, 120, 104, 102, 97, 104, 91, 114, 105, 90, 132, 91, 111, 114, 94, 105, 97, 124, 99, 89, 111, 113, 114, 120, 118, 111, 114, 104, 87, 89, 112, 102, 127, 111, 118, 132, 111, 100, 121, 112, 101, 113, 108, 119, 107, 80, 104, 109, 115, 114, 116, 122, 112, 106, 113, 101, 82, 118, 112, 112, 125, 113, 97, 105, 125, 108, 95, 121, 108, 111, 95, 117, 97, 117, 83, 94, 76, 114, 109, 118, 120, 97, 88, 105, 122, 120, 108, 87, 108, 116, 122, 102, 95, 99, 117, 112, 88, 95, 88, 107, 107, 95, 95, 95, 113, 106, 118, 109, 125, 110, 101, 100, 114, 89, 109, 106, 80, 114, 94, 107, 101, 105, 105, 121, 89, 111, 106, 126, 91, 125, 96, 101, 83, 94, 131, 99, 99, 93, 119, 121, 102, 110, 101, 114, 111, 86, 110, 104, 117, 99, 122, 106, 115, 108, 108, 89, 105, 121, 115, 107, 115, 100, 109, 113, 86, 111, 115, 108, 105, 118, 132, 106, 126, 100, 109, 111, 96, 114, 114, 104, 116, 119, 106, 106, 105, 114, 102, 119, 100, 108, 82, 93, 102, 122, 105, 100, 110, 111, 89, 117, 118, 89, 115, 103, 106, 93, 101, 106, 92, 95, 98, 90, 111, 107, 115, 109, 106, 122, 74, 116, 99, 123, 94, 111, 102, 132, 91, 105, 100, 102, 111, 100, 112, 113, 94, 115, 102, 125, 109, 107, 105, 100, 106, 88, 87, 112, 99, 90, 86, 97, 101, 123, 102, 94, 98, 92, 131, 116, 89, 104, 103, 88, 86, 106, 113, 91, 124, 107, 124, 120, 125, 116, 115, 107, 117, 129, 113, 112, 109, 107, 98, 114, 98, 131, 95, 92, 108, 90, 112, 108, 113, 111, 104, 114, 100, 110, 105, 106, 127, 113, 99, 119, 97, 96, 99, 110, 103, 84, 83, 97, 104, 111, 122, 110, 95, 106, 124, 95, 135, 132, 88, 108, 114, 104, 106, 103, 126, 99, 111, 97, 81, 102, 98, 101, 98, 102, 90, 125, 93, 125, 97, 87, 98, 95, 93, 109, 128, 122, 129, 93, 99, 127, 120, 115, 121, 106, 98, 100, 98, 113, 119, 103, 111, 96, 101, 103, 98, 115, 100, 113, 101, 111, 117, 97, 72, 95, 101, 74, 100, 96, 106, 125, 108, 89, 105, 119, 104, 114, 130, 101, 119, 118, 114, 100, 113, 108, 98, 96, 101, 104, 119, 119, 132, 110, 100, 97, 117, 85, 114, 104, 89, 98, 83, 100, 100, 109, 109, 109, 99, 90, 112, 113, 93, 103, 95, 92, 96, 100, 113, 114, 104, 107, 91, 93, 98, 95, 93, 102, 116, 85, 106, 114, 98, 119, 110, 104, 94, 102, 131, 109, 116, 126, 113, 114, 102, 94, 101, 111, 102, 102, 123, 102, 96, 89, 111, 112, 117, 101, 115, 106, 121, 110, 94, 102, 98, 93, 94, 95, 108, 118, 121, 94, 104, 106, 103, 105, 112, 99, 96, 117, 119, 128, 130, 106, 104, 99, 100, 107, 97, 106, 118, 104, 123, 115, 109, 104, 99, 105, 111, 100, 113, 126, 118, 103, 94, 111, 95, 115, 97, 97, 113, 88, 123, 93, 96, 88, 115, 106, 106, 128, 117, 100, 105, 116, 126, 95, 117, 96, 109, 116, 91, 101, 94, 92, 82, 117, 107, 101, 122, 117, 94, 109, 110, 108, 93, 100, 103, 112, 111, 106, 103, 110, 117, 93, 111, 92, 115, 120, 108, 102, 96, 96, 99, 100, 125, 123, 104, 118, 98, 116, 107, 85, 126, 92, 114, 100, 102, 79, 85, 96, 93, 106, 93, 102, 106, 111, 78, 97, 112, 108, 104, 119, 110, 91, 92, 94, 111, 108, 131, 96, 95, 139, 116, 128, 124, 110, 114, 103, 122, 102, 113, 100, 105, 118, 107, 108, 116, 94, 115, 123, 94, 98, 105, 116, 103, 88, 117, 109, 102, 108, 117, 114, 105, 88, 127, 95, 104, 85, 114, 103, 98, 127, 92, 97, 90, 70, 93, 107, 118, 103, 110, 122, 114, 101, 125, 109, 104, 92, 95, 127, 92, 108, 90, 121, 103, 105, 76, 124, 130, 114, 109, 99, 114, 94, 92, 99, 102, 111, 104, 103, 84, 102, 88, 108, 98, 92, 79, 89, 108, 93, 114, 113, 97, 107, 109, 92, 110, 126, 122, 115, 105, 130, 97, 116, 111, 116, 104, 110, 114, 108, 116, 100, 103, 112, 78, 102, 99, 92, 114, 99, 108, 103, 105, 117, 97, 115, 99, 124, 91, 109, 103, 110, 119, 117, 137, 105, 95, 100, 77, 90, 114, 97, 113, 92, 96, 101, 104, 71, 100, 115, 97, 84, 107, 92, 87, 105, 123, 102, 108, 96, 118, 121, 101, 79, 109, 91, 106, 99, 92, 124, 107, 105, 94, 104, 108, 102, 109, 101, 108, 88, 108, 108, 105, 101, 105, 99, 106, 111, 104, 108, 101, 122, 94, 109, 123, 83, 108, 98, 110, 103, 118, 125, 81, 131, 100, 109, 98, 89, 113, 95, 120, 110, 107, 88, 117, 93, 102, 106, 96, 134, 124, 106, 99, 79, 95, 120, 104, 97, 102, 106, 91, 117, 82, 126, 124, 100, 99, 87, 92, 104, 113, 107, 114, 113, 101, 103, 91, 109, 116, 104, 126, 116, 101, 116, 126, 126, 98, 101, 102, 109, 90, 109, 94, 111, 127, 107, 109, 114, 96, 90, 108, 115, 99, 93, 112, 103, 107, 108, 116, 124, 110, 112, 99, 115, 123, 108, 108, 114, 103, 112, 97, 107, 117, 91, 120, 123, 107, 127, 124, 109, 105, 107, 116, 108, 95, 114, 119, 113, 85, 131, 110, 104, 96, 93, 97, 117, 89, 109, 104, 113, 105, 111, 107, 117, 93, 107, 95, 104, 107, 102, 83, 119, 105, 115, 75, 106, 115, 89, 119, 116, 106, 102, 96, 120, 96, 107, 97, 116, 112, 105, 90, 114, 109, 99, 99, 113, 118, 103, 121, 126, 87, 124, 115, 105, 121, 111, 115, 104, 115, 114, 96, 108, 106, 104, 120, 95, 111, 107, 107, 108, 114, 102, 111, 99, 100, 91, 90, 104, 122, 86, 89, 100, 129, 103, 105, 111, 103, 101, 103, 125, 96, 99, 127, 99, 76, 106, 124, 112, 122, 87, 97, 134, 117, 99, 96, 109, 112, 122, 92, 82, 98, 105, 102, 101, 119, 90, 106, 122, 114, 97, 79, 101, 127, 99, 96, 115, 97, 96, 105, 112, 131, 107, 118, 116, 103, 98, 104, 101, 134, 105, 111, 84, 95, 108, 126, 92, 110, 102, 101, 111, 109, 102, 125, 102, 110, 108, 118, 88, 119, 111, 118, 105, 102, 106, 103, 82, 101, 94, 119, 104, 106, 110, 107, 103, 125, 98, 111, 101, 102, 106, 116, 106, 121, 82, 117, 93, 125, 129, 100, 104, 96, 105, 113, 93, 99, 117, 99, 116, 95, 121, 87, 95, 88, 100, 106, 104, 130, 95, 107, 98, 85, 104, 104, 94, 99, 102, 120, 107, 125, 124, 100, 99, 122, 113, 109, 92, 94, 97, 91, 104, 116, 110, 95, 107, 121, 111, 128, 96, 105, 104, 110, 111, 110, 111, 122, 89, 100, 102, 106, 113, 87, 100, 115, 104, 111, 116, 113, 110, 104, 116, 124, 126, 100, 100, 100, 100, 140, 70, 115, 103, 105, 105, 94, 119, 91, 102, 110, 108, 98, 101, 128, 100, 95, 112, 105, 119, 114, 106, 125, 82, 111, 106, 115, 122, 96, 106, 92, 113, 119, 83, 113, 101, 100, 117, 100, 104, 110, 90, 128, 104, 112, 113, 118, 108, 105, 121, 100, 125, 111, 131, 85, 93, 105, 101, 115, 123, 115, 101, 97, 111, 78, 100, 136, 117, 110, 108, 92, 106, 104, 127, 138, 106, 111, 102, 109, 105, 100, 114, 88, 106, 109, 103, 97, 104, 106, 91, 108, 109, 103, 113, 119, 113, 92, 96, 98, 95, 111, 107, 82, 110, 107, 99, 104, 94, 107, 86, 97, 106, 114, 99, 120, 106, 91, 97, 96, 101, 84, 112, 118, 93, 107, 96, 116, 95, 101, 129, 111, 99, 105, 98, 82, 112, 107, 108, 90, 114, 96, 120, 111, 98, 110, 98, 101, 106, 101, 113, 116, 126, 123, 132, 120, 91, 90, 102, 113, 114, 88, 111, 109, 78, 96, 108, 93, 119, 112, 91, 104, 101, 122, 107, 111, 126, 101, 111, 90, 103, 94, 114, 103, 106, 113, 109, 105, 123, 105, 122, 93, 116, 112, 106, 94, 103, 107, 112, 93, 125, 118, 100, 111, 115, 97, 114, 106, 119, 106, 105, 106, 112, 118, 107, 118, 129, 90, 113, 116, 119, 105, 109, 102, 100, 109, 93, 98, 92, 104, 116, 103, 114, 101, 126, 92, 106, 110, 90, 106, 113, 119, 127, 110, 105, 94, 87, 136, 100, 103, 85, 104, 125, 96, 105, 123, 126, 109, 99, 120, 122, 110, 113, 116, 123, 109, 107, 134, 108, 91, 104, 94, 104, 106, 93, 116, 104, 113, 91, 104, 107, 88, 104, 104, 98, 91, 119, 103, 84, 95, 99, 111, 115, 107, 94, 130, 98, 90, 98, 112, 107, 110, 95, 115, 98, 114, 92, 105, 95, 94, 128, 117, 106, 105, 105, 99, 133, 113, 139, 84, 91, 110, 98, 125, 111, 115, 89, 92, 121, 105, 106, 81, 84, 110, 118, 103, 108, 111, 116,
  96, 92, 114, 104, 102, 107, 116, 103, 124, 106, 86, 103, 99, 95, 102, 105, 117, 99, 109, 88, 122, 105, 123, 111, 103, 121, 105, 118, 88, 115, 97, 78, 135, 114, 102, 74, 121, 97, 105, 91, 115, 102, 114, 97, 96, 94, 80, 96, 100, 113, 100, 97, 106, 94, 97, 124, 116, 100, 95, 117, 114, 109, 89, 95, 86, 104, 102, 124, 97, 109, 114, 105, 109, 98, 108, 102, 89, 130, 104, 96, 93, 109, 96, 108, 88, 109, 118, 103, 97, 119, 118, 91, 94, 102, 118, 95, 115, 120, 102, 111, 93, 106, 108, 79, 104, 88, 105, 109, 115, 90, 122, 86, 105, 102, 117, 92, 127, 112, 106, 99, 107, 124, 98, 105, 105, 129, 121, 118, 105, 101, 95, 122, 126, 83, 115, 114, 85, 97, 106, 95, 86, 98, 100, 118, 98, 115, 121, 115, 104, 115, 94, 96, 112, 119, 114, 89, 88, 104, 91, 109, 121, 99, 89, 104, 122, 98, 100, 128, 103, 92, 96, 115, 96, 133, 103, 106, 126, 133, 101, 98, 105, 106, 121, 124, 106, 93, 98, 93, 83, 102, 118, 106, 117, 113, 105, 108, 100, 116, 92, 92, 102, 100, 98, 122, 90, 91, 104, 97, 111, 99, 98, 104, 74, 101, 97, 124, 93, 111, 102, 99, 102, 106, 105, 112, 107, 100, 82, 90, 92, 93, 109, 98, 109, 115, 109, 99, 101, 120, 128, 104, 101, 92, 102, 125, 107, 98, 101, 134, 128, 100, 104, 105, 129, 76, 111, 96, 92, 83, 108, 89, 108, 107, 117, 101, 106, 88, 119, 100, 127, 100, 102, 106, 111, 126, 119, 117, 99, 106, 119, 116, 108, 103, 111, 104, 114, 130, 103, 112, 100, 87, 105, 82, 110, 108, 101, 92, 114, 89, 109, 111, 98, 103, 105, 123, 120, 92, 106, 116, 95, 106, 114, 111, 121, 74, 92, 98, 114, 116, 120, 109, 119, 98, 96, 106, 109, 116, 118, 131, 112, 125, 119, 91, 100, 94, 94, 84, 107, 115, 100, 119, 92, 104, 116, 103, 93, 109, 111, 81, 94, 91, 109, 120, 96, 112, 102, 105, 128, 105, 85, 101, 114, 94, 97, 114, 108, 102, 104, 89, 119, 89, 90, 103, 93, 90, 105, 127, 91, 108, 120, 109, 93, 119, 102, 89, 123, 125, 117, 106, 97, 103, 120, 115, 109, 106, 98, 116, 116, 86, 86, 102, 99, 87, 123, 112, 92, 110, 109, 106, 111, 113, 103, 93, 99, 93, 124, 111, 109, 116, 100, 104, 109, 106, 104, 113, 100, 96, 104, 125, 87, 92, 104, 93, 99, 110, 95, 112, 96, 97, 103, 102, 110, 120, 115, 102, 116, 96, 128, 108, 107, 111, 107, 89, 110, 100, 116, 96, 85, 109, 95, 107, 106, 134, 95, 119, 100, 111, 116, 95, 127, 110, 99, 88, 88, 105, 109, 105, 108, 106, 116, 123, 103, 80, 125, 116, 110, 73, 99, 83, 104, 118, 100, 89, 115, 97, 97, 105, 103, 90, 116, 101, 95, 101, 88, 100, 108, 89, 122, 102, 99, 112, 118, 110, 93, 80, 92, 111, 110, 126, 107, 104, 98, 100, 105, 90, 104, 91, 107, 96, 80, 106, 119, 92, 114, 128, 110, 120, 96, 131, 85, 126, 117, 100, 111, 104, 102, 112, 106, 103, 104, 106, 108, 104, 89, 98, 92, 96, 107, 107, 108, 94, 116, 111, 109, 98, 111, 107, 100, 114, 112, 96, 104, 110, 111, 111, 119, 115, 97, 110, 105, 95, 106, 107, 99, 110, 104, 122, 97, 96, 93, 103, 111, 117, 102, 109, 102, 105, 98, 105, 107, 105, 112, 101, 112, 102, 125, 83, 76, 120, 92, 133, 104, 98, 89, 105, 96, 105, 89, 112, 113, 95, 95, 108, 114, 104, 110, 92, 106, 100, 111, 110, 113, 106, 110, 103, 101, 107, 103, 92, 116, 112, 91, 107, 103, 128, 100, 126, 115, 113, 114, 88, 118, 104, 102, 97, 106, 82, 109, 109, 106, 85, 98, 104, 119, 102, 111, 112, 96, 98, 112, 91, 85, 118, 110, 89, 96, 92, 104, 104, 93, 113, 102, 109, 95, 110, 96, 99, 127, 112, 113, 78, 92, 99, 113, 92, 95, 88, 111, 100, 114, 120, 109, 112, 92, 113, 80, 116, 117, 135, 107, 104, 127, 96, 95, 87, 112, 118, 101, 105, 88, 105, 103, 110, 98, 102, 100, 125, 106, 102, 115, 99, 98, 98, 87, 104, 99, 99, 87, 129, 125, 81, 119, 116, 109, 108, 120, 118, 105, 94, 127, 101, 108, 103, 104, 106, 93, 95, 90, 93, 115, 96, 104, 109, 110, 116, 110, 112, 123, 110, 113, 127, 84, 107, 95, 123, 127, 102, 105, 101, 108, 103, 108, 110, 117, 111, 118, 111, 94, 84, 113, 101, 100, 116, 100, 117, 123, 120, 100, 108, 107, 89, 118, 112, 118, 118, 102, 102, 103, 113, 115, 129, 99, 101, 83, 95, 115, 105, 122, 106, 98, 122, 127, 112, 122, 92, 123, 121, 113, 98, 105, 94, 109, 104, 100, 116, 94, 98, 94, 106, 114, 105, 90, 86, 101, 89, 109, 113, 87, 110, 114, 103, 81, 96, 125, 92, 128, 92, 88, 98, 113, 120, 88, 98, 90, 109, 104, 115, 94, 105, 91, 93, 125, 93, 134, 102, 105, 87, 110, 102, 83, 112, 105, 127, 126, 117, 109, 86, 129, 104, 112, 108, 90, 106, 123, 110, 94, 116, 98, 101, 104, 98, 105, 113, 97, 125, 120, 83, 108, 118, 104, 112, 94, 84, 105, 110, 116, 105, 119, 95, 109, 107, 103, 102, 107, 117, 92, 94, 101, 92, 89, 93, 105, 102, 118, 115, 114, 107, 98, 102, 105, 110, 90, 112, 114, 95, 130, 114, 97, 120, 97, 102, 84, 97, 100, 90, 115, 108, 119, 93, 105, 91, 119, 111, 103, 121, 100, 93, 121, 119, 118, 114, 71, 92, 92, 95, 114, 118, 132, 119, 93, 102, 110, 101, 126, 123, 84, 97, 101, 113, 103, 86, 122, 118, 105, 122, 100, 105, 87, 123, 126, 116, 126, 79, 119, 123, 116, 112, 101, 103, 109, 98, 113, 95, 106, 120, 87, 107, 86, 79, 95, 98, 114, 108, 115, 124, 104, 100, 98, 90, 121, 106, 108, 97, 104, 132, 111, 117, 126, 97, 118, 100, 135, 88, 92, 97, 107, 121, 117, 127, 111, 107, 87, 100, 116, 95, 99, 117, 120, 105, 113, 106, 106, 112, 105, 103, 85, 108, 98, 99, 111, 113, 98, 124, 123, 119, 91, 89, 104, 77, 115, 85, 106, 78, 100, 93, 108, 113, 93, 127, 113, 78, 94, 105, 123, 124, 128, 120, 95, 101, 98, 111, 122, 99, 129, 101, 98, 117, 112, 118, 119, 119, 133, 100, 102, 103, 89, 96, 105, 120, 111, 110, 111, 109, 119, 104, 99, 120, 129, 89, 118, 116, 117, 108, 98, 117, 99, 102, 112, 96, 106, 105, 98, 99, 100, 103, 110, 111, 122, 101, 92, 107, 118, 102, 121, 114, 111, 108, 109, 112, 89, 83, 94, 93, 111, 104, 110, 105, 104, 102, 90, 101, 111, 112, 103, 94, 100, 131, 93, 103, 108, 134, 104, 121, 114, 107, 107, 103, 82, 90, 109, 100, 109, 87, 108, 105, 104, 120, 111, 99, 101, 91, 121, 99, 106, 89, 117, 108, 104, 122, 125, 98, 95, 80, 110, 110, 118, 120, 94, 99, 92, 107, 120, 101, 111, 116, 116, 98, 95, 106, 85, 77, 132, 108, 120, 99, 94, 96, 96, 128, 94, 112, 111, 112, 112, 113, 102, 119, 110, 124, 97, 103, 122, 109, 100, 93, 113, 106, 112, 117, 120, 105, 110, 114, 109, 113, 103, 91, 108, 91, 107, 85, 111, 101, 83, 96, 95, 116, 112, 103, 103, 125, 113, 93, 105, 113, 115, 92, 98, 95, 96, 94, 127, 98, 97, 103, 114, 92, 111, 128, 83, 107, 90, 123, 92, 98, 109, 108, 108, 100, 94, 103, 101, 114, 102, 103, 95, 93, 96, 89, 109, 89, 107, 105, 116, 118, 108, 110, 102, 103, 104, 83, 107, 95, 100, 89, 107, 107, 111, 111, 100, 96, 95, 115, 102, 100, 104, 102, 115, 111, 114, 95, 96, 102, 122, 109, 122, 103, 107, 116, 97, 105, 103, 82, 125, 105, 112, 126, 113, 94, 122, 116, 114, 95, 98, 109, 89, 117, 121, 97, 111, 122, 111, 89, 95, 113, 117, 105, 108, 103, 117, 105, 91, 111, 109, 118, 109, 96, 111, 105, 129, 89, 103, 117, 105, 96, 97, 118, 110, 113, 108, 109, 110, 116, 96, 101, 103, 96, 107, 96, 92, 115, 116, 112, 102, 86, 103, 101, 93, 79, 98, 104, 100, 122, 116, 102, 90, 93, 100, 93, 112, 98, 102, 96, 89, 112, 98, 103, 97, 102, 89, 114, 106, 126, 98, 107, 94, 126, 134, 115, 111, 118, 116, 103, 117, 110, 115, 111, 109, 112, 110, 125, 118, 78, 87, 92, 97, 104, 103, 100, 88, 116, 104, 100, 97, 102, 98, 90, 112, 104, 86, 110, 104, 98, 113, 111, 116, 91, 110, 106, 113, 118, 91, 101, 92, 109, 110, 101, 101, 104, 119, 100, 109, 115, 89, 105, 118, 103, 130, 96, 98, 96, 99, 114, 97, 100, 113, 134, 98, 125, 97, 107, 104, 120, 116, 88, 104, 108, 119, 125, 98, 93, 121, 101, 116, 108, 98, 127, 107, 101, 118, 99, 97, 114, 82, 113, 94, 106, 106, 102, 96, 101, 109, 119, 93, 115, 113, 96, 93, 92, 126, 102, 105, 93, 123, 101, 100, 88, 103, 97, 121, 108, 102, 129, 116, 97, 117, 110, 110, 97, 83, 81, 104, 133, 100, 86, 102, 96, 125, 95, 113, 107, 109, 102, 82, 91, 101, 126, 106, 103, 101, 117, 93, 104, 110, 89, 98, 92, 110, 93, 110, 87, 99, 113, 91, 93, 92, 103, 86, 95, 130, 121, 90, 118, 101, 133, 98, 95, 97, 107, 89, 128, 105, 109, 114, 99, 80, 115, 113, 119, 121, 127, 93, 100, 102, 109, 125, 102, 102, 94, 76, 99, 96, 118, 114, 110, 108, 105, 109, 106, 115, 114, 115, 102, 114, 105, 118, 118, 130, 95, 101, 113, 100, 76, 99, 114, 87, 99, 90, 111, 109, 106, 106, 111, 102, 118, 119, 116, 101, 103, 110, 112, 76, 104, 105, 102, 104, 131, 105, 112, 88, 65, 123, 105, 94, 112, 99, 94, 125, 93, 105, 86, 111, 111, 82, 110, 93, 93, 113, 96, 89, 117, 105, 107, 99, 102, 90, 105, 109, 102, 120, 100, 111, 121, 114, 127, 113, 102, 112, 103, 110, 98, 92, 116, 93, 96, 110, 111, 107, 108, 92, 108, 107, 110, 119, 125, 116, 104, 111, 85, 85, 100, 96, 104, 106, 108, 93, 93, 96, 106, 99, 115, 124, 115, 79, 104, 117, 109, 92, 107, 99, 98, 99, 105, 111, 85, 98, 107, 107, 125, 123, 99, 110, 126, 113, 93, 93, 102, 108, 116, 123, 100, 97, 86, 113, 109, 107, 90, 99, 119, 101, 125, 81, 102, 99, 107, 118, 110, 96, 106, 104, 96, 116, 118, 94, 83, 91, 71, 96, 111, 117, 109, 112, 108, 106, 94, 113, 108, 102, 113, 122, 100, 102, 102, 108, 117, 95, 104, 98, 103, 84, 119, 116, 102, 99, 96, 108, 115, 121, 121, 120, 113, 100, 103, 98, 102, 112, 100, 94, 108, 116, 118, 115, 111, 95, 118, 105, 108, 79, 84, 106, 104, 96, 113, 85, 112, 101, 95, 102, 95, 96, 85, 108, 77, 84, 91, 113, 134, 122, 112, 115, 101, 70, 113, 123, 98, 103, 106, 93, 81, 106, 101, 101, 108, 99, 98, 98, 96, 96, 102, 108, 106, 116, 118, 122, 104, 86, 103, 83, 129, 104, 112, 99, 97, 106, 110, 89, 106, 107, 113, 112, 110, 103, 113, 106, 92, 107, 108, 108, 94, 116, 77, 101, 86, 109, 91, 99, 96, 111, 111, 113, 100, 115, 95, 112, 116, 115, 126, 111, 95, 98, 110, 84, 99, 120, 98, 108, 90, 119, 103, 111, 108 };
  
//Constants used to set pin numbers
const int leftPedalPin = 12;
const int rightPedalPin = 13;

const int ledPin = 13;

const int autoClickLedPin = 1;
const int leftClickLedPin = 2;
const int rightClickLedPin = 0;

const int potPin = 5;
const int maxSSPin = 11;

//Opcodes for the MAX7221 and MAX7219
const uint16_t OP_NOOP = 0;
const uint16_t OP_DIGIT0 = 1;
//Note: all OP_DIGITn are +n offsets from OP_DIGIT0
const uint16_t OP_DIGIT1 = 2;
const uint16_t OP_DIGIT2 = 3;
const uint16_t OP_DIGIT3 = 4;
const uint16_t OP_DIGIT4 = 5;
const uint16_t OP_DIGIT5 = 6;
const uint16_t OP_DIGIT6 = 7;
const uint16_t OP_DIGIT7 = 8;
const uint16_t OP_DECODEMODE = 9;
const uint16_t OP_INTENSITY = 10;
const uint16_t OP_SCANLIMIT = 11;
const uint16_t OP_SHUTDOWN = 12;
const uint16_t OP_DISPLAYTEST = 15;

int lastLeftPedalState = HIGH;  //HIGH - not pressed, LOW - pressed
uint32_t lastLeftPressTime = 0;
int lastRightPedalState = HIGH;  //HIGH - not pressed, LOW - pressed
uint32_t lastRightPressTime = 0;

bool leftPedalPressed = false;
bool rightPedalPressed = false;

//Iterator for stepping through the list of click times (for the autoclick mode)
int iterator = 0;

//The start time of when the user presses both pedals, for switching from normal mode to autoclick mode
uint32_t startSwitchTime = 0;

//Potentiometer reads
int potRead = 200;
int oldPotRead = 200;

//Speed of the autoclicking
double clickSpeed = 4.8;
const double ARRAY_CLICK_SPEED = 4.7;

class MouseRptParser : public HIDReportParser {
  public:
    virtual void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

void MouseRptParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
  //Serial.println(len - 1);
  //Serial.println("");
  if (len - 1 > 3) {
    uint8_t mouseRpt[4];

    //Buttons
    mouseRpt[0] = buf[1];
    //Change the hid report if the pedals are pressed
    if (leftPedalPressed || rightPedalPressed) 
    {
      mouseRpt[0] = 0;
      if (!autoClickMode) 
      {
        if (leftPedalPressed) 
        {
          mouseRpt[0] += 1;
        }
        if (rightPedalPressed)
        {
          mouseRpt[0] += 2;
        }
      }
    }

    //X and Y
    mouseRpt[1] = buf[2];
    mouseRpt[2] = buf[3];

    //Scroll
    mouseRpt[3] = buf[4];
    
    //Send hid report
    HID().SendReport(1,mouseRpt,sizeof(mouseRpt));
  }
}

class HIDUniversalFixed : public HIDUniversal {
  public:
    HIDUniversalFixed(USB *p) : HIDUniversal(p) {}
    virtual bool BuffersIdentical(uint8_t len, uint8_t *buf1, uint8_t *buf2);
};

bool HIDUniversalFixed::BuffersIdentical(uint8_t len, uint8_t *buf1, uint8_t *buf2) {
  for(uint8_t i = 0; i < len; i++)
    if(buf1[i] != buf2[i])
      return false;
  if (buf1[4] != 0)
    return false;
  return true;
}

USB Usb;
HIDUniversalFixed Hid(&Usb);

MouseRptParser Prs;

void setup()
{
  //Initialize pins
  pinMode(leftPedalPin, INPUT);
  pinMode(rightPedalPin, INPUT);

  pinMode(ledPin, OUTPUT);

  pinMode(autoClickLedPin, OUTPUT);
  pinMode(leftClickLedPin, OUTPUT);
  pinMode(rightClickLedPin, OUTPUT);

  pinMode(maxSSPin, OUTPUT);
  digitalWrite(maxSSPin, HIGH);
  
  if (Usb.Init() == -1) {
  //  Serial.println("USB host shield did not start.");
  }

  Hid.SetReportParser(0, &Prs);

  Mouse.begin();

  delay(200);
  
  //Set up 7-segment display
  sendData(OP_SHUTDOWN, 1);
  sendData(OP_DECODEMODE, 0xFF);
  sendData(OP_SCANLIMIT, 1);
  sendData(OP_INTENSITY, 7);
  sendData(OP_DISPLAYTEST, 0);

  //Serial.begin(9600);
}

void sendData(uint16_t cmd, uint8_t data)
//Send a simple command to the MAX7219 using the hardware SPI interface
{
  uint16_t x = (cmd << 8) | data;
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0)); //8 MHz
  digitalWrite(maxSSPin, LOW);
  SPI.transfer16(x);
  digitalWrite(maxSSPin, HIGH);
  SPI.endTransaction();
}

void loop()
{
  //Handle potentiometer and 7-segment displays
  oldPotRead = potRead;
  potRead = analogRead(potPin);
  if(abs(potRead - oldPotRead) < 15) 
  {
    potRead = oldPotRead;
  }
  
  int normPotRead = min(9, (int)map(potRead, 0, 1023, 0, 10));

  //Potentiometer settings
  //4.7, 4.8, 4.9, 5.0, 5.1, 6.9, 7.0, 7.1, 11, 12
  switch(normPotRead) 
  {
    case 0:
      sendData(OP_DIGIT1, 128 + 4);
      sendData(OP_DIGIT0, 7);
      clickSpeed = 4.7;
      break;
    case 1:
      sendData(OP_DIGIT1, 128 + 4);
      sendData(OP_DIGIT0, 8);
      clickSpeed = 4.8;
      break;
    case 2:
      sendData(OP_DIGIT1, 128 + 4);
      sendData(OP_DIGIT0, 9);
      clickSpeed = 4.9;
      break;
    case 3:
      sendData(OP_DIGIT1, 128 + 5);
      sendData(OP_DIGIT0, 0);
      clickSpeed = 5.0;
      break;
    case 4:
      sendData(OP_DIGIT1, 128 + 5);
      sendData(OP_DIGIT0, 1);
      clickSpeed = 5.1;
      break;
    case 5:
      sendData(OP_DIGIT1, 128 + 6);
      sendData(OP_DIGIT0, 9);
      clickSpeed = 6.9;
      break;
    case 6:
      sendData(OP_DIGIT1, 128 + 7);
      sendData(OP_DIGIT0, 0);
      clickSpeed = 7.0;
      break;
    case 7:
      sendData(OP_DIGIT1, 128 + 7);
      sendData(OP_DIGIT0, 1);
      clickSpeed = 7.1;
      break;
    case 8:
      sendData(OP_DIGIT1, 1);
      sendData(OP_DIGIT0, 1);
      clickSpeed = 11;
      break;
    case 9:
      sendData(OP_DIGIT1, 1);
      sendData(OP_DIGIT0, 2);
      clickSpeed = 12;
      break;
  }
  
  //Handle USB clicking
  Usb.Task();
  
  uint32_t currentMillis = millis();
  
  int leftPedalState = digitalRead(leftPedalPin);
  int rightPedalState = digitalRead(rightPedalPin);

  bool switchModes = false;

  //Switching modes
  if (leftPedalState == LOW && rightPedalState == LOW) 
  {
    if ((currentMillis - startSwitchTime) >= 3000) 
    {
      autoClickMode = !autoClickMode;
      startSwitchTime = currentMillis;
      if (autoClickMode) 
      {
        digitalWrite(autoClickLedPin, HIGH);
      }
      else 
      {
        digitalWrite(autoClickLedPin, LOW);
      }
    }
  }
  else 
  {
    switchModes = false;
    startSwitchTime = currentMillis;
  }

  //Handling clicking with the two modes
  if (autoClickMode) 
  {
    if (iterator >= 3950) 
    {
      iterator = 0;
    }

    //Left click
    if (leftPedalState == LOW) 
    {
      leftPedalPressed = true;
      if (!Mouse.isPressed(MOUSE_LEFT) 
          && (currentMillis - lastLeftPressTime) >= pgm_read_byte_near(clickTimesArray + iterator) * ARRAY_CLICK_SPEED/clickSpeed) 
      {
        Mouse.press(MOUSE_LEFT);
        lastLeftPressTime = currentMillis;
        //Serial.println(pgm_read_byte_near(clickTimesArray + iterator));
        iterator++;
        digitalWrite(leftClickLedPin, HIGH);
      }
      else if ((currentMillis - lastLeftPressTime) >= pgm_read_byte_near(clickTimesArray + iterator) * ARRAY_CLICK_SPEED/clickSpeed) 
      {
        Mouse.release(MOUSE_LEFT);
        lastLeftPressTime = currentMillis;
        //Serial.println(pgm_read_byte_near(clickTimesArray + iterator));
        iterator++;
        digitalWrite(leftClickLedPin, LOW);
      }
    }
    else 
    {
      leftPedalPressed = false;

      if (Mouse.isPressed(MOUSE_LEFT) 
          && (currentMillis - lastLeftPressTime) >= pgm_read_byte_near(clickTimesArray + iterator) * ARRAY_CLICK_SPEED/clickSpeed) 
      {
        Mouse.release(MOUSE_LEFT);
        iterator++;
        digitalWrite(leftClickLedPin, LOW);
      }
    }

    //Right click
    if (rightPedalState == LOW) 
    {
      rightPedalPressed = true;
      if (!Mouse.isPressed(MOUSE_RIGHT) 
          && (currentMillis - lastRightPressTime) >= pgm_read_byte_near(clickTimesArray + iterator) * ARRAY_CLICK_SPEED/clickSpeed) 
      {
        Mouse.press(MOUSE_RIGHT);
        lastRightPressTime = currentMillis;
        iterator++;
        digitalWrite(rightClickLedPin, HIGH);
      }
      else if ((currentMillis - lastRightPressTime) >= pgm_read_byte_near(clickTimesArray + iterator) * ARRAY_CLICK_SPEED/clickSpeed) 
      {
        Mouse.release(MOUSE_RIGHT);
        lastRightPressTime = currentMillis;
        iterator++;
        digitalWrite(rightClickLedPin, LOW);
      }
    }
    else 
    {
      rightPedalPressed = false;

      if (Mouse.isPressed(MOUSE_RIGHT) 
          && (currentMillis - lastRightPressTime) >= pgm_read_byte_near(clickTimesArray + iterator) * ARRAY_CLICK_SPEED/clickSpeed) 
      {
        Mouse.release(MOUSE_RIGHT);
        iterator++;
        digitalWrite(rightClickLedPin, LOW);
      }
    }
  }
  else 
  {
    //Left click
    if (leftPedalState == LOW && !Mouse.isPressed(MOUSE_LEFT) 
        && (currentMillis - lastLeftPressTime) >= 50) 
    {
      leftPedalPressed = true;
      Mouse.press(MOUSE_LEFT);
      lastLeftPressTime = currentMillis;
      digitalWrite(leftClickLedPin, HIGH);
    }
    else if (leftPedalState == HIGH && Mouse.isPressed(MOUSE_LEFT)
             && (currentMillis - lastLeftPressTime) >= 50)
    {
      leftPedalPressed = false;
      Mouse.release(MOUSE_LEFT);
      lastLeftPressTime = currentMillis;
      digitalWrite(leftClickLedPin, LOW);
    }
  
    //Right click
    if (rightPedalState == LOW && !Mouse.isPressed(MOUSE_RIGHT) 
        && (currentMillis - lastRightPressTime) >= 50) 
    {
      rightPedalPressed = true;
      Mouse.press(MOUSE_RIGHT);
      lastRightPressTime = currentMillis;
      digitalWrite(rightClickLedPin, HIGH);
    }
    else if (rightPedalState == HIGH && Mouse.isPressed(MOUSE_RIGHT)
             && (currentMillis - lastRightPressTime) >= 50)
    {
      rightPedalPressed = false;
      Mouse.release(MOUSE_RIGHT);
      lastRightPressTime = currentMillis;
      digitalWrite(rightClickLedPin, LOW);
    }
  }
}
