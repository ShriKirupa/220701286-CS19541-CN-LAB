import socket

def start_client(server_host='127.0.0.1', server_port=12345):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as client_socket:
        print(f"Connected to UDP Server at {server_host}:{server_port}")

        while True:
            message = input("You: ")
            client_socket.sendto(message.encode(), (server_host, server_port))  # Send message to server
            if message.lower() == 'exit':
                print("Disconnected from server.")
                break
            data, _ = client_socket.recvfrom(1024)  # Receive message from server
            server_response = data.decode()
            if server_response.lower() == 'exit':
                print("Server has closed the connection.")
                break
            print(f"Server: {server_response}")

if __name__ == "__main__":
    start_client()
