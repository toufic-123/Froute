import bluetooth
import time

def send_data_to_arduino(data):
    port = 1  # RFCOMM port (must match the port configured in Arduino sketch)
    server_address = "98:DA:50:01:C9:A0"  # Replace with your Arduino's Bluetooth address
    client_sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    client_sock.connect((server_address, port))

    print(f"Connected to {server_address}")

    client_sock.send(data)
    print(f"Sent data: {data}")

    time.sleep(10)

    received_data = client_sock.recv(1024)
    print(f"Received data: {received_data}")
    print(f"Received data length: {len(received_data)}")

    client_sock.close()

if __name__ == "__main__":
    data_to_send = "Hello, Arduino!\n"
    send_data_to_arduino(data_to_send)
