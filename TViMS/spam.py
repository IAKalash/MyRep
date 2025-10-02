import pandas as pd
import re
import math
from collections import defaultdict

def parse(text):
    return set(re.sub(r'[^\w\s]', '', str(text).lower()).split())

def train(df_train):
    df_train['tokens'] = (df_train['Subject'] + ' ' + df_train['Message']).map(parse)
    
    spam_df = df_train[df_train['Spam/Ham'] == 'spam']
    ham_df = df_train[df_train['Spam/Ham'] == 'ham']
    
    spam_total = len(spam_df)
    ham_total = len(ham_df)
    total = spam_total + ham_total
    
    spam_prior = spam_total / total
    ham_prior = ham_total / total
    
    word_spam_counts = defaultdict(int)
    word_ham_counts = defaultdict(int)

    for tokens in spam_df['tokens']:
        for word in tokens:
            word_spam_counts[word] += 1

    for tokens in ham_df['tokens']:
        for word in tokens:
            word_ham_counts[word] += 1

    return {
        'spam_prior': spam_prior,
        'ham_prior': ham_prior,
        'spam_word_counts': word_spam_counts,
        'ham_word_counts': word_ham_counts,
        'spam_total': spam_total,
        'ham_total': ham_total
    }

def predict(subject, message, model):
    tokens = parse(subject + ' ' + message)

    log_spam = math.log(model['spam_prior'])
    log_ham = math.log(model['ham_prior'])

    for word in tokens:
        p_spam = (model['spam_word_counts'].get(word, 0) + 1) / (model['spam_total'] + 2)
        p_ham = (model['ham_word_counts'].get(word, 0) + 1) / (model['ham_total'] + 2)

        log_spam += math.log(p_spam)
        log_ham += math.log(p_ham)

    return 'spam' if log_spam > log_ham else 'ham'


def eval_metrics(df_test, model):
    tp = tn = fp = fn = 0

    for _, row in df_test.iterrows():
        pred = predict(row['Subject'], row['Message'], model)
        actual = row['Spam/Ham']
        if actual == 'spam':
            if pred == 'spam':
                tp += 1
            else:
                fn += 1
        else:
            if pred == 'ham':
                tn += 1
            else:
                fp += 1

    total = tp + tn + fp + fn
    accuracy = (tp + tn) / total if total else 0
    sensitivity = tp / (tp + fn) if tp + fn else 0
    specificity = tn / (tn + fp) if tn + fp else 0

    return accuracy, sensitivity, specificity


def split_dataset(df, coef=0.8):
    df = df.sample(frac=1)
    split = int(len(df) * coef)
    return df.iloc[:split], df.iloc[split:]


def main():
    df = pd.read_csv('enron_spam_data.csv')
    df = df[['Subject', 'Message', 'Spam/Ham']].dropna()

    train_df, test_df = split_dataset(df, 0.7)
    model = train(train_df)

    accuracy, sensitivity, specificity = eval_metrics(test_df, model)

    print(f'Accuracy:     {accuracy:.4f}')
    print(f'Sensitivity:  {sensitivity:.4f}')
    print(f'Specificity:  {specificity:.4f}')

if __name__ == '__main__':
    main()