
import bluetooth

bd_addr = "D4:D2:52:88:61:0B"

port = 1

sock=bluetooth.BluetoothSocket( bluetooth.RFCOMM )
sock.connect((bd_addr, port))

sock.send("hello!!")

sock.close()