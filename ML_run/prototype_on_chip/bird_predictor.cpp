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

#include "bird_predictor.h"

#include "constants.h"

// How many times the most recent gesture has been matched in a row
//int continuous_count = 0;
// The result of the last prediction
//int last_predict = -1;

// Return the result of the last prediction
// 0: wing("W"), 1: ring("O"), 2: slope("angle"), 3: unknown
int PredictGesture(float* output) {
    if (output == nullptr) {
        return 0.0f;  // Return a default value or handle the error as needed
    }

    // Extract and return the first float from the output tensor
    return output[0];
}


