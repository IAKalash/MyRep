import numpy as np
import random

def eval_MAD(selection):
    selection = np.sort(selection)
    median = np.median(selection)
    selection = abs(selection - median)
    return np.median(selection)


def eval_dispersion(selection):
    mean = np.mean(selection)
    return np.sum(np.power(selection - mean, 2)) / len(selection)
    

def generate_selections(selection, m):
    size = len(selection)
    res = []
    for _ in range(m):
        res.append(random.choices(selection, k=size))
    return np.array(res)


def main():
    selection = np.random.exponential(2.0, 10000)

    print("Generating selections...")
    selections = generate_selections(selection, 1000)
    print("Selections generated. Evaluating statistics...")

    mads = np.array([eval_MAD(x) for x in selections])
    dispersions = np.array([eval_dispersion(x) for x in selections])

    size = mads.size

    mad_CI = mads[round(size * 0.025) : round(size * 0.975)]
    disp_CI = dispersions[round(size * 0.025) : round(size * 0.975)]

    print("\n--- Bootstrap Results ---")
    print(f"Original MAD: {eval_MAD(selection):.6f}")
    print(f"95% CI for MAD: [{np.min(mad_CI):.6f}, {np.max(mad_CI):.6f}]")

    print(f"\nOriginal Dispersion: {eval_dispersion(selection):.6f}")
    print(f"95% CI for Dispersion: [{np.min(disp_CI):.6f}, {np.max(disp_CI):.6f}]")



main()    