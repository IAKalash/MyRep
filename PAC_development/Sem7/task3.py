import pandas as pd

df = pd.read_csv('./wells_info_na.csv')
df.columns = df.columns.str.strip()

df.replace("", pd.NA, inplace=True)
df.replace(" ", pd.NA, inplace=True)

df['CompletionDate'] = pd.to_datetime(df['CompletionDate'], errors='coerce')
df['FirstProductionDate'] = pd.to_datetime(df['FirstProductionDate'], errors='coerce')

numeric_cols = df.select_dtypes(include=['float64', 'int64']).columns
categorical_cols = df.select_dtypes(include=['object', 'category']).columns


for col in numeric_cols:
    median_val = df[col].median()
    df[col].fillna(median_val, inplace=True)

for col in categorical_cols:
    mode_val = df[col].mode()
    df[col].fillna(mode_val[0], inplace=True)

df['CompletionDate'].fillna(df['CompletionDate'].median(), inplace=True)

print(df)