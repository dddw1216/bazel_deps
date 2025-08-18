#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cassert>

extern "C" {
#include "lz4.h"
#include "lz4hc.h"
}

void test_basic_compression() {
    std::cout << "=== Testing Basic LZ4 Compression ===" << std::endl;
    
    // 测试数据
    std::string original_data = "Hello, this is a test string for LZ4 compression. "
                               "It contains repeated patterns that should compress well. "
                               "LZ4 is a very fast compression algorithm that provides "
                               "good compression ratios for many types of data.";
    
    int original_size = original_data.size();
    int max_compressed_size = LZ4_compressBound(original_size);
    
    std::vector<char> compressed_data(max_compressed_size);
    
    // 压缩
    int compressed_size = LZ4_compress_default(
        original_data.c_str(), 
        compressed_data.data(), 
        original_size, 
        max_compressed_size
    );
    
    if (compressed_size < 0) {
        std::cerr << "Compression failed!" << std::endl;
        return;
    }
    
    std::cout << "Original size: " << original_size << " bytes" << std::endl;
    std::cout << "Compressed size: " << compressed_size << " bytes" << std::endl;
    std::cout << "Compression ratio: " << (float)compressed_size / original_size * 100 << "%" << std::endl;
    
    // 解压缩
    std::vector<char> decompressed_data(original_size);
    int decompressed_size = LZ4_decompress_safe(
        compressed_data.data(),
        decompressed_data.data(),
        compressed_size,
        original_size
    );
    
    if (decompressed_size < 0) {
        std::cerr << "Decompression failed!" << std::endl;
        return;
    }
    
    std::cout << "Decompressed size: " << decompressed_size << " bytes" << std::endl;
    
    // 验证数据完整性
    if (decompressed_size == original_size && 
        memcmp(original_data.c_str(), decompressed_data.data(), original_size) == 0) {
        std::cout << "✓ Data integrity verified - compression/decompression successful!" << std::endl;
    } else {
        std::cerr << "✗ Data integrity check failed!" << std::endl;
    }
}

void test_hc_compression() {
    std::cout << "\n=== Testing LZ4 HC (High Compression) ===" << std::endl;
    
    // 测试数据
    std::string original_data = "This is a test string for LZ4 HC compression. "
                               "HC mode provides better compression ratios than "
                               "the default mode, but is slower. "
                               "It's useful when compression ratio is more important than speed.";
    
    int original_size = original_data.size();
    int max_compressed_size = LZ4_compressBound(original_size);
    
    std::vector<char> compressed_data(max_compressed_size);
    
    // HC 压缩
    int compressed_size = LZ4_compress_HC(
        original_data.c_str(),
        compressed_data.data(),
        original_size,
        max_compressed_size,
        9  // 最高压缩级别
    );
    
    if (compressed_size < 0) {
        std::cerr << "HC compression failed!" << std::endl;
        return;
    }
    
    std::cout << "Original size: " << original_size << " bytes" << std::endl;
    std::cout << "HC compressed size: " << compressed_size << " bytes" << std::endl;
    std::cout << "Compression ratio: " << (float)compressed_size / original_size * 100 << "%" << std::endl;
    
    // 解压缩
    std::vector<char> decompressed_data(original_size);
    int decompressed_size = LZ4_decompress_safe(
        compressed_data.data(),
        decompressed_data.data(),
        compressed_size,
        original_size
    );
    
    if (decompressed_size < 0) {
        std::cerr << "Decompression failed!" << std::endl;
        return;
    }
    
    std::cout << "Decompressed size: " << decompressed_size << " bytes" << std::endl;
    
    // 验证数据完整性
    if (decompressed_size == original_size && 
        memcmp(original_data.c_str(), decompressed_data.data(), original_size) == 0) {
        std::cout << "✓ HC compression/decompression successful!" << std::endl;
    } else {
        std::cerr << "✗ HC data integrity check failed!" << std::endl;
    }
}

void test_compression_levels() {
    std::cout << "\n=== Testing Different Compression Levels ===" << std::endl;
    
    std::string test_data = "Testing different compression levels with LZ4. "
                           "Level 1 is fastest, level 9 provides best compression. "
                           "This string will be compressed multiple times to compare results.";
    
    int original_size = test_data.size();
    int max_compressed_size = LZ4_compressBound(original_size);
    
    for (int level = 1; level <= 9; level++) {
        std::vector<char> compressed_data(max_compressed_size);
        
        int compressed_size = LZ4_compress_fast(
            test_data.c_str(),
            compressed_data.data(),
            original_size,
            max_compressed_size,
            level
        );
        
        if (compressed_size > 0) {
            float ratio = (float)compressed_size / original_size * 100;
            std::cout << "Level " << level << ": " << compressed_size << " bytes (" 
                     << ratio << "%)" << std::endl;
        }
    }
}

int main() {
    std::cout << "LZ4 Library Test" << std::endl;
    std::cout << "=================" << std::endl;
    
    try {
        test_basic_compression();
        test_hc_compression();
        test_compression_levels();
        
        std::cout << "\n=== All tests completed successfully! ===" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
