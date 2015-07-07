(ns app.test.blocklist
  (:use app.blocklist
        app.wav
        clojure.test))

(deftest blocklist
  (is (= 86 (count (build (sinusoid 1 440) 44100 512))))
  (is (= 2 (count (build (sinusoid 1 440) 44100 22049))))
  (let [bl (build (sinusoid 1 440) 44100 512)]
    (is (not (= false (second (search bl (first bl) 0)))))
    (is (= 0.0 (first (search bl (first bl) 0))))))
