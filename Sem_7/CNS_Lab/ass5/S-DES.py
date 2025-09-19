import time
import random
import string


class SimplifiedDES:
    """
    Simplified DES (S-DES) Implementation
    This class implements the complete S-DES algorithm including:
    - Key generation and scheduling
    - Encryption and decryption
    - All necessary permutations and S-box operations
    """

    def __init__(self):
        # Initial Permutation (IP)
        self.IP = [2, 6, 3, 1, 4, 8, 5, 7]

        # Final Permutation (IP^-1)
        self.IP_INV = [4, 1, 3, 5, 7, 2, 8, 6]

        # Expansion/Permutation (E/P)
        self.EP = [4, 1, 2, 3, 2, 3, 4, 1]

        # Permutation P4
        self.P4 = [2, 4, 3, 1]

        # Permutation P10 for key generation
        self.P10 = [3, 5, 2, 7, 4, 10, 1, 9, 8, 6]

        # Permutation P8 for key generation
        self.P8 = [6, 3, 7, 4, 8, 5, 10, 9]

        # S-Box 0
        self.S0 = [[1, 0, 3, 2], [3, 2, 1, 0], [0, 2, 1, 3], [3, 1, 3, 2]]

        # S-Box 1
        self.S1 = [[0, 1, 2, 3], [2, 0, 1, 3], [3, 0, 1, 0], [2, 1, 0, 3]]

    def permute(self, data, table):
        """Apply permutation based on given table"""
        return [data[i - 1] for i in table]

    def left_shift(self, data, shifts):
        """Perform left circular shift"""
        return data[shifts:] + data[:shifts]

    def xor(self, a, b):
        """XOR two binary lists"""
        return [x ^ y for x, y in zip(a, b)]

    def s_box_lookup(self, data, s_box):
        """Perform S-box substitution"""
        # First and last bits form row
        row = (data[0] << 1) | data[3]
        # Middle bits form column
        col = (data[1] << 1) | data[2]

        # Get value from S-box
        val = s_box[row][col]

        # Convert to 2-bit binary
        return [(val >> 1) & 1, val & 1]

    def string_to_bits(self, text):
        """Convert string to list of bits"""
        bits = []
        for char in text:
            # Convert each character to 8-bit binary
            char_bits = [int(b) for b in format(ord(char), "08b")]
            bits.extend(char_bits)
        return bits

    def bits_to_string(self, bits):
        """Convert list of bits to string"""
        text = ""
        # Process 8 bits at a time
        for i in range(0, len(bits), 8):
            byte = bits[i : i + 8]
            if len(byte) == 8:  # Ensure we have a complete byte
                char_code = sum(bit * (2 ** (7 - j)) for j, bit in enumerate(byte))
                text += chr(char_code)
        return text

    def generate_keys(self, key_10bit):
        """
        Generate K1 and K2 from 10-bit master key
        """
        print(f"Master key (10-bit): {key_10bit}")

        # Step 1: Apply P10 permutation
        p10_result = self.permute(key_10bit, self.P10)
        print(f"After P10: {p10_result}")

        # Step 2: Split into two 5-bit halves
        left_half = p10_result[:5]
        right_half = p10_result[5:]
        print(f"Left half: {left_half}, Right half: {right_half}")

        # Step 3: Left shift by 1 for K1
        left_k1 = self.left_shift(left_half, 1)
        right_k1 = self.left_shift(right_half, 1)
        combined_k1 = left_k1 + right_k1

        # Step 4: Apply P8 to get K1
        k1 = self.permute(combined_k1, self.P8)
        print(f"K1: {k1}")

        # Step 5: Left shift by 2 more (total 3) for K2
        left_k2 = self.left_shift(left_k1, 2)
        right_k2 = self.left_shift(right_k1, 2)
        combined_k2 = left_k2 + right_k2

        # Step 6: Apply P8 to get K2
        k2 = self.permute(combined_k2, self.P8)
        print(f"K2: {k2}")

        return k1, k2

    def f_function(self, right_half, subkey):
        """
        The f-function used in Feistel rounds
        """
        # Step 1: Expansion/Permutation
        expanded = self.permute(right_half, self.EP)

        # Step 2: XOR with subkey
        xor_result = self.xor(expanded, subkey)

        # Step 3: S-box substitution
        left_4bits = xor_result[:4]
        right_4bits = xor_result[4:]

        s0_output = self.s_box_lookup(left_4bits, self.S0)
        s1_output = self.s_box_lookup(right_4bits, self.S1)

        # Step 4: Combine S-box outputs
        combined = s0_output + s1_output

        # Step 5: Apply P4 permutation
        result = self.permute(combined, self.P4)

        return result

    def encrypt_block(self, plaintext_8bit, k1, k2):
        """
        Encrypt a single 8-bit block
        """
        print(f"\n--- Encrypting block: {plaintext_8bit} ---")

        # Step 1: Initial Permutation
        ip_result = self.permute(plaintext_8bit, self.IP)
        print(f"After IP: {ip_result}")

        # Step 2: Split into left and right halves
        left = ip_result[:4]
        right = ip_result[4:]
        print(f"Initial: Left={left}, Right={right}")

        # Step 3: First Feistel round with K1
        f_output = self.f_function(right, k1)
        new_left = self.xor(left, f_output)
        new_right = right
        print(f"After Round 1: Left={new_left}, Right={new_right}")

        # Step 4: Swap halves
        left, right = new_right, new_left
        print(f"After Swap: Left={left}, Right={right}")

        # Step 5: Second Feistel round with K2
        f_output = self.f_function(right, k2)
        new_left = self.xor(left, f_output)
        new_right = right
        print(f"After Round 2: Left={new_left}, Right={new_right}")

        # Step 6: Combine halves
        combined = new_left + new_right

        # Step 7: Final Permutation
        ciphertext = self.permute(combined, self.IP_INV)
        print(f"Final ciphertext: {ciphertext}")

        return ciphertext

    def decrypt_block(self, ciphertext_8bit, k1, k2):
        """
        Decrypt a single 8-bit block (same as encrypt but with keys reversed)
        """
        print(f"\n--- Decrypting block: {ciphertext_8bit} ---")

        # Step 1: Initial Permutation
        ip_result = self.permute(ciphertext_8bit, self.IP)
        print(f"After IP: {ip_result}")

        # Step 2: Split into left and right halves
        left = ip_result[:4]
        right = ip_result[4:]
        print(f"Initial: Left={left}, Right={right}")

        # Step 3: First Feistel round with K2 (reversed order)
        f_output = self.f_function(right, k2)
        new_left = self.xor(left, f_output)
        new_right = right
        print(f"After Round 1: Left={new_left}, Right={new_right}")

        # Step 4: Swap halves
        left, right = new_right, new_left
        print(f"After Swap: Left={left}, Right={right}")

        # Step 5: Second Feistel round with K1 (reversed order)
        f_output = self.f_function(right, k1)
        new_left = self.xor(left, f_output)
        new_right = right
        print(f"After Round 2: Left={new_left}, Right={new_right}")

        # Step 6: Combine halves
        combined = new_left + new_right

        # Step 7: Final Permutation
        plaintext = self.permute(combined, self.IP_INV)
        print(f"Final plaintext: {plaintext}")

        return plaintext

    def encrypt_message(self, message, key_10bit, verbose=True):
        """
        Encrypt a complete message
        """
        if verbose:
            print(f"\n=== ENCRYPTING MESSAGE: '{message}' ===")

        # Generate subkeys
        k1, k2 = self.generate_keys(key_10bit)

        # Convert message to bits
        message_bits = self.string_to_bits(message)
        if verbose:
            print(f"Message in bits: {message_bits}")

        # Pad message to multiple of 8 bits if necessary
        while len(message_bits) % 8 != 0:
            message_bits.append(0)

        # Encrypt each 8-bit block
        encrypted_bits = []
        for i in range(0, len(message_bits), 8):
            block = message_bits[i : i + 8]
            encrypted_block = self.encrypt_block(block, k1, k2)
            encrypted_bits.extend(encrypted_block)

        # Convert back to string
        encrypted_message = self.bits_to_string(encrypted_bits)

        if verbose:
            print(f"Encrypted message: '{encrypted_message}'")
            print(f"Encrypted bits: {encrypted_bits}")

        return encrypted_message, encrypted_bits

    def decrypt_message(self, encrypted_bits, key_10bit, verbose=True):
        """
        Decrypt a complete message from encrypted bits
        """
        if verbose:
            print(f"\n=== DECRYPTING MESSAGE ===")
            print(f"Encrypted bits: {encrypted_bits}")

        # Generate subkeys
        k1, k2 = self.generate_keys(key_10bit)

        # Decrypt each 8-bit block
        decrypted_bits = []
        for i in range(0, len(encrypted_bits), 8):
            block = encrypted_bits[i : i + 8]
            decrypted_block = self.decrypt_block(block, k1, k2)
            decrypted_bits.extend(decrypted_block)

        # Convert back to string
        decrypted_message = self.bits_to_string(decrypted_bits)

        if verbose:
            print(
                f"Decrypted message: '{decrypted_message.rstrip(chr(0))}'"
            )  # Remove null padding

        return decrypted_message.rstrip(chr(0))  # Remove null padding


def generate_test_messages():
    """Generate test messages of different lengths"""
    messages = {
        "short": "Hi",
        "medium": "Hello World! This is a test.",
        "long": "This is a much longer message designed to test the performance of our Simplified DES implementation with multiple blocks of data.",
        "very_long": "".join(
            random.choices(string.ascii_letters + string.digits + " ", k=200)
        ),
    }
    return messages


def performance_test():
    """Test performance with different message lengths"""
    print("\n" + "=" * 80)
    print("PERFORMANCE ANALYSIS")
    print("=" * 80)

    # Initialize S-DES
    sdes = SimplifiedDES()

    # Test key
    test_key = [1, 0, 1, 0, 0, 0, 0, 0, 1, 0]

    # Generate test messages
    test_messages = generate_test_messages()

    results = []

    for category, message in test_messages.items():
        print(
            f"\n--- Testing {category.upper()} message ({len(message)} characters) ---"
        )
        print(f"Message: '{message[:50]}{'...' if len(message) > 50 else ''}'")

        # Test encryption time
        start_time = time.time()
        encrypted_msg, encrypted_bits = sdes.encrypt_message(
            message, test_key, verbose=False
        )
        encryption_time = time.time() - start_time

        # Test decryption time
        start_time = time.time()
        decrypted_msg = sdes.decrypt_message(encrypted_bits, test_key, verbose=False)
        decryption_time = time.time() - start_time

        # Verify correctness
        is_correct = message == decrypted_msg

        results.append(
            {
                "category": category,
                "length": len(message),
                "encryption_time": encryption_time * 1000,  # Convert to milliseconds
                "decryption_time": decryption_time * 1000,
                "total_time": (encryption_time + decryption_time) * 1000,
                "correct": is_correct,
            }
        )

        print(f"Encryption time: {encryption_time * 1000:.4f} ms")
        print(f"Decryption time: {decryption_time * 1000:.4f} ms")
        print(f"Verification: {'✓ PASS' if is_correct else '✗ FAIL'}")

    # Print summary table
    print(f"\n{'=' * 80}")
    print("PERFORMANCE SUMMARY")
    print(f"{'=' * 80}")
    print(
        f"{'Category':<12} {'Length':<8} {'Encrypt(ms)':<12} {'Decrypt(ms)':<12} {'Total(ms)':<10} {'Status':<8}"
    )
    print("-" * 80)

    for result in results:
        print(
            f"{result['category']:<12} {result['length']:<8} {result['encryption_time']:<12.4f} "
            f"{result['decryption_time']:<12.4f} {result['total_time']:<10.4f} "
            f"{'✓' if result['correct'] else '✗':<8}"
        )

    return results


def main():
    """Main demonstration of S-DES algorithm"""
    print("SIMPLIFIED DES (S-DES) IMPLEMENTATION")
    print("=" * 50)

    # Initialize S-DES
    sdes = SimplifiedDES()

    # Test key (10-bit)
    master_key = [1, 0, 1, 0, 0, 0, 0, 0, 1, 0]

    # Example 1: Simple demonstration
    print("\n1. BASIC DEMONSTRATION")
    print("-" * 30)
    test_message = "Hello"
    print(f"Original message: '{test_message}'")

    # Encrypt
    encrypted_msg, encrypted_bits = sdes.encrypt_message(test_message, master_key)

    # Decrypt
    decrypted_msg = sdes.decrypt_message(encrypted_bits, master_key)

    print(f"\nVerification: {'SUCCESS' if test_message == decrypted_msg else 'FAILED'}")

    # Example 2: Step-by-step single block
    print(f"\n\n2. DETAILED SINGLE BLOCK EXAMPLE")
    print("-" * 40)
    single_char = "A"
    print(f"Encrypting single character: '{single_char}'")

    # Generate keys
    k1, k2 = sdes.generate_keys(master_key)

    # Convert to bits
    char_bits = sdes.string_to_bits(single_char)
    print(f"Character '{single_char}' in binary: {char_bits}")

    # Encrypt the 8-bit block
    encrypted_block = sdes.encrypt_block(char_bits, k1, k2)

    # Decrypt the block
    decrypted_block = sdes.decrypt_block(encrypted_block, k1, k2)

    # Convert back to character
    decrypted_char = sdes.bits_to_string(decrypted_block)
    print(f"Decrypted back to: '{decrypted_char}'")
    print(
        f"Single block verification: {'SUCCESS' if single_char == decrypted_char else 'FAILED'}"
    )

    # Example 3: Performance analysis
    performance_test()

    # Example 4: Different keys demonstration
    print(f"\n\n3. DIFFERENT KEYS DEMONSTRATION")
    print("-" * 40)
    test_msg = "Test"
    keys = [
        [1, 0, 1, 0, 0, 0, 0, 0, 1, 0],  # Key 1
        [0, 1, 0, 1, 1, 1, 1, 1, 0, 1],  # Key 2
        [1, 1, 1, 0, 0, 1, 1, 0, 1, 0],  # Key 3
    ]

    for i, key in enumerate(keys, 1):
        print(f"\nKey {i}: {key}")
        encrypted, _ = sdes.encrypt_message(test_msg, key, verbose=False)
        print(f"'{test_msg}' → Encrypted: {[ord(c) for c in encrypted]}")


if __name__ == "__main__":
    main()
