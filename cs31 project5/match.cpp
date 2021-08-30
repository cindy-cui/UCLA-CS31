#include <iostream>
using namespace std;
#include <string>
#include <cstring>
#include <cctype>
#include <cassert>



const int MAX_WORD_LENGTH = 20;
int cleanupRules(char wordin[][MAX_WORD_LENGTH+1], char wordout[][MAX_WORD_LENGTH+1], int nRules);
int determineScore(const char document[], const char wordin[][MAX_WORD_LENGTH+1],const char wordout[][MAX_WORD_LENGTH+1], int nRules);
void rotateLeft(char a[][MAX_WORD_LENGTH+1], int n, int pos);


int main() {
    const int TEST1_NRULES = 3;
                char test1win[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
                    "family", "unhappy", "horse",
                };
                char test1wout[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
                    "",       "horse",   "",
                };
                assert(determineScore("Happy families are all alike; every unhappy family is unhappy in its own way.",
                            test1win, test1wout, TEST1_NRULES) == 2);
                assert(determineScore("Happy horses are all alike; every unhappy horse is unhappy in its own way.",
                            test1win, test1wout, TEST1_NRULES-1) == 0);
                assert(determineScore("Happy horses are all alike; every unhappy horse is unhappy in its own way.",
                            test1win, test1wout, TEST1_NRULES) == 1);
                assert(determineScore("A horse!  A horse!  My kingdom for a horse!",
                            test1win, test1wout, TEST1_NRULES) == 1);
                assert(determineScore("horse:stable ratio is 10:1",
                            test1win, test1wout, TEST1_NRULES) == 0);
                assert(determineScore("**** 2020 ****",
                            test1win, test1wout, TEST1_NRULES) == 0);
                cout << "All tests succeeded" << endl;
   
}

    

    


// function to move string to end of array
void rotateLeft(char a[][MAX_WORD_LENGTH+1], int n, int pos){
    if (pos == n-1) return;
        
    char temp [MAX_WORD_LENGTH+1];
    strcpy (temp, a[pos]); //temp variable with string at pos in array a
    
    for (int i = pos; i < n - 1; i++){
        strcpy(a[i], a[i+1]);  // shifting elements to the left
    }
    strcpy (a[n-1], temp); // sets last element to original one at pos

}




int cleanupRules(char wordin[][MAX_WORD_LENGTH+1], char wordout[][MAX_WORD_LENGTH+1], int nRules){
    
    if (nRules <= 0) return 0; // no clean rules
    
    
    for (int i = 0; i < nRules; i++){ // looping thru all words
        for (int j = 0; wordin[i][j] != '\0'; j++){ // looping thru characters of each word
            if (isalpha(wordin[i][j])){
                wordin[i][j] = tolower(wordin[i][j]); // making all characters lowercase
            }
        }
    }
                        
    for (int i = 0; i < nRules; i++){ // looping thru all words
        for (int j = 0; wordout[i][j] != '\0'; j++){ // looping thru characters of each word
            if (isalpha(wordout[i][j])){
                wordout[i][j] = tolower(wordout[i][j]); // making al characters lowercase
            }
        }
    }
    
    
  int valid = nRules; // # of total
    
    //check conditions
    
    //checking for empty wordin
    for (int i = 0; i < valid; i++){ // look through all rules
        if (strlen(wordin[i]) == 0){
            rotateLeft(wordin, valid , i); //rotating all rules forward and moving i element to the end
            rotateLeft(wordout, valid , i); // changing both arrays together
            valid = valid -1; // one less valid rule
            i--; //move loop counter back one as well
            if (valid == 0) return 0;
            
            
        }
    }
    
    
    //checking for non alphabetical characters in wordin
    for (int i = 0; i < valid; i++){ // looping thru all words
        for (int j = 0; wordin[i][j] != '\0'; j++){ // looping thru characters of each word
            if (!isalpha(wordin[i][j])){ // not an alphab letter
                rotateLeft(wordin, valid, i); //rotating all rules forward and moving i element to the end
                rotateLeft(wordout, valid, i); // changing both arrays together
                valid = valid - 1;
                i--; //move loop counter back one as well
                if (valid == 0) return 0;

            }
        }
    }
     

    //checking for non alphabetical letters in wordout
    for (int i = 0; i < valid; i++){
        for (int j = 0; wordout[i][j] != '\0'; j++){
            if (!isalpha(wordout[i][j])){ //not an alphab letter
                rotateLeft(wordin,valid, i); // rotating all rules forward
                rotateLeft(wordout, valid, i);
                valid = valid - 1;
                i--; //move loop counter back one as well
                if (valid == 0) return 0;
                

            }
        }
    }

    
    //checking if wordin and wordout are the same
    for (int i = 0; i < valid; i++){
        if (strcmp(wordin[i], wordout[i]) == 0){ // //if wordin and wordout are the same
            rotateLeft(wordin, valid, i); //rotating all rules forward and moving i element to the end
            rotateLeft(wordout, valid, i); // changing both arrays together
            valid = valid -1; // one less valid rule
            i--; //move loop counter back one as well
            if (valid == 0) return 0;

        }
    }

    
    // checking no other one-word rule and no two-word rule has the same wordin word as that one-word rule
    for (int i = 0; i < valid; i++){
        if (strlen(wordout[i]) == 0){ // when it's a one word rule
            for (int j = 0; j < valid; j++){ // check wordin[i] against all other wordins
                if (strcmp (wordin[i], wordin[j]) == 0  && i != j){ // if they have the same wordins
                    rotateLeft(wordin, valid, j); // rotating j away
                    rotateLeft(wordout, valid, j);
                    valid = valid -1; // one less valid rule
                    i--; //move loop counter back one as well
                    if (valid == 0) return 0;

                    
                }
            }
        }
    }

    //checking for duplicate two word rules
    for (int i = 0; i < valid; i++){
        for (int j = 0; j < valid; j++){
            if (strcmp(wordin[i], wordin[j]) == 0 && strcmp(wordout[i], wordout[j]) == 0  && i != j){ // duplicate two word rule
                rotateLeft(wordin, valid, j); //rotate j away
                rotateLeft(wordout, valid, j);
                valid = valid -1;
                i--; //move loop counter back one as well
                if (valid == 0) return 0;

            }
        }
    }
    
    
    
    
    return valid; //valid ones remaining
                                        
}
    
    









int determineScore(const char document[], const char wordin[][MAX_WORD_LENGTH+1],const char wordout[][MAX_WORD_LENGTH+1], int nRules){
    if (nRules <= 0) return 0; // no rules
    char copydoc [251+2]; // document with max 250 characters + zero byte + beginning/end space
    int rulecount = 0;
    
    
    copydoc[0] = ' '; // start doc with a space
    int count = 1;
    for (int i = 0; document[i] != '\0'; i++){ //looping thru characters of document
        if (isalpha(document[i]) || isspace(document[i])){
            if (isalpha(document[i])){
                copydoc[count] = tolower(document[i]);
            } // makes characters lowercase when copying over
            else copydoc[count] = document[i]; // copies spaces over
            count++;
        }
    }
    copydoc[count] = ' '; // ending space
    copydoc[count+1] = '\0';
    

    
    
    for (int i = 0; i < nRules; i++){//looping through all the rules
      
        char intemp [23] = ""; // creating copies of the rules, but with extra spaces surrounding the words
        char outtemp [23] = "";//strlen(wordout[i]) + 2
        
        intemp [0] = ' ';
        strcat(intemp, wordin[i]); // copying the rule in
        strcat(intemp, " "); // ending space
        
        outtemp [0] = ' ';
        strcat(outtemp, wordout[i]); // copying the rule in
        strcat(outtemp, " "); // ending spacee

            
        if (strlen(wordout[i]) == 0){ // one-word rule
            if(strstr(copydoc, intemp) != NULL){ // found the word within document
                rulecount++; //increment rule count when rule met
            }
        }
        else if (strstr(copydoc, intemp) != NULL && strstr(copydoc,outtemp) == NULL){ // wordin found but wordout not found
            rulecount++; // increment rulecount when rules met
        }
        
    }
    
    return rulecount;
    
}


