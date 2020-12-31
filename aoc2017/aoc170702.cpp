#include <set>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
using namespace stlab;
struct Node
{
  std::string key;
  int value;
  int subtreeTotal;
  std::vector<Node> childs;
  int calTotal()
  {
    int total = 0;
    for (auto &c : childs) {
      c.calTotal();
      total += c.subtreeTotal;
    }
    subtreeTotal = value + total;
    return subtreeTotal;
  }
  friend std::ostream &operator<<(std::ostream &os, const Node &n)
  {
    os << "{" << n.key << ":" << n.value << ":" << n.subtreeTotal;
    for (const auto &c : n.childs) {
      os << c;
    }
    os << "}";
    return os;
  }
  auto operator<=>(const std::string &other) const
  {
    return key <=> other;
  }
  auto operator<=>(const Node &other) const
  {
    return key <=> other.key;
  }
};
struct compare
{
  using is_transparent = void;
  bool operator()(const Node &l, const Node &r) const
  {
    return l < r;
  }
  bool operator()(const Node &l, const std::string &r) const
  {
    return l.key < r;
  }
  bool operator()(const std::string &l, const Node &r) const
  {
    return l < r.key;
  }
};
typedef std::map<Node, std::vector<std::string>, compare> NodesType;
class Tree
{
  NodesType allnodes;
  Node root;
  void insert(Node &root)
  {
    auto &values = allnodes[root];
    for (auto k : values) {
      if (auto it = allnodes.find(k); it != allnodes.end()) {
        root.childs.push_back(it->first);
      }
    }
    for (auto i = root.childs.begin(); i != root.childs.end(); ++i) {
      insert(*i);
    }
  }

public:
  Tree(const NodesType &all, Node const &r) : allnodes(all), root(r)
  {
    insert(root);
  }
  friend std::ostream &operator<<(std::ostream &os, const Tree &r)
  {
    os << r.root;
    return os;
  }
  int calTotal()
  {
    return root.calTotal();
  }
  void outputTotal() const
  {
    for (auto const &c : root.childs) {
      std::cout << c.value << ":" << c.subtreeTotal << ",";
    }
  }
};


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string line;
    NodesType allnodes;
    while (std::getline(ifs, line)) {
      std::istringstream iss(line);
      Node node;
      iss >> node.key;
      iss >> node.value;
      std::istream_iterator<std::string> b(iss), e;
      std::vector<std::string> v(b, e);
      allnodes[node] = v;
    }
    Node n{ "hlqnsbe", 77 };
    Tree tree(allnodes, n);
    tree.calTotal();
    tree.outputTotal();
    std::cout << "\n";

    std::cout << tree << std::endl;
  }
}
