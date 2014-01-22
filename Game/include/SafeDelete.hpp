#ifndef SAFE_DELETE
#define SAFE_DELETE(x) {if (x!=nullptr) { delete x; x = nullptr;}}
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) {if (x!=nullptr) { delete[] x; x = nullptr;}}
#endif

