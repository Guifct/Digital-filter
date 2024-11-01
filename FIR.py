
#FIR
import numpy as np
import scipy.signal as sg
import matplotlib.pyplot as plt

def myfreqz(b, a=1):
    w, h = sg.freqz(b, a, worN=8000, fs=fs)
    h_dB = 20 * np.log10(abs(h))

    plt.subplot(211)
    plt.semilogx(w, h_dB)
    plt.ylabel('Magnitude (dB)')
    plt.title(r'Frequency response')

    plt.subplot(212)
    h_Phase = np.unwrap(np.angle(h)) 
    plt.semilogx(w, h_Phase*(180/np.pi))
    plt.ylabel('Phase (radians)')
    plt.xlabel(r'Normalized Frequency (x$\pi$ rad/sample)')
    plt.title(r'Phase response')
    plt.subplots_adjust(hspace=0.5)

fc = 250
fs = 4000
wc = fc/(fs/2)

M = 15
a = sg.firwin(M, cutoff=wc, window="hamming")

myfreqz(a)
print(a)