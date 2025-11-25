#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

int createBitDirectory() {
  try {
    if (fs::create_directory(".bit")) {
      std::cout << "Created bit repository in current direcotry.\n";
    } else {
      std::cout << "Bit directory already exists.\n";
    }

    fs::create_directories(".bit/objects");
    fs::create_directories(".bit/refs");

    fs::path headFile = fs::current_path() / ".git" / "HEAD";
    std::ofstream outFile(headFile);
    if (!outFile) {
      std::cerr << "Failed to generate HEAD file: " << headFile << std::endl;
      return -1;
    }

    outFile << "ref: refs/heads/main\n";
    outFile.close();

    std::cout << "Initialized HEAD file.\n";
    
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return -1;
  }


  std::cout << "Initialized bit repository";
  
  return 0;
}
