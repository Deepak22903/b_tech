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

    def generate_keys(self, key_10bit, verbose=False):
        """
        Generate K1 and K2 from 10-bit master key
        """
        if verbose:
            print(f"Master key: {key_10bit}")

        # Apply P10 permutation
        p10_result = self.permute(key_10bit, self.P10)

        # Split into two 5-bit halves
        left_half = p10_result[:5]
        right_half = p10_result[5:]

        # Left shift by 1 for K1
        left_k1 = self.left_shift(left_half, 1)
        right_k1 = self.left_shift(right_half, 1)
        combined_k1 = left_k1 + right_k1
        k1 = self.permute(combined_k1, self.P8)

        # Left shift by 2 more for K2
        left_k2 = self.left_shift(left_k1, 2)
        right_k2 = self.left_shift(right_k1, 2)
        combined_k2 = left_k2 + right_k2
        k2 = self.permute(combined_k2, self.P8)

        if verbose:
            print(f"K1: {k1}, K2: {k2}")

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

    def encrypt_block(self, plaintext_8bit, k1, k2, verbose=False):
        """
        Encrypt a single 8-bit block
        """
        if verbose:
            print(f"Encrypting: {plaintext_8bit}")

        # Initial Permutation
        ip_result = self.permute(plaintext_8bit, self.IP)

        # Split and first round
        left, right = ip_result[:4], ip_result[4:]
        f_output = self.f_function(right, k1)
        new_left = self.xor(left, f_output)

        # Swap and second round
        left, right = right, new_left
        f_output = self.f_function(right, k2)
        new_left = self.xor(left, f_output)

        # Final permutation
        combined = new_left + right
        ciphertext = self.permute(combined, self.IP_INV)

        if verbose:
            print(f"Encrypted: {ciphertext}")

        return ciphertext

    def decrypt_block(self, ciphertext_8bit, k1, k2, verbose=False):
        """
        Decrypt a single 8-bit block (same as encrypt but with keys reversed)
        """
        if verbose:
            print(f"Decrypting: {ciphertext_8bit}")

        # Initial Permutation
        ip_result = self.permute(ciphertext_8bit, self.IP)

        # Split and first round (with K2)
        left, right = ip_result[:4], ip_result[4:]
        f_output = self.f_function(right, k2)
        new_left = self.xor(left, f_output)

        # Swap and second round (with K1)
        left, right = right, new_left
        f_output = self.f_function(right, k1)
        new_left = self.xor(left, f_output)

        # Final permutation
        combined = new_left + right
        plaintext = self.permute(combined, self.IP_INV)

        if verbose:
            print(f"Decrypted: {plaintext}")

        return plaintext

    def encrypt_message(self, message, key_10bit, verbose=False):
        """
        Encrypt a complete message
        """
        if verbose:
            print(f"Encrypting: '{message}'")

        # Generate subkeys
        k1, k2 = self.generate_keys(key_10bit, verbose)

        # Convert to bits and pad
        message_bits = self.string_to_bits(message)
        while len(message_bits) % 8 != 0:
            message_bits.append(0)

        # Encrypt each block
        encrypted_bits = []
        for i in range(0, len(message_bits), 8):
            block = message_bits[i : i + 8]
            encrypted_block = self.encrypt_block(block, k1, k2, verbose)
            encrypted_bits.extend(encrypted_block)

        encrypted_message = self.bits_to_string(encrypted_bits)

        if verbose:
            print(f"Result: '{encrypted_message}'")

        return encrypted_message, encrypted_bits

    def decrypt_message(self, encrypted_bits, key_10bit, verbose=False):
        """
        Decrypt a complete message from encrypted bits
        """
        if verbose:
            print(f"Decrypting message...")

        # Generate subkeys
        k1, k2 = self.generate_keys(key_10bit, verbose)

        # Decrypt each block
        decrypted_bits = []
        for i in range(0, len(encrypted_bits), 8):
            block = encrypted_bits[i : i + 8]
            decrypted_block = self.decrypt_block(block, k1, k2, verbose)
            decrypted_bits.extend(decrypted_block)

        decrypted_message = self.bits_to_string(decrypted_bits)

        if verbose:
            print(f"Result: '{decrypted_message.rstrip(chr(0))}'")

        return decrypted_message.rstrip(chr(0))


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
    print("\nPERFORMANCE ANALYSIS")
    print("=" * 50)

    sdes = SimplifiedDES()
    test_key = [1, 0, 1, 0, 0, 0, 0, 0, 1, 0]

    test_messages = {
        "Short": "Hi",
        "Medium": "Hello World! This is a test.",
        "Long": "This is a much longer message for testing performance with multiple blocks.",
        "Very Long": "".join(random.choices(string.ascii_letters + " ", k=100)),
    }

    print(
        f"{'Type':<12} {'Length':<8} {'Encrypt(ms)':<12} {'Decrypt(ms)':<12} {'Status':<8}"
    )
    print("-" * 60)

    for category, message in test_messages.items():
        # Encryption timing
        start = time.time()
        encrypted_msg, encrypted_bits = sdes.encrypt_message(
            message, test_key, verbose=False
        )
        enc_time = (time.time() - start) * 1000

        # Decryption timing
        start = time.time()
        decrypted_msg = sdes.decrypt_message(encrypted_bits, test_key, verbose=False)
        dec_time = (time.time() - start) * 1000

        status = "✓" if message == decrypted_msg else "✗"

        print(
            f"{category:<12} {len(message):<8} {enc_time:<12.4f} {dec_time:<12.4f} {status:<8}"
        )


def main():
    """Main demonstration"""
    print("SIMPLIFIED DES (S-DES) IMPLEMENTATION")
    print("=" * 40)

    sdes = SimplifiedDES()
    master_key = [1, 0, 1, 0, 0, 0, 0, 0, 1, 0]

    # Basic demonstration
    print("\n1. BASIC EXAMPLE")
    test_message = "Hello"
    print(f"Original: '{test_message}'")

    encrypted_msg, encrypted_bits = sdes.encrypt_message(
        test_message, master_key, verbose=True
    )
    decrypted_msg = sdes.decrypt_message(encrypted_bits, master_key, verbose=True)

    print(
        f"Verification: {'✓ SUCCESS' if test_message == decrypted_msg else '✗ FAILED'}"
    )

    # Step-by-step example
    print(f"\n2. STEP-BY-STEP SINGLE BLOCK")
    char = "A"
    print(f"Processing: '{char}'")

    k1, k2 = sdes.generate_keys(master_key, verbose=True)
    char_bits = sdes.string_to_bits(char)
    print(f"Binary: {char_bits}")

    encrypted_block = sdes.encrypt_block(char_bits, k1, k2, verbose=True)
    decrypted_block = sdes.decrypt_block(encrypted_block, k1, k2, verbose=True)
    decrypted_char = sdes.bits_to_string(decrypted_block)

    print(
        f"Result: '{decrypted_char}' - {'✓ SUCCESS' if char == decrypted_char else '✗ FAILED'}"
    )

    # Performance test
    performance_test()


if __name__ == "__main__":
    main()
