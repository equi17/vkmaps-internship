#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

std::vector<int> calcDistances(const std::vector<std::vector<int>>& graph, int start_vertex) {
    // С помощью -1 обозначаем еще не посещенные вершины
    std::vector<int> distances(graph.size(), -1);
    distances[start_vertex] = 0;

    // Создаем очередь, куда будем записывать запланированные к посещению вершины
    std::queue<int> q;
    q.push(start_vertex);

    // Обход графа в ширину
    while(!q.empty()) {
        int current_vertex = q.front();
        q.pop();

        // Рассматриваем все смежные вершины
        for(int neighbor: graph[current_vertex]) {
            // Отбрасываем ранее обработанные вершины
            if(distances[neighbor] == -1) {
                q.push(neighbor);
                distances[neighbor] = distances[current_vertex] + 1;
            }
        }
    }

    return distances;
}

int main() {
    std::ifstream input_file("graph.txt");

    int num_vertices, num_edges;
    input_file >> num_vertices >> num_edges;

    // Представление графа в виде списков смежности
    std::vector<std::vector<int>> graph(num_vertices);
    for(int i = 0; i < num_edges; ++i) {
        int u, v;
        input_file >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int start_vertex;
    input_file >> start_vertex;

    std::vector<int> distances = calcDistances(graph, start_vertex);

    for(int distance: distances)
        std::cout << distance << '\n';
}