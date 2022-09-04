(ns app.wav
  "Functions for manipulating a sound whose amplitude representation
  is arrays of doubles."
  (:require [clojure.java.io :as io]
            [hiphip.double :as dbl]
            [incanter.core :as incanter]
            [incanter.charts :as charts]
            [primitive-math :as p])
  (:import [java.nio ByteBuffer]
           [java.util.concurrent LinkedBlockingQueue]
           [javax.sound.sampled
            AudioFileFormat$Type
            AudioFormat
            AudioFormat$Encoding
            AudioInputStream
            AudioSystem]))

;;; Abstraction

;; TODO: It feels like the channels and duration stuff are the real
;; core of the abstraction, and the way you get amplitudes is sort of
;; orthogonal. Maybe there's another abstraction that can get pulled
;; out here.

(defprotocol SampledSound
  "Represents a sound as a sequence of vectors of Java double arrays."
  (channels [this] "Returns the number of channels in the sound.")
  (duration [this] "Returns the duration of the sound in seconds.")
  (chunks [this sample-rate] "Returns a sequence of sequences each
  containing a sequence of double arrays - one per channel - populated
  with the data for this sound. The total number of samples per
  channel will be (* duration sample-rate)"))

;;; Sound construction

(defmacro defsound
  "Expands to define a function `name` that accepts arguments `args`
  returns a sound with `duration`, `channels` whose samples are
  determined by `expr`. Inside expr, the sample rate, the total number
  of samples, the current sample index, and the current channel number
  will be bound to the four symbols in `bindings`."
  [name
   duration-param
   channels-param
   docstring
   args
   [sample-rate num-samples index c]
   expr]
  `(defn ~name
     ~docstring
     ~(vec (concat [duration-param
                    channels-param]
                   args))
     (let [duration# (double ~duration-param)
           chans# (double ~channels-param)]
       (reify SampledSound
         (channels [this#] ~channels-param)
         (duration [this#] duration#)
         (chunks [this# ~sample-rate]
           (let [chunk-size#  (long (* duration# ~sample-rate))
                 ~num-samples (long (* duration# ~sample-rate))
                 num-chunks#  (-> ~num-samples (/ chunk-size#) Math/ceil long)]
             (concat
              (for [chunk-num# (range (dec num-chunks#))]
                (let [base-index# (p/* (long chunk-num#) chunk-size#)]
                  (for [~c (range chans#)]
                    (dbl/amake [i# chunk-size#]
                               (let [~index (p/+ i# base-index#)]
                                 ~expr)))))
              ;; Handle the last chunk specially, since it's probably
              ;; shorter.
              [(let [chunks-so-far# (p/- num-chunks# 1)
                     samples-so-far# (p/* chunk-size# chunks-so-far#)
                     samples-remaining# (p/- ~num-samples samples-so-far#)]
                 (for [~c (range chans#)]
                   (dbl/amake [i# samples-remaining#]
                              (let [~index (p/+ i# (p/* (p/- num-chunks# 1) chunk-size#))]
                                ~expr))))])))))))

(defsound constant duration chans
  "Returns a sound of `duration` that has `chans` channels, each of
  which is constant at `x`."
  [x]
  [sample-rate num-samples i c]
  x)

(defn silence
  "Returns a sound of `duration` with `chans` channels of silence."
  [dur chans]
  (constant dur chans 0.0))

;; TODO: It would be nice if we had a way to indicate local bindings
;; that we want to be in effect outside the amake so we don't have all
;; these stupid calls to double inside the inner loop.
(defsound linear duration chans
  "Returns a sound of `duration` that has `chans` channels, each of
  which changes linearly from `start` to `end`."
  [start end]
  [sample-rate num-samples i c]
  (p/+ (double start)
       (p/* (p/- (double end)
                 (double start))
            (p/div (double i)
                   (double num-samples)))))

(defsound fn-sound duration chans
  "Creates a SampledSound `duration` seconds long where the amplitudes
  are produced by `f`, a function of a channel number and a time in
  seconds."
  [f]
  [sample-rate num-samples i c]
  (f c (p/div (double i) (double sample-rate))))

(defn sinusoid
  "Returns a single-channel sound of `duration` and `frequency`"
  [^double duration ^double frequency]
  (fn-sound duration 1 (fn sinusoid-fn [^long c ^double t]
                      (Math/sin (p/* t frequency 2.0 Math/PI)))))

(defn square-wave
  "Produces a single-channel sound that toggles between 1.0 and -1.0
  at frequency `freq`."
  [^double duration ^double frequency]
  (fn-sound duration 1 (fn square-wave-fn [^long c ^double t]
                         (let [x (-> t (p/* frequency 2.0) long)]
                           (if (even? x) 1.0 -1.0)))))

(defn- to-double-arrays
  "Return a seq of arrays of doubles that decode the values in buf."
  [^bytes buf ^long bytes-read ^long bytes-per-sample ^long chans]
  (let [samples-read (/ bytes-read bytes-per-sample chans)
        bb           (ByteBuffer/allocate bytes-read)
        arrs         (repeatedly chans #(double-array samples-read))]
    (.put bb buf 0 bytes-read)
    (.position bb 0)
    (dotimes [n samples-read]
      (doseq [arr arrs]
        ;; TODO: We're hardcoded to .getShort here, but the
        ;; bytes-per-sample is a parameter. Should probably have
        ;; something that knows how to read from a ByteBuffer given a
        ;; number of bits.
        (dbl/aset arr n (p/div (double (.getShort bb)) 32768.0))))
    arrs))

(defn- sample-chunks
  "Return a seq of chunks from an AudioInputStream."
  [^AudioInputStream ais ^long chans ^long bytes-per-sample ^long chunk-size]
  (let [buf (byte-array (p/* chunk-size chans bytes-per-sample))
        bytes-read (.read ais buf)]
    (when (pos? bytes-read)
      (lazy-seq
       (cons (to-double-arrays buf (long bytes-read) bytes-per-sample chans)
             (sample-chunks ais chans bytes-per-sample chunk-size))))))

(defn- read-duration
  "Given a path to a .wav or .mp3 file, return the duration in
  seconds."
  [path]
  (let [file                 (io/file path)
        base-file-format     (AudioSystem/getAudioFileFormat file)
        base-file-properties (.properties base-file-format)
        base-file-duration   (get base-file-properties "duration")]
    (if base-file-duration
      (/ base-file-duration 1000000.0)
      (let [in (AudioSystem/getAudioInputStream file)
            base-format (.getFormat in)
            frame-length (.getFrameLength in)
            frames-per-second (.getSampleRate base-format)]
        (.close in)
        (/ frame-length (double frames-per-second))))))

(defn read-sound
  "Given a path to a .wav or .mp3 file, return a SampledSound instance
  over it."
  [path]
  (let [file                 (io/file path)
        base-file-format     (-> file  AudioSystem/getAudioFileFormat .getFormat)
        base-file-properties (.properties base-file-format)
        dur                  (read-duration path)
        chans                (.getChannels base-file-format)
        file-sample-rate     (.getSampleRate base-file-format)
        file-encoding        (.getEncoding base-file-format)]
    (reify SampledSound
      (duration [this] dur)
      (channels [this] chans)
      (chunks [this sample-rate]
        (let [bits-per-sample  16
              bytes-per-sample (-> bits-per-sample (/ 8) long)
              in               (AudioSystem/getAudioInputStream file)
              decoded          (if (= AudioFormat$Encoding/PCM_SIGNED file-encoding)
                                 in
                                 (AudioSystem/getAudioInputStream
                                  (AudioFormat. AudioFormat$Encoding/PCM_SIGNED
                                                file-sample-rate
                                                bits-per-sample
                                                chans
                                                (* bytes-per-sample chans)
                                                file-sample-rate
                                                true)
                                  ^AudioInputStream in))
              resampled        (if (= sample-rate file-sample-rate)
                                 decoded
                                 (AudioSystem/getAudioInputStream
                                  (AudioFormat. AudioFormat$Encoding/PCM_SIGNED
                                                sample-rate
                                                bits-per-sample
                                                chans
                                                (* bytes-per-sample chans)
                                                sample-rate
                                                true)
                                  ^AudioInputStream decoded))]
          (sample-chunks resampled chans bytes-per-sample (* dur sample-rate)))))))

;;; Sound manipulation

(defn peak
  "Returns the maximum absolute amplitude of `s` when sampled at
  `sample-rate`. If provided, will return immediately on finding a
  value above `limit`."
  ([s sample-rate] (peak s sample-rate Double/MAX_VALUE))
  ([s sample-rate limit]
     (loop [c             (chunks s sample-rate)
            max-amplitude Double/MIN_VALUE]
       ;; It's weird that I have to do the destructuring in a let
       ;; rather than above where we bind c, but if I don't, this loop
       ;; retains head and runs out of memory for longer sequences.
       (let [[head-chunk & more-chunks] c]
        (cond
         ;; Short-circuit if we hit `limit`
         (< limit max-amplitude) max-amplitude

         ;; Sequence has been consumed
         (not (seq head-chunk)) max-amplitude

         :else
         (recur more-chunks
                (double (apply max
                               (map (fn [^doubles arr]
                                      (dbl/areduce [e arr]
                                                   m max-amplitude
                                                   (max m (Math/abs e))))
                                    head-chunk)))))))))

;;; Sound operations

;; An operation takes one or more sounds and returns a new sound

(defn append
  "Concatenates two sounds together"
  [s1 s2]
  {:pre [(= (channels s1) (channels s2))]}
  (let [d1 (duration s1)
        d2 (duration s2)]
    (reify SampledSound
      (duration [this] (+ d1 d2))
      (channels [this] (channels s1))
      (chunks [this sample-rate]
        (concat (chunks s1 sample-rate)
                (chunks s2 sample-rate))))))

(defn- dbl-asub
  "Returns the part of `arr` whose indices fall in [`start` `end`)."
  [arr ^long start ^long end]
  (dbl/amake [i (p/- end start)]
             (dbl/aget arr (p/+ i start))))

(defn- drop-samples
  "Drops `n` samples from `chunks`."
  [^long n chunks]
  (cond
   (zero? n) chunks

   (< n (dbl/alength (ffirst chunks)))
   (lazy-seq
    (cons (map #(dbl-asub % n (dbl/alength %)) (first chunks))
          (rest chunks)))

   (seq chunks)
   (recur (- n (dbl/alength (ffirst chunks))) (rest chunks))))

(defn- take-samples
  "Returns chunks from `chunks` until `n` samples have been returned."
  [^long n chunks]
  (cond
   (not (seq chunks)) nil

   (not (pos? n)) nil

   (< n (dbl/alength (ffirst chunks)))
   [(map #(dbl-asub % 0 n) (first chunks))]

   :else
   (lazy-seq
    (cons (first chunks)
          (take-samples (- n (dbl/alength (ffirst chunks)))
                        (rest chunks))))))

(defn multiplex
  "Takes a single-channel sound `s` and returns an `n`-channel sound
  whose channels are all identical to channel 0 of `s`."
  [s ^long n]
  {:pre [(== 1 (channels s))]}
  (if (== 1 n)
    s
    (reify SampledSound
      (duration [this] (duration s))
      (channels [this] n)
      (chunks [this sample-rate]
        (map (fn [[arr]] (repeat n arr))
             (chunks s sample-rate))))))

(defn trim
  "Truncates `s` to the region between `start` and `end`. If `end` is
  beyond the end of the sound, just trim to the end."
  [s ^double start ^double end]
  {:pre [(<= 0 start (duration s))
         (<= start end)]}
  (let [end* (min (duration s) end)
        dur  (- end* start)]
    (reify SampledSound
      (duration [this] dur)
      (channels [this] (channels s))
      (chunks [this sample-rate]
        (let [samples-to-drop (-> start (* sample-rate) long)
              samples-to-take (-> dur (* sample-rate) long)]
          (->> (chunks s sample-rate)
               (drop-samples samples-to-drop)
               (take-samples samples-to-take)))))))

(defn- combine-chunks
  "Returns a sequence of chunks whose contents are corresponding
  elements of chunks1 and chunks2 combined by calling `f` on them. `f`
  should be a function of the number of samples in the chunk to be
  produced, the first chunk, the offset in that chunk at which to
  start, the second chunk, and the offset in that chunk at which to
  start. If no offsets are provided, defaults to zero."
  ([f chunks1 chunks2] (combine-chunks f chunks1 0 chunks2 0))
  ([f chunks1 offset1 chunks2 offset2]
     (let [[head1 & more1] chunks1
           [head2 & more2] chunks2]
       (cond
        (and head1 head2)
        (let [len1       (dbl/alength (first head1))
              len2       (dbl/alength (first head2))
              samples    (min (- len1 offset1) (- len2 offset2))
              consumed1? (= len1 (+ samples offset1))
              consumed2? (= len2 (+ samples offset2))]
          (lazy-seq
           (cons
            (f samples head1 offset1 head2 offset2)
            (combine-chunks f
                            (if consumed1? more1 chunks1)
                            (if consumed1? 0 (+ offset1 samples))
                            (if consumed2? more2 chunks2)
                            (if consumed2? 0 (+ offset2 samples))))))

        (and head1 (not head2))
        (cons (map #(dbl-asub % offset1 (dbl/alength %)) head1)
              more1)

        (and (not head1) head2)
        (cons (map #(dbl-asub % offset2 (dbl/alength %)) head2)
              more2)))))

(defn mix
  "Mixes sounds `s1` and `s2` together."
  [s1 s2]
  {:pre [(= (channels s1) (channels s2))]}
  (let [d1 (duration s1)
        d2 (duration s2)]
    (reify SampledSound
      (duration [this] (max d1 d2))
      (channels [this] (channels s1))
      (chunks [this sample-rate]
        (let [s1* (if (< d1 d2)
                    (append s1 (silence (- d2 d1) (channels s1)))
                    s1)
              s2* (if (<= d1 d2)
                    s2
                    (append s2 (silence (- d1 d2) (channels s2))))]
          (combine-chunks (fn mix-fn [samples head1 offset1 head2 offset2]
                            (let [o1 (long offset1)
                                  o2 (long offset2)]
                              (map #(dbl/amake [i samples]
                                               (p/+ (dbl/aget %1 (p/+ i o1))
                                                    (dbl/aget %2 (p/+ i o2))))
                                   head1
                                   head2)))
                          (chunks s1* sample-rate)
                          (chunks s2* sample-rate)))))))

(defn gain
  "Changes the amplitude of `s` by `g`."
  [s ^double g]
  (reify SampledSound
    (duration [this] (duration s))
    (channels [this] (channels s))
    (chunks [this sample-rate]
      (map (fn [chunk]
             (map (fn [channel-chunk]
                    (dbl/amap [x channel-chunk]
                              (p/* x g)))
                  chunk))
           (chunks s sample-rate)))))


(defn envelope
  "Multiplies the amplitudes of `s1` and `s2`, trimming the sound to
  the shorter of the two."
  [s1 s2]
  {:pre [(= (channels s1) (channels s2))]}
  (let [dur (min (duration s1) (duration s2))]
    (reify SampledSound
      (duration [this] dur)
      (channels [this] (channels s1))
      (chunks [this sample-rate]
        (let [s1* (if (< dur (duration s1))
                    (trim s1 0 dur)
                    s1)
              s2* (if (< dur (duration s2))
                    (trim s2 0 dur)
                    s2)]
          (combine-chunks (fn envelope-fn [samples head1 offset1 head2 offset2]
                            (map #(dbl/amake [i samples]
                                             (p/* (dbl/aget %1 (p/+ i (long offset1)))
                                                  (dbl/aget %2 (p/+ i (long offset2)))))
                                 head1
                                 head2))
                          (chunks s1* sample-rate)
                          (chunks s2* sample-rate)))))))

(defn fade-in
  "Fades `s` linearly from zero at the beginning to full volume at
  `duration`."
  [s ^double fade-duration]
  (let [chans (channels s)]
    (-> (linear fade-duration chans 0 1.0)
        (append (constant (- (duration s) fade-duration) chans 1.0))
        (envelope s))))

(defn fade-out
  "Fades the s to zero for the last `duration`."
  [s ^double fade-duration]
  (let [chans (channels s)]
    (-> (constant (- (duration s) fade-duration) chans 1.0)
        (append (linear fade-duration chans 1.0 0))
        (envelope s))))

(defn segmented-linear
  "Produces a sound with `chans` channels whose amplitudes change
  linearly as described by `spec`. Spec is a sequence of interleaved
  amplitudes and durations. For example the spec
  1.0 30
  0   10
  0   0.5
  1.0
  (written that way on purpose - durations and amplitudes are in columns)
  would produce a sound whose amplitude starts at 1.0, linearly
  changes to 0.0 at time 30, stays at 0 for 10 seconds, then ramps up
  to its final value of 1.0 over 0.5 seconds"
  [chans & spec]
  {:pre [(and (odd? (count spec))
              (< 3 (count spec)))]}
  (->> spec
       (partition 3 2)
       (map (fn [[start duration end]] (linear duration chans start end)))
       (reduce append)))

(defn timeshift
  "Inserts `dur` seconds of silence at the beginning of `s`"
  [s ^double dur]
  (append (silence dur (channels s)) s))

(defn ->stereo
  "Creates a stereo sound. If given one single-channel sound,
  duplicates channel zero on two channels. If given a single stereo
  sound, returns it. If given two single-channel sounds, returns a
  sound with the first sound on channel 0 and the second sound on
  channel 1."
  ([s]
     (case (long (channels s))
       2 s
       1 (reify SampledSound
           (duration [this] (duration s))
           (channels [this] 2)
           (chunks [this sample-rate]
             (map (fn [[l] [r]] (vector l r))
                  (chunks s sample-rate) (chunks s sample-rate))))
       (throw (ex-info "Can't steroize sound with other than one or two channels"
                       {:reason :cant-stereoize-channels
                        :s      s}))))
  ([l r]
     (when-not (= 1 (channels l) (channels r))
       (throw (ex-info "Can't steroize two sounds unless they are both single-channel"
                       {:reason :cant-stereoize-channels
                        :l-channels (channels l)
                        :r-channels (channels r)})))
     (reify SampledSound
       (duration [this] (min (duration l) (duration r)))
       (channels [this] 2)
       (chunks [this sample-rate]
         (combine-chunks (fn stereo-fn [samples [head1] offset1 [head2] offset2]
                           [(dbl-asub head1 offset1 (+ offset1 samples))
                            (dbl-asub head2 offset2 (+ offset2 samples))])
                         (chunks l sample-rate)
                         (chunks r sample-rate))))))

(defn pan
  "Takes a two-channel sound and mixes the channels together by
  `amount`, a float on the range [0.0, 1.0]. The ususal use is to take
  a sound with separate left and right channels and combine them so
  each appears closer to stereo center. An `amount` of 0.0 would leave
  both channels unchanged, 0.5 would result in both channels being the
  same (i.e. appearing to be mixed to stereo center), and 1.0 would
  switch the channels."
  [s ^double amount]
  {:pre [(= 2 (channels s))]}
  (let [amount-complement (- 1.0 amount)]
    (reify SampledSound
      (duration [this] (duration s))
      (channels [this] 2)
      (chunks [this sample-rate]
        (map (fn [[arr1 arr2]]
               [(dbl/amap [e1 arr1
                           e2 arr2]
                           (p/+ (p/* e1 amount-complement)
                                (p/* e2 amount)))
                (dbl/amap [e1 arr1
                           e2 arr2]
                           (p/+ (p/* e1 amount)
                                (p/* e2 amount-complement)))])
             (chunks s sample-rate))))))

;; TODO: maybe make these into functions that return operations rather
;; than sounds.

;;; Playback

;; TODO: This is identical to the one in sound.clj. Merge them if we
;; don't get rid of sound.clj
(defmacro shortify
  "Takes a floating-point number f in the range [-1.0, 1.0] and scales
  it to the range of a 16-bit integer. Clamps any overflows."
  [f]
  (let [max-short-as-double (double Short/MAX_VALUE)]
    `(let [clamped# (-> ~f (min 1.0) (max -1.0))]
       (short (p/* ~max-short-as-double clamped#)))))

(defn- sample-provider
  [s ^LinkedBlockingQueue q ^long sample-rate]
  (let [chans          (channels s)]
    (future
      (loop [[head-chunk & more] (chunks s sample-rate)]
        (if-not head-chunk
          (.put q ::eof)
          (let [chunk-len  (dbl/alength (first head-chunk))
                byte-count (p/* chans 2 chunk-len)
                bb         (ByteBuffer/allocate byte-count)
                buffer     (byte-array byte-count)]
            (dotimes [n chunk-len]
              ;; TODO: Find a more efficient way to do this
              (doseq [arr head-chunk]
                (.putShort bb (shortify (dbl/aget arr n)))))
            (.position bb 0)
            (.get bb buffer)
            ;; Bail if the player gets too far behind
            (when (.offer q buffer 2 java.util.concurrent.TimeUnit/SECONDS)
              (recur more))))))))

;; TODO: This is identical to the one in sound.clj. Merge them if we
;; don't get rid of sound.clj
(defn play
  "Plays `s` asynchronously. Returns a value that can be passed to `stop`."
  [s]
  (let [sample-rate 44100
        chans       (channels s)
        sdl         (AudioSystem/getSourceDataLine (AudioFormat. sample-rate
                                                                 16
                                                                 chans
                                                                 true
                                                                 true))
        stopped     (atom false)
        q           (LinkedBlockingQueue. 10)
        provider    (sample-provider s q sample-rate)]
    {:player   (future (.open sdl)
                       (loop [buf ^bytes (.take q)]
                         (when-not (or @stopped (= buf ::eof))
                           (.write sdl buf 0 (alength buf))
                           (.start sdl) ;; Doesn't hurt to do it more than once
                           (recur (.take q)))))
     :stop     (fn []
                 (reset! stopped true)
                 (future-cancel provider)
                 (.stop sdl))
     :q        q
     :provider provider
     :sdl      sdl}))

(defn stop
  "Stops playing the sound represented by `player` (returned from `play`)."
  [player]
  ((:stop player)))

;;; Serialization

(defn- sampled-input-stream
  "Returns an implementation of `InputStream` over the data in `s`."
  [s sample-rate]
  (let [;; Empty chunks, while valid, will screw us over by causing us
        ;; to return zero from read
        useful-chunks    (remove (fn [[arr]] (== 0 (dbl/alength arr)))
                                 (chunks s sample-rate))
        chunks-remaining (atom useful-chunks)
        offset           (atom 0)
        chans            (channels s)]
    (proxy [java.io.InputStream] []
      (available [] (-> (duration s) (* sample-rate) long (* (channels s) 2)))
      (close [])
      (mark [readLimit] (throw (UnsupportedOperationException.)))
      (markSupported [] false)
      (read ^int
        ([] (throw (ex-info "Not implemented" {:reason :not-implemented})))
        ([^bytes buf] (.read ^java.io.InputStream this buf 0 (alength buf)))
        ([^bytes buf off len]
           (if-not @chunks-remaining
             -1
             (let [[head-chunk & more-chunks] @chunks-remaining
                   chunk-frames               (dbl/alength (first head-chunk))
                   start-frame                (long @offset)
                   chunk-frames-remaining     (- chunk-frames start-frame)
                   chunk-bytes-remaining      (* chunk-frames-remaining 2 chans)
                   frames-requested           (/ len 2 chans)
                   read-remainder?            (<= chunk-frames-remaining frames-requested)
                   frames-to-read             (if read-remainder?
                                                chunk-frames-remaining
                                                frames-requested)
                   bytes-to-read              (if read-remainder? chunk-bytes-remaining len)
                   bb                         (ByteBuffer/allocate bytes-to-read)]
               (when (zero? bytes-to-read)
                 (throw (ex-info "Zero bytes requested"
                                 {:reason                 :no-bytes-requested
                                  :off                    off
                                  :len                    len
                                  :start-frame            start-frame
                                  :chunk-frames           chunk-frames
                                  :chunk-frames-remaining chunk-frames-remaining
                                  :frames-requested       frames-requested
                                  :read-remainder?        read-remainder?
                                  :frames-to-read         frames-to-read
                                  :bytes-to-read          bytes-to-read})))
               (dotimes [n frames-to-read]
                 ;; TODO: Find a more efficient way to do this
                 (doseq [arr head-chunk]
                   (.putShort bb (shortify (dbl/aget arr (p/+ start-frame n))))))
               (.position bb 0)
               (.get bb buf off bytes-to-read)
               (if read-remainder?
                 (do (reset! chunks-remaining more-chunks)
                     (reset! offset 0))
                 (swap! offset + frames-to-read))
               bytes-to-read))))
      (reset [] (throw (UnsupportedOperationException.)))
      (skip [n] (throw (ex-info "Not implemented" {:reason :not-implemented}))))))

(defn save
  "Save sound `s` to `path` as a 16-bit WAV at `sample-rate`."
  [s path sample-rate]
  (AudioSystem/write (AudioInputStream.
                      (sampled-input-stream s sample-rate)
                      (AudioFormat. sample-rate 16 (channels s) true true)
                      (-> s duration (* sample-rate) long))
                     AudioFileFormat$Type/WAVE
                     (io/file path)))


;;; Visualization

(defn- every-nth
  "Given a sequence of double arrays, return a collection holding
  every `n`th sample."
  [arrays period]
  (loop [remaining arrays
         n         period
         acc       []]
    (let [[head & more] remaining
          head-length (when head (dbl/alength head))]
      (if head
        (if (< n head-length)
          (recur remaining (+ n period) (conj acc (dbl/aget head n)))
          (recur more (- n head-length) acc))
        acc))))

;; TODO: There's definitely a protocol to be extracted here, assuming
;; the continuous-time stuff lives on.
(defn visualize
  "Visualizes channel `c` (default 0) of `s` by plotting it on a graph."
  ([s] (visualize s 0))
  ([s c]
     (let [num-data-points 4000
           ;; For short sounds, we need to sample at a higher rate, or
           ;; the graph won't be smooth enough. For longer sounds, we
           ;; can get away with a lower rate.
           sample-rate (if (< (/ num-data-points 16000) (duration s))
                         16000
                         44100)
           channel-chunks (map #(nth % c) (chunks s sample-rate))
           num-samples (-> s duration (* sample-rate) long)
           sample-period (max 1 (-> num-samples (/ num-data-points) long))
           indexes (range 0 num-samples sample-period)
           times (map #(/ (double %) sample-rate) indexes)
           samples (every-nth channel-chunks sample-period)]

       (incanter/view
        (charts/set-stroke-color
         (charts/xy-plot
          times
          samples)
         java.awt.Color/black))

       )))
