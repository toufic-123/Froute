from base_station.arduino_receiver import ArduinoComms
import location
import time

WAITING = 0
QUERYING = 1
START_COMMAND = "START"

'''
This is the master file. This should do the following:
1. Wait for Arduino to be reset
2. Query to get directions
3. Pipe those directions to arduino
4. Display directions on arduino
'''

class Froute():
    def __init__(self):
        self.arduinocomms = ArduinoComms()
        self.state = None
        self.msg_queue = []

    def phase1(self):
        self.state = WAITING
        print("Starting Waiting...")
        while self.state == WAITING:
            msgs = self.arduinocomms.receive_message()
            for msg in msgs:
                self.msg_queue.append(msg)
            while len(self.msg_queue) > 0:
                msg = self.msg_queue.pop(0)
                if msg == START_COMMAND:
                    print("Finished Waiting!")
                    time.sleep(1)
                    return

    def phase2(self):
        self.state = QUERYING
        print("Starting Querying...")
        location_response = location.main()
        self.arduinocomms.send_data_to_arduino(location_response['location_name'])
        time.sleep(1)
        return





def main():
    froute = Froute()
    froute.phase1()
    froute.phase2()

     

        

if __name__ == "__main__":
    main()