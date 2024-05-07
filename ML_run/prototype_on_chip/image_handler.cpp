/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "image_handler.h"

#include <Arduino.h>
#include <Wire.h>

#include "FS.h"      // SD Card ESP32
#include "SD_MMC.h"  // SD Card ESP32

/* this is a little annoying to figure out, as a tip - when
 * holding the board straight, output should be (0, 0, 1)
 * tiling the board 90* left, output should be (0, 1, 0)
 * tilting the board 90* forward, output should be (1, 0, 0);
 */
 



#include "constants.h"


TfLiteStatus SetupImage(tflite::ErrorReporter* error_reporter) {
  // Wait until we know the serial port is ready
  //while (!Serial) { yield(); }

  //SETUP SD CARD
  if (!SD_MMC.begin()) {
    error_reporter->Report("SD Card Mount Failed");
    return kTfLiteError;
  }

  if (cardType == CARD_NONE) {
    error_reporter->Report("No SD Card attached");
    return kTfLiteError;
  }

  error_reporter->Report("SD Mounted");

  return kTfLiteOk;
}

// get image from sd and convert the jpg into bitmap into tensor

String findFirstJpg() {
    File root = SD_MMC.open("/");
    if (!root) {
        return "";  // Return empty string if failed to open root directory
    }

    while (File file = root.openNextFile()) {
        String filename = file.name();
        if (filename.endsWith(".jpg") || filename.endsWith(".JPG")) {
            file.close();
            return filename;  // Return the first JPG file found
        }
        file.close();
    }
    return "";  // Return empty string if no JPG files found
}

bool ReadImage(tflite::ErrorReporter* error_reporter, float* input,
                       int length) {

  uint8_t buffer[320*240*3];

  String jpgFilename = findFirstJpg();  // Find the first JPG file
    if (jpgFilename.length() > 0) {
        error_reporter->Report(
        "First JPG file found: "
        );
        error_reporter->Report(jpgFilename);

        File jpgFile = SD_MMC.open(jpgFilename);  // Open the JPG file
        if (jpgFile) {
            // read into buffer
            int bytesRead = 0;
            while (jpegFile.available() && bytesRead < 320*240*3) {
                buffer[bytesRead] = jpegFile.read();
                bytesRead++;
            }
            jpgFile.close();  // Close the JPG file
        } else {
            error_reporter->Report("Failed to open JPG file");
            return false
        }
    } else {
        error_reporter->Report("No JPG files found");
        return false
    }

  // Convert buffer to float32 tensor with normalization
  float* inputTensor = input->data.f;
  for (int i = 0; i < 320*240*3; i++) {
    inputTensor[i] = static_cast<float>(buffer[i]);  // insert into tensor
  }
  return true;
}
