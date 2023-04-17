# Smart Parking Lot
![HeaderSpaceIt](https://user-images.githubusercontent.com/56721954/230046019-0ab0f713-a5ff-4f26-965a-71f06fece0cc.png)


A smart parking solution that automatically check available parking space and return a guidance path and booking code to the user for the designated space.

## Key Features
+ Showing designated parking spot ​
+ Identify car's owner​
+ Showing available spaces (real time)​
+ Identify the designated spot (right/wrong) (real time)​
+ In/out time record (real time)

## Specification

1 x Raspberry Pi 4\
1 x GPIO Extension (MCP23017 using I2C bus)\
2 x Ultrasonic Sensor (HC-SR04 module)\
2 x RFID reader (RFID RC522)\
2 x (16x2) LCD Display\
1 x Monitor

## Program Flow Chart
![Shopping Process Flow Graph (1)](https://user-images.githubusercontent.com/56721954/230095325-960b2b8f-7d38-4a16-8ade-bc07b927bafd.png)

## Backend Work

### Hardware
+ Hardware connection with I2C bus extension
+ RFID reader class
+ LCD display class
+ QR code display class
+ Ultrasonic sensor connection class

### Software

Doxygen documentation of project
+ Clone the repo
+ go to html/
+ run index.html in your browser
[doxygen documentation html](html/index.html)

