#!/usr/bin/env  python3

import sys
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.colors as mc

def main():
    data = np.loadtxt(sys.argv[1]) + 1
    plt.hist(data.flatten())
    plt.show()
    plt.pcolor(data, cmap='gray') 
    plt.show()

    return(0)


if __name__ == "__main__":
    main()
