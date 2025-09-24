# echo_server.py - Simple TCP Echo Server
import socket

def main():
    # Create TCP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Allow reuse of address (helpful for testing)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    # Bind to localhost:8888
    host = 'localhost'
    port = 8888
    server_socket.bind((host, port))
    
    # Listen for connections (backlog of 1)
    server_socket.listen(1)
    print(f"Server listening on {host}:{port}")
    
    try:
        while True:
            # Accept connection
            client_socket, client_address = server_socket.accept()
            print(f"Client connected from {client_address}")
            
            # Receive message (up to 1024 bytes)
            message = client_socket.recv(1024)
            if message:
                message_str = message.decode('utf-8')
                print(f"Received: {message_str.strip()}")
                
                # Echo message back
                client_socket.send(message)
                print(f"Sent back: {message_str.strip()}")
            
            # Close client connection
            client_socket.close()
            print("Connection closed\n")
            
    except KeyboardInterrupt:
        print("\nServer shutting down...")
    finally:
        server_socket.close()

if __name__ == "__main__":
    main()