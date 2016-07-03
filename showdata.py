#!/usr/bin/env  python3

import sys
import matplotlib
matplotlib.use('tkagg')
import matplotlib.pyplot as plt
import numpy as np

def main():
    data = np.fromfile(sys.argv[1],'double',-1)
    data = data.reshape((2,data.shape[0]/2))
    print(data)
    

    return(0)


if __name__ == "__main__":
    main()
