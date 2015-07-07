(ns app.test.listen
  (:use [app.listen])
  (:use [clojure.test]))

(deftest fading-test
  (is (= (seq [0.0 0.5 1.0 0.5 0.0]) (seq (fadeinout! (double-array [1 1 1 1 1]) 2 2))))
  (is (= (seq[0.0 1.0 0.0]) (seq (fadeinout! (double-array [1 1 1]) 1 1)))))

(deftest normalise-test
  (is (= (seq[0.0 1.0 0.0]) (seq (normalise! (double-array [0 10 0])))))
  (is (= (seq[0.0 -1.0 0.0]) (seq (normalise! (double-array [0 -10 0]))))))

(deftest fft-test
  (is 9 (count (fftify (double-array [1 0 0 0 1 0 0 0 1])))))

(deftest mfcc-test
  (is 13 (count (first (mfccify (double-array [1 0 0 0 1 0 0 0 1]))))))

(deftest diff-test
  (is 1.0 (diff (double-array [1 2 3 4]) (double-array [1 2 3 5])))
  (is 1.0 (diff (double-array [1 3 3 4]) (double-array [1 2 3 4])))
  (is 0.1 (diff (double-array [1 3 3.1 4]) (double-array [1 3 3 4])))
  (is 0.1 (diff (double-array [0.9 3 3.1 4]) (double-array [0.9 2.9 3.1 4])))
  )
