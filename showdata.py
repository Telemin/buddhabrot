#!/usr/bin/env  python3

import sys
import matplotlib
matplotlib.use('agg')
import matplotlib.image as mi
import matplotlib.cm as mcm

import numpy as np

def main():
    data = np.fromfile(sys.argv[1],'long',-1)
    data = data.reshape((1000,1000))
    data = np.log(data)
    mi.imsave("abb.png",data,cmap=mcm.viridis)    

    return(0)


if __name__ == "__main__":
    main()
