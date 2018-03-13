# Kalman

[![Build Status](https://travis-ci.org/juliangaal/kalman.svg?branch=master)](https://travis-ci.org/juliangaal/kalman)

This repo is based on examples of Kalman2d filtering from [this](https://github.com/balzer82/Kalman) great repo.

#### Currently includes:
* 2d Kalman example: Python prototype, C++
* 6d Kalman for ball trajectory

#### WIP:
* Kalman for PicoFlexx Ball Trajectory (no synthetic data)

#### Build this repo yourself:
* [QuantStack/xtl](https://github.com/QuantStack/xtl)
* [QuantStack/xtensor](https://github.com/QuantStack/xtensor)
* [QuantStack/xtensor-blas](https://github.com/QuantStack/xtensor-blas)
* blas: `brew install openblas` / `sudo apt-get install libblas-dev`
* Lapack `brew install lapack` / `sudo apt-get installliblapack-dev`

Or use provided install script: [linux](https://raw.githubusercontent.com/juliangaal/kalman/master/install/linux.bash) | [mac](https://raw.githubusercontent.com/juliangaal/kalman/master/install/mac.bash)
