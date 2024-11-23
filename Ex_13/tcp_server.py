import socket

def start_server(host='127.0.0.1', port=12345):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((host, port))
        server_socket.listen(1)
        print(f"Server started on {host}:{port}, waiting for a connection...")

        conn, addr = server_socket.accept()
        print(f"Connected to {addr}")

        while True:
            client_message = conn.recv(1024).decode()
            if client_message.lower() == 'exit':
                print("Client disconnected.")
                break
            print(f"Client: {client_message}")
            server_message = input("You: ")
            conn.send(server_message.encode())
            if server_message.lower() == 'exit':
                print("Server shutting down.")
                break

if __name__ == "__main__":
    start_server()
