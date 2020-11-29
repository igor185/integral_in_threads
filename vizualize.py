import pandas as pd
import matplotlib.pyplot as plt

DATA_DIR = "./results/"
SAVE_DIR = "./graphics/"


def save_plot(file):
    df = pd.read_csv(DATA_DIR + file + ".csv")

    plt.plot(df["threads"], df["time"])

    plt.savefig(SAVE_DIR + file + ".png")

    plt.close()


save_plot("result1")
save_plot("result2")
save_plot("result3")
save_plot("result4")