#include <map>
#include <iostream>
#include <sstream>
#include <fstream>

int main(int argc, char **argv)
{
  std::ifstream ifs(argv[1]);
  std::multimap<std::string, std::string> m;
  std::string line;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    std::string s, t;
    iss >> t;

    while (iss >> s) {
      m.insert(std::make_pair(s, t));
    }
  }
  std::string s = m.begin()->first;
  for (auto it = m.find(s); it != m.end();) {
    s = it->second;
    it = m.find(s);
  }
  std::cout << s << std::endl;
}