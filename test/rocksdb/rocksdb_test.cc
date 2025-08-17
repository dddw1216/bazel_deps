#include <iostream>
#include <string>

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"

int main() {
    rocksdb::DB* db;
    rocksdb::Options options;
    options.create_if_missing = true;
    
    // 打开数据库
    rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/testdb", &db);
    if (!status.ok()) {
        std::cerr << "Failed to open database: " << status.ToString() << std::endl;
        return 1;
    }
    
    // 写入数据
    std::string key = "hello";
    std::string value = "world";
    status = db->Put(rocksdb::WriteOptions(), key, value);
    if (!status.ok()) {
        std::cerr << "Failed to write: " << status.ToString() << std::endl;
        delete db;
        return 1;
    }
    
    // 读取数据
    std::string result;
    status = db->Get(rocksdb::ReadOptions(), key, &result);
    if (status.ok()) {
        std::cout << "Successfully read: " << key << " = " << result << std::endl;
    } else {
        std::cerr << "Failed to read: " << status.ToString() << std::endl;
    }
    
    delete db;
    return 0;
}
