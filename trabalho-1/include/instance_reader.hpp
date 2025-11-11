#ifndef INSTANCE_READER_HPP
#define INSTANCE_READER_HPP

#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include <iostream>
#include <sstream>

typedef std::tuple<int, int, int> DelayConstraint;

struct Instance {
  int num_jobs{};
  std::vector<int> processing_times{};
  std::vector<DelayConstraint> delay_constraints{};
  std::vector<std::vector<int>> setup_times{};
};

auto read_instance(const std::string& filepath) -> Instance {
  auto instance = Instance{};
  auto file = std::ifstream{filepath};
  
  if (!file) {
    std::cerr << "Error opening file: " << filepath << std::endl;
    throw std::runtime_error("File not found");
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.starts_with("R=")) {
      instance.num_jobs = std::stoi(line.substr(2));
    }
    else if (line.starts_with("Pi=")) {
      auto ss = std::stringstream{line.substr(4)};
      auto token = std::string{};
      while (std::getline(ss, token, ',')) {
        instance.processing_times.push_back(std::stoi(token));
      }
    }
    else if (line.starts_with("A=")) {
      while (std::getline(file, line)) {
        if (line.starts_with("Sij=")) {
          // Rewind one line for the next section
          file.seekg(-static_cast<int>(line.length()) - 1, std::ios::cur);
          break;
        }
        auto ss = std::stringstream{line};
        auto token = std::string{};
        auto values = std::vector<int>{};
        while (std::getline(ss, token, ',')) {
          values.push_back(std::stoi(token));\
        }
        instance.delay_constraints.emplace_back(values[0], values[1], values[2]);
      }
    }
    else if (line.starts_with("Sij=")) {
      while (std::getline(file, line)) {
        auto ss = std::stringstream{line};
        auto token = std::string{};
        auto row = std::vector<int>{};
        while (std::getline(ss, token, ',')) {
          row.push_back(std::stoi(token));
        }
        instance.setup_times.push_back(row);
      }
    }
  }
  

  return instance;
}

auto print_instance(const Instance& instance) -> void {
  std::cout << "Number of Jobs: " << instance.num_jobs << "\n";
  std::cout << "Processing Times: ";
  for (const auto& pt : instance.processing_times) {
    std::cout << pt << " ";
  }
  std::cout << "\nDelay Constraints:\n";
  for (const auto& dc : instance.delay_constraints) {
    std::cout << "  (" << std::get<0>(dc) << ", " << std::get<1>(dc) << ", " << std::get<2>(dc) << ")\n";
  }
  std::cout << "Setup Times:\n";
  for (const auto& row : instance.setup_times) {
    for (const auto& st : row) {
      std::cout << st << " ";
    }
    std::cout << "\n";
  }
}

#endif // INSTANCE_READER_HPP