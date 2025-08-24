import string
from collections import Counter
import re


class CaesarCryptanalysis:
    def __init__(self):
        # Expected letter frequencies in English (in percentage)
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

        # Common English words for validation
        self.common_words = {
            "THE",
            "AND",
            "FOR",
            "ARE",
            "BUT",
            "NOT",
            "YOU",
            "ALL",
            "CAN",
            "HER",
            "WAS",
            "ONE",
            "OUR",
            "HAD",
            "WITH",
            "HAVE",
            "THIS",
            "WILL",
            "HIS",
            "FROM",
            "THEY",
            "SHE",
            "HIM",
            "BEEN",
            "HAS",
            "MORE",
            "HER",
            "WHO",
            "WHAT",
            "WERE",
            "SAID",
            "EACH",
            "WHICH",
            "THEIR",
            "TIME",
            "WOULD",
            "THERE",
            "WE",
            "WAY",
            "COULD",
            "MY",
            "THAN",
            "FIRST",
            "BEEN",
            "CALL",
            "ITS",
            "NOW",
            "FIND",
            "LONG",
            "DOWN",
            "DAY",
            "DID",
            "GET",
            "COME",
            "MADE",
            "MAY",
            "PART",
        }

    def caesar_decrypt(self, ciphertext, shift):
        """Decrypt text using Caesar cipher with given shift."""
        result = ""
        for char in ciphertext:
            if char.isalpha():
                ascii_offset = 65 if char.isupper() else 97
                shifted = (ord(char) - ascii_offset - shift) % 26
                result += chr(shifted + ascii_offset)
            else:
                result += char
        return result

    def calculate_frequency_score(self, text):
        """Calculate how closely text matches English letter frequencies."""
        # Remove non-alphabetic characters and convert to uppercase
        clean_text = "".join(char.upper() for char in text if char.isalpha())

        if not clean_text:
            return float("inf")

        # Count letter frequencies
        letter_count = Counter(clean_text)
        text_length = len(clean_text)

        # Calculate chi-squared statistic
        chi_squared = 0
        for letter in string.ascii_uppercase:
            observed = letter_count.get(letter, 0)
            expected = (self.english_freq[letter] / 100) * text_length

            if expected > 0:
                chi_squared += ((observed - expected) ** 2) / expected

        return chi_squared

    def calculate_word_score(self, text):
        """Calculate score based on common English words found."""
        words = re.findall(r"\b[A-Za-z]+\b", text.upper())
        common_word_count = sum(1 for word in words if word in self.common_words)

        if not words:
            return 0

        return common_word_count / len(words)

    def calculate_combined_score(self, text):
        """Combine frequency analysis and word recognition for better accuracy."""
        freq_score = self.calculate_frequency_score(text)
        word_score = self.calculate_word_score(text)

        # Lower frequency score is better, higher word score is better
        # Normalize and combine (weight word score more heavily)
        combined = freq_score - (word_score * 1000)
        return combined

    def analyze_caesar_cipher(self, ciphertext):
        """Perform complete cryptanalysis of Caesar cipher."""
        print("Caesar Cipher Cryptanalysis")
        print("=" * 50)
        print(f"Ciphertext: {ciphertext}")
        print("\nTrying all possible shifts (0-25):\n")

        results = []

        for shift in range(26):
            decrypted = self.caesar_decrypt(ciphertext, shift)
            freq_score = self.calculate_frequency_score(decrypted)
            word_score = self.calculate_word_score(decrypted)
            combined_score = self.calculate_combined_score(decrypted)

            results.append(
                {
                    "shift": shift,
                    "text": decrypted,
                    "freq_score": freq_score,
                    "word_score": word_score,
                    "combined_score": combined_score,
                }
            )

            print(
                f"Shift {shift:2d}: {decrypted[:60]}{'...' if len(decrypted) > 60 else ''}"
            )
            print(
                f"         Freq Score: {freq_score:.2f}, Word Score: {word_score:.3f}"
            )
            print()

        # Sort by combined score (lower is better)
        results.sort(key=lambda x: x["combined_score"])

        print("=" * 50)
        print("ANALYSIS RESULTS (Best candidates):")
        print("=" * 50)

        for i, result in enumerate(results[:5]):
            print(f"\nRank {i + 1}:")
            print(f"Shift: {result['shift']}")
            print(f"Text: {result['text']}")
            print(f"Frequency Score: {result['freq_score']:.2f}")
            print(f"Word Recognition Score: {result['word_score']:.3f}")
            print(f"Combined Score: {result['combined_score']:.2f}")

        print("\n" + "=" * 50)
        print("MOST LIKELY PLAINTEXT:")
        print("=" * 50)
        best_result = results[0]
        print(f"Shift used: {best_result['shift']}")
        print(f"Plaintext: {best_result['text']}")

        return best_result

    def interactive_analysis(self):
        """Interactive mode for analyzing user input."""
        print("Interactive Caesar Cipher Cryptanalysis")
        print("Enter 'quit' to exit\n")

        while True:
            ciphertext = input("Enter ciphertext to analyze: ").strip()

            if ciphertext.lower() == "quit":
                break

            if not ciphertext:
                print("Please enter some text to analyze.\n")
                continue

            try:
                self.analyze_caesar_cipher(ciphertext)
                print("\n" + "=" * 60 + "\n")
            except Exception as e:
                print(f"Error analyzing cipher: {e}\n")


def main():
    analyzer = CaesarCryptanalysis()

    # Example analysis with a sample ciphertext
    sample_cipher = "WKLV LV D VHFUHW PHVVDJH HQFRGHG ZLWK FDHVDU FLSKHU"
    print("EXAMPLE ANALYSIS:")
    print("=" * 60)
    analyzer.analyze_caesar_cipher(sample_cipher)

    print("\n" + "=" * 60)
    print("=" * 60 + "\n")

    # Interactive mode
    analyzer.interactive_analysis()


if __name__ == "__main__":
    main()
