import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.linear_model import LogisticRegression
from xgboost import XGBClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler

def preprocess_data(file_path):
    data = pd.read_csv(file_path, skipinitialspace=True)
    data.columns = data.columns.str.strip()
    
    data = data.drop(data.columns[0], axis=1)

    X = data.drop('label', axis=1)
    y = data['label']
    
    return X, y

def split_data(X, y):
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.2, random_state=42
    )
    return X_train, X_test, y_train, y_test

def train_decision_tree(X_train, y_train, X_test, y_test):
    dt_model = DecisionTreeClassifier(
        max_depth=10,
        min_samples_split=10,
        min_samples_leaf=5,
        random_state=42
    )
    dt_model.fit(X_train, y_train)
    
    y_pred = dt_model.predict(X_test)
    accuracy = accuracy_score(y_test, y_pred)
    
    print(f"Decision Tree Results: {accuracy:.4f}")
    
    return dt_model, accuracy

def train_xgboost(X_train, y_train, X_test, y_test):
    xgb_model = XGBClassifier(
        n_estimators=100,
        max_depth=6,
        learning_rate=0.1,
        eval_metric='logloss',
        random_state=42
    )
    xgb_model.fit(X_train, y_train)
    
    y_pred = xgb_model.predict(X_test)
    accuracy = accuracy_score(y_test, y_pred)
    
    print(f"XGBoost Results: {accuracy:.4f}")
    
    return xgb_model, accuracy

def train_logistic_regression(X_train, y_train, X_test, y_test):
    scaler = StandardScaler()
    X_train_scaled = scaler.fit_transform(X_train)
    X_test_scaled = scaler.transform(X_test)
    
    lr_model = LogisticRegression(
        C=1.0,
        solver='liblinear',
        random_state=42,
        max_iter=1000
    )
    lr_model.fit(X_train_scaled, y_train)
    
    y_pred = lr_model.predict(X_test_scaled)
    accuracy = accuracy_score(y_test, y_pred)
    
    print(f"Logistic Regression Results: {accuracy:.4f}")
    
    return lr_model, accuracy

def eval_features(dt_model, feature_names, n_features=2):
    importances = dt_model.feature_importances_
    feature_importance = pd.Series(importances, index=feature_names)
    top_features = feature_importance.nlargest(n_features).index.tolist()
    
    print(f"\nTop {n_features} features:")
    for i, feature in enumerate(top_features, 1):
        print(f"  {i}. {feature}: {feature_importance[feature]:.4f}")
    
    return top_features

def train_on_features(X_train, X_test, y_train, y_test, features):
    
    X_train_top = X_train[features]
    X_test_top = X_test[features]
    
    # Decision Tree
    dt_model_top = DecisionTreeClassifier(
        max_depth=10,
        min_samples_split=10,
        min_samples_leaf=5,
        random_state=42
    )
    dt_model_top.fit(X_train_top, y_train)
    y_pred_dt = dt_model_top.predict(X_test_top)
    accuracy_dt = accuracy_score(y_test, y_pred_dt)
    
    # XGBoost
    xgb_model_top = XGBClassifier(
        n_estimators=100,
        max_depth=6,
        learning_rate=0.1,
        eval_metric='logloss',
        random_state=42
    )
    xgb_model_top.fit(X_train_top, y_train)
    y_pred_xgb = xgb_model_top.predict(X_test_top)
    accuracy_xgb = accuracy_score(y_test, y_pred_xgb)
    
    # Logistic Regression
    scaler = StandardScaler()
    X_train_top_scaled = scaler.fit_transform(X_train_top)
    X_test_top_scaled = scaler.transform(X_test_top)
    
    lr_model_top = LogisticRegression(
        C=1.0,
        solver='liblinear',
        random_state=42,
        max_iter=1000
    )
    lr_model_top.fit(X_train_top_scaled, y_train)
    y_pred_lr = lr_model_top.predict(X_test_top_scaled)
    accuracy_lr = accuracy_score(y_test, y_pred_lr)
    
    print("\nTop features:")
    print(f"  Decision Tree Accuracy: {accuracy_dt:.4f}")
    print(f"  XGBoost Accuracy: {accuracy_xgb:.4f}")
    print(f"  Logistic Regression Accuracy: {accuracy_lr:.4f}")
    
    return accuracy_dt, accuracy_xgb, accuracy_lr

def main():

    X, y = preprocess_data('titanic_prepared.csv')
    X_train, X_test, y_train, y_test = split_data(X, y)
    
    print('-' * 20)
    dt_model, dt_accuracy = train_decision_tree(X_train, y_train, X_test, y_test)
    xgb_model, xgb_accuracy = train_xgboost(X_train, y_train, X_test, y_test)
    lr_model, lr_accuracy = train_logistic_regression(X_train, y_train, X_test, y_test)
    
    print('-' * 20)
    print('-' * 20)
    
    top_features = eval_features(dt_model, X.columns)

    print('-' * 20)
    print('-' * 20)
    
    dt_acc_top, xgb_acc_top, lr_acc_top = train_on_features(
        X_train, X_test, y_train, y_test, top_features
    )

main()