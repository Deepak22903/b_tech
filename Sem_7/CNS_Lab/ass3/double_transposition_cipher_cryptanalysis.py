import itertools
import math
from collections import Counter
from pycipher import ColTrans

def get_bigram_frequencies():
    return {
        'TH': 1.52, 'HE': 1.28, 'IN': 0.94, 'ER': 0.94, 'AN': 0.82, 'RE': 0.68, 'ES': 0.56, 'ON': 0.57,
        'ST': 0.55, 'NT': 0.56, 'EN': 0.55, 'AT': 0.59, 'ED': 0.53, 'TO': 0.43, 'OR': 0.43, 'EA': 0.47,
        'HI': 0.46, 'IS': 0.46, 'OU': 0.50, 'AR': 0.48, 'AS': 0.33, 'DE': 0.38, 'RT': 0.42, 'VE': 0.42
    }

def score_text(text, bigram_frequencies):
    text = text.upper()
    bigrams = [text[i:i+2] for i in range(len(text) - 1)]
    score = 0
    print(f"Scoring text: {text}")
    for bigram, freq in bigram_frequencies.items():
        count = bigrams.count(bigram)
        if count > 0:
            print(f"  Found bigram: {bigram}, count: {count}")
        score += count * math.log(freq)
    print(f"  Score: {score}")
    return score

def decrypt_transposition(ciphertext, key):
    key_len = len(key)
    msg_len = len(ciphertext)
    num_cols = key_len
    num_rows = int(math.ceil(msg_len / num_cols))
    num_shaded_boxes = (num_cols * num_rows) - msg_len

    grid = [['' for _ in range(num_cols)] for _ in range(num_rows)]

    read_order = sorted(range(key_len), key=lambda k: key[k])

    cipher_idx = 0
    for col_idx in read_order:
        for row_idx in range(num_rows):
            if not (row_idx == num_rows - 1 and col_idx >= key_len - num_shaded_boxes):
                if cipher_idx < msg_len:
                    grid[row_idx][col_idx] = ciphertext[cipher_idx]
                    cipher_idx += 1

    plaintext = ''
    for row in grid:
        plaintext += ''.join(row)

    return plaintext

def cryptanalyze_double_transposition(ciphertext, key_len1, key_len2):
    bigram_frequencies = get_bigram_frequencies()
    best_score = -float('inf')
    best_plaintext = ""
    best_key1 = None
    best_key2 = None

    possible_keys1 = list(itertools.permutations(range(key_len1)))
    if key_len2 == 1:
        possible_keys2 = [(0,)]
    else:
        possible_keys2 = list(itertools.permutations(range(key_len2)))

    print("Step 1: Generating all possible keys (permutations of column indices)...")
    print(f"Number of possible keys for the first transposition: {len(possible_keys1)}")
    print(f"Number of possible keys for the second transposition: {len(possible_keys2)}")

    print("\nStep 2: Iterating through all possible key pairs and decrypting the ciphertext...")
    
    for i, key1 in enumerate(possible_keys1):
        intermediate_plaintext = decrypt_transposition(ciphertext, key1)
        
        for key2 in possible_keys2:
            plaintext = decrypt_transposition(intermediate_plaintext, key2)
            
            score = score_text(plaintext, bigram_frequencies)
            
            if score > best_score:
                best_score = score
                best_plaintext = plaintext
                best_key1 = key1
                best_key2 = key2
        
        if (i + 1) % 10 == 0:
            print(f"  ... tested {i + 1} primary keys")


    print("\nStep 3: Identifying the most likely plaintext based on bigram frequency analysis.")
    print("\n--- Cryptanalysis Complete ---")
    print(f"Best Score: {best_score}")
    print(f"Best Key 1: {best_key1}")
    print(f"Best Key 2: {best_key2}")
    print(f"Plaintext: {best_plaintext}")


if __name__ == '__main__':
    ciphertext = "EOHLL"
    key_len1 = 3
    key_len2 = 1

    print("--- Cryptanalysis of Double Transposition Cipher ---")
    print(f"Ciphertext: {ciphertext}")
    print(f"Key Length 1: {key_len1}")
    print(f"Key Length 2: {key_len2}")
    print("----------------------------------------------------")
    
    cryptanalyze_double_transposition(ciphertext, key_len1, key_len2)