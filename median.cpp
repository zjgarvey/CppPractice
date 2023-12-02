#include<iostream>
#include<vector>

using namespace std;

int findmedian(vector<int> Aorig){
    /*
    This function computes the median by dividing the remaining array
    into a left segment and a right segment. Whichever side has more elements
    must also contain the median, so search that next. 

    If lucky, the median gets guessed immediately, requiring O(N) work to check.

    On average, the division step will result in a new search segment that is 3/4 
    the size of the previous search segment. If this continues to occur, then there
    will be about log_(4/3)(N) iterations of the loop, during which const*((3/4)^iter)*N
    comparisons will be computed, yeilding a runtime of O(N) from :
        N*Sum_{i=0}^{log_{4/3}(N)} ((3/4)^i) =  
        = N*( 4 - 3*(3/4)^(log_{4/3}(N)) ) = 
        = N*(4 - 3/N) 
        ~ N
    The worst case is O(N^2), when the array is alternating towards the median at 
    the end. This is because the section to search will only decrease by 1 on each
    iteration, and will require N total searches 
    */

    //initialize some segment sizes
    int r = 0;
    int rdead = 0; 
    int l = 0;
    int ldead = 0; 
    int eq =0;
    // to be a median, #left && #right <= thresh.
    int size = Aorig.size();
    int thresh = size/2; 
    //initialize segment to search
    vector<int> A = Aorig; 
    //these will store elements to the left and right of x
    vector<int> left; 
    vector<int> right;
    //initialize proposed median
    int x;
    //in case something goes wrong
    int iter = 0;
    float xtemp; 
    bool foundone = false;
    
    
    while (iter < size) {
        //pick an x in the search set
        x = A[0]; 
        l=0;
        r=0;
        eq=0;

        for (int a : A) {
            if (a<x) {left.push_back(a); l++;}
            if (a>x) {right.push_back(a); r++;}
            if (a == x) {eq++;}
        }

        //check if median
        if (l+ldead <= thresh && r+rdead <= thresh) {
            if (size%2 == 0){ 
                if (!foundone) {
                    foundone = true;
                    xtemp = static_cast<float>(x);
                    cout << "x1 = "<< xtemp <<endl;
                } 
                else { 
                    cout << "x2 = " << x << endl;
                    xtemp += static_cast<float>(x); 
                    xtemp /= 2;
                    cout << "real median = " << xtemp << endl;
                    return xtemp;
                    }
            }
            else {return x;}
        }

        if (l+ldead > r+rdead){ A = left; rdead += (r + eq);} //left contains median, kill right
        else{ A = right; ldead += (l + eq);} //right contains median, kill left

        iter++;
        left.clear();
        right.clear();
    }
}

int main() {
    vector<int> X;

    // A worst-case scenario:
    int alt = -1;
    for (int i = 0; i < 10420; i++) {
        alt*=-1;
        X.push_back(alt*(10420 - i));
        }
    
    /*
    for (int i = 1; i <= 2; i++){
        X.push_back(i);
    }
    */

    int median = findmedian(X);
    cout << "median = " << median << endl;
    return 0;
}