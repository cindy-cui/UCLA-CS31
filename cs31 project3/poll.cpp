
#include <iostream>
#include <cassert>
#include <string>
using namespace std;

bool isValidUppercaseStateCode(string stateCode);
bool isSyntacticallyCorrect(string pollData);
int tallyVotes(string pollData, char party, int& voteTally);



int main(){
    
    string pollData;
    getline(cin, pollData);
    
    bool correct = isSyntacticallyCorrect(pollData);
    
    if (correct == true){ // outputting if its syntactically correct
        cout << "valid" << endl;
    }
    
    if (correct == false){
        cout << "invalid" << endl;
    }
    
    int voteTally = 0; // initiating voteTally in main

    int votes = tallyVotes(pollData, 'd', voteTally);

    
    cout << "error code: " << votes << endl; // error code returned from tallyVotes function
    cout << "voteTally: " << voteTally << endl; // updated voteTally value
    
}






bool isValidUppercaseStateCode(string stateCode)  // valid state code function provided in spec
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
        "KY.LA.ME.MD.MA.MI.MN.MO.MS.MT.NE.NV.NH.NJ.NM.NY.NC."
        "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}







bool isSyntacticallyCorrect(string pollData){
    
    if (pollData == "") return true; // accounts for empty string

    for (int i = 0; i < pollData.length(); i++){    // make everything uppercase
        if (isalpha(pollData.at(i))){
            pollData[i] = toupper(pollData.at(i));
        }
    }

    while (true){ // loop to check thru each #, state code, + party
        
        if (isdigit(pollData[0]) && !isdigit(pollData[1])){ // for only one digit
            if (isValidUppercaseStateCode(pollData.substr(1, 2)) == true){ //checks valid state
                if(isalpha(pollData[3])){ // checks that the party exists as a letter
                    pollData = pollData.substr(4); //cuts off part we alr looked at
                }
                else return false; // if the party isnt a character
            }
            else return false; // if the state code isn't valid
        }
        
        else if (isdigit(pollData[0]) && isdigit(pollData[1])){ // two digits
            
            if (isValidUppercaseStateCode(pollData.substr(2, 2)) == true){ // checks valid state code
                if(isalpha(pollData[4])){ // checks that party is a letter
                    pollData = pollData.substr(5); //cuts off part we alr looked at
                }
                else return false; // party isnt a character
            }
            else return false; // state code isn't valid
        }
        
        else return false; // if the # of votes isn't one or two digits
        
        if (pollData.length() == 0){ // once we've run through the entire string
            return true;
        }
            
    }

    return true;
    
}
















int tallyVotes(string pollData, char party, int& voteTally){
    

    
    for (int i = 0; i < pollData.length(); i++){    // make everything uppercase
        if (isalpha(pollData.at(i))){
            pollData[i] = toupper(pollData.at(i));
        }
    }
    
    party = toupper(party); //changing party to caps
    
    if (isSyntacticallyCorrect(pollData) == false){ // checks if it's syntactically correct
        return 1;
    }
    
    if (!isalpha(party)){ //checks if the party is a letter
        return 2;
    }

        
    for (int i = 0; i < pollData.length() - 2 ; i++){ // checks if there are values of zero
        if (pollData[i] == '0' && pollData[i+1] == '0'){ //checking for two 00's
            return 3;
        }
        if (isalpha(pollData[i]) && pollData[i+1] == '0' && isalpha(pollData[i+2])){ // checking for letter, 0, letter -- single 0
            return 3;
        }
    }
    
    voteTally = 0; //sets voteTally to 0 in order to start tallying
        
    for (int i = 0; i < pollData.length() - 2; i++){
        if (isalpha(pollData[i]) && isalpha(pollData[i+1]) && isalpha(pollData[i+2]) ){
            if (pollData[i+2] == party){
                if (isdigit(pollData[i-1]) && isdigit(pollData[i-2]) ){ //two digits
                    voteTally += stoi(pollData.substr(i-2, 2)); //converting string to int and adding to vote tally
                }
                else { //one digit
                    voteTally += stoi(pollData.substr(i-1, 1)); //converting string to int
                }
            }
        }
    }
    
    return 0;
    

}

