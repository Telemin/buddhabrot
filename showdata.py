#!/usr/bin/env  python3

import sys
import matplotlib
matplotlib.use('tkagg')
import matplotlib.pyplot as plt
import numpy as np

def main():
    data = np.fromfile(sys.argv[1],'double',-1)
    data = data.reshape((data.shape[0]/2,2)).T
    print(data[0])
    print(data[1])
    
    plt.plot(data[0],data[1],'k.')
    plt.xlim(-2,2)
    plt.ylim(-2,2)
    plt.show()

    return(0)


if __name__ == "__main__":
    main()
