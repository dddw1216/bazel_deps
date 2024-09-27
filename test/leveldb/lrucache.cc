#include <iostream>
#include <string>

#include "include/leveldb/cache.h"

int main(int argc, char** argv) {
  leveldb::Cache* p_cache_1 = leveldb::NewLRUCache(1000);
  std::cout << "TotalCharge=" << p_cache_1->TotalCharge() << std::endl;
  return 0;
}