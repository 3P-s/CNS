import socket

def power(a, b, P):
    return pow(a, b, P)

def alice_server():
    # Prime number P and Primitive Root G
    P = int(input('Enter Prime: '))
    G = int(input('Enter Primitive Root: '))

    # Alice's private key (a)
    a = int(input('Enter Alice Private Key: '))
    
    print(f"Prime number P: {P}")
    print(f"Primitive root G: {G}")
    print(f"Alice's private key: {a}")

    # Generate Alice's public key (x)
    x = power(G, a, P)
    print(f"Alice's public key (x): {x}")

    # Create socket for Alice
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('localhost', 12345))
    server_socket.listen(1)
    print("Waiting for Bob to connect...")

    # Accept connection from Bob (client)
    conn, addr = server_socket.accept()
    print(f"Connected by {addr}")

    # Send Alice's public key to Bob
    conn.send(str(x).encode())

    # Receive Bob's public key (y) from Bob
    y = int(conn.recv(1024).decode())
    print(f"Bob's public key received: {y}")

    # Generate the shared secret key
    ka = power(y, a, P)
    print(f"Shared secret key (Alice): {ka}")

    # Close the connection
    conn.close()
    server_socket.close()

if __name__ == "__main__":
    alice_server()
