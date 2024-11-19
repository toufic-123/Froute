import bluetooth

addr = None
service = bluetooth.find_service(address=addr)
print(service)