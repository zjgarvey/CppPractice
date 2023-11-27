#include<iostream>
#include<map>
#include<vector>
#include<queue>

using namespace std;

class dirgraph{

    //default constructor will generate an empty graph

    protected:
        map<int, vector<int>> edgeout;
        int nodeMax = -1;
        int edgeCount = 0;

    public: 

        //adds a node to the graph and initializes an empty edge list
        void addNode() {
            nodeMax++;
            vector<int> nothing (0,0);
            edgeout[nodeMax] = nothing;
            cout << "Added node at " << nodeMax << endl;
        }

        //adds n new nodes
        void addNodes(int n) {
            int j = 0;
            while (j < n){
                addNode();
                j++;
            }
        }

        //adds an edge between source and target
        void addEdge(int source, int target) {
            //check if source and target are in graph
            if (source > nodeMax || target > nodeMax) {
                cout << "Error: source and target nodes are not in graph!" << endl;
            }
            else{
                //check if edge already exists
                bool alreadyedge = false;
                for (int n: edgeout[source]) {
                    if (n == target){
                        alreadyedge = true;
                    }
                }
                if (!alreadyedge) {
                    //add the edge
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

        void printAllEdges() {
            for (int n = 0; n<=nodeMax; n++) {
                cout << "Edges for node " << n << ":" << endl;
                printEdges(n);
            }
        }

        void terminput() {
            bool val1 = true;
            bool val2 = true;
            int source, target, lastnode;
            cout << "How many vertices? " ;
            cin >> lastnode;
            addNodes(lastnode);
            lastnode++;
            cout << "Let's make some edges. \nAt any point, type -1 to finish input." << endl;
            while (val1) {
                cout << "Input source: ";
                cin >> source;
                if (source == -1) {
                    val1 = false;
                    cout << "Stopping input." << endl;
                    break;
                }
                cout << '\n' << "Input targets for source " << source << ": " ;
                val2 = val1;
                while (val2){
                    cin >> target;
                    if (target == -1){
                        val2 = false;
                        cout << "Returning to source input." << endl;
                        break;
                    }
                    cout << "Making Edge " << source << "->" << target << endl;
                    addEdge(source,target);
                }
            }
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
    vector<int> marks (nodeMax + 1,-1);
    Q.push(source);
    int qsize = 1;
    while (!found && qsize != 0) {
        iter++;
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
    if (sze > 0){
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
    G.terminput();
    G.printAllEdges();

    int source;
    cout << "Source for path search: ";
    cin >> source;
    cout << '\n';
    int target;
    cout << "Target for path search: ";
    cin >> target;
    cout << '\n';

    G.pathprinter(source, target);

    return 0;
}

