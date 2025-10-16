#include "random.hpp"

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <fstream>

auto pick_jobs(std::vector<int>& jobs, int min, int max)-> std::vector<int> {
  auto picked = std::vector<int>{};
  auto num_picked = std::min(prng::get_int(min, max), static_cast<int>(jobs.size()));

  for (auto i = 0; i < num_picked; ++i) {
    picked.push_back(jobs.front());
    jobs.erase(jobs.begin());
  }

  return picked;
}

auto main() -> int {
  auto jobs = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
  std::shuffle(jobs.begin(), jobs.end(), prng::mt);

  auto A = std::array<double, 20 * 20>{}; // delay matrix

  auto previous_level = pick_jobs(jobs, 2, 8);

  while (!jobs.empty()) {
    auto current_level = pick_jobs(jobs, 2, 8);

    for (auto i : previous_level) {
      auto precedes = prng::get_int(0, 1) == 1;
      if (!precedes) continue;

      auto idx = prng::get_int(0u, static_cast<unsigned>(current_level.size()) - 1);
      auto j = current_level[idx];
      auto delay = prng::get_real(20.0, 40.0);
      A[static_cast<unsigned>(i) * 20u + static_cast<unsigned>(j)] = delay;

      std::cout << "Job " << i << " precedes job " << j << " with delay " << delay << "\n";
    }

    previous_level = current_level;
  }

  auto S = std::array<double, 20 * 20>{}; // setup matrix
  for (auto i = 0u; i < 20u; ++i) {
    for (auto j = 0u; j < 20u; ++j) {
      if (i == j) continue;
      S[i * 20u + j] = prng::get_real(5.0, 10.0);
    }
  }

  auto P = std::array<double, 20>{}; // processing times
  for (auto i = 0u; i < 20u; ++i) {
    P[i] = prng::get_real(10.0, 20.0);
  }

  // saving everything to file
  auto file = std::ofstream{"instance.txt"};
  file << "20\n";

  // processing times
  for (auto i = 0u; i < 20u; ++i) {
    file << P[i] << "\n";
  }

  for (auto i = 0u; i < 20u; ++i) {
    for (auto j = 0u; j < 20u; ++j) {
      file << S[i * 20u + j] << (j == 19u ? "\n" : " ");
    }
  }

  for (auto i = 0u; i < 20u; ++i) {
    for (auto j = 0u; j < 20u; ++j) {
      file << A[i * 20u + j] << (j == 19u ? "\n" : " ");
    }
  }

  return 0;
}
