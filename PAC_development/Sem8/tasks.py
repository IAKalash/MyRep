import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

def main():
    # ===================== 1
    df = pd.read_csv('./wells_info_with_prod.csv')
    df.columns = df.columns.str.strip()

    df['FirstProductionDate'] = pd.to_datetime(df['FirstProductionDate'])
    df['FirstProd_Year'] = df['FirstProductionDate'].dt.year

    X = df[[
        'FirstProd_Year',
        'formation',
        'LATERAL_LENGTH_BLEND',
        'PROP_PER_FOOT',
        'WATER_PER_FOOT'
    ]].copy()

    y = df['Prod1Year']

    X = pd.get_dummies(X, columns=['formation'], drop_first=True)

    # ===================== 2
    X_train, X_test, y_train, y_test = train_test_split(
        X, y,
        test_size=0.2
    )

    # ===================== 3
    scaler_X = StandardScaler()

    numeric_cols = X_train.select_dtypes(include='number').columns
    scaler_X.fit(X_train[numeric_cols])

    X_train_scaled = scaler_X.transform(X_train[numeric_cols])
    X_test_scaled = scaler_X.transform(X_test[numeric_cols])

    X_train_scaled = pd.DataFrame(X_train_scaled, columns=numeric_cols, index=X_train.index)
    X_test_scaled = pd.DataFrame(X_test_scaled, columns=numeric_cols, index=X_test.index)

    cat_cols = [col for col in X_train.columns if col.startswith('formation_')]
    X_train_scaled[cat_cols] = X_train[cat_cols].values
    X_test_scaled[cat_cols] = X_test[cat_cols].values

    # ===================== 4
    scaler_y = StandardScaler()

    y_train_scaled = scaler_y.fit_transform(y_train.values.reshape(-1, 1)).flatten()
    y_test_scaled = scaler_y.transform(y_test.values.reshape(-1, 1)).flatten()

    y_train_scaled = pd.DataFrame({'Prod1Year': y_train_scaled}, index=y_train.index)
    y_test_scaled = pd.DataFrame({'Prod1Year': y_test_scaled}, index=y_test.index)

    # ===================== 5
    print(X_test_scaled.head())
    print(y_train_scaled.head())

main()