# Gesture Recognition Using Raspberry Pi Pico and Edge Impulse
In this project, we have developed a Gesture recognition system using the Raspberry Pi Pico using the Edge Impulse platform. This involves using the MPU6050 Accelerometer and Gyroscope sensor and leveraging TinyML to collect sensor data, train using ML model by edge impulse, and deploy it on the Pico.


## Requirements

### Hardware

* [Raspberry Pi Pico](https://www.raspberrypi.org/products/raspberry-pi-pico/).
* MPU6050 sensor module (an integrated 6-axis motion tracking device with accelerometer and gyroscope)
* Arduino Uno(for wireless connectivity as the wifi module in our Pi Pico W wasn’t working.

### Software

* [Edge Impulse CLI](https://docs.edgeimpulse.com/docs/cli-installation).
* [GNU ARM Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads).
* [CMake](https://cmake.org/install/).
* Arduino IDE(for displaying our final output)
* Rasperry Pi Pico SDK

## Building the application
Setting Up the C/C++ SDK
<br>
1.	Installing the SDK
2.	Install necessary tools:
brew install cmake
brew tap ArmMbed/homebrew-formulae
brew install arm-none-eabi-gcc


## Collecting Data and Training the Model Using Edge Impulse
1.	Log in to Edge Impulse, create a new project, and use the Data forwarder to collect accelerometer data.
2.	Label and record data for different gestures (e.g., idle, up-down, left-right, forward-backward).
3.	Design the ML model using Spectral Analysis processing and train the neural network with the collected data.
<br>
## Deploying the ML Model
1.	Deploy the trained model to the Raspberry Pi Pico by building a C++ library in Edge Impulse.
<br>
2.	Open the serial monitor to see the output predictions for different gestures.

