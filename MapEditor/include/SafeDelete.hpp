#ifndef SAFE_DELETE
#define SAFE_DELETE(x) {if (x!=nullptr) { delete x; x = nullptr;}}
#endif
#ifndef SAFE_DELETE_ARRAY1D
#define SAFE_DELETE_ARRAY1D(x) {if (x!=nullptr) { delete[] x; x = nullptr;}}
#endif

