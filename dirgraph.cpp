#include<iostream>
#include<map>
#include<vector>
#include<queue>
#include<stdexcept>

using namespace std;

class dirgraph{
    //default constructor will generate an empty graph
    //the function terminput will generate a graph based on inputs

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
            if (n<=0){throw invalid_argument("Need an positive integer number of nodes.\n");}
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
                throw invalid_argument("source and target nodes are not in graph!\n");
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
        //removes an existing edge (unused)
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
        //removes a node

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
            int source, target, lastnode;
            cout << "How many vertices? " ;
            lastnode = -1;
            cin >> lastnode;
            try { 
                // prevent weird inputs from causing havoc.
                addNodes(lastnode);
            } catch (invalid_argument& e) { cout << e.what(); return; }
            lastnode++;

            cout << "Let's make some edges. \n";
            cout << "The input should be two integers, source and target.\n";
            cout << "At any point, type -1 to finish input." << endl;

            while (true) {
                source = -1;
                cin >> source;
                if (source == -1) {
                    cout << "\nStopping input." << endl;
                    break;
                }
                target = -1; 
                cin >> target;
                if (target == -1){
                    cout << "\nStopping input." << endl;
                    break;
                }

                try {
                    addEdge(source,target);
                    cout << "Made edge " << source << "->" << target << endl;
                } catch (invalid_argument& e) { 
                    cerr << e.what();
                }
            }

            int code;

            while (true){
                cout << "\nPerform an action. Input 0 for options.\n" ;
                code = -1;
                cin >> code;
                cout << "\n-----------------------------\n";
                if (code == -1) {break;}
                if (code == 0){
                    cout << "-----------OPTIONS-----------\n";
                    cout << "-1:               quit\n";
                    cout << " 0:               options\n";
                    cout << " 1:               add one node\n";
                    cout << " 2 nodeint:       delete node (and associated edges) at nodeint\n";
                    cout << " 3 source target: add edge between source and target\n";
                    cout << " 4:               print edges\n";
                    cout << " 5 source target: find path between source and target\n\n";
                }
                if (code == 1){
                    addNode();
                }
                if (code == 2){
                    cin >> source;
                    removeNode(source);
                }
                if (code == 3){
                    cin >> source >> target;
                    addEdge(source,target);
                }
                if (code == 4){
                    printAllEdges();
                }
                if (code == 5){
                    cin >> source >> target;
                    pathprinter(source,target);
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
            if((sze - i)%10 == 0){
                cout << " ->\n ";
            }
            cout << " -> " << path[i] ;
        }
        cout << '\n';
    }
    else{ cout << "No valid path." << '\n';}
}



int main() {
    dirgraph G;
    G.terminput();

    return 0;
}

