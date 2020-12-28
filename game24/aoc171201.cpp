//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
//  Sample output
//
// DFS categorized directed graph
// tree: 0 --> 2
// tree: 2 --> 1
// back: 1 --> 1
// tree: 1 --> 3
// back: 3 --> 1
// tree: 3 --> 4
// back: 4 --> 0
// back: 4 --> 1
// forward or cross: 2 --> 3

// BFS categorized directed graph
// tree: 0 --> 2
// tree: 2 --> 1
// tree: 2 --> 3
// cycle: 1 --> 1
// cycle: 1 --> 3
// cycle: 3 --> 1
// tree: 3 --> 4
// cycle: 4 --> 0
// cycle: 4 --> 1

#include <boost/config.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <string>
#include <range/v3/algorithm/transform.hpp>

#include <boost/graph/visitors.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/depth_first_search.hpp>


template<class Tag>
struct edge_printer : public boost::base_visitor<edge_printer<Tag>>
{
  int *n = 0;
  typedef Tag event_filter;
  edge_printer(std::string edge_t) : m_edge_type(edge_t) {}
  template<class Edge, class Graph>
  void operator()(Edge e, Graph &G)
  {
    //std::cout << m_edge_type << ": " << source(e, G) << " --> " << target(e, G) << std::endl;
    if (n) {
      *n += 1;
    }
  }
  int Count() const
  {
    return *n;
  }

  std::string m_edge_type;
};
template<class Tag>
edge_printer<Tag> print_edge(std::string type, Tag)
{
  return edge_printer<Tag>(type);
}

typedef boost::adjacency_list<> Graph;
typedef std::pair<int, int> E;
struct Bags
{
  int test(const Graph &G, int n) const
  {

    using std::endl;
    using std::cout;
    using namespace boost;

    //cout << endl
    //     << "BFS categorized directed graph" << endl;
    //boost::breadth_first_search(G, vertex(0, G), visitor(make_bfs_visitor(std::make_pair(print_edge("tree", on_tree_edge()), print_edge("cycle", on_non_tree_edge())))));
    cout << endl
         << "BFS jiayuehua categorized directed graph" << endl;
    auto ep = print_edge("tree", on_tree_edge());
    auto epb = print_edge("tree", on_non_tree_edge());
    int num = 0;
    ep.n = &num;
    boost::breadth_first_search(G, vertex(n, G), visitor(make_bfs_visitor(std::make_pair(ep, print_edge("cycle", on_non_tree_edge())))));
    cout << endl;
    return num + 1;
  }
  std::vector<E> edges_;
  int shinygoldid_ = 0;
  Graph G_;

public:
  int shinygoldidNum() const
  {
    return test(G_, shinygoldid_);
  }
  friend std::istream &operator>>(std::istream &is, Bags &bags)
  {
    std::set<int> bagid_;
    std::multimap<int, int> edges_;
    std::string line;
    int src;
    int dst;


    for (int i = 0, n = 0; std::getline(is, line); ++n) {
      std::istringstream iss(line);
      iss >> src;
      bagid_.insert(src);

      for (; iss >> dst;) {
        bagid_.insert(dst);
        edges_.insert(std::pair{ src, dst });
      }
    }

    Graph G(edges_.begin(), edges_.end(), bagid_.size());
    bags.G_ = G;

    return is;
  }
};
int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string color, attr;
    Bags bags;
    ifs >> bags;
    std::cout << bags.shinygoldidNum() << std::endl;
  }
}
