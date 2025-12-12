import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

def preprocess(table):
    table.fillna(table['n_hos_beds'].mean(), inplace=True)
    numeric_cols = table.select_dtypes(include=np.number).columns.tolist()
    numeric_cols.remove('price')
    numeric_cols.remove('Sold')

    X_numeric = table[numeric_cols]

    corr_matrix = X_numeric.corr().abs()
    to_drop = set()

    for column in corr_matrix.columns:
        correlated_features = corr_matrix.index[corr_matrix[column] > 0.9].tolist()

        for feature in correlated_features:
            if feature not in to_drop and feature != column:
                to_drop.add(column)
        
    X_numeric = X_numeric.drop(columns=list(to_drop))


    y = table['price']
    for col in X_numeric:
        original_corr = abs(X_numeric[col].corr(y))
        log_corr = abs(np.log(X_numeric[col]).corr(y))
        sqrt_corr = abs(np.sqrt(X_numeric[col]).corr(y))

        best_corr = max(original_corr, log_corr, sqrt_corr)
        
        if best_corr == log_corr:
            X_numeric[col] = np.log(X_numeric[col])
        elif best_corr == sqrt_corr:
            X_numeric[col] = np.sqrt(X_numeric[col])



    cat_cols = table.select_dtypes(include=['object']).columns
    X_categorical = pd.get_dummies(table[cat_cols], drop_first=True)


    table = pd.concat([X_numeric, X_categorical, table['Sold'], table['price']], axis=1)
    return table


def get_stats(X, y, feature_names):
    XTX_inv = np.linalg.inv(X.T @ X)
    betas = XTX_inv @ X.T @ y

    y_pred = X @ betas
    errors = y - y_pred
        
    disp = errors.T @ errors / (X.shape[0] - X.shape[1])


    cov_matrix = disp * XTX_inv
    
    betas_disp = np.sqrt(np.diag(cov_matrix)).reshape(-1, 1)
    
    T = betas / betas_disp
    
    p_values = 2 * (1 - stats.norm.cdf(np.abs(T)))
    
    results_df = pd.DataFrame({
        'Feature': feature_names,
        'Beta': betas.flatten(),
        'SE': betas_disp.flatten(),
        'T-stat': T.flatten(),
        'P-value': p_values.flatten()
    })
    
    return results_df, disp

def backward_elimination(table):
    y = table['price'].values.reshape(-1, 1).astype(float)
    features = table.drop(columns=['price']).columns.tolist()
    
    while True:
        X_df = table[features]
        X = X_df.values.astype(float)
   
        X_const = np.hstack([np.ones((X.shape[0], 1)), X])
        current_names = ['Beta0'] + features
        
        stats_df, sigma_sq = get_stats(X_const, y, current_names)
            
        predictors_df = stats_df[stats_df['Feature'] != 'Beta0']
        
        max_p_value = predictors_df['P-value'].max()
        worst_feature = predictors_df.loc[predictors_df['P-value'].idxmax(), 'Feature']
        
        if max_p_value <= 0.05:
            return stats_df, sigma_sq, features
        
        features.remove(worst_feature)




def get_beta_params(E, sigma):
    if sigma**2 >= E * (1 - E):
        raise ValueError("Дисперсия слишком велика для данного среднего.")
        
    sum = (E * (1 - E) / sigma**2) - 1
    alpha_param = E * sum
    beta_param = (1 - E) * sum
    return alpha_param, beta_param

def plot_beta_distributions(params_dict, title="Bayesian Update of Sold Probability"):
    """
    Строит графики плотности вероятности (PDF) для списка параметров.
    params_dict: словарь { 'Label': (alpha, beta) }
    """
    x = np.linspace(0, 1, 1000)
    plt.figure(figsize=(10, 6))
    
    for label, (a, b) in params_dict.items():
        y = stats.beta.pdf(x, a, b)
        mean_val = a / (a + b)
        plt.plot(x, y, label=f"{label} (Mean={mean_val:.3f})", linewidth=2)
        
    plt.title(title)
    plt.xlabel("Вероятность продажи (p)")
    plt.ylabel("Плотность вероятности")
    plt.legend()
    plt.grid(alpha=0.3)
    plt.show()

def task4():
    df = pd.read_csv("./House-Prices.csv")
    df['waterbody'].fillna('None', inplace=True)

    prior_mean = 0.5
    prior_std = 0.15
    
    try:
        alpha_0, beta_0 = get_beta_params(prior_mean, prior_std)
    except ValueError as e:
        print(f"Ошибка параметров: {e}")
        return

    groups = ['None', 'River', 'Lake', 'Lake and River']
    
    distributions_to_plot = {
        'Prior (Априор)': (alpha_0, beta_0)
    }

    print("\n--- Апостериорные оценки по группам (waterbody) ---")
    
    for group in groups:
        subset = df[df['waterbody'] == group]
        n_observations = len(subset)
        
        successes = subset['Sold'].sum()
        failures = n_observations - successes
        
        alpha_new = alpha_0 + successes
        beta_new = beta_0 + failures
        
        post_mean = alpha_new / (alpha_new + beta_new)
        post_std = np.sqrt((alpha_new * beta_new) / ((alpha_new + beta_new)**2 * (alpha_new + beta_new + 1)))
        
        print(f"Группа '{group}':")
        print(f"  Наблюдений: {n_observations} (Продано: {successes}, Не продано: {failures})")
        print(f"  Апостериор: Mean={post_mean:.4f}, Std={post_std:.4f}")
        
        distributions_to_plot[f'Posterior ({group})'] = (alpha_new, beta_new)

    plot_beta_distributions(distributions_to_plot, title="Априорное vs Апостериорное распределение по типу водоема")

    
    target_group = groups[1]
    subset_seq = df[df['waterbody'] == target_group]['Sold'].values
    
    curr_alpha, curr_beta = alpha_0, beta_0
    
    checkpoints = [0, len(subset_seq)//4, len(subset_seq)//2, len(subset_seq)]
    seq_plot_data = {'Prior': (alpha_0, beta_0)}
    
    for i, is_sold in enumerate(subset_seq):
        if is_sold == 1:
            curr_alpha += 1
        else:
            curr_beta += 1
            
        if (i + 1) in checkpoints:
            label = f"After {i+1}"
            seq_plot_data[label] = (curr_alpha, curr_beta)
            
    plot_beta_distributions(seq_plot_data, title=f"Последовательное обучение (Группа: {target_group})")





def main():
    table = pd.read_csv("./House-Prices.csv")
    table = preprocess(table)

    stats, sigma, features = backward_elimination(table)

    print(stats)
    # print(table[features])

    task4()



if __name__ == "__main__":
    main()