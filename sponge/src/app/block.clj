(ns app.block
  (:use app.wav)
  (:require [hiphip.double :as v]
            [app.listen :as listen]))

;; whacks pcm
(defn build [pcm]
  ;(listen/normalise! pcm)
  (listen/fadeinout! pcm 50 100)
  {:pcm pcm
   :fft (listen/fftify (v/aclone pcm))
   :mfcc (first (listen/mfccify (v/aclone pcm)))})

;; scores fft and mfcc simulataneosly with a weighting
(defn diff [a b ratio]
  (cond
   (= ratio 0) (listen/diff (:fft a) (:fft b))
   (= ratio 1) (listen/diff (:mfcc a) (:mfcc b))
   :else (+ (* (listen/diff (:fft a) (:fft b)) (- 1 ratio))
            (* (listen/diff (:mfcc a) (:mfcc b))) ratio)))
