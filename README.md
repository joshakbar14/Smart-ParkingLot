# Smart Parking Lot
![HeaderSpaceIt](https://user-images.githubusercontent.com/56721954/230046019-0ab0f713-a5ff-4f26-965a-71f06fece0cc.png)

A smart parking solution that automatically check available parking space and return a guidance path and booking code to the user for the designated space.

## Key Features
+ Showing designated parking spot ​
+ Identify car's owner​
+ Showing available spaces (real time)​
+ Identify the designated spot (right/wrong) (real time)​

## Hardware Needed

1 x Raspberry Pi 3\
2 x Ultrasonic Sensor (HC-SR04 module)\
1 x RFID reader (RFID RC522)\
1 x Monitor

## Program Flow Chart
![Shopping Process Flow Graph (1)](https://user-images.githubusercontent.com/56721954/230095325-960b2b8f-7d38-4a16-8ade-bc07b927bafd.png)

# Installation
## Prerequisites

    apt-get install cmake
    apt-get install libpigpio-dev


## Building:

To build:

    cmake .

    make

## Run it

    sudo ./running.o

## Usage examples

+ Wire the required hardware into the PI. See the hardware wiring diagram in the doc file.
+ run the program
+ Tap an ID card into the RFID card reader
+ Program will print the designated parking space according to the ultrasonic sensor position
+ Park the car into the designated space
+ The parking space availability will automatically updated and sent in the command window
+ If the parking space is full, the program will return "No parking space available, please come back later"

## Documentation
Doxygen documentation of project
+ Clone the repo
+ go to html/
+ run index.html in your browser
+ [doxygen documentation html](html/)

