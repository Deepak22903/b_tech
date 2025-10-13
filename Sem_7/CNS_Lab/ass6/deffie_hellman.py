#!/usr/bin/env python3
"""
Diffie-Hellman Key Exchange with Man-In-The-Middle Attack Demonstration
"""


def power_mod(base, exp, mod):
    """Calculate (base^exp) % mod efficiently"""
    return pow(base, exp, mod)


def normal_diffie_hellman():
    """Demonstrate normal Diffie-Hellman key exchange"""
    print("=" * 60)
    print("NORMAL DIFFIE-HELLMAN KEY EXCHANGE")
    print("=" * 60)

    # Public parameters (known to everyone)
    p = 23  # Prime modulus
    g = 5  # Generator
    print(f"\n1. Public Parameters:")
    print(f"   Prime (p) = {p}")
    print(f"   Generator (g) = {g}")

    # Alice's private key
    alice_private = 6
    print(f"\n2. Alice's Private Key:")
    print(f"   a = {alice_private} (secret)")

    # Bob's private key
    bob_private = 15
    print(f"\n3. Bob's Private Key:")
    print(f"   b = {bob_private} (secret)")

    # Alice computes public key
    alice_public = power_mod(g, alice_private, p)
    print(f"\n4. Alice Computes Public Key:")
    print(f"   A = g^a mod p = {g}^{alice_private} mod {p} = {alice_public}")

    # Bob computes public key
    bob_public = power_mod(g, bob_private, p)
    print(f"\n5. Bob Computes Public Key:")
    print(f"   B = g^b mod p = {g}^{bob_private} mod {p} = {bob_public}")

    # Exchange public keys
    print(f"\n6. Public Key Exchange:")
    print(f"   Alice sends A = {alice_public} to Bob")
    print(f"   Bob sends B = {bob_public} to Alice")

    # Alice computes shared secret
    alice_shared = power_mod(bob_public, alice_private, p)
    print(f"\n7. Alice Computes Shared Secret:")
    print(f"   s = B^a mod p = {bob_public}^{alice_private} mod {p} = {alice_shared}")

    # Bob computes shared secret
    bob_shared = power_mod(alice_public, bob_private, p)
    print(f"\n8. Bob Computes Shared Secret:")
    print(f"   s = A^b mod p = {alice_public}^{bob_private} mod {p} = {bob_shared}")

    # Verify they match
    print(f"\n9. Result:")
    if alice_shared == bob_shared:
        print(f"   ✓ SUCCESS! Both share the same secret: {alice_shared}")
        print(f"   ✓ Secure communication can now begin!")
    else:
        print(f"   ✗ ERROR: Secrets don't match!")

    return alice_shared, bob_shared


def mitm_attack():
    """Demonstrate Man-In-The-Middle attack on Diffie-Hellman"""
    print("\n\n" + "=" * 60)
    print("DIFFIE-HELLMAN WITH MAN-IN-THE-MIDDLE ATTACK")
    print("=" * 60)

    # Public parameters
    p = 23
    g = 5
    print(f"\n1. Public Parameters:")
    print(f"   Prime (p) = {p}")
    print(f"   Generator (g) = {g}")

    # Private keys
    alice_private = 6
    bob_private = 15
    eve_private_for_alice = 4
    eve_private_for_bob = 9

    print(f"\n2. Private Keys:")
    print(f"   Alice's private key: a = {alice_private}")
    print(f"   Bob's private key: b = {bob_private}")
    print(f"   Eve's private key (for Alice): e1 = {eve_private_for_alice}")
    print(f"   Eve's private key (for Bob): e2 = {eve_private_for_bob}")

    # Compute public keys
    alice_public = power_mod(g, alice_private, p)
    bob_public = power_mod(g, bob_private, p)
    eve_public_for_alice = power_mod(g, eve_private_for_alice, p)
    eve_public_for_bob = power_mod(g, eve_private_for_bob, p)

    print(f"\n3. Public Keys Computed:")
    print(f"   Alice: A = {alice_public}")
    print(f"   Bob: B = {bob_public}")
    print(f"   Eve (for Alice): E1 = {eve_public_for_alice}")
    print(f"   Eve (for Bob): E2 = {eve_public_for_bob}")

    # Attack begins
    print(f"\n4. ATTACK PHASE:")
    print(f"   Alice sends A = {alice_public} → Eve intercepts!")
    print(f"   Eve sends E1 = {eve_public_for_alice} to Bob (pretending to be Alice)")
    print(f"   Bob sends B = {bob_public} → Eve intercepts!")
    print(f"   Eve sends E2 = {eve_public_for_bob} to Alice (pretending to be Bob)")

    # Compute shared secrets
    alice_shared = power_mod(eve_public_for_bob, alice_private, p)
    bob_shared = power_mod(eve_public_for_alice, bob_private, p)
    eve_alice_shared = power_mod(alice_public, eve_private_for_alice, p)
    eve_bob_shared = power_mod(bob_public, eve_private_for_bob, p)

    print(f"\n5. Shared Secrets Computed:")
    print(f"   Alice's secret: {alice_shared} (thinks she shares with Bob)")
    print(f"   Bob's secret: {bob_shared} (thinks he shares with Alice)")
    print(f"   Eve's secret with Alice: {eve_alice_shared}")
    print(f"   Eve's secret with Bob: {eve_bob_shared}")

    print(f"\n6. ATTACK RESULT:")
    print(f"   ✗ Alice and Bob have DIFFERENT secrets!")
    print(f"   ✗ Alice shares {alice_shared} with Eve (not Bob)")
    print(f"   ✗ Bob shares {bob_shared} with Eve (not Alice)")
    print(f"   ⚠ Eve can decrypt ALL messages from both parties!")

    # Demonstrate message interception
    print(f"\n7. MESSAGE INTERCEPTION EXAMPLE:")
    print(f"   Alice encrypts 'Hello Bob' with key {alice_shared}")
    print(f"   → Eve decrypts with key {alice_shared} (reads: 'Hello Bob')")
    print(f"   → Eve re-encrypts with key {bob_shared} and sends to Bob")
    print(f"   → Bob decrypts with key {bob_shared} (receives: 'Hello Bob')")
    print(f"   → Bob thinks the message came directly from Alice!")

    print(f"\n8. PREVENTION:")
    print(f"   ✓ Use authenticated key exchange (e.g., TLS with certificates)")
    print(f"   ✓ Verify identity before establishing shared secret")
    print(f"   ✓ Use digital signatures to authenticate public keys")


def main():
    """Run both demonstrations"""
    # Normal Diffie-Hellman
    normal_diffie_hellman()

    # MITM Attack
    mitm_attack()

    print("\n" + "=" * 60)
    print("DEMONSTRATION COMPLETE")
    print("=" * 60)


if __name__ == "__main__":
    main()
