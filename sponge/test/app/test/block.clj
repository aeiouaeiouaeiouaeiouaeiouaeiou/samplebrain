(ns app.test.block
  (:use app.block
        clojure.test)
  (:require [hiphip.double :as v]))


(deftest block
  (let [block (build (v/amake [_ 512] 1))]
    (is (= 512 (count (:fft block))))
    (is (= 13 (count (:mfcc block))))
    (let [block2 (build (v/amake [_ 512] 0))]
      (is (not (= 0 (diff block block2 0))))
      (is (not (= 0 (diff block block2 1))))
      (is (not (= 0 (diff block block2 0.5)))))))
