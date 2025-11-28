import matplotlib.pyplot as plt
import numpy as np
from scipy.special import comb, factorial
from scipy.stats import norm, gamma, beta
from matplotlib.widgets import Slider

def gen_discrete(n, probs):
    u = np.random.random(n)
    cumsum = np.cumsum(probs)
    return np.searchsorted(cumsum, u)


def bernoulli_gen(params, size):
    p = params[0]
    return (np.random.random(size) <= p).astype(int)

def binomial_gen(params, size):
    N, P = int(params[0]), params[1]
    x = np.arange(N + 1)
    probs = comb(N, x) * (P ** x) * ((1 - P) ** (N - x))
    return gen_discrete(size, probs)

def geometric_gen(params, size):
    p = params[0]
    return np.ceil(np.log(1 - np.random.random(size)) / np.log(1 - p))

def poisson_gen(params, size):
    lam = params[0]
    k_max = int(lam + 4 * np.sqrt(lam)) + 10 
    x = np.arange(k_max)
    probs = (lam ** x * np.exp(-lam)) / factorial(x)
    return gen_discrete(size, probs)

def uniform_gen(params, size):
    a, b = params[0], params[1]
    return a + (b - a) * np.random.random(size)

def exponential_gen(params, size):
    alpha = params[0]
    return -np.log(1 - np.random.random(size)) / alpha

def laplace_gen(params, size):
    alpha = params[0]
    u = np.random.random(size)
    return np.where(u < 0.5, np.log(2*u)/alpha, -np.log(2*(1-u))/alpha)

def normal_gen(params, size):
    a, sigma = params[0], params[1]
    return norm.rvs(loc=a, scale=sigma, size=size)

def cauchy_gen(params, size):
    return np.tan(np.pi * (np.random.random(size) - 0.5))

def custom_gen(params, size):
    return 1.0 / np.sqrt(1.0 - np.random.random(size))

def gamma_gen(params, size):
    k = params[0]
    return gamma.rvs(a=k, scale=1, size=size)

def beta_gen(params, size):
    a, b = params[0], params[1]
    return beta.rvs(a=a, b=b, size=size)

DISTS = {
    'Бернулли': (bernoulli_gen, ['p'], {'p':(0.01,1.0)}, True),
    'Биномиальное': (binomial_gen, ['n','p'], {'n':(1,50),'p':(0.01,0.99)}, True),
    'Геометрическое': (geometric_gen, ['p'], {'p':(0.01,0.99)}, True),
    'Пуассона': (poisson_gen, ['лямбда'], {'лямбда':(0.1,20.0)}, True),
    'Равномерное': (uniform_gen, ['a','b'], {'a':(-10,10),'b':(-10,10)}, False),
    'Показательное': (exponential_gen, ['альфа'], {'альфа':(0.1,5.0)}, False),
    'Лапласа': (laplace_gen, ['альфа'], {'альфа':(0.1,5.0)}, False),
    'Нормальное': (normal_gen, ['a','сигма'], {'a':(-10,10),'сигма':(0.1,5.0)}, False),
    'Коши': (cauchy_gen, [], {}, False),
    'Кастомное (2/t^3)': (custom_gen, [], {}, False),
    'Гамма': (gamma_gen, ['k (форма)'], {'k (форма)':(0.1,10.0)}, False), 
    'Бета': (beta_gen, ['a','b'], {'a':(0.1,10.0),'b':(0.1,10.0)}, False)
}

CPT = {
    'Бернулли (p=0.5)': (bernoulli_gen, [0.5], 0.5, 0.25),
    'Равномерное [0,1]': (uniform_gen, [0,1], 0.5, 1/12),
    'Показательное (alpha=1)': (exponential_gen, [1], 1, 1),
    'Пуассона (лямбда=3)': (poisson_gen, [3], 3, 3),
    'Геометрическое (p=0.3)': (geometric_gen, [0.3], 1/0.3, (1-0.3)/0.3**2),
    'Биномиальное (n=10, p=0.5)': (binomial_gen, [10,0.5], 5, 2.5),
    'Лапласа (alpha=1)': (laplace_gen, [1], 0, 2)
}


def stats(sample):
    mean, var = np.mean(sample), np.var(sample, ddof=1)
    disp = np.sqrt(var)
    assym = np.mean((sample - mean)**3) / disp**3 if disp > 0 else 0
    exscess = np.mean((sample - mean)**4) / disp**4 - 3 if disp > 0 else 0
    return mean, var, assym, exscess


def plot_distribution(name, size, params, ax):
    func_gen, _, _, is_discrete = DISTS[name]
    sample = func_gen(params, size)
    
    if name == 'Коши': sample = sample[(sample > -25) & (sample < 25)]
    if 'Кастомное' in name: sample = sample[sample < 20]
    
    ax.clear()
    
    if is_discrete:
        u, c = np.unique(sample, return_counts=True)
        ax.bar(u, c/len(sample), alpha=0.7, color='skyblue', edgecolor='k', label='Выборка')
        x = np.arange(np.min(u), np.max(u)+1)
        
        y = []
        if name=='Биномиальное': 
            N, P = int(params[0]), params[1]
            y = comb(N, x) * P**x * (1-P)**(N-x)
        elif name=='Геометрическое': 
            P = params[0]
            y = P * (1-P)**(x-1)
        elif name=='Пуассона': 
            lam = params[0]
            y = lam**x * np.exp(-lam) / factorial(x)
        elif name=='Бернулли': 
            P = params[0]
            y = [1-P, P] if len(x)==2 else []
            
        if len(y) > 0: ax.plot(x, y, 'ro-', label='Теория')
        ax.set_ylabel('Вероятность P(X=k)')
        
    else:
        ax.hist(sample, bins=50, density=True, alpha=0.7, color='lightcoral', edgecolor='k', label='Выборка')
        x = np.linspace(np.min(sample), np.max(sample), 200)
        
        y = []
        if name=='Равномерное': 
            a, b = params
            y = [1/(b-a) if a<=i<=b else 0 for i in x]
        elif name=='Показательное': 
            alpha = params[0]
            y = alpha * np.exp(-alpha * x) * (x >= 0)
        elif name=='Лапласа': 
            alpha = params[0]
            y = 0.5 * alpha * np.exp(-alpha * np.abs(x))
        elif name=='Нормальное': 
            a, sigma = params
            y = 1/(sigma*np.sqrt(2*np.pi)) * np.exp(-(x-a)**2/(2*sigma**2))
        elif name=='Коши': 
            y = 1/(np.pi*(1+x**2))
        elif 'Кастомное' in name: 
            y = [2*i**(-3) if i>=1 else 0 for i in x]
            
        if len(y) > 0: ax.plot(x, y, 'r-', lw=2, label='Теория')
        ax.set_ylabel('Плотность f(x)')
    
    mean, var, assym, exscess = stats(sample)
    ax.set_title(f'Распределение: {name}\nСреднее={mean:.3f}, Дисперсия={var:.3f}\nАсимметрия={assym:.3f}, Эксцесс={exscess:.3f}')
    ax.legend()
    ax.grid(True, alpha=0.3)

def task12():
    names = list(DISTS.keys())
    print("\n".join(f"{i+1}. {n}" for i, n in enumerate(names)))
    
    try: 
        choice = int(input("Ваш выбор (1-12): ")) - 1
        name = names[choice]
    except (ValueError, IndexError): 
        print("Неверный выбор.")
        return
    
    info = DISTS[name]
    fig, ax = plt.subplots(figsize=(10, 7))
    plt.subplots_adjust(bottom=0.35) 
    
    slider_size_ax = plt.axes([0.15, 0.25, 0.7, 0.03])
    sliders = {'N': Slider(slider_size_ax, 'Размер N', 100, 10000, valinit=1000, valstep=100)}
    
    for i, param_name in enumerate(info[1]):
        param_range = info[2][param_name]
        min_val, max_val = param_range
        param_ax = plt.axes([0.15, 0.20 - i * 0.05, 0.7, 0.03])
        val_step = 1 if param_name in ['n', 'k'] else None
        
        sliders[param_name] = Slider(param_ax, param_name, min_val, max_val, 
                                     valinit=(min_val + max_val) / 2, valstep=val_step)

    def update_plot(val):
        params_values = [sliders[p].val for p in info[1]]
        
        if name=='Равномерное' and params_values[0] >= params_values[1]: 
            params_values[1] = params_values[0] + 0.1
            
        plot_distribution(name, int(sliders['N'].val), params_values, ax)
        fig.canvas.draw_idle()
    
    for s in sliders.values(): 
        s.on_changed(update_plot)
        
    update_plot(0) 
    plt.show()

def task3():
    names = list(CPT.keys())
    print("\n".join(f"{i+1}. {n}" for i, n in enumerate(names)))
    
    try: 
        choice = int(input("Ваш выбор (1-7): ")) - 1
        name = names[choice]
    except (ValueError, IndexError): 
        print("Неверный выбор.")
        return

    func_gen, params, true_mean, true_variance = CPT[name]
    
    _, ax = plt.subplots(figsize=(10, 6))
    plt.subplots_adjust(bottom=0.25)
    
    slider_n_ax = plt.axes([0.15, 0.15, 0.7, 0.03])
    slider_n = Slider(slider_n_ax, 'n (число слагаемых)', 1, 500, valinit=50, valstep=1)
    
    slider_N_ax = plt.axes([0.15, 0.1, 0.7, 0.03])
    slider_N = Slider(slider_N_ax, 'N (число экспериментов)', 1000, 50000, valinit=10000, valstep=1000)

    def update_cpt(val):
        n, N = int(slider_n.val), int(slider_N.val)

        matrix = func_gen(params, N * n).reshape(N, n)
        
        sums = np.sum(matrix, axis=1)

        standardized_sums = (sums - n * true_mean) / np.sqrt(n * true_variance)
        
        ax.clear()
        
        ax.hist(standardized_sums, bins=70, density=True, alpha=0.6, color='lightgreen', label='Гистограмма стандартизованных сумм')

        x = np.linspace(-4, 4, 100)
        standard_normal_pdf = 1/np.sqrt(2*np.pi) * np.exp(-x**2/2)
        ax.plot(x, standard_normal_pdf, 'r-', lw=2, label='Теория N(0, 1)')
        
        mean_sample, var_sample, _, _ = stats(standardized_sums)
        
        ax.set_title(f'ЦПТ для {name}\nЧисло слагаемых n={n}\n'
                     f'Выборочные статистики: Среднее={mean_sample:.3f}, Дисперсия={var_sample:.3f}')
        ax.set_xlim(-4, 4)
        ax.legend()
        ax.grid(True, alpha=0.3)

    slider_n.on_changed(update_cpt)
    slider_N.on_changed(update_cpt)
    
    update_cpt(0) 
    plt.show()


if __name__ == "__main__":
    while True:
        print("1. Распределения")
        print("2. ЦПТ")
        print("q. Выход")
        choice = input(">> ")
        if choice == '1':
            task12()
        elif choice == '2':
            task3()
        elif choice.lower() == 'q':
            break