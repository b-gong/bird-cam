import serial
import time
from io import BytesIO

serial_port = serial.Serial(
    port="/dev/ttyS0",  # Specify your UART port
    baudrate=115200,         # Set baud rate (match with your device)
    timeout=1              # Set timeout value in seconds
)

try:
    while True:
        if serial_port.in_waiting > 0:
            image_data = b''
            time.sleep(2)
            while True:
                data = ser.read(14474)  # Adjust buffer size as needed
                if data:
                    image_data += data
                else:
                    break
            image_stream = io.BytesIO(image_data)
except KeyboardInterrupt:
    print("Program terminated by user.")
finally:
    serial_port.close()