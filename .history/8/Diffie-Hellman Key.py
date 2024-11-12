def power(a, b, P):
    if b == 1:
        return a
    else:
        return pow(a, b, P)

# Driver program
def main():
    # Both the persons will be agreed upon the public keys G and P
    P = int(input("Enter the prime number P: "))  # 23
    print(f"The value of Prime Value : {P}")

    G = int(input("Enter the primitive root G: "))  # 9
    print(f"The value of Primitive Root : {G}")

    # Alice will choose the private key a
    a = int(input("Enter the private key a for Alice: "))  # 4
    print(f"The private key a for Alice : {a}")

    x = power(G, a, P)  # gets the generated key

    # Bob will choose the private key b
    b = int(input("Enter the private key b for Bob: "))  # 3
    print(f"The private key b for Bob : {b}")

    y = power(G, b, P)  # gets the generated key

    # Generating the secret key after the exchange of keys
    ka = power(y, a, P)  # Secret key for Alice
    kb = power(x, b, P)  # Secret key for Bob
    print(f"Secret key for Alice is : {ka}")
    print(f"Secret key for Bob is : {kb}")


main()
