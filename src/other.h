#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include <AccelStepper.h>
#include <ArduinoJson.h>
//#include <Array.h>
#include <LittleFS.h>
#include <Streaming.h>
#include <algorithm>
#include <bits/stdc++.h>
#include <iostream> // for testing output in main
#include <set>
#include <string>

#include "BluetoothSerial.h" // Bluetooth Serial -> works ONLY on ESP32
#include "FS.h"
using namespace std;

#define Debug 1 // set to 0 if Serial prints not needed

#if Debug == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)   // defined to nothing
#define debugln(x) // defined to nothing
#endif

#define waterPin 2 // Water off-LOW on - HIGH

#define MotorInterfaceType 8
#define home 0 // All steppers homing position is 0

#define FORMAT_LITTLEFS_IF_FAILED true
//* Hall Effect sensor pins
#define hHomePin 34
#define vHomePin 39
#define sHomePin 36

#define resetSlider 255 // reset slider poition & clear button backgrounds
//* The above also temporarily disables the steppers

