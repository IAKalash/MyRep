import pandas as pd
import datetime

def sexToBool(sex):
    if sex in ['Ж', 'ж']:
        return 0
    return 1

def liters(num):
    if num > 10 or num < 0:
        return pd.NA
    return num

def ages(row):
    num = row['age']

    if num < 18:
        row['age1'] = 1
    elif num > 50:
        row['age3'] = 1
    else: 
        row['age2'] = 1

    return row

def drinks(drink):
    if drink in ['Cola', 'Fanta', 'Water']:
        return 0
    return 1

def time(row):
    date = datetime.datetime.strptime(row['session_start'], '%H:%M:%S.%f')
    time = datetime.time(date.hour, date.minute)

    if time < datetime.time(12):
        row['morning'] = 1
    elif time > datetime.time(18):
        row['evening'] = 1
    else: 
        row['day'] = 1

    return row

def main():
    table = pd.read_csv('./titanic_with_labels.csv', sep=' ', index_col=0)


    table = table[table['sex'].isin(['м', 'M', 'ж', 'Ж', 'Мужчина'])] # 1
    table['sex'] = table['sex'].apply(sexToBool)


    table['row_number'] = table['row_number'].fillna(table['row_number'].max()) # 2


    table['liters_drunk'] = table['liters_drunk'].apply(liters)
    table['liters_drunk'].fillna(table['liters_drunk'].mean().round(), inplace=True) # 3


    table['age1'] = 0
    table['age2'] = 0
    table['age3'] = 0
    table = table.apply(ages, axis=1).drop(columns=['age']) # 4


    table['drink'] = table['drink'].apply(drinks) # 5


    table = pd.merge(table, pd.read_csv('./cinema_sessions.csv', sep=' ', index_col=0), on='check_number') # 6
    table['morning'] = 0
    table['day'] = 0
    table['evening'] = 0
    table = table.apply(time, axis=1)


    print(table)


main()