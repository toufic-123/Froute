import bluetooth
import time

DELIMETER = '\n'
GARBAGE = '@'

def send_data_to_arduino(data):
    port = 1  # RFCOMM port (must match the port configured in Arduino sketch)
    server_address = "98:DA:50:01:C9:A0"  # Replace with your Arduino's Bluetooth address
    client_sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    client_sock.connect((server_address, port))

    print(f"Connected to {server_address}")

    # client_sock.send(data)
    # print(f"Sent data: {data}")

    all_msgs = []

    for _ in range(100):    
        
        msgs = receive_message(client_sock)
        for msg in msgs:
            all_msgs.append(msg)
        
    print(all_msgs)
    

    client_sock.close()


def receive_message(socket):
    received_data = socket.recv(1024)
    data = []
    for byte in received_data:
        data.append(chr(byte))

    buffer = []
    msgs = []
    for char in data:
         buffer.append(char)
         if char == GARBAGE:
             buffer = []
         if char == DELIMETER:
             msgs.append(buffer[:-1].copy())
             buffer = []

    string_msgs = []

    for msg in msgs:
        new_msg = "".join(msg)
        string_msgs.append(new_msg)
    return string_msgs


if __name__ == "__main__":
    data_to_send = "Hello, Arduino!\n"
    send_data_to_arduino(data_to_send)
