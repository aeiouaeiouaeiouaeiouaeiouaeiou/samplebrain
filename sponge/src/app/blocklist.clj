(ns app.blocklist
  (:use app.wav)
  (:require [hiphip.double :as dbl]
            [app.block :as block]))

(defn build [sound rate block-size]
  (let [data (first (first (.chunks sound rate)))]
    (println (count data))
    (for [block-index (range (- (/ (count data) block-size) 1))]
      (block/build
       (dbl/amake
        [i block-size]
        (aget data (+ (* block-index block-size) i)))))))

(defn search [blocks target-block ratio]
  (reduce
   (fn [r b]
     (let [d (block/diff target-block b ratio)]
       (if (> (first r) d)
         [d b] r)))
   [9999999999999 false]
   blocks))
