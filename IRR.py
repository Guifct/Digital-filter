
#ISTO EH IIRRRRRRRRR

#IIR
import numpy as np
import scipy.signal as sg
import matplotlib.pyplot as plt

def to_w_analog(w,ts):
    return (2/ts)*np.tan(w*ts/2)

def myfreqz(b, a=1):
    w, h = sg.freqz(b, a)
    h_dB = 20 * np.log10(abs(h))

    plt.subplot(211)
    plt.semilogx(((w*fs)/(2*np.pi)), h_dB)
    plt.ylabel('Magnitude (dB)')
    plt.title(r'Frequency response')

    plt.subplot(212)
    h_Phase = np.unwrap(np.angle(h))
    plt.semilogx(((w*fs)/(2*np.pi)), h_Phase)
    plt.ylabel('Phase (radians)')
    plt.xlabel(r'Normalized Frequency (x$\pi$ rad/sample)')
    plt.title(r'Phase response')
    plt.subplots_adjust(hspace=0.5)


fc = 200
wc = 2 * np.pi * fc
fs = 1000
N = 3
wanalg = to_w_analog(wc, 1/fs)

num, den = sg.bessel(N,wanalg, btype ='low', analog = True)
numz, denz = sg.bilinear(num, den, fs) #bilinear trans
print(numz,denz)
myfreqz(numz,denz)

