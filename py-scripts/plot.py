import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


df = pd.read_csv("eulerocromer.csv")
x = df['t'].to_numpy()
y = df['x'].to_numpy()
# v = df['v'].to_numpy()
plt.plot(x, y)
# plt.plot(x,v)

df = pd.read_csv("leapfrog.csv")
x = df['t'].to_numpy()
y = df['x'].to_numpy()
# v = df['v'].to_numpy()
plt.plot(x, y)
# plt.plot(x,v)

plt.show()
