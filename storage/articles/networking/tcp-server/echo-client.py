# echo_client.py - Simple TCP Echo Client
import socket

def main():
    # Create TCP socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Server details
    host = 'localhost'
    port = 8888
    
    try:
        # Connect to server
        print(f"Connecting to {host}:{port}")
        client_socket.connect((host, port))
        print("Connected!")
        
        # Message to send
        message = "Hello Server!"
        print(f"Sending: {message}")
        
        # Send message (encode string to bytes)
        client_socket.send(message.encode('utf-8'))
        
        # Receive echo response
        response = client_socket.recv(1024)
        response_str = response.decode('utf-8')
        print(f"Received: {response_str}")
        
    except ConnectionRefusedError:
        print("Error: Could not connect to server. Is the server running?")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        # Close connection
        client_socket.close()
        print("Connection closed")

if __name__ == "__main__":
    main()