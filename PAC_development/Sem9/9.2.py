import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.linear_model import LogisticRegression
from xgboost import XGBClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler
from sklearn.base import BaseEstimator, ClassifierMixin

class MyRandomForest(BaseEstimator, ClassifierMixin):
    
    def __init__(self, n_estimators=100, max_features='sqrt', random_state=None):
        self.n_estimators = n_estimators
        self.max_features = max_features
        self.random_state = random_state
        self.trees = []
        
    def fit(self, X, y):
        X_array = X.values if hasattr(X, 'values') else X
        y_array = y.values if hasattr(y, 'values') else y
        
        n_samples, n_features = X_array.shape
        
        n_features_per_tree = max(1, int(np.sqrt(n_features)))
            
        rng = np.random.RandomState(self.random_state)
        self.trees = []
        
        for i in range(self.n_estimators):
            sample_indices = rng.choice(n_samples, size=n_samples, replace=True)
            X_bootstrap = X_array[sample_indices]
            y_bootstrap = y_array[sample_indices]
            
            feature_indices = rng.choice(n_features, size=n_features_per_tree, replace=False)
            X_bootstrap_features = X_bootstrap[:, feature_indices]
            
            tree = DecisionTreeClassifier(random_state=rng.randint(0, 10000))
            tree.fit(X_bootstrap_features, y_bootstrap)
            
            self.trees.append((tree, feature_indices))
        
        return self
    
    def predict(self, X):
        X_array = X.values if hasattr(X, 'values') else X
        
        all_predictions = []
        for tree, feature_indices in self.trees:
            X_features = X_array[:, feature_indices]
            predictions = tree.predict(X_features)
            all_predictions.append(predictions)
        
        all_predictions = np.array(all_predictions)
        
        final_predictions = []
        for i in range(all_predictions.shape[1]):
            votes = all_predictions[:, i]
            counts = np.bincount(votes.astype(int))
            winner = np.argmax(counts)
            final_predictions.append(winner)
        
        return np.array(final_predictions)
    

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

def train_my_random_forest(X_train, y_train, X_test, y_test):
    rf_model = MyRandomForest(
        n_estimators=50,
        random_state=42
    )
    rf_model.fit(X_train, y_train)
    
    y_pred = rf_model.predict(X_test)
    accuracy = accuracy_score(y_test, y_pred)
    
    print(f"My Random Forest Results: {accuracy:.4f}")
    
    return rf_model, accuracy

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
    
    # My Random Forest
    rf_model_top = MyRandomForest(
        n_estimators=50,
        random_state=42
    )
    rf_model_top.fit(X_train_top, y_train)
    y_pred_rf = rf_model_top.predict(X_test_top)
    accuracy_rf = accuracy_score(y_test, y_pred_rf)
    
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
    print(f"  My Random Forest Accuracy: {accuracy_rf:.4f}")
    print(f"  XGBoost Accuracy: {accuracy_xgb:.4f}")
    print(f"  Logistic Regression Accuracy: {accuracy_lr:.4f}")
    
    return accuracy_dt, accuracy_rf, accuracy_xgb, accuracy_lr

def main():
    X, y = preprocess_data('titanic_prepared.csv')
    X_train, X_test, y_train, y_test = split_data(X, y)
    
    print('-' * 20)
    
    dt_model, dt_accuracy = train_decision_tree(X_train, y_train, X_test, y_test)
    my_rf_model, my_rf_accuracy = train_my_random_forest(X_train, y_train, X_test, y_test)
    xgb_model, xgb_accuracy = train_xgboost(X_train, y_train, X_test, y_test)
    lr_model, lr_accuracy = train_logistic_regression(X_train, y_train, X_test, y_test)
    
    print('-' * 20)
    
    top_features = eval_features(dt_model, X.columns)

    print('-' * 20)
    
    dt_acc_top, rf_acc_top, xgb_acc_top, lr_acc_top = train_on_features(
        X_train, X_test, y_train, y_test, top_features
    )

main()