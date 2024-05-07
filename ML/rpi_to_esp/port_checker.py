import serial.tools.list_ports
import time

def list_connected_ports():
    while True:
        ports = serial.tools.list_ports.comports()
        if ports:
            print("Available serial ports:")
            for port, desc, hwid in sorted(ports):
                print(f"  {port}: {desc} [{hwid}]")
        else:
            print("No serial ports found.")
        time.sleep(1)  # Adjust the delay as needed

if __name__ == "__main__":
    list_connected_ports()