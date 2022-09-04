# aggregate sound from mfcc or fft similarity of chunks

import numpy as np
import scipy.io.wavfile
from features import mfcc
from features import logfbank
from features import base
import copy

source_dir = "../sound/source/"
render_dir = "../sound/render/"

def fadeinout(s,slength,elength):
    s = copy.deepcopy(s)
    for i in range(0,slength):
        m = float(i)/slength;
        s[i]*=m
    for i in range(0,elength):
        m = float(i)/elength;
        s[(len(s)-1)-i]*=m
    return s

def normalise(s):
    m = 0
    p = 999999999999999999
    for i in range(0,len(s)):
        if m<s[i]: m=s[i]
        if p>s[i]: p=s[i]
    b = max(m,-p)
    if b>0:
        s/=float(b/10000.0)
    return s

def chop(wav,size,overlap,rand):
    ret = []
    pos = 0
    seg = []
    samples = wav[1]
    while (pos+size<len(samples)):
        ret.append([0,fadeinout(samples[pos:pos+size],500,500)])
        pos+=(size-overlap)
    return ret

def fftify(chopped):
    return map(lambda i: np.fft.fft(i[1]), chopped)

def mfccify(chopped,rate):
    ret = []
    for sig in chopped:
        ret.append(logfbank(sig[1],rate))
    return ret

def fftdiff(a,b):
    return (abs(a-b)).sum(dtype=np.float128)

def diffify(a,b):
    return map(lambda a,b: fftdiff(a,b), a, b)

def search(fft,bank):
    closest = 99999999999999999
    ret = -1
    for i,tfft in enumerate(bank):
        dist = fftdiff(fft,tfft)
        if dist<closest:
            ret = i
            closest = dist
    print(ret)
    return ret

def unit_test():
    print(fftdiff(np.array([0,0,0,0]),np.array([1,1,1,1])))
    #assert(fftdiff(np.array([0,0,0,0]),np.array([1,1,1,1]))==1)
    print(fftdiff(np.array([-100,-1000,0,0]),np.array([-1,-1,-1,-1])))
    print(fadeinout(np.array([10,10,10,10,10,10,10]),3))

#unit_test()

class transponge():
    def __init__(self,chp_size,chp_overlap,dst_filename):
        dst =  scipy.io.wavfile.read(dst_filename)
        self.src_chp=[]
        self.src_fft=[]
        self.chp_size = chp_size
        self.chp_overlap = chp_overlap
        self.dst_chp = chop(dst,self.chp_size,self.chp_overlap,0)
        print("number of target blocks: "+str(len(self.dst_chp)))
        self.dst_fft = mfccify(self.dst_chp,dst[0])
        #self.dst_fft = fftify(self.dst_chp)
        self.dst_chp = [] # clear
        self.dst_size = len(dst[1])

    def add(self,src_filename):
        src =  scipy.io.wavfile.read(src_filename)
        print("adding "+src_filename)
        src_chp=chop(src,self.chp_size,self.chp_overlap,0)
        self.src_chp+=src_chp
        self.src_fft+=mfccify(src_chp,src[0])
        print("number of source blocks now: "+str(len(self.dst_fft)))

        #self.src_fft+=fftify(src_chp)

    def process(self):
        out = np.zeros(self.dst_size,dtype=self.src_chp[0][1].dtype)
        pos = 0
        for i,seg in enumerate(self.dst_fft):
            # collect indices of closest sections
            ii = search(seg,self.src_fft)
            for s in range(0,self.chp_size):
                if pos+s<self.dst_size:
                    sample = self.src_chp[ii][1][s]
                    out[pos+s]=out[pos+s]+(sample*0.25)
            pos+=(self.chp_size-self.chp_overlap)
            print((i/float(len(self.dst_fft)))*100.0)
            if i%10==0: scipy.io.wavfile.write(render_dir+"pwr-acid-mfccnonorm1500.wav",44100,out)


def run(l):
    t = transponge(l,int(l*0.75),source_dir+"pw-right.wav")

    t.add(source_dir+"totalsine.wav")

#    t.add(source_dir+"water.wav")
#    t.add(source_dir+"cumbia.wav")
#    t.add(source_dir+"pista07.wav")
#    t.add(source_dir+"sailingbybit.wav")
    t.add(source_dir+"808.wav")
    t.add(source_dir+"joey.wav")

#    t.add("full.wav")
    print("processing")
    t.process()

run(1500)
