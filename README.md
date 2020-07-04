AdvSketch
============

Introduction
--------
AdvSketch is an algorithm that can find frequent items with high accuracy and high throughput using small memory.
We show that its error is often much smaller than the state-of-the-art -- Unbiased SpaceSaving, and provide the accuracy guarantee.
We conduct extensive experiments on two real datasets and one synthetic dataset. 
Our experimental results show that compared with the state-of-the-art, USS, our algorithm improves the insertion throughput 5 times and the accuracy 200 times.


Repository structure
--------------------
*  `alg/`: the implementation of algorithms
*  `alg/common`: the hash function and data structure used by many algorithms
*  `alg/AdvSketch.h`: the implementation of our AdvSketch
*  `benchmark.h`: C++ header of some benchmarks about accuracy and throughput

Requirements
-------
- cmake
- g++

We conducted all the experiments on a machine with two 6-core processors (12 threads, Intel Xeon CPU E5-2620 @2 GHz) and 64 GB DRAM memory. 
Each processor has three levels of cache memory: one 32KB L1 data caches and one 32KB L1 instruction cache for each core, one 256KB L2 cache for each core, and one 15MB L3 cache shared by all cores.

How to run
-------

```bash
$ cmake .
$ make
$ ./AdvSketch your-dataset
```