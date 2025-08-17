// Copyright (c) 2025 ddu_db.
#include <iostream>
#include <spdlog/spdlog.h>

int main() {
    std::cout << "Testing spdlog from bazel_deps..." << std::endl;
    
    // 测试基本日志功能
    spdlog::info("Hello from spdlog!");
    spdlog::warn("This is a warning message");
    spdlog::error("This is an error message");
    
    // 测试格式化日志
    spdlog::info("Testing formatted log: {}", 42);
    spdlog::error("Error occurred in function {} at line {}", __FUNCTION__, __LINE__);
    
    std::cout << "spdlog test completed successfully!" << std::endl;
    return 0;
}
