(ns app.listen
  (:use app.wav)
  (:require [hiphip.double :as v])
  (:import javax.swing.ImageIcon
           edu.emory.mathcs.jtransforms.fft.DoubleFFT_1D
           org.openimaj.audio.features.MFCC
           org.openimaj.audio.samples.FloatSampleBuffer
           org.openimaj.audio.AudioFormat
           ))

(defn fftify [s]
  (let [fft (new DoubleFFT_1D (count s))]
    (.realForward fft s)
    (v/afill! [i s] (Math/abs i))
    s))

(defn mfccify [s]
  (let [mfcc (new MFCC)]
    (.calculateMFCC mfcc (new FloatSampleBuffer s
                              (new AudioFormat 64 44100 1)))))

;; crappy envelope
(defn fadeinout! [xs slen elen]
  (doall (for [i (range 0 slen)]
           (v/aset xs i (* (v/aget xs i) (/ i slen)))))
  (doall (for [i (range 0 elen)]
           (let [idx (- (- (count xs) 1) i)]
             (v/aset xs idx (* (v/aget xs idx) (/ i elen))))))
  xs)

;; assumes zero crossing
(defn normalise! [xs]
  (let [peak (v/areduce [i xs] m 0 (max m (Math/abs i)))]
    (v/afill! [x xs] (/ x peak)))
  xs)

(defn diff [a b]
  (Math/abs (v/asum [i a j b] (- i j))))
