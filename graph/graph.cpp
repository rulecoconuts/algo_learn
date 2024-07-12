#include "graph.h"
#include <stdio.h>

int main()
{
    Graph<char> graph;

    size_t hashA = std::hash<char>{}('a');
    size_t hashB = std::hash<char>{}('b');

    graph.addEdge('a', 'b', 0);
    graph.addEdge('a', 'c', 1);
    graph.addEdge('c', 'e', 1);
    graph.addEdge('b', 'd', 1);
    graph.addEdge('d', 'f', 1);
    graph.addEdge('e', 'f', 1);

    graph.breadFirstTraverse('a', [](char node)
                             { printf("%c -> ", node); });
}