import bluetooth

DELIMETER = '\n'
GARBAGE = '`'

class ArduinoComms():
    def __init__(self) -> None:
        port = 1  # RFCOMM port (must match the port configured in Arduino sketch)
        server_address = "98:DA:50:01:C9:A0"  # Replace with your Arduino's Bluetooth address
        self.client_sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        self.client_sock.connect((server_address, port))

        print(f"Connected to {server_address}")

    def send_data_to_arduino(self, data):

        if data[-1] != '\n':
            data += '\n'
        self.client_sock.send(data)
        print(f"Sent data: {data}")
        

        # self.client_sock.close()


    def receive_message(self):

        received_data = self.client_sock.recv(1024)
        data = []
        for byte in received_data:
            data.append(chr(byte))

        buffer = []
        msgs = []
        for char in data:
            print(char)
            buffer.append(char)
            if char == GARBAGE:
                print('HERE!!!!!!!!!!!!!')
                buffer = []
            if char == DELIMETER:
                msgs.append(buffer[:-1].copy())
                buffer = []

        string_msgs = []

        for msg in msgs:
            new_msg = "".join(msg)
            string_msgs.append(new_msg)
        
        # if len(msgs) > 0:
            # print(msgs)

        return string_msgs


    if __name__ == "__main__":
        data_to_send = "Hello, Arduino!\n"
        send_data_to_arduino(data_to_send)
