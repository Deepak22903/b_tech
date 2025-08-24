import re
from collections import Counter
from itertools import permutations
import math


class DoubleTranspositionCryptanalysis:
    def __init__(self):
        # English letter frequency (approximate percentages)
        self.english_freq = {
            "A": 8.12,
            "B": 1.49,
            "C": 2.78,
            "D": 4.25,
            "E": 12.02,
            "F": 2.23,
            "G": 2.02,
            "H": 6.09,
            "I": 6.97,
            "J": 0.15,
            "K": 0.77,
            "L": 4.03,
            "M": 2.41,
            "N": 6.75,
            "O": 7.51,
            "P": 1.93,
            "Q": 0.10,
            "R": 5.99,
            "S": 6.33,
            "T": 9.06,
            "U": 2.76,
            "V": 0.98,
            "W": 2.36,
            "X": 0.15,
            "Y": 1.97,
            "Z": 0.07,
        }

        # Common English bigrams and trigrams for additional analysis
        self.common_bigrams = [
            "TH",
            "HE",
            "IN",
            "ER",
            "AN",
            "RE",
            "ED",
            "ND",
            "ON",
            "EN",
        ]
        self.common_trigrams = [
            "THE",
            "AND",
            "ING",
            "HER",
            "HAT",
            "HIS",
            "THA",
            "ERE",
            "FOR",
            "ENT",
        ]

    def calculate_ic(self, text):
        """Calculate Index of Coincidence"""
        text = text.upper().replace(" ", "")
        n = len(text)
        if n <= 1:
            return 0

        freq = Counter(text)
        ic = sum(f * (f - 1) for f in freq.values()) / (n * (n - 1))
        return ic

    def chi_squared_score(self, text):
        """Calculate chi-squared statistic compared to English"""
        text = text.upper().replace(" ", "")
        if not text:
            return float("inf")

        observed = Counter(text)
        n = len(text)
        chi_squared = 0

        for letter in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
            expected = (self.english_freq[letter] / 100) * n
            observed_count = observed.get(letter, 0)
            if expected > 0:
                chi_squared += ((observed_count - expected) ** 2) / expected

        return chi_squared

    def count_common_patterns(self, text):
        """Count common English patterns (bigrams, trigrams)"""
        text = text.upper().replace(" ", "")
        score = 0

        # Count bigrams
        for i in range(len(text) - 1):
            bigram = text[i : i + 2]
            if bigram in self.common_bigrams:
                score += 2

        # Count trigrams
        for i in range(len(text) - 2):
            trigram = text[i : i + 3]
            if trigram in self.common_trigrams:
                score += 3

        return score

    def fitness_score(self, text):
        """Comprehensive fitness score for English-like text"""
        ic = self.calculate_ic(text)
        chi2 = self.chi_squared_score(text)
        patterns = self.count_common_patterns(text)

        # English IC is around 0.067
        ic_score = abs(ic - 0.067)

        # Lower chi-squared is better, normalize it
        chi2_score = chi2 / 1000 if chi2 < float("inf") else 10

        # Higher pattern count is better
        pattern_score = patterns / max(len(text) // 10, 1)

        # Combined score (lower is better)
        return ic_score + chi2_score - pattern_score

    def columnar_transpose_decrypt(self, ciphertext, key):
        """Decrypt using columnar transposition with given key"""
        if not ciphertext or not key:
            return ""

        # Remove spaces and convert to uppercase
        ciphertext = ciphertext.upper().replace(" ", "")

        # Calculate grid dimensions
        num_cols = len(key)
        num_rows = math.ceil(len(ciphertext) / num_cols)

        # Pad ciphertext if necessary
        padded_length = num_rows * num_cols
        ciphertext += "X" * (padded_length - len(ciphertext))

        # Create sorted key positions
        sorted_key = sorted(enumerate(key), key=lambda x: x[1])

        # Fill the grid column by column according to sorted key
        grid = [[""] * num_cols for _ in range(num_rows)]

        pos = 0
        for _, orig_col in sorted_key:
            for row in range(num_rows):
                if pos < len(ciphertext):
                    grid[row][orig_col] = ciphertext[pos]
                    pos += 1

        # Read row by row
        plaintext = ""
        for row in range(num_rows):
            for col in range(num_cols):
                plaintext += grid[row][col]

        return plaintext.rstrip("X")

    def generate_keys(self, max_length=6):
        """Generate possible keys for brute force attack"""
        keys = []

        # Try numeric keys of different lengths
        for length in range(2, max_length + 1):
            # Generate permutations of numbers 1 to length
            for perm in permutations(range(1, length + 1)):
                keys.append(perm)

        # Try some common alphabetic patterns
        common_words = ["KEY", "CODE", "WORD", "TEXT", "HELP"]
        for word in common_words:
            if len(word) <= max_length:
                # Convert word to numeric key based on alphabetical order
                sorted_chars = sorted(enumerate(word), key=lambda x: x[1])
                key = [0] * len(word)
                for i, (orig_pos, _) in enumerate(sorted_chars):
                    key[orig_pos] = i + 1
                keys.append(tuple(key))

        return keys

    def brute_force_single_transposition(self, ciphertext, max_key_length=6):
        """Attempt to break single transposition cipher"""
        print("Attempting single transposition decryption...")

        keys = self.generate_keys(max_key_length)
        best_score = float("inf")
        best_result = ""
        best_key = None

        for key in keys:
            try:
                decrypted = self.columnar_transpose_decrypt(ciphertext, key)
                if decrypted:  # Only process if decryption was successful
                    score = self.fitness_score(decrypted)

                    if score < best_score:
                        best_score = score
                        best_result = decrypted
                        best_key = key
            except Exception as e:
                continue

        return best_result, best_key, best_score

    def analyze_double_transposition(self, ciphertext, max_key_length=5):
        """Main function to analyze double transposition cipher"""
        print(f"Analyzing ciphertext: {ciphertext}")
        print(f"Length: {len(ciphertext)}")
        print(f"Initial IC: {self.calculate_ic(ciphertext):.4f}")
        print(f"Initial Chi-squared: {self.chi_squared_score(ciphertext):.2f}")
        print("-" * 50)

        # Step 1: Try single transposition first
        single_result, single_key, single_score = self.brute_force_single_transposition(
            ciphertext, max_key_length
        )

        print("Best single transposition attempt:")
        print(f"Key: {single_key}")
        print(f"Score: {single_score:.4f}")
        if single_result:
            print(f"Result: {single_result}")
            print(f"IC: {self.calculate_ic(single_result):.4f}")
        else:
            print("Result: No valid decryption found")
            print("IC: N/A")
        print("-" * 50)

        # Step 2: Try double transposition
        print("Attempting double transposition decryption...")

        keys = self.generate_keys(max_key_length)
        best_score = float("inf")
        best_result = ""
        best_keys = (None, None)

        # Try all combinations of two keys
        for i, key1 in enumerate(keys[:25]):  # Increased limit for better coverage
            if i % 5 == 0:
                print(f"Progress: Testing key {i + 1}/25...")

            # First decryption
            try:
                intermediate = self.columnar_transpose_decrypt(ciphertext, key1)
                if not intermediate:
                    continue
            except:
                continue

            for key2 in keys[:20]:  # Inner loop with fewer keys
                try:
                    # Second decryption
                    final_result = self.columnar_transpose_decrypt(intermediate, key2)
                    if not final_result:
                        continue

                    score = self.fitness_score(final_result)

                    if score < best_score:
                        best_score = score
                        best_result = final_result
                        best_keys = (key1, key2)

                        # Print promising results
                        if single_result and score < single_score:
                            print(f"Promising result found!")
                            print(f"Keys: {key1}, {key2}")
                            print(f"Score: {score:.4f}")
                            print(f"Partial result: {final_result[:50]}...")

                except Exception as e:
                    continue

        print("\n" + "=" * 50)
        print("CRYPTANALYSIS RESULTS")
        print("=" * 50)

        print("\nBest Single Transposition:")
        print(f"Key: {single_key}")
        print(f"Score: {single_score:.4f}")
        if single_result:
            print(f"Result: {single_result}")
        else:
            print("Result: No valid decryption found")

        print("\nBest Double Transposition:")
        print(f"Keys: {best_keys}")
        print(f"Score: {best_score:.4f}")
        if best_result:
            print(f"Result: {best_result}")
        else:
            print("Result: No valid decryption found")

        if best_result and single_result and best_score < single_score:
            print("\n*** Double transposition appears to be the correct method ***")
            return best_result, best_keys
        elif single_result and (not best_result or single_score <= best_score):
            print("\n*** Single transposition appears to be the correct method ***")
            return single_result, single_key
        elif best_result:
            print("\n*** Double transposition appears to be the correct method ***")
            return best_result, best_keys
        else:
            print("\n*** No valid decryption found with current parameters ***")
            return None, None


# Example usage and demonstration
if __name__ == "__main__":
    # Create analyzer instance
    analyzer = DoubleTranspositionCryptanalysis()

    # Example 1: Known double transposition cipher
    print("EXAMPLE 1: Double Transposition Cipher")
    print("=" * 60)

    # Let's create a test case first
    original_text = "ATTACKATDAWN"
    print(f"Original text: {original_text}")

    # Encrypt with double transposition (keys: (3,1,2) and (2,3,1))
    # First encryption with key (3,1,2)
    def encrypt_columnar(text, key):
        text = text.upper().replace(" ", "")
        num_cols = len(key)
        num_rows = math.ceil(len(text) / num_cols)

        # Pad text
        padded_text = text + "X" * (num_rows * num_cols - len(text))

        # Create grid - fill row by row
        grid = []
        pos = 0
        for row in range(num_rows):
            grid_row = []
            for col in range(num_cols):
                if pos < len(padded_text):
                    grid_row.append(padded_text[pos])
                else:
                    grid_row.append("X")
                pos += 1
            grid.append(grid_row)

        # Read columns in sorted key order
        result = ""
        # Create position mapping: key value -> original column position
        key_positions = [(key[i], i) for i in range(len(key))]
        key_positions.sort()  # Sort by key value

        for _, col_idx in key_positions:
            for row in range(num_rows):
                result += grid[row][col_idx]

        return result

    # Double encrypt
    key1 = (3, 1, 2)
    key2 = (2, 3, 1)

    first_encrypt = encrypt_columnar(original_text, key1)
    double_encrypted = encrypt_columnar(first_encrypt, key2)

    print(f"After first encryption (key {key1}): {first_encrypt}")
    print(f"After second encryption (key {key2}): {double_encrypted}")
    print()

    # Now analyze the double encrypted text
    result, keys = analyzer.analyze_double_transposition(
        double_encrypted, max_key_length=4
    )

    print("\n" + "=" * 60)
    print("EXAMPLE 2: Try with a different ciphertext")
    print("=" * 60)

    # Another example - you can replace this with your actual ciphertext
    mystery_cipher = "TROFSIOEHTANETKLAWSWYDODTNLORUNYHTEPTHAISETG"
    result2, keys2 = analyzer.analyze_double_transposition(
        mystery_cipher, max_key_length=4
    )
