# OpenMP Pixelmatch
An OpenMP C port of pixelmatch, the smallest, simplest and fastest JavaScript pixel-level image comparison library.

### Time Trials

```bash
mkdir build
cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DENABLE_OPENMP=OFF .. 
ninja
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DENABLE_OPENMP=ON  ..
ninja

./benchmark1-non-openmp-release ../assets/image1.jpg ../assets/image2.jpg
# Differences: 7573862
# Time taken for pixelmatch: 0.276000 seconds

./benchmark1-openmp-release     ../assets/image1.jpg ../assets/image2.jpg
# Differences: 7573862
# Time taken for pixelmatch: 0.058000 seconds
# 4.76 speedup!

./benchmark2-non-openmp-release
# Time taken for pixelmatch: 33.025000 seconds
# Total time: 62.843000 seconds

./benchmark2-openmp-release
# Time taken for pixelmatch: 6.692000 seconds
# Total time: 51.080000 seconds
```


### Links
- [pixelmatch](https://github.com/mapbox/pixelmatch)
- [pixelmatch-cpp](https://github.com/mapbox/pixelmatch-cpp)
