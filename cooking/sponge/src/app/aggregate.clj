(ns app.aggregate
  (:use app.wav)
  (:require [hiphip.double :as dbl]
            [app.block :as block]
            [app.blocklist :as blocklist]))

(defn data-to-sound [data]
  (reify SampledSound
    (duration [this] (/ (count data) 44100))
    (channels [this] 1)
    (chunks [this sample-rate]
      ;; sloooow
      [[data]])))

(defn sound-to-data [sound]
  (first (first (.chunks sound 44100))))

(defn render-blocklist [blocklist]
  (reify SampledSound
    (duration [this] (/ (* (count (:pcm (first blocklist)))
                           (count blocklist)) 44100))
    (channels [this] 1)
    (chunks [this sample-rate]
      ;; sloooow
      (let [strp (map (fn [b] (:pcm b)) blocklist)]
        [[(double-array (apply concat strp))]]))))

(defn render-blocklist-fft [blocklist]
  (reify SampledSound
    (duration [this] (/ (* (count (:pcm (first blocklist)))
                           (count blocklist)) 44100))
    (channels [this] 1)
    (chunks [this sample-rate]
      ;; sloooow
      (let [strp (map (fn [b] (:fft b)) blocklist)]
        [[(double-array (apply concat strp))]]))))

(defn search [src target ratio]
   (map
    (fn [block]
      (let [r (blocklist/search src block ratio)]
        (println (first r)) (second r)))
    target))

(defn aggregate [source-path-list target-filename rate block-size ratio]
  (let [blocks (apply
                concat
                (map
                 (fn [filename]
                   (blocklist/build (read-sound filename) rate block-size))
                 source-path-list))
        target (blocklist/build (read-sound target-filename) rate block-size)]
    (println "built sources")
    (render-blocklist (search blocks target ratio))))
