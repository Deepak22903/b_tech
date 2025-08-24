#!/usr/bin/env python3
import math, random, string
from collections import Counter, defaultdict
from dataclasses import dataclass

ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"


def clean_text(s: str) -> str:
    return "".join(ch for ch in s.upper() if ch in ALPHA)


def coltrans_encrypt(plaintext: str, perm):
    k = len(perm)
    L = len(plaintext)
    rows = (L + k - 1) // k
    grid = [list(plaintext[i : i + k].ljust(k, "\x00")) for i in range(0, L, k)]
    cols = []
    for c in range(k):
        col_chars = []
        for r in range(rows):
            if r < len(grid) and c < len(grid[r]) and grid[r][c] != "\x00":
                col_chars.append(grid[r][c])
        cols.append("".join(col_chars))
    return "".join(cols[c] for c in perm)


def coltrans_decrypt(ciphertext: str, perm):
    k = len(perm)
    L = len(ciphertext)
    rows = (L + k - 1) // k
    rem = L % k
    col_lengths = [rows if (rem == 0 or j < rem) else (rows - 1) for j in range(k)]
    cols_by_perm = []
    idx = 0
    for c in perm:
        clen = col_lengths[c]
        cols_by_perm.append(ciphertext[idx : idx + clen])
        idx += clen
    cols = [""] * k
    for slot, c in enumerate(perm):
        cols[c] = cols_by_perm[slot]
    plaintext_chars = []
    for r in range(rows):
        for c in range(k):
            if r < len(cols[c]):
                plaintext_chars.append(cols[c][r])
    return "".join(plaintext_chars)


def dt_encrypt(plaintext: str, perm1, perm2) -> str:
    return coltrans_encrypt(coltrans_encrypt(plaintext, perm1), perm2)


def dt_decrypt(ciphertext: str, perm1, perm2) -> str:
    return coltrans_decrypt(coltrans_decrypt(ciphertext, perm2), perm1)


def train_ngram_model(sample_text: str, n: int = 3, k_smooth: float = 0.2):
    sample = clean_text(sample_text)
    if len(sample) < n:
        raise ValueError("Training text too short for n-gram model.")
    counts = Counter(sample[i : i + n] for i in range(len(sample) - n + 1))
    total = sum(counts.values())
    V = 26**n
    log_probs = defaultdict(lambda: math.log(k_smooth / (total + k_smooth * V)))
    for ngr, c in counts.items():
        log_probs[ngr] = math.log((c + k_smooth) / (total + k_smooth * V))
    return {"log_probs": log_probs, "n": n}


def score_text_ngram(text: str, model) -> float:
    s = clean_text(text)
    n = model["n"]
    if len(s) < n:
        return float("-inf")
    lp = 0.0
    log_probs = model["log_probs"]
    for i in range(len(s) - n + 1):
        lp += log_probs[s[i : i + n]]
    return lp


def random_perm(k: int):
    p = list(range(k))
    random.shuffle(p)
    return p


def neighbor_swaps(p, n_swaps: int = 1):
    p2 = p[:]
    for _ in range(n_swaps):
        a, b = random.sample(range(len(p2)), 2)
        p2[a], p2[b] = p2[b], p2[a]
    return p2


@dataclass
class DTResult:
    perm1: list
    perm2: list
    score: float
    plaintext: str
    c1: int
    c2: int


def hill_climb_dt(
    ciphertext: str,
    c1: int,
    c2: int,
    model,
    iterations: int = 4000,
    temp_start: float = 3.0,
    temp_end: float = 0.1,
) -> DTResult:
    perm1 = random_perm(c1)
    perm2 = random_perm(c2)
    best_perm1 = perm1[:]
    best_perm2 = perm2[:]
    best_plain = dt_decrypt(ciphertext, perm1, perm2)
    best_score = score_text_ngram(best_plain, model)
    cur_perm1, cur_perm2 = best_perm1[:], best_perm2[:]
    cur_plain, cur_score = best_plain, best_score
    for it in range(1, iterations + 1):
        T = temp_start + (temp_end - temp_start) * (it / iterations)
        if random.random() < 0.5:
            cand_perm1 = neighbor_swaps(cur_perm1, 1)
            cand_perm2 = cur_perm2[:]
        else:
            cand_perm1 = cur_perm1[:]
            cand_perm2 = neighbor_swaps(cur_perm2, 1)
        cand_plain = dt_decrypt(ciphertext, cand_perm1, cand_perm2)
        cand_score = score_text_ngram(cand_plain, model)
        delta = cand_score - cur_score
        if delta >= 0 or math.exp(delta / max(T, 1e-6)) > random.random():
            cur_perm1, cur_perm2 = cand_perm1, cand_perm2
            cur_plain, cur_score = cand_plain, cand_score
            if cur_score > best_score:
                best_perm1, best_perm2 = cur_perm1[:], cur_perm2[:]
                best_plain, best_score = cur_plain, cur_score
    return DTResult(best_perm1, best_perm2, best_score, best_plain, c1, c2)


def break_dt(
    ciphertext: str,
    model,
    c1_range=range(5, 11),
    c2_range=range(5, 11),
    restarts: int = 6,
    iterations: int = 4000,
):
    best_overall = None
    for c1 in c1_range:
        for c2 in c2_range:
            local_best = None
            for _ in range(restarts):
                res = hill_climb_dt(ciphertext, c1, c2, model, iterations=iterations)
                if (local_best is None) or (res.score > local_best.score):
                    local_best = res
            if (best_overall is None) or (local_best.score > best_overall.score):
                best_overall = local_best
    return best_overall


DEMO_TRAIN = """
IT IS A TRUTH UNIVERSALLY ACKNOWLEDGED THAT A SINGLE MAN IN POSSESSION OF A GOOD FORTUNE
MUST BE IN WANT OF A WIFE HOWEVER LITTLE KNOWN THE FEELINGS OR VIEWS OF SUCH A MAN MAY BE
ON HIS FIRST ENTERING A NEIGHBOURHOOD THIS TRUTH IS SO WELL FIXED IN THE MINDS OF THE
SURROUNDING FAMILIES THAT HE IS CONSIDERED AS THE RIGHTFUL PROPERTY OF SOME ONE OR OTHER
OF THEIR DAUGHTERS THE BUSINESS OF HER LIFE WAS TO GET HER DAUGHTERS MARRIED ITS SOLACE
WAS VISITING AND NEWS
"""

if __name__ == "__main__":
    import argparse, sys

    ap = argparse.ArgumentParser(
        description="Break a Double Transposition cipher via n-gram scoring + hill-climbing."
    )
    ap.add_argument(
        "--cipher",
        "-c",
        type=str,
        required=True,
        help="Ciphertext to solve (quotes ok). Non-letters ignored.",
    )
    ap.add_argument(
        "--c1min", type=int, default=5, help="Min columns first transposition."
    )
    ap.add_argument(
        "--c1max",
        type=int,
        default=10,
        help="Max columns first transposition (inclusive).",
    )
    ap.add_argument(
        "--c2min", type=int, default=5, help="Min columns second transposition."
    )
    ap.add_argument(
        "--c2max",
        type=int,
        default=10,
        help="Max columns second transposition (inclusive).",
    )
    ap.add_argument(
        "--restarts", type=int, default=8, help="Random restarts per (c1,c2)."
    )
    ap.add_argument("--iters", type=int, default=4500, help="Iterations per climb.")
    args = ap.parse_args()

    C = clean_text(args.cipher)
    model = train_ngram_model(DEMO_TRAIN, n=3, k_smooth=0.2)
    best = break_dt(
        C,
        model,
        c1_range=range(args.c1min, args.c1max + 1),
        c2_range=range(args.c2min, args.c2max + 1),
        restarts=args.restarts,
        iterations=args.iters,
    )

    print("=== BEST SOLUTION ===")
    print(f"c1={best.c1}, c2={best.c2}")
    print(f"perm1={best.perm1}")
    print(f"perm2={best.perm2}")
    print(f"score={best.score:.2f}")
    print("plaintext:")
    print(best.plaintext)
