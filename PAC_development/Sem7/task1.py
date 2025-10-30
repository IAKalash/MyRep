import pandas as pd
import numpy as np

def main():
    df = pd.DataFrame(np.random.rand(10, 5))
    print(df, "\n")
    print(df[df>0.3].mean(1))

main()