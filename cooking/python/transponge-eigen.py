# wierd eigensound approach - project into learned pca space

# fft -> matrix -> ifft -> sound

from magicsquares import *
import numpy as np
import scipy.io.wavfile
import math

source_dir = "../sound/source/"
render_dir = "../sound/render/"

def fadeinout(s,slength,elength):
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

def arr_to_fv(a):
    vp = FloatVector(len(a))
    for i in range(0,vp.Size()):
        vp[i]=float(a[i])
    return vp

def fv_to_arr(a):
    ret = np.zeros(a.Size(),dtype=np.float32)
    for i in range(0,a.Size()):
        ret[i]=a[i]
    return ret

def build_pca(filename,s):
    pca = PCA(len(s[0]))
    for i,v in enumerate(s):
        print(i/float(len(s))*100.0)
        pca.AddFeature(arr_to_fv(v))
    print("making eigenmatrix")
    pca.Calculate()
    print("saving eigenmatrix")
    f = OpenFile(filename, "wb")
    pca.Save(f)
    CloseFile(f)
    return pca

def load_pca(filename):
    pca = PCA(1)
    f = OpenFile(filename, "rb")
    pca.Load(f)
    CloseFile(f)
    pca.Compress(2,40)
    return pca

def synth_sound(s,pca):
    p = pca.Project(arr_to_fv(s))
    #for i in range(0,p.Size()):
    #    if i<50 and i>5: p[i]=0
    #    if i>100: p[i]=0
    s = pca.Synth(p)
    return s

def project_eigen_sound(pca,row,gain):
    return fv_to_arr(pca.GetEigenTransform().GetRowVector(row)*gain)

def fftify(chopped):
    return map(lambda i: np.array(np.fft.fft(i),dtype=np.float32), chopped)

def chop(wav,size,overlap):
    ret = []
    pos = 0
    seg = []
    samples = wav[1]
    while (pos+size<len(samples)):
        ret.append(samples[pos:pos+size]) # 50,100
        pos+=(size-overlap)
    return ret

class transponge():
    def __init__(self,chp_size,chp_overlap,dst_filename):
        dst =  scipy.io.wavfile.read(dst_filename)
        self.src_chp=[]
        self.src_fft=[]
        self.chp_size = chp_size
        self.chp_overlap = chp_overlap
        self.dst_chp = chop(dst,self.chp_size,self.chp_overlap)
        self.dst_fft = fftify(self.dst_chp)
        print(self.chp_overlap)
        print (len(self.dst_chp))
        self.dst_size = len(dst[1])

    def add(self,src_filename):
        src =  scipy.io.wavfile.read(src_filename)
        src_chp=chop(src,self.chp_size,self.chp_overlap)
        self.src_fft+=fftify(src_chp)
        self.src_chp+=src_chp
        print("src now: "+str(len(self.src_chp)))

    def learn(self,filename):
        scipy.io.wavfile.write(render_dir+"input.wav",44100,np.concatenate(self.src_fft))
        self.pca = build_pca(filename,self.src_fft)

    def load(self,filename):
        self.pca = load_pca(filename)

    def process(self):
        out = np.zeros(self.dst_size,dtype=np.int16)
        pos = 0
        for i,seg in enumerate(self.dst_fft):
            fft = fv_to_arr(synth_sound(seg,self.pca))
            resynth = fadeinout(np.fft.ifft(fft),50,50)
            print(resynth[55])
            for s in range(0,self.chp_size):
                if pos+s<self.dst_size:
                    out[pos+s]+=resynth[s]
            pos+=(self.chp_size-self.chp_overlap)
            print((i/float(len(self.dst_chp)))*100.0)
            if i%10==0: scipy.io.wavfile.write(render_dir+"pca-out-amen-wierd.wav",44100,out)

    def process_eigensound(self,row):
        print self.pca.GetEigenValues()[0]

        out = []
        for row in range(0,50):
            for i in range(0,10):
                #gain = (i/float(100)-0.5)*2
                #gain = 1/self.pca.GetEigenValues()[row]
                gain =100000
                #print("gain:"+str(gain))
                n = project_eigen_sound(self.pca,row,gain)

                pcm = np.fft.ifft(n).astype(np.float32)
                pcm*=3
                print(pcm[0])


                out.append(pcm)
            scipy.io.wavfile.write(render_dir+"eigensound.wav",44100,np.concatenate(out).astype(np.int16))

def run(l):
    t = transponge(l,int(l*0.75),source_dir+"pw2.wav")

#    t.add(source_dir+"full.wav")
#    t.add(source_dir+"808.wav")
#    t.add(source_dir+"amen_brother.wav")

#    t.add(source_dir+"sailingbybit.wav")
#    t.add(source_dir+"dreambit.wav")
    #t.add(source_dir+"pw2.wav")

    #print("learning")
    #t.learn("amen-fft.pca")

    #print("loading")
    #t.load("sailingby-fft.pca")
#    t.load("acid-fft.pca")
    #t.load("full-fft.pca")
#    t.load("808-fft.pca")

    t.load("amen-fft.pca")


    #t.process_eigensound(3)


#    print("processing")
    t.process()

run(512)

'''import matplotlib.pyplot as plt

sound = scipy.io.wavfile.read(source_dir+"808.wav")[1]


fourier = np.fft.fft(sound)
n = len(sound)
timestep = 0.01
freq = np.fft.fftfreq(n, d=timestep)

freq = freq.astype(np.float32)

for i in range(0,1000):
    print(freq[i])

scipy.io.wavfile.write(render_dir+"fft.wav", 44100, freq)
'''
