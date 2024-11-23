import socket

def start_server(host='127.0.0.1', port=12345):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as server_socket:
        server_socket.bind((host, port))
        print(f"UDP Server started on {host}:{port}")

        while True:
            data, addr = server_socket.recvfrom(1024)  # Receive message from client
            client_message = data.decode()
            if client_message.lower() == 'exit':
                print("Client disconnected.")
                break
            print(f"Client: {client_message}")
            server_message = input("You: ")
            server_socket.sendto(server_message.encode(), addr)  # Send message to client
            if server_message.lower() == 'exit':
                print("Server shutting down.")
                break

if __name__ == "__main__":
    start_server()
