import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.neighbors import KNeighborsClassifier
from xgboost import XGBClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score

def preprocess_data(data):
    data = data.copy()
    data.columns = data.columns.str.strip()
    features = ['Pclass', 'Sex', 'Age', 'SibSp', 'Parch', 'Fare', 'Embarked']
    X = data[features]
    y = data['Survived']

    X['Age'] = pd.to_numeric(X['Age'])

    X['Age'] = X['Age'].fillna(X['Age'].median())
    X['Embarked'] = X['Embarked'].fillna('S')

    X = pd.get_dummies(X, columns=['Sex', 'Embarked'], drop_first=True)

    return X, y

def split_data(X, y):
    X_temp, X_test, y_temp, y_test = train_test_split(X, y, test_size=0.15, random_state=42)
    X_train, X_val, y_train, y_val = train_test_split(X_temp, y_temp, test_size=0.1765, random_state=42)
    return X_train, X_val, X_test, y_train, y_val, y_test

def scale(X_train, X_val, X_test):
    scaler = StandardScaler()
    X_train_scaled = scaler.fit_transform(X_train)
    X_val_scaled = scaler.transform(X_val)
    X_test_scaled = scaler.transform(X_test)
    return X_train_scaled, X_val_scaled, X_test_scaled

def train_random_forest(X_train, y_train, X_val, y_val, X_test, y_test):
    rf_model = RandomForestClassifier(
        n_estimators=100,
        max_depth=5,
        min_samples_split=5,
        random_state=42
    )
    rf_model.fit(X_train, y_train)
    val_pred = rf_model.predict(X_val)
    test_pred = rf_model.predict(X_test)
    val_accuracy = accuracy_score(y_val, val_pred)
    test_accuracy = accuracy_score(y_test, test_pred)
    print("Random Forest Results:")
    print(f"  Validation Accuracy: {val_accuracy:.4f}")
    print(f"  Test Accuracy: {test_accuracy:.4f}")
    return rf_model, val_accuracy, test_accuracy

def train_xgboost(X_train, y_train, X_val, y_val, X_test, y_test):
    xgb_model = XGBClassifier(
        n_estimators=100,
        max_depth=3,
        learning_rate=0.1,
        eval_metric='logloss',
        random_state=42
    )
    xgb_model.fit(X_train, y_train)
    val_pred = xgb_model.predict(X_val)
    test_pred = xgb_model.predict(X_test)
    val_accuracy = accuracy_score(y_val, val_pred)
    test_accuracy = accuracy_score(y_test, test_pred)
    print("XGBoost Results:")
    print(f"  Validation Accuracy: {val_accuracy:.4f}")
    print(f"  Test Accuracy: {test_accuracy:.4f}")
    return xgb_model, val_accuracy, test_accuracy


def train_logistic_regression(X_train_scaled, y_train, X_val_scaled, y_val, X_test_scaled, y_test):
    lr_model = LogisticRegression(
        C=1.0,
        solver='liblinear',
        random_state=42
    )
    lr_model.fit(X_train_scaled, y_train)
    val_pred = lr_model.predict(X_val_scaled)
    test_pred = lr_model.predict(X_test_scaled)
    val_accuracy = accuracy_score(y_val, val_pred)
    test_accuracy = accuracy_score(y_test, test_pred)
    print("Logistic Regression Results:")
    print(f"  Validation Accuracy: {val_accuracy:.4f}")
    print(f"  Test Accuracy: {test_accuracy:.4f}")
    return lr_model, val_accuracy, test_accuracy

def train_knn(X_train_scaled, y_train, X_val_scaled, y_val, X_test_scaled, y_test):
    knn_model = KNeighborsClassifier(
        n_neighbors=5,
        weights='uniform'
    )
    knn_model.fit(X_train_scaled, y_train)
    val_pred = knn_model.predict(X_val_scaled)
    test_pred = knn_model.predict(X_test_scaled)
    val_accuracy = accuracy_score(y_val, val_pred)
    test_accuracy = accuracy_score(y_test, test_pred)
    print("KNN Results:")
    print(f"  Validation Accuracy: {val_accuracy:.4f}")
    print(f"  Test Accuracy: {test_accuracy:.4f}")
    return knn_model, val_accuracy, test_accuracy

def eval_features(X_train, X_val, X_test, y_train, y_val, y_test):
    model = RandomForestClassifier(
        n_estimators=100,
        max_depth=5,
        min_samples_split=5,
        random_state=42
    )
    model.fit(X_train, y_train)

    importances = model.feature_importances_
    feature_names = X_train.columns
    feature_importance = pd.Series(importances, index=feature_names).sort_values(ascending=False)

    print("\nFeature Importances:")
    print(feature_importance)

    feature_subsets = {
        '2': feature_importance.index[:2].tolist(),
        '4': feature_importance.index[:4].tolist(),
        '8': feature_importance.index[:8].tolist()
    }

    for _, features in feature_subsets.items():
        print(f"\nFeatures: {features}")
        
        X_train_subset = X_train[features]
        X_val_subset = X_val[features]
        X_test_subset = X_test[features]

        X_train_scaled, X_val_scaled, X_test_scaled = scale(X_train_subset, X_val_subset, X_test_subset)

        print()
        train_random_forest(X_train_subset, y_train, X_val_subset, y_val, X_test_subset, y_test)
        print()
        train_logistic_regression(X_train_scaled, y_train, X_val_scaled, y_val, X_test_scaled, y_test)
        print()
        train_knn(X_train_scaled, y_train, X_val_scaled, y_val, X_test_scaled, y_test)
        print()
        train_xgboost(X_train_scaled, y_train, X_val_scaled, y_val, X_test_scaled, y_test)

def main():
    data = pd.read_csv('train.csv', skipinitialspace=True)

    X, y = preprocess_data(data)

    X_train, X_val, X_test, y_train, y_val, y_test = split_data(X, y)

    eval_features(X_train, X_val, X_test, y_train, y_val, y_test)

main()