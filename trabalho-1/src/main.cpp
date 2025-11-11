#include "instance_reader.hpp"

#include <iostream>
#include <fstream>
#include <string>

auto main() -> int {
  auto instance = read_instance("../instances/n10.txt");
  
  print_instance(instance);

  return 0;
}
