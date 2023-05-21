import matplotlib.pyplot as plt
from plot_ping import parse_ping

def ertt_get(fname):
    ertt = []
    tt = []
    with open('./'+fname+'_cwnd.txt', 'r') as f:
        for i, line in enumerate(f.readlines()):
	    xx = line.strip().split(' ')
	    if i == 0: 
	        tt_0 = float(xx[0])
	    if '10.0.0.1' in xx[1]:
	        tt.append(float(xx[0])-tt_0-1.0)
	        ertt.append(abs(float(xx[-2]))/1e3)
    return tt, ertt   
	
from pylab import figure
import plot_defaults
from matplotlib.ticker import MaxNLocator
from helper import *

def plot_srtt_ertt(fname):
    fig = figure(figsize=(16, 6))
    ax = fig.add_subplot(111)
    f = "{}_pings.txt".format(fname)
    data = parse_ping(f)
    xaxis = map(float, col(0, data))
    freq=10
    start_time = xaxis[0]
    xaxis = map(lambda x: (x - start_time) / freq, xaxis)
    qlens = map(float, col(1, data))

    ax.plot(xaxis, qlens, lw=2, label='Sampled_RTT')
    ax.xaxis.set_major_locator(MaxNLocator(4))

    plt.ylabel("RTT (ms)")
    plt.xlabel("Ping #")
    plt.grid(True)
    tt, ertt = ertt_get(fname)
    plt.plot(tt, ertt, '-', label='Estimated_RTT')
    plt.legend()
    plt.show()
