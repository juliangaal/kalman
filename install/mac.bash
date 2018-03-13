#!/bin/bash

INSTALL_PATH=/usr/local/include

brew update && sudo rm /usr/local/include/c++ && brew install lapack liblas openblas
mkdir ~/QuantStack && cd ~/QuantStack
git clone https://github.com/QuantStack/xtl.git
cd xtl && mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH ..
sudo make install
cd ~/QuantStack
git clone https://github.com/QuantStack/xtensor.git
cd xtensor && mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH ..
sudo make install
cd ~/QuantStack
git clone https://github.com/QuantStack/xtensor-blas.git
cd xtensor-blas && mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH ..
sudo make install
cd && rm -rf ~/QuantStack

git clone https://github.com/juliangaal/kalman && cd kalman
mkdir build && cd build
cmake ..
make -j
./Test