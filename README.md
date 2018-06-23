# MECC Bike Controller

To compile and run this code, you first need to install the [vlpp library](https://github.com/marcusrugger/functional-vlpp) by downloading the ZIP and importing it through the Arduino IDE.

## Programming the controller board

Although the controller may resemble many of the larger Arduinos like the Uno and Due, it is based off of the Arduino Lilypad and therefore 
the `Tools->Board Type` should be set to "Lilypad Arduino".

| option | value |
|--------|-------|
| `Tools->Board Type` | `Lilypad Arduino` |
| `Tools->Processor` | `ATmega328P` |
| `Tools->Programmer` | `AVR ISP` |

Because the controller does not have an onboard programmer, an external programmer is necessary. I use the [SparkFun FTDI Basic Breakout - 3.3V](https://www.sparkfun.com/products/9873) but any programmer should work as long as the pinout of the programmer matches the programming header on the controller.

