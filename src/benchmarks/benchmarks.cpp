#include "benchmarks/benchmark_utils.hpp"
#include "parser/tick.hpp"
#include "datastructures/lockfree_ringbuffer.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    datastructures::LockFreeRingBuffer<parser::Tick, 1 << 16> rb;
    parser::Tick tick{0ULL, 42, 100.25, 10};
    parser::Tick out{};

    std::ofstream csv("../reports/results.csv");
    csv << "benchmark,value\n";

    // --- Latency Benchmark ---
    uint64_t start = benchmarks::now_ns();
    rb.push(tick);
    rb.pop(out);
    uint64_t end = benchmarks::now_ns();
    uint64_t latency = end - start;
    std::cout << "Latency per tick: " << latency << " ns\n";
    csv << "latency," << latency << "\n";

    // --- Throughput Benchmark ---
    const std::size_t iterations = 1'000'000;
    start = benchmarks::now_ns();
    for (std::size_t i = 0; i < iterations; ++i) {
        rb.push(tick);
        rb.pop(out);
    }
    end = benchmarks::now_ns();
    double throughput = iterations / ((end - start) / 1e9);
    std::cout << "Throughput: " << throughput << " ticks/sec\n";
    csv << "throughput," << throughput << "\n";

    // --- Jitter Analysis ---
    std::vector<uint64_t> latencies;
    const std::size_t jitter_iters = 1000;
    for (std::size_t i = 0; i < jitter_iters; ++i) {
        uint64_t js = benchmarks::now_ns();
        rb.push(tick);
        rb.pop(out);
        uint64_t je = benchmarks::now_ns();
        latencies.push_back(je - js);
    }

    uint64_t min = *std::min_element(latencies.begin(), latencies.end());
    uint64_t max = *std::max_element(latencies.begin(), latencies.end());
    double avg = std::accumulate(latencies.begin(), latencies.end(), 0ULL) / (double)jitter_iters;

    std::cout << "Latency jitter analysis:\n";
    std::cout << "Min: " << min << " ns, Max: " << max << " ns, Avg: " << avg << " ns\n";

    csv << "jitter_min," << min << "\n";
    csv << "jitter_max," << max << "\n";
    csv << "jitter_avg," << avg << "\n";

    csv.close();
    return 0;
}