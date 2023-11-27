#include<iostream>
#include<map>
#include<vector>
#include<queue>

using namespace std;

class dirgraph{
    protected:
        map<int, vector<int>> edgeout;
        int nodeMax = -1;
        int edgeCount = 0;

    public: 
        void addNode() {
            nodeMax++;
            vector<int> nothing (0,0);
            edgeout[nodeMax] = nothing;
            cout << "Added node at " << nodeMax << endl;
        }

        void addNodes(int n) {
            int j = 0;
            while (j < n){
                addNode();
                j++;
            }
        }

        void addEdge(int source, int target) {
            if (source > nodeMax || target > nodeMax) {
                cout << "Error: source and target nodes are not in graph!" << endl;
            }
            else{
                bool alreadyedge = false;
                for (int n: edgeout[source]) {
                    if (n == target){
                        alreadyedge = true;
                    }
                }
                if (!alreadyedge) {
                    edgeout[source].push_back(target);
                    edgeCount++;
                }
            }
        }

        void removeEdge(int source, int target) {
            int sze = edgeout[source].size();
            for (int n = 0; n < sze; n ++) {
                if (edgeout[source][n] == target) {
                    edgeout[source].erase(edgeout[source].begin() + n);
                    edgeCount--;
                    break;
                }
            }
        }

        void removeNode(int node) {
            if (node > nodeMax) {
                cout << "Not a node!" << endl;
            }
            else{
                for (int other = 0; other <= nodeMax; other++){
                    removeEdge(other,node);
                    removeEdge(node,other);
                }
                for (int other = node; other < nodeMax; other++){
                    edgeout[other] = edgeout[other+1];
                }
                nodeMax--;
                cout << "Node removed at " << node;
                cout << ". All nodes after have been shifted back by 1." << endl;
            }
        }

        void printEdges(int source) {
            if (source > nodeMax) {
                cout << "Node is not in graph!" << endl;
            }
            for (int e: edgeout[source]) {
                cout << e << " ";
            }
            cout << '\n';
        }

        vector<int> pathfinder (int source, int target);

        void pathprinter(int source, int target);
};

vector<int> dirgraph::pathfinder (int source, int target) {
    vector<int> path (0,0); 
    if (source > nodeMax || target > nodeMax) {
        return path;
    }
    int iter = 0;
    bool found = false;
    queue<int> Q;
    vector<int> marks (nodeMax,-1);
    Q.push(source);
    marks[source] = -1;
    int qsize = 1;
    while (!found && qsize != 0) {
        int N = Q.front();
        Q.pop();
        qsize--;
        for (int n : edgeout[N]) {
            if (marks[n] == -1) {
                Q.push(n);
                qsize++;
                marks[n] = N;
                if (n == target) {found = true; break;}
            }
        }
        iter++;
    }
    if (found) {
        int index = target;
        for (int i = 0 ; i < iter; i++) {
            path.push_back(index);
            index = marks[index];
        }
    }

    return path;
}

void dirgraph::pathprinter(int source, int target) {
    auto path = pathfinder(source,target);
    int sze = path.size();
    if (path.size() != 0){
    cout << "path from " << source << " to " << target << ": " << '\n' << source;
    for (int i = sze - 1; i>=0; i--){
        cout << " -> " << path[i] ;
    }
    cout << '\n';
    }
    else{ cout << "No valid path." << '\n';}
}

int main() {
    dirgraph G;
    G.addNodes(4);
    G.addEdge(3,1);
    G.addEdge(3,3);
    G.addEdge(2,3);
    G.addEdge(1,0);
    G.addNode();
    G.addEdge(4,4);

    for (int n = 0; n<=4; n++) {
        cout << "Edges for node " << n << ":" << endl;
        G.printEdges(n);
    }
    
    int source;
    cout << "Source: ";
    cin >> source;
    cout << '\n';
    int target;
    cout << "Target: ";
    cin >> target;
    cout << '\n';

    G.pathprinter(source, target);

    return 0;
}

