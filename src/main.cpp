#include <iostream>
#include <vector>
#include <random>
#include <chrono>

int main() {
    // const int numElements = 125000000;  // 大约占用500MB内存
    // const int numElements = 150000000;  // 大约占用600MB内存
    const int numElements = 135000000;     // 大约占用540MB内存

    // 动态分配内存
    std::vector<int>* data = new std::vector<int>(numElements);

    // 填充数据
    for (int i = 0; i < numElements; ++i) {
        (*data)[i] = i;
    }

    // 创建随机数引擎
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, numElements - 1);

    // 开始计时
    auto startTime = std::chrono::high_resolution_clock::now();

    // 访问和使用数据（乱序访存）
    int sum = 0;
    int accTime = 100000;
    for (int i = 0; i < accTime; ++i) {
        int index = distribution(generator);  // 随机索引
        sum += (*data)[index];
    }

    // 停止计时
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // 打印总和和耗时
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Time: " << duration.count() << " ms" << std::endl;

    // 释放内存
    delete data;

    return 0;
}
