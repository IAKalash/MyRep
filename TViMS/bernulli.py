import matplotlib.pyplot as plt
import numpy as np
import math

def gen_segment(l, n):
    p = min(l / n, 1)
    res = np.random.random(n)

    return (res < p).astype(np.int8)


def bernulli(l, n, N):
    successes = np.zeros(N, dtype=int)
    distances = []

    for i in range(N):
        segment = gen_segment(l, n)
        successes[i] = segment.sum()

        pos = np.where(segment)[0]
        if len(pos) > 1:
            distances.append(np.diff(pos))
        else:
            distances.append(np.array([], dtype=int))

    all_dist = np.concatenate(distances) if distances else np.array([])
    return successes, all_dist


def puasson(l, N):
    all_distances = []

    for _ in range(N):
        X = np.random.poisson(l)
        if X <= 1:
            continue

        points = np.random.uniform(low=0.0, high=1.0, size=X)
        points.sort()

        diffs = np.diff(points)
        all_distances.append(diffs)

    return np.concatenate(all_distances) if all_distances else np.array([])
    

def puasson_exp(l, N):
    successes = np.zeros(N, dtype=int)
    
    for i in range(N):
        t = 0.0
        count = 0
        
        while True:
            delta_t = np.random.exponential(1 / l)
            t += delta_t
            
            if t > 1.0:
                break
                
            count += 1
        
        successes[i] = count
    
    return successes


def build_histo(arr, histName, color, ax=None):
    arr = np.array(arr, dtype=float)

    n = len(arr)
    m = 1 + math.floor(math.log2(n))
    min_val = arr.min()
    max_val = arr.max()

    delta = (max_val - min_val) / m
    edges = np.linspace(min_val, max_val, m + 1)
    hist_counts, _ = np.histogram(arr, edges)
    heights = hist_counts / (n * delta)
    if ax is None:
        _, ax = plt.subplots(figsize=(7, 5))

    ax.bar(edges[:-1], heights, width=delta, align='edge',
           color=color, edgecolor='black', label=histName)


    ax.set_title(histName)
    ax.set_xlabel('Значение')
    ax.set_ylabel('Плотность')
    ax.grid(True, alpha=0.3)

    return ax


def main():
    l = 5
    N = 5000

    successes, distances = bernulli(l, 100000, N)
    build_histo(successes, "Успехи", color='skyblue')
    build_histo(distances, "Расстояния", color='red')

    dists2 = puasson(l, N)
    build_histo(dists2, "Пуассон расстояния", color='red')

    successes2 = puasson_exp(l, N)
    build_histo(successes2, "Пуассон успехи", color='skyblue')
    plt.show()

    
main()