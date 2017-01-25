#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 1000000 + 5;

// Disjoint Set
class Disjoint_set {
public:
    Disjoint_set(int s = 10)
    {
        d = new int[s + 1];
        size = s; 
        for(int i = 0; i < s + 1; i++){
            d[i] = i; // initialize
        } 
    }

    ~Disjoint_set()
    {
        delete [] d;
    }

    int find(int n)
    {
        return (d[n] == n) ? d[n] : d[n] = find(d[n]); // find root and update
    }

    bool Union(int a, int b)
    {
        int x = find(a);
        int y = find(b);
        if(x != y) d[x] = y;
        return x != y; // return for kruskal
    }

private:
    int *d;
    int size;
};

class Edge {
public:
    Edge(int start, int end, int weight):start(start), end(end), weight(weight)
    {
    
    }

    bool operator<(const Edge& rhs) const
    {
        return this->weight < rhs.weight;
    }

    friend class MST;

private:
    int start, end, weight;
};

class MST {
public:
    MST():length(0), ds(Disjoint_set(MAX_SIZE))
    {

    }

    void add_edge(int start, int end, int weight) // add edge to graph
    {
        graph.push_back(Edge(start, end, weight)); // make graph
    }

    void kruskal() // kruskal's algorithm
    {
        // init
        mst.clear();
        length = 0;
        // sort graph by weight
        sort(graph.begin(), graph.end());
        // find MST
        for(auto edge : graph){
            if(ds.Union(edge.start, edge.end)){
                mst.push_back(edge);
                length += edge.weight;
            }
        }
    }

    void print() // print answer
    {
        for(auto edge : mst){
            cout << edge.start << " " << edge.end << " " << edge.weight << endl;
        }
        cout << length << endl;
    }

private:
    vector<Edge> graph;
    vector<Edge> mst;
    Disjoint_set ds;
    int length;
};

int main(int argc, char *argv[])
{
    string filename;
    cin >> filename;
    fstream fs;
    fs.open(filename, fstream::in);
    MST mst;
    int start, end, weight;
    while(fs >> start >> end >> weight){
        mst.add_edge(start, end, weight);
    }
    mst.kruskal();
    mst.print();
    fs.close();
}
