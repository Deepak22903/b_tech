import random

# Shared prime (p) and base (g) known to all parties
p = 23  # A small prime number (for demonstration purposes, larger primes are used in practice)
g = 5   # A primitive root modulo 23

# Step 1: Key generation for Sarvesh and Sam (legitimate participants)
# Sarvesh generates her private and public keys
sarvesh_private_key = random.randint(1, p - 1)
sarvesh_public_key = pow(g, sarvesh_private_key, p)
print("Sarvesh's Keys:")
print(f"  Private Key: {sarvesh_private_key}")
print(f"  Public Key: {sarvesh_public_key}\n")

# Sam generates his private and public keys
sam_private_key = random.randint(1, p - 1)
sam_public_key = pow(g, sam_private_key, p)
print("Sam's Keys:")
print(f"  Private Key: {sam_private_key}")
print(f"  Public Key: {sam_public_key}\n")

# Step 2: Key generation for the Hacker (MITM attacker)
# Hacker generates two sets of private and public keys
hacker_private_key_sarvesh = random.randint(1, p - 1)
hacker_private_key_sam = random.randint(1, p - 1)

hacker_public_key_for_sarvesh = pow(g, hacker_private_key_sarvesh, p)
hacker_public_key_for_sam = pow(g, hacker_private_key_sam, p)

print("Hacker's Keys:")
print(f"  Private Key (for Sarvesh): {hacker_private_key_sarvesh}")
print(f"  Public Key (for Sarvesh): {hacker_public_key_for_sarvesh}")
print(f"  Private Key (for Sam): {hacker_private_key_sam}")
print(f"  Public Key (for Sam): {hacker_public_key_for_sam}\n")

# Step 3: MITM attack simulation
# Hacker intercepts and modifies the public keys exchanged between Sarvesh and Sam
# Sarvesh receives the hacker's public key instead of Sam's
# Sam receives the hacker's public key instead of Sarvesh's

# Sarvesh computes a shared secret using the intercepted key (Hacker's public key)
sarvesh_shared_secret = pow(hacker_public_key_for_sam, sarvesh_private_key, p)

# Sam computes a shared secret using the intercepted key (Hacker's public key)
sam_shared_secret = pow(hacker_public_key_for_sarvesh, sam_private_key, p)

# Hacker computes shared secrets with both Sarvesh and Sam
hacker_shared_secret_with_sarvesh = pow(sarvesh_public_key, hacker_private_key_sarvesh, p)
hacker_shared_secret_with_sam = pow(sam_public_key, hacker_private_key_sam, p)

# Step 4: Output the results
print("--- Shared Secrets ---")
print(f"Sarvesh's Shared Secret (with Hacker unknowingly): {sarvesh_shared_secret}")
print(f"Sam's Shared Secret (with Hacker unknowingly): {sam_shared_secret}")
print(f"Hacker's Shared Secret with Sarvesh: {hacker_shared_secret_with_sarvesh}")
print(f"Hacker's Shared Secret with Sam: {hacker_shared_secret_with_sam}\n")

# Step 5: Explanation of MITM attack
print("--- Explanation of MITM Attack ---")
print("1. Sarvesh and Sam generate and exchange public keys.")
print("2. The hacker intercepts the public keys exchanged between them and replaces them with their own.")
print("3. As a result, Sarvesh and Sam unknowingly share their secrets with the hacker.")
print("4. The hacker can now decrypt and re-encrypt messages between Sarvesh and Sam, effectively acting as a middleman.")
