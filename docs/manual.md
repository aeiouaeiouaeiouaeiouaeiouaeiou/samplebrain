# Samplebrain Manual
        
## Brain tweaks:

These settings control how the block search works.
    
### fft / mfcc

Choose whether to search using FFT (raw frequency analysis) or MFCC
(Mel-frequency cepstral coefficients) which are higher order paramters
that attempt to model perception of sound. MFCC is usually a bit
better, but it depends on what you are doing, you can blend between
them to use a mix. Setting this to 0% or 100% switches off the other
search option, so is a bit more CPU friendly.
   
### freq & dynamics / freq only

Search using both frequency (pitch) and dynamics (volume changes over
time), or only frequency - which uses normalised blocks. Generally you
want the first option.
   
### fft subsection

When using FFT mode you can select a subrange of the (100) frequency
bins to use for scoring potential blocks, potentially allowing you to
target a specific frequency range. Not terribly useful in practice.
     
### novelty

One thing that tends to happen is that the same block or set of blocks
can be overused if there isn't enough variation in the brain
blocks. Sometimes we want to bias the selection against reuse, so
novelty biases the selection away from similarity - if you turn it all
the way up it will ignore the target completely and just play the
least used ones in some odd semi-random order.
    
### boredom

This increases the speed at which novelty wears off, creating a wider
spread of possible blocks. Not quite clear exactly why this is
different to increasing novelty, but it sounds different.
    
### stickyness

If the error is under this threshold, play the next block in the brain
rather than the closest. This will have the effect of elongating
chunks of brain samples that you hear.
    
### search stretch

Repeats blocks in the target a fixed amount, like a simple timestretch
- in synaptic mode this gives the system repeated attempts to find a
closer match.
        
### algorithm

* basic

Searches all samples in the brain, and uses the closest match.
    
* reversed

Searches all samples in the brain, and uses the least closest
match. In practice this needs work, as it tends to select silent or
very quiet blocks.

* synaptic

As brains get larger, we get more blocks, and they get slower to
search. This mode provides a constant search time over arbitrarily
huge brains. When generating the brains we connect them together into
a network via similarity (via connections called synapses). We keep a
position in the network and only search the nearby blocks - this
assumes that sounds tend to change gradually, or at least more
gradually than the small block lengths.
    
* slide

Similar to synaptic but if we can't find a close enough match (based
on synaptic slide error) we stretch the target, repeating blocks until
we land on a block that is close enough. This mode warps the timing of
the target.

### num synapses

How many connections to check in synaptic or slide mode.
    
### synaptic slide error

The acceptable error to consider a block as "close enought" in slide mode.

## Target sound:

These settings control how the target sound is broken up into blocks.
    
### load target

Load a target sound to try and match
    
### block size

The size of the blocks in samples. This does not need to match the
brain block size, but it probably should.

### block overlap

Percentage overlap in blocks.
     
### window shape

The shape of the window - "dodgy" is actually box.

### (re)generate blocks

Compute the target blocks.
    
### use mic input

Attempts to stream blocks live from the microphone. I think this is
broken at present.

## Mix:

These are settings that happen after the search.
    
### autotune

Attempt to pitch bend the chosen brain block to better match the target.
 
### normalised

Mix in normalised brain blocks - removing all dynamics. Might work
with frequency only search.
        
### brain / target

Mix in the target blocks to the output - for cheating, or testing purposes.
    
### stereo mode

Run everything once for left and again for right speaker.
    
## Brain contents

These settings allow you to build a brain of samples, and switch in
and out specific samples during playback.
        
### all/none

You can select which samples to use without regenerating the
brain. This selects all or none of the samples.
     
### load sound/directory/clear

Load sounds into the brain, either individually or entire directories
in one go.
    
### block size

The size of the blocks in samples. This does not need to match the
target block size, but it probably should.

### block overlap

Percentage overlap in blocks.
     
### window shape

The shape of the window - "dodgy" is actually box.

### (re)generate blocks

Compute the brain blocks.
    
### load brain/save brain

You can save and load brains separately to the targets.
    
## Lower bar

General playback settings
    
### play/pause/record/stop

Start/stop and record
    
### volume

Global volume

### load/save session

Load and save the entire session.

## Net tab

This allows you to control multiple instances of samplebrain over the
network all running their own brains simultaneously. This feature has
not been tested well!
