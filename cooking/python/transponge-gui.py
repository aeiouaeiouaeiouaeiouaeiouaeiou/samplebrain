# aggregate sound from mfcc or fft similarity of chunks

import numpy as np
import scipy.io.wavfile
from features import mfcc
from features import logfbank
from features import base
import copy

import platform;

if int(platform.python_version_tuple()[0])>2:
	from tkinter import *
	from tkinter.filedialog import *
	from tkinter.messagebox import *
else:
	from Tkinter import *
	from tkFileDialog import *
	from tkMessageBox import *


source_dir = "../sound/source/"
render_dir = "../sound/render/"
version = "0.0.1"

def msg(msg):
    print(msg)

def clear_msg():
    pass

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
    msg(str(ret))
    return ret

#unit_test()

class transponge():
    def __init__(self):
        self.src=[]
        self.dst=[0,[]]
        self.src_chp=[]
        self.dst_chp=[]
        self.src_fft=[]
        self.dst_fft=[]

    def set_target(self,dst_filename):
        self.dst = scipy.io.wavfile.read(dst_filename)
        msg("succesfully loaded "+dst_filename+" as the target")

    def add_source(self,src_filename):
        self.src.append(scipy.io.wavfile.read(src_filename))
        msg("succesfully loaded "+src_filename+" as a source")
        msg("(now have "+str(len(self.src))+" sounds in brain...)")

    def prepare(self,chp_size,chp_overlap,mfcc):
        self.chp_size = chp_size
        self.chp_overlap = chp_overlap

        msg("chopping up target wav...")
        self.dst_chp = chop(self.dst,self.chp_size,self.chp_overlap,0)
        msg("number of target blocks: "+str(len(self.dst_chp)))

        msg("processing target blocks")

        if mfcc:
            self.dst_fft = mfccify(self.dst_chp,self.dst[0])
        else:
            self.dst_fft = fftify(self.dst_chp)

        self.dst_chp = [] # clear
        self.dst_size = len(self.dst[1])

        for i,src in enumerate(self.src):
            msg("chopping up source wav no. "+str(i+1))
            chopped=chop(src,self.chp_size,self.chp_overlap,0)
            msg("number of target blocks: "+str(len(chopped)))
            self.src_chp+=chopped
            if mfcc:
                self.src_fft+=mfccify(chopped,src[0])
            else:
                self.src_fft+=fftify(chopped)

            msg("total number of source blocks now: "+str(len(self.dst_fft)))


    def process(self,filename):
        out = np.zeros(self.dst_size,dtype=self.src_chp[0][1].dtype)
        pos = 0
        for i,seg in enumerate(self.dst_fft):
            # collect indices of closest sections
            ii = search(seg,self.src_fft)
            clear_msg()
            for s in range(0,self.chp_size):
                if pos+s<self.dst_size:
                    sample = self.src_chp[ii][1][s]
                    out[pos+s]=out[pos+s]+(sample*0.25)
            pos+=(self.chp_size-self.chp_overlap)
            msg(str((i/float(len(self.dst_fft)))*100.0)[:5]+"%")
            if i%10==0: scipy.io.wavfile.write(render_dir+filename,44100,out)



class win:
    def __init__(self):
        self.sponge = transponge()

        # create window
        self.root = Tk()
        self.root.title("transpongerator brain "+version)
        f=Frame(self.root)
        f.pack(fill=NONE);
        Button(f, text="load a source", command=self.load_source).grid(row=0, column=0, sticky="we")
        Button(f, text="load the target", command=self.load_target).grid(row=0, column=1, sticky="we")
        self.run_button = Button(f, text="run", command=self.run)
        self.run_button.grid(row=0, column=2, sticky="we")
        self.mfcc_var = IntVar()
        cb=Checkbutton(f, text="use mfcc", variable=self.mfcc_var, command=self.mfcc)
        cb.grid(row=1, column=0)
        cb.select()

        rf = Frame(f)
        rf.grid(row=1, column=3)
        Label(rf, text="overlap").grid(row=0,column=0)
        self.overlap_entry = Entry(rf, width=5)
        self.overlap_entry.grid(row=1, column=0)
        self.overlap_entry.bind("<Return>", self.on_overlap)
        self.overlap_entry.delete(0, END)
        self.overlap_entry.insert(0, "0.75")
        self.overlap=0.75

        rf = Frame(f)
        rf.grid(row=1, column=4)
        Label(rf, text="window size").grid(row=0,column=0)
        self.window_entry = Entry(rf, width=5)
        self.window_entry.grid(row=1, column=0)
        self.window_entry.bind("<Return>", self.on_window_size)
        self.window_entry.delete(0, END)
        self.window_entry.insert(0, "3000")
        self.window_size=3000


        self.debug = Text(self.root, font = "Helvetica 24 bold", height=10, width=60)
        self.debug.pack()
        self.debug.insert(END, "ready...\n")

        #Label(lf, text="Branch length").grid(row=0,column=0)
        #self.length_scale = Scale(lf, from_=0, to=100, orient=HORIZONTAL, command=self.on_length)
        #self.length_scale.grid(row=1, column=0)
        #self.length_scale.set(30)

        #t.grid_rowconfigure(1,weight=0)
        # start event loop


    def msg(self,msg):
        self.debug.insert(0.0, msg+"\n")
        self.root.update()

    def clear_msg(self):
        self.debug.delete(0.0, END)
        self.root.update()

    def load_target(self):
        filename = askopenfilename(title = "load target wav")
        if filename!="":
            self.sponge.set_target(filename)

    def load_source(self):
        filename = askopenfilename(title = "load source wav into brain")
        if filename!="":
            self.sponge.add_source(filename)

    def on_window_size(self,event):
        try:
            self.window_size = float(self.window_entry.get())
        except:
            pass

    def on_overlap(self,event):
        try:
            self.overlap = float(self.overlap_entry.get())
        except:
            pass

    def run(self):
        self.msg("preparing: windowsize: "+str(self.window_size))
        self.msg("overlap: "+str(self.overlap))
        self.sponge.prepare(int(self.window_size),int(self.window_size*self.overlap),self.mfcc_var.get()==1)
        msg("processing...")
        self.sponge.process("brain_out.wav")
        msg("done, saved in brain_out.wav")



    def mfcc(self):
        pass


w = win()

msg = w.msg
clear_msg = w.clear_msg

try:
    w.root.mainloop()
except Exception,e:
    msg(e)
