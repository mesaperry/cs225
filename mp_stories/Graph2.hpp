#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <stack>

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 * 
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 * 
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::list<std::string> path;
  std::queue<std::string> to_visit;
  std::vector<std::string> visited;
  std::unordered_map<std::string, std::string> previous;

  std::string curr;
  to_visit.push(start);
  visited.push_back(start);
  while (!to_visit.empty()) {
    curr = to_visit.front();
    to_visit.pop();
    for (auto edge_: incidentEdges(curr)) {
      std::string neighbor = edge_.get().dest().key();
      if (std::find(visited.begin(), visited.end(), neighbor) == visited.end()) {
        to_visit.push(neighbor);
        visited.push_back(neighbor);
        previous[neighbor] = curr;
      }
    }
    for (auto edge_: incidentEdges(curr)) {
      std::string neighbor = edge_.get().source().key();
      if (std::find(visited.begin(), visited.end(), neighbor) == visited.end()) {
        to_visit.push(neighbor);
        visited.push_back(neighbor);
        previous[neighbor] = curr;
      }
    }
  }

  std::stack<std::string> path_reverse;
  curr = end;
  while (curr != start) {
    path_reverse.push(curr);
    curr = previous.at(curr);
  }
  path_reverse.push(curr);
  while (!path_reverse.empty()) {
    path.push_back(path_reverse.top());
    path_reverse.pop();
  }
  return path;
}

