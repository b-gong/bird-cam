# Copyright 2018 The TensorFlow Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================
"""label_image for tflite."""

import argparse
import time

import serial
import io
from io import BytesIO

import numpy as np
from PIL import Image
import tflite_runtime.interpreter as tflite

serial_port = serial.Serial(
    port="/dev/ttyS0",  # Specify your UART port
    baudrate=115200,         # Set baud rate (match with your device)
    timeout=1              # Set timeout value in seconds
)

def load_labels(filename):
    with open(filename, 'r') as f:
        return [line.strip() for line in f.readlines()]

def receive_image_from_serial(serial_port, buffer_size=14474):
    try:
        while True:
            if serial_port.in_waiting > 0:
                image_data = b''
                # time.sleep(2)
                # while True:
                #     data = serial_port.read(buffer_size)
                #     if data:
                #         image_data += data
                #     else:
                #         break

                # image_stream = io.BytesIO()
                # image_stream.write(image_data)
                # image_stream.seek(0)
                # img = Image.open(image_stream)


                try:
                    while True:
                        data = serial_port.read(1024)  # Read data from serial port (adjust buffer size as needed)
                        if data:
                            image_data += data  # Write data to the file
                        else:
                            break  # Exit the loop if no more data is received
                except KeyboardInterrupt:
                    break


                with open('example.jpg', 'wb') as file:
                    file.write(image_data)
                interpret_image()
    except KeyboardInterrupt:
        print("Program terminated by user.")
    finally:
        serial_port.close()

def interpret_image():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-m',
        '--model_file',
        default='mobilenetv2.tflite',
        help='.tflite model to be executed')
    parser.add_argument(
        '-l',
        '--label_file',
        default='labels.txt',
        help='name of file containing labels')
    parser.add_argument(
        '--num_threads', default=None, type=int, help='number of threads')
    parser.add_argument(
        '-e', '--ext_delegate', help='external_delegate_library path')
    parser.add_argument(
        '-o',
        '--ext_delegate_options',
        help='external delegate options, \
                format: "option1: value1; option2: value2"')

    args = parser.parse_args()

    ext_delegate = None
    ext_delegate_options = {}

    # parse extenal delegate options
    if args.ext_delegate_options is not None:
        options = args.ext_delegate_options.split(';')
        for o in options:
            kv = o.split(':')
            if (len(kv) == 2):
                ext_delegate_options[kv[0].strip()] = kv[1].strip()
            else:
                raise RuntimeError('Error parsing delegate option: ' + o)

    # load external delegate
    if args.ext_delegate is not None:
        print('Loading external delegate from {} with args: {}'.format(
            args.ext_delegate, ext_delegate_options))
        ext_delegate = [
            tflite.load_delegate(args.ext_delegate, ext_delegate_options)
        ]

    interpreter = tflite.Interpreter(
        model_path=args.model_file,
        experimental_delegates=ext_delegate,
        num_threads=args.num_threads)
    interpreter.allocate_tensors()

    input_details = interpreter.get_input_details()
    output_details = interpreter.get_output_details()

    # check the type of the input tensor
    floating_model = input_details[0]['dtype'] == np.float32

    # NxHxWxC, H:1, W:2
    height = input_details[0]['shape'][1]
    width = input_details[0]['shape'][2]
    img = Image.open('example.jpg')
    input_array = np.array(img, dtype=np.float32)
    # add N dim
    input_data = np.expand_dims(input_array, axis=0)

    # if floating_model:
    #   input_data = (np.float32(input_data) - args.input_mean) / args.input_std

    interpreter.set_tensor(input_details[0]['index'], input_data)

    start_time = time.time()
    interpreter.invoke()
    stop_time = time.time()

    output_data = interpreter.get_tensor(output_details[0]['index'])
    results = np.squeeze(output_data)

    largest_index = np.argmax(results)
    labels = load_labels(args.label_file)

    print(labels[largest_index]);


if __name__ == '__main__':
    try:
        receive_image_from_serial(serial_port)
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        serial_port.close()
