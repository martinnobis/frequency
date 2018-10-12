# Frequency
Add type safety to your frequency calculations.

## Installing

Single header file, simply download and include it:
```c++
#include "frequency.h"
```

## Usage
```cpp
frequency<Hz> f1 {5.5};              // 5.5 Hz
frequency<KHz> f2 {5.5};             // 5.5 KHz

auto f3 = f1 + f2;                   // 5505.5 Hz
```

## Compatability
Requires C++11.

## Running the tests
Ensure that you have at least cmake 3.1.0 installed.
```
mkdir build
cd build
cmake ../
make
./frequency
```

## License
MIT-licensed. See LICENSE.

