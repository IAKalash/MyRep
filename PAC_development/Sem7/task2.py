import pandas as pd

def main():
    table = pd.read_csv('./wells_info.csv')
    table.columns = table.columns.str.strip()
    
    delta = pd.to_datetime(table["CompletionDate"]).dt.to_period('M').astype(int) - \
        pd.to_datetime(table["FirstProductionDate"]).dt.to_period('M').astype(int)
    print(delta)
    

main()