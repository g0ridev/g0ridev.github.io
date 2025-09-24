from socket import *

#server's address
serverIP = '127.0.0.1'
serverPort = 5051
# serverIP = '192.168.1.2'
# serverPort = 5050
serverAddr = (serverIP, serverPort)


#create a socket
clientSocket = socket(AF_INET, SOCK_DGRAM) #use UDP


#create a message to send multiple responses
while True:
    # msg takes input
    msg = input("Enter a message: ")
    #encode msg

    encoded = msg.encode()
    print(encoded)
    clientSocket.sendto(encoded, serverAddr)

    if msg == "exit":
        break

    response, serverAdd_response = clientSocket.recvfrom(2048)
    response = response.decode()
    print(response)



# send something 
# clientSocket.sendto(encoded, serverAddr)


# send TASK: recieve a response from the server
            # Hint: user recvfrom() method
    

#just for info
# print(clientSocket)



