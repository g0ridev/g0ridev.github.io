from socket import *



#server's address
serverIP = '127.0.0.1'
serverPort = 5051
# serverIP = '127.0.0.1'
# serverPort = 5052
serverAddr = (serverIP, serverPort)

#create a socket
serverSocket = socket(AF_INET, SOCK_DGRAM)

#where should this server be located?
serverSocket.bind(serverAddr)

#just for info
print(serverSocket)



#recieve somethiing
while True:

    received, clientAddr = serverSocket.recvfrom(2048)
    received = received.decode()
    print(received)
    if received == 'exit':
       break

    
    # Task: send a response to the client that just contacted you

    # hint: use clientAddr and sendto() method
    # msg takes input

    msg = "this message from server to client. "
    #encode msg

    encoded = msg.encode()
    # sends to client
    serverSocket.sendto(encoded, clientAddr)





