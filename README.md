# Smart Parking Lot
![HeaderSpaceIt](https://user-images.githubusercontent.com/56721954/230046019-0ab0f713-a5ff-4f26-965a-71f06fece0cc.png)

A smart parking solution that automatically check available parking space and return a guidance path and booking code to the user for the designated space.

## Key Features
+ Showing designated parking spot ​
+ Identify car's owner​
+ Showing available spaces (real time)​
+ Identify the designated spot (right/wrong) (real time)​

## Hardware Needed

![WhatsApp Image 2023-04-17 at 19 30 42](https://user-images.githubusercontent.com/122471221/232579129-8b6bc4cc-c8ce-4b1e-8033-c9cdf1c03d5a.jpg)

1 x Raspberry Pi 3\
2 x Ultrasonic Sensor (HC-SR04 module)\
2 x Buzzer\
1 x RFID reader (RFID RC522)\
2 x Toy Car or equivalent\
1 x Monitor

## UML
![UML class](https://user-images.githubusercontent.com/56721954/232925987-1163e684-ac65-45ea-a20b-585b28e22e48.png)


## Program Flow Chart
![Shopping Process Flow Graph (2)](https://user-images.githubusercontent.com/56721954/232926866-8adb6238-dcd4-4646-9dee-0a75def8d478.png)

# Installation
## Prerequisites

    apt-get install cmake
    apt-get install libpigpio-dev
    apt-get install qtdeclarative5-dev-tools
    apt-get install libqwt-qt5-dev


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
