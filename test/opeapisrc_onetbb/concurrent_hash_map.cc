#include <cassert>
#include <iostream>

#include <string>

#include "include/oneapi/tbb/concurrent_hash_map.h"

int main(int argc, char** argv) {
  tbb::concurrent_hash_map<std::string, std::string> cmap;
  assert(cmap.insert({"k1", "v1"}));
  assert(!cmap.insert({"k1", "v1"}));
  assert(cmap.insert({"k2", "v2"}));
  std::cout << "LINE:" << __LINE__ << " " << "log_1" << std::endl;

  tbb::concurrent_hash_map<std::string, std::string>::accessor ac1;
  assert(cmap.find(ac1, "k1"));
  std::cout << "LINE:" << __LINE__ << " " << "log_2" << std::endl;
  ac1.~accessor();

  bool erase_ret = cmap.erase("k1");
  std::cout << "LINE:" << __LINE__ << " " << "erase_ret=" << erase_ret << std::endl;
  // std::cout << "LINE:" << __LINE__ << " " << "k1=" << ac1->second << std::endl;
  // ac1->second = "v1.1";

  tbb::concurrent_hash_map<std::string, std::string>::accessor ac2;
  bool res = cmap.find(ac2, "k1");
  std::cout << "LINE:" << __LINE__ << " " << "res=" << res << std::endl;

  return 0;
}