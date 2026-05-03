def rc4(key, data):
    S = list(range(256))
    j = 0
    key_length = len(key)

    for i in range(256):
        j = (j + S[i] + key[i % key_length]) % 256
        S[i], S[j] = S[j], S[i]

    i = 0
    j = 0
    result = []

    for byte in data:
        i = (i + 1) % 256
        j = (j + S[i]) % 256

        S[i], S[j] = S[j], S[i]

        K = S[(S[i] + S[j]) % 256]
        result.append(byte ^ K)

    return bytes(result)

def xor_bytes(a, b):
    return bytes(x ^ y for x, y in zip(a, b))

def demo_rc4():
    print("=== RC4 Encryption/Decryption Demo ===")

    key = b"secretkey"
    plaintext = b"Hello, this is a secret message!"

    ciphertext = rc4(key, plaintext)
    print("Ciphertext:", ciphertext)

    decrypted = rc4(key, ciphertext)
    print("Decrypted :", decrypted)
    print()

def demo_attack():
    print("=== Many-Time Pad Attack Demo ===")

    key = b"secretkey"

    m1 = b"Attack at dawn"
    m2 = b"Send more money"

    c1 = rc4(key, m1)
    c2 = rc4(key, m2)

    print("Ciphertext 1:", c1)
    print("Ciphertext 2:", c2)

    xored = xor_bytes(c1, c2)
    print("C1 XOR C2  :", xored)

    print("\n--- Crib Dragging Example ---")

    guess = b"Attack"
    recovered = xor_bytes(xored[:len(guess)], guess)

    print("Guess (m1):", guess)
    print("Recovered part of m2:", recovered)
    print()

if __name__ == "__main__":
    demo_rc4()
    demo_attack()
