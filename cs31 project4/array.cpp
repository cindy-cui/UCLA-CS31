#include <iostream>
using namespace std;
#include <string>
#include <cassert>


int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int divide(string a[], int n, string divider);



int main() {
    string h[7] = { "martha", "mark", "joe", "susan", "", "kamala", "lindsey" };
            assert(lookup(h, 7, "kamala") == 5);
            assert(lookup(h, 7, "joe") == 2);
            assert(lookup(h, 2, "joe") == -1);
            assert(positionOfMax(h, 7) == 3);

            string g[4] = { "martha", "mark", "lindsey", "sara" };
            assert(differ(h, 4, g, 4) == 2);
            assert(appendToAll(g, 4, "?") == 4 && g[0] == "martha?" && g[3] == "sara?");
            assert(rotateLeft(g, 4, 1) == 1 && g[1] == "lindsey?" && g[3] == "mark?");

            string e[4] = { "joe", "susan", "", "kamala" };
            assert(subsequence(h, 7, e, 4) == 2);

            string d[5] = { "mark", "mark", "mark", "susan", "susan" };
            assert(countRuns(d, 5) == 2);
        
            string f[3] = { "lindsey", "joe", "mike" };
            assert(lookupAny(h, 7, f, 3) == 2);
            assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "lindsey");
        
            assert(divide(h, 7, "lindsey") == 3);
        
            cout << "All tests succeeded" << endl;
}


int appendToAll(string a[], int n, string value){
    // append value to end of every element in array
    if (n < 0) return -1;
    if (n == 0) return 0; //array would be unchanged
    for (int i = 0; i < n; i++){
        a[i] = a[i] + value; // appending value to every element
    }
    return n;
}



int lookup(const string a[], int n, string target){
    if (n <= 0) return -1; //wont find target in empty string
    for (int i = 0; i < n; i++){
        if (a[i] == target) return i; // return position of target if found
    }
    return -1; // if not found, return -1
}



int positionOfMax(const string a[], int n){
    if (n <= 0) return -1; // no interesting elements
    int position = 0;
    string value = a[0];
    for (int i = 0; i < n; i++){
        if (a[i] > value) {
            position = i; // keeps track of position with greatest
            value = a[i]; // update value to contain new greatest
        }
    }
    
    for (int j = 0; j < n; j++){
        if (a[j] == value){
            return j;
        }  // looking for first occurrence of the greatest string
    }
    return position;
}





int rotateLeft(string a[], int n, int pos){
    if (n <= 0) return -1; //0 elements --> nothing to rotate
    if (pos < 0 || pos >= n) return -1; //if position is out of bounds
    if (pos == n-1) return pos; // last element, nothing to rotate
    
    string temp = a[pos];
    
    for (int i = pos; i < n - 1; i++){
        a[i] = a[i+1];
    }
    a[n-1] = temp; // sets last element to original one at pos
    return pos;
    
}



int countRuns(const string a[], int n){
    if (n < 0) return -1;
    if (n == 0) return 0; //no sequences
    int counter = 0; //to count sequences
    string temp = "";
    
    for (int i = 0; i < n; i++){
        if (a[i] != temp) {
            counter++; // increments when the element is diff from one before it
            temp = a[i]; //setting the new temp
        }
    }
    
    return counter;
    
}


int flip(string a[], int n){
    if (n < 0) return -1;
    string temp;
    if (n == 0) return 0; // nothing to flip
    for (int i = 0; i < n/2; i++){
        temp = a[i];
        a[i] = a[n-1-i]; // replacing
        a[n-1-i] = temp; //finish swap
    }
    
    return n;
}



int differ(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0 || n2 < 0) return -1;
    if (n1 == 0) return 0; //can't compare when one array is alr empty
    if (n2 == 0) return 0;
    
    
    int end = 0;
    if (n1 < n2) end = n1;
    else end = n2; // determining shorter one
    
    for (int i = 0; i < end; i++){
        if (a1[i] != a2[i]) return i; // if the elements are not correspondingly equal at position i
    }
    
    return end; // returns n that runs out first
}



int subsequence(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0 || n2 < 0) return -1;
    int counter = 0;
    
    if (n2 == 0) return 0; // 0 counts as subsequence of any sequence starting at 0
    if (n1 < n2) return -1; // cannot possibly contain n2
    
    for (int i = 0; i < n1 - n2; i++){// looping thru elements of a1
        for (int j = 0; j < n2; j++){ //looping thru the sequence of a2
            if (a1[j+i] == a2[j]) counter++;
            else break;
        }
        
        if (counter == n2) return i;
        else counter = 0; //reset
    }
    
    return -1;
}




int lookupAny(const string a1[], int n1, const string a2[], int n2){
    if (n1 <= 0 || n2 <= 0) return -1; //cannot compare when there are no interesting elements
    
    for (int i = 0 ; i < n1; i ++){//loop through a1
        for (int j = 0; j < n2; j++){
            if (a1[i] == a2[j]) return i; // when an equivalent element is found
        }
    }
    return -1;
}


int divide(string a[], int n, string divider){
    if (n < 0) return -1;
    if (n == 0) return 0; //returning n when there are no such elements
    string temp;
   
    for (int i = 0; i < n; i++){ // swap elements until they're in order from least to greatest
        for (int j = i+1; j < n; j++){
            if (a[i] > a[j]){
                temp = a[i]; // swapping
                a[i] = a[j];
                a[j] = temp;
            
            }
        }
    }
    
    for (int i = 0; i < n; i++){
        if (a[i] >= divider) return i; //looking for first element that's >
    }
    return n;
    
}






