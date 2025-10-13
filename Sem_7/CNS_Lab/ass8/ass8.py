#!/usr/bin/env python3
"""
Lab Assignment 8: Cryptography Fundamentals and RSA Implementation
"""

import time
import random


# ============================================================================
# 1. Prime Number Check
# ============================================================================
def is_prime(n):
    """Check if a number is prime"""
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False

    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True


def test_prime():
    """Test prime number checking"""
    print("=" * 60)
    print("1. PRIME NUMBER CHECK")
    print("=" * 60)

    test_numbers = [2, 17, 25, 97, 100, 541]

    for num in test_numbers:
        result = is_prime(num)
        print(f"   {num} is {'PRIME' if result else 'NOT PRIME'}")

    # User input
    try:
        user_num = int(input("\nEnter a number to check: "))
        result = is_prime(user_num)
        print(f"   {user_num} is {'PRIME' if result else 'NOT PRIME'}")
    except:
        pass


# ============================================================================
# 2. GCD (Greatest Common Divisor)
# ============================================================================
def gcd(a, b):
    """Calculate GCD using Euclidean algorithm"""
    while b:
        a, b = b, a % b
    return a


def test_gcd():
    """Test GCD calculation"""
    print("\n" + "=" * 60)
    print("2. GCD (GREATEST COMMON DIVISOR)")
    print("=" * 60)

    test_pairs = [(48, 18), (100, 75), (17, 19), (270, 192)]

    for a, b in test_pairs:
        result = gcd(a, b)
        print(f"   GCD({a}, {b}) = {result}")

    # User input
    try:
        a = int(input("\nEnter first number: "))
        b = int(input("Enter second number: "))
        result = gcd(a, b)
        print(f"   GCD({a}, {b}) = {result}")
    except:
        pass


# ============================================================================
# 3. Relatively Prime Check
# ============================================================================
def are_relatively_prime(a, b):
    """Check if two numbers are relatively prime (coprime)"""
    return gcd(a, b) == 1


def test_relatively_prime():
    """Test relatively prime checking"""
    print("\n" + "=" * 60)
    print("3. RELATIVELY PRIME (COPRIME) CHECK")
    print("=" * 60)

    test_pairs = [(15, 28), (21, 14), (17, 19), (25, 35)]

    for a, b in test_pairs:
        result = are_relatively_prime(a, b)
        gcd_val = gcd(a, b)
        print(
            f"   {a} and {b}: {'RELATIVELY PRIME' if result else 'NOT RELATIVELY PRIME'} (GCD = {gcd_val})"
        )

    # User input
    try:
        a = int(input("\nEnter first number: "))
        b = int(input("Enter second number: "))
        result = are_relatively_prime(a, b)
        print(
            f"   {a} and {b} are {'RELATIVELY PRIME' if result else 'NOT RELATIVELY PRIME'}"
        )
    except:
        pass


# ============================================================================
# 4. Multiplicative Inverse (Modular Inverse)
# ============================================================================
def extended_gcd(a, b):
    """Extended Euclidean Algorithm"""
    if a == 0:
        return b, 0, 1
    gcd_val, x1, y1 = extended_gcd(b % a, a)
    x = y1 - (b // a) * x1
    y = x1
    return gcd_val, x, y


def multiplicative_inverse(a, m):
    """Find multiplicative inverse of a modulo m"""
    gcd_val, x, y = extended_gcd(a, m)

    if gcd_val != 1:
        return None  # Inverse doesn't exist
    else:
        return (x % m + m) % m


def test_multiplicative_inverse():
    """Test multiplicative inverse calculation"""
    print("\n" + "=" * 60)
    print("4. MULTIPLICATIVE INVERSE (MODULAR INVERSE)")
    print("=" * 60)

    test_pairs = [(3, 11), (7, 26), (5, 12), (15, 26)]

    for a, m in test_pairs:
        inv = multiplicative_inverse(a, m)
        if inv:
            verification = (a * inv) % m
            print(f"   Inverse of {a} mod {m} = {inv}")
            print(f"   Verification: ({a} × {inv}) mod {m} = {verification}")
        else:
            print(f"   Inverse of {a} mod {m} doesn't exist (GCD ≠ 1)")
        print()

    # User input
    try:
        a = int(input("Enter number (a): "))
        m = int(input("Enter modulus (m): "))
        inv = multiplicative_inverse(a, m)
        if inv:
            print(f"   Inverse of {a} mod {m} = {inv}")
            print(f"   Verification: ({a} × {inv}) mod {m} = {(a * inv) % m}")
        else:
            print(f"   Inverse doesn't exist (GCD({a}, {m}) ≠ 1)")
    except:
        pass


# ============================================================================
# 5. RSA Algorithm Implementation
# ============================================================================
class RSA:
    """RSA encryption/decryption implementation"""

    def __init__(self, p=None, q=None):
        """Initialize RSA with two prime numbers"""
        if p and q:
            self.p = p
            self.q = q
        else:
            # Generate small primes for demonstration
            self.p = self.generate_prime(50, 100)
            self.q = self.generate_prime(50, 100)

        self.n = self.p * self.q
        self.phi = (self.p - 1) * (self.q - 1)
        self.e = self.select_e()
        self.d = multiplicative_inverse(self.e, self.phi)

    def generate_prime(self, min_val, max_val):
        """Generate a random prime number in range"""
        while True:
            num = random.randint(min_val, max_val)
            if is_prime(num):
                return num

    def select_e(self):
        """Select public exponent e"""
        # Common choice: 65537 (if valid), otherwise find one
        e = 65537
        if e < self.phi and gcd(e, self.phi) == 1:
            return e

        # Find a valid e
        for e in range(3, self.phi, 2):
            if gcd(e, self.phi) == 1:
                return e
        return 3

    def encrypt(self, plaintext):
        """Encrypt plaintext (integer)"""
        if plaintext >= self.n:
            raise ValueError(f"Plaintext must be less than n={self.n}")
        return pow(plaintext, self.e, self.n)

    def decrypt(self, ciphertext):
        """Decrypt ciphertext"""
        return pow(ciphertext, self.d, self.n)

    def encrypt_string(self, message):
        """Encrypt a string message"""
        # Convert string to numbers (ASCII values)
        encrypted = []
        for char in message:
            ascii_val = ord(char)
            if ascii_val >= self.n:
                raise ValueError(
                    f"Character '{char}' cannot be encrypted (ASCII {ascii_val} >= {self.n})"
                )
            encrypted.append(self.encrypt(ascii_val))
        return encrypted

    def decrypt_string(self, encrypted_list):
        """Decrypt list of encrypted numbers back to string"""
        decrypted = ""
        for num in encrypted_list:
            ascii_val = self.decrypt(num)
            decrypted += chr(ascii_val)
        return decrypted

    def print_keys(self):
        """Print RSA keys"""
        print(f"\n   Prime p: {self.p}")
        print(f"   Prime q: {self.q}")
        print(f"   Modulus n = p × q: {self.n}")
        print(f"   Phi(n) = (p-1) × (q-1): {self.phi}")
        print(f"   Public exponent e: {self.e}")
        print(f"   Private exponent d: {self.d}")
        print(f"\n   Public Key: ({self.e}, {self.n})")
        print(f"   Private Key: ({self.d}, {self.n})")


def test_rsa():
    """Test RSA implementation with timing"""
    print("\n" + "=" * 60)
    print("5. RSA ALGORITHM IMPLEMENTATION")
    print("=" * 60)

    # Example 1: Small primes for demonstration
    print("\n--- Example 1: Predefined Small Primes ---")
    p, q = 61, 53
    rsa = RSA(p, q)
    rsa.print_keys()

    # Encrypt/decrypt a number
    plaintext = 42
    print(f"\n   Original message (number): {plaintext}")

    start_time = time.time()
    ciphertext = rsa.encrypt(plaintext)
    encrypt_time = time.time() - start_time
    print(f"   Encrypted: {ciphertext}")
    print(f"   Encryption time: {encrypt_time * 1000:.6f} ms")

    start_time = time.time()
    decrypted = rsa.decrypt(ciphertext)
    decrypt_time = time.time() - start_time
    print(f"   Decrypted: {decrypted}")
    print(f"   Decryption time: {decrypt_time * 1000:.6f} ms")
    print(f"   Verification: {'SUCCESS' if plaintext == decrypted else 'FAILED'}")

    # Example 2: String encryption
    print("\n--- Example 2: String Encryption ---")
    message = "HELLO"
    print(f"   Original message: {message}")

    start_time = time.time()
    encrypted_msg = rsa.encrypt_string(message)
    encrypt_time = time.time() - start_time
    print(f"   Encrypted (list): {encrypted_msg}")
    print(f"   Encryption time: {encrypt_time * 1000:.6f} ms")

    start_time = time.time()
    decrypted_msg = rsa.decrypt_string(encrypted_msg)
    decrypt_time = time.time() - start_time
    print(f"   Decrypted message: {decrypted_msg}")
    print(f"   Decryption time: {decrypt_time * 1000:.6f} ms")
    print(f"   Verification: {'SUCCESS' if message == decrypted_msg else 'FAILED'}")

    # Example 3: Larger primes
    print("\n--- Example 3: Random Larger Primes ---")
    rsa2 = RSA()  # Generate random primes
    rsa2.print_keys()

    plaintext = 100
    print(f"\n   Original message: {plaintext}")

    start_time = time.time()
    ciphertext = rsa2.encrypt(plaintext)
    encrypt_time = time.time() - start_time
    print(f"   Encrypted: {ciphertext}")
    print(f"   Encryption time: {encrypt_time * 1000:.6f} ms")

    start_time = time.time()
    decrypted = rsa2.decrypt(ciphertext)
    decrypt_time = time.time() - start_time
    print(f"   Decrypted: {decrypted}")
    print(f"   Decryption time: {decrypt_time * 1000:.6f} ms")

    # Performance comparison
    print("\n--- Performance Summary ---")
    print(f"   Total encryption time: {encrypt_time * 1000:.6f} ms")
    print(f"   Total decryption time: {decrypt_time * 1000:.6f} ms")
    print(f"   Encryption/Decryption ratio: {encrypt_time / decrypt_time:.2f}")


# ============================================================================
# Main Program
# ============================================================================
def main():
    """Run all tests"""
    print("\n" + "=" * 60)
    print("LAB ASSIGNMENT 8: CRYPTOGRAPHY FUNDAMENTALS")
    print("=" * 60)

    while True:
        print("\n" + "=" * 60)
        print("MENU")
        print("=" * 60)
        print("1. Check Prime Number")
        print("2. Find GCD")
        print("3. Check Relatively Prime")
        print("4. Find Multiplicative Inverse")
        print("5. RSA Algorithm (with timing)")
        print("6. Run All Tests")
        print("0. Exit")
        print("=" * 60)

        try:
            choice = input("\nEnter your choice (0-6): ").strip()

            if choice == "1":
                test_prime()
            elif choice == "2":
                test_gcd()
            elif choice == "3":
                test_relatively_prime()
            elif choice == "4":
                test_multiplicative_inverse()
            elif choice == "5":
                test_rsa()
            elif choice == "6":
                test_prime()
                test_gcd()
                test_relatively_prime()
                test_multiplicative_inverse()
                test_rsa()
            elif choice == "0":
                print("\nExiting program. Goodbye!")
                break
            else:
                print("\nInvalid choice! Please try again.")

        except KeyboardInterrupt:
            print("\n\nProgram interrupted. Goodbye!")
            break
        except Exception as e:
            print(f"\nError: {e}")


if __name__ == "__main__":
    main()
