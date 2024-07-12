#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <queue>
#include <functional>
#include <stack>

template <typename K>
class Edge
{
    K node;
    double weight;

public:
    Edge(K node, double weight = 0) : node(node), weight(weight)
    {
    }

    K getNode() const
    {
        return node;
    }

    double getWeight() const
    {
        return weight;
    }

    bool operator==(const Edge<K> &other) const
    {
        return other.node == node;
    }
};

namespace std
{
    // template <>
    // struct hash<char>
    // {
    //     std::size_t operator()(const char &val) const
    //     {
    //         return (int)val;
    //     }
    // };

    template <typename K>
    struct hash<Edge<K>>
    {
        std::size_t operator()(const Edge<K> &edge) const
        {
            return hash<K>{}(edge.getNode());
        }
    };
}

template <typename K>
class Graph
{
    using EdgeList = std::unordered_set<Edge<K>>;
    using AdjacencyList = std::unordered_map<K, EdgeList>;
    AdjacencyList adjacencyList;

public:
    void add(K node)
    {
        typename AdjacencyList::iterator pointer = adjacencyList.find(node);
        if (pointer != adjacencyList.end())
            return;
        adjacencyList[node] = std::unordered_set<Edge<K>>();
    }

    void addEdge(K a, K b, double weight)
    {
        add(a);
        add(b);

        EdgeList &aEdges = adjacencyList.at(a);

        aEdges.erase(Edge(b, 0));
        aEdges.insert(Edge(b, weight));

        size_t aSize = aEdges.size();

        EdgeList &bEdges = adjacencyList.at(b);
        bEdges.erase(Edge(a, 0));
        bEdges.erase(Edge(a, weight));
    }

    bool contains(K node)
    {
        return adjacencyList.find(node) != adjacencyList.end();
    }

    void breadFirstTraverse(K startNode, std::function<void(K)> visit)
    {
        if (!contains(startNode))
            return;
        std::queue<K> nodeQueue;
        std::unordered_set<K> visited;

        nodeQueue.push(startNode);

        while (!nodeQueue.empty())
        {
            K currentNode = nodeQueue.front();
            nodeQueue.pop();

            // Skip node if it has already been visited
            if (visited.find(currentNode) != visited.end())
                continue;

            visit(currentNode);

            visited.insert(currentNode);

            // Queue a visit for all neighbours of currentNode
            EdgeList &neighbours = adjacencyList.at(currentNode);
            for (Edge<K> edge : neighbours)
            {
                nodeQueue.push(edge.getNode());
            }
        }
    }

    void depthFirstTraverse(K startNode, std::function<void(K)> visit)
    {
        if (!contains(startNode))
            return;
        std::stack<K> nodeStack;
        std::unordered_set<K> visited;

        nodeStack.push(startNode);

        while (!nodeStack.empty())
        {
            K currentNode = nodeStack.top();
            nodeStack.pop();

            // Skip node if it has already been visited
            if (visited.find(currentNode) != visited.end())
                continue;

            visit(currentNode);
            visited.insert(currentNode);

            EdgeList neighbours = adjacencyList.at(currentNode);
            for (Edge<K> edge : neighbours)
            {
                nodeStack.push(edge.getNode());
            }
        }
    }
};