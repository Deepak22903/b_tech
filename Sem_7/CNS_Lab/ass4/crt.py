def extended_gcd(a, b):
    if a == 0:
        return b, 0, 1

    gcd, x1, y1 = extended_gcd(b % a, a)
    x = y1 - (b // a) * x1
    y = x1

    return gcd, x, y


def mod_inverse(a, m):
    gcd, x, _ = extended_gcd(a, m)
    if gcd != 1:
        raise ValueError(f"Modular inverse of {a} modulo {m} does not exist")
    return x % m


def are_pairwise_coprime(moduli):
    from math import gcd

    n = len(moduli)
    for i in range(n):
        for j in range(i + 1, n):
            if gcd(moduli[i], moduli[j]) != 1:
                return False
    return True


def chinese_remainder_theorem(remainders, moduli):
    if len(remainders) != len(moduli):
        raise ValueError("Number of remainders and moduli must be equal")

    if not are_pairwise_coprime(moduli):
        raise ValueError("Moduli must be pairwise coprime")

    n = len(moduli)

    M = 1
    for m in moduli:
        M *= m

    x = 0
    for i in range(n):
        Mi = M // moduli[i]
        yi = mod_inverse(Mi, moduli[i])
        x += remainders[i] * Mi * yi

    return x % M, M


def solve_congruences(congruences):
    remainders = [a for a, m in congruences]
    moduli = [m for a, m in congruences]

    return chinese_remainder_theorem(remainders, moduli)


def verify_solution(x, congruences):
    print("Verification:")
    for i, (a, m) in enumerate(congruences):
        result = x % m
        status = "✓" if result == a else "✗"
        print(f"  x ≡ {result} (mod {m}) {status} (expected {a})")
    return all(x % m == a for a, m in congruences)


def input_congruences():
    n = int(input("Enter number of congruences: "))
    congruences = []

    for i in range(n):
        print(f"\nCongruence {i + 1}:")
        a = int(input("  Enter remainder (a): "))
        m = int(input("  Enter modulus (m): "))
        congruences.append((a, m))
        print(f"  x ≡ {a} (mod {m})")

    return congruences


def run_examples():
    print("Running example test cases...")

    examples = [[(2, 3), (3, 5), (2, 7)], [(1, 4), (2, 9), (3, 25)], [(1, 6), (2, 9)]]

    for i, congruences in enumerate(examples, 1):
        print(f"\nExample {i}:")
        for a, m in congruences:
            print(f"  x ≡ {a} (mod {m})")

        try:
            x, M = solve_congruences(congruences)
            print(f"Solution: x ≡ {x} (mod {M})")
            verify_solution(x, congruences)
        except ValueError as e:
            print(f"Error: {e}")


def main_menu():
    print("\nChinese Remainder Theorem Solver")
    print("=" * 40)
    print("1. Solve your own congruences")
    print("2. Run example test cases")
    print("3. Exit")
    return input("\nChoose an option (1-3): ")


if __name__ == "__main__":
    while True:
        choice = main_menu()

        if choice == "1":
            try:
                congruences = input_congruences()
                print(f"\nSolving system:")
                for a, m in congruences:
                    print(f"  x ≡ {a} (mod {m})")

                x, M = solve_congruences(congruences)
                print(f"\nSolution: x ≡ {x} (mod {M})")
                verify_solution(x, congruences)

            except ValueError as e:
                print(f"Error: {e}")
            except Exception as e:
                print(f"Invalid input: {e}")

        elif choice == "2":
            run_examples()

        elif choice == "3":
            print("Goodbye!")
            break

        else:
            print("Invalid choice. Please enter 1, 2, or 3.")

        input("\nPress Enter to continue...")
        print("\n" + "=" * 50)
