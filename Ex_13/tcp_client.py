import socket

def start_client(host='127.0.0.1', port=12345):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        client_socket.connect((host, port))
        print(f"Connected to the server at {host}:{port}")

        while True:
            message = input("You: ")
            client_socket.send(message.encode())
            if message.lower() == 'exit':
                print("Disconnected from server.")
                break
            server_response = client_socket.recv(1024).decode()
            if server_response.lower() == 'exit':
                print("Server has closed the connection.")
                break
            print(f"Server: {server_response}")

if __name__ == "__main__":
    start_client()
