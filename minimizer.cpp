#include <bits/stdc++.h>

using namespace std; 

class people{
    public:
    set<string> UPIs;
    string name;
    int NetAmount = 0;
    int number_of_UPI;
};

int maxIndex(people *netAmount , int numPeople){
    int max = 0;
    for(int i = 1; i < numPeople ; i++){
        if(netAmount[max].NetAmount < netAmount[i].NetAmount){
            max = i;
        }
    }
    return max;
 }

int minIndex(people *netAmount , int numPeople){
    int min = 0;
    for(int i = 1; i < numPeople ; i++){
        if(netAmount[min].NetAmount > netAmount[i].NetAmount){
            min = i;
        }
    }
    return min;
 }

pair<int,string> validMax(people *netAmount , int numpeople,int minInd,people * input,int maxUPI){
    int maxIndex = -1;
    int max = INT_MIN;
    string matchType;

    for(int i =0; i<numpeople;i++){
        if(netAmount[i].NetAmount<=0) continue;

        vector<string> v(maxUPI);
        vector<string> :: iterator ls = set_intersection(netAmount[minInd].UPIs.begin(),netAmount[minInd].UPIs.end(),netAmount[i].UPIs.begin(),netAmount[i].UPIs.end(),v.begin());

        if((ls - v.begin()) != 0 && max < netAmount[i].NetAmount ){
            matchType = *(v.begin());
            max= netAmount[i].NetAmount;
            maxIndex = i;

        }
    }

    return make_pair(maxIndex,matchType);
}

void print(vector<vector<pair<int,string>>> & ansgraph , int numpeople , people * input){
    cout<<"                      Minimum required Transactions are.    "<<endl;
    cout<<"   _________________________________________________________________________"<<endl<<endl; 
    for(int i =0 ; i< numpeople; i++){
        for(int j =0 ; j<numpeople;j++){
            if(i==j) continue;
            //if(ansgraph[i][j].first == 0 && ansgraph[j][i].first == 0) continue;

            if(ansgraph[i][j].first != 0 && ansgraph[j][i].first !=0){

                if(ansgraph[i][j].first == ansgraph[j][i].first){
                    ansgraph[i][j].first = 0;
                    ansgraph[j][i].first = 0;
                }

                else if(ansgraph[i][j].first > ansgraph[j][i].first){
                    ansgraph[i][j].first -= ansgraph[j][i].first;
                    ansgraph[j][i].first = 0;
                    cout<<"         "<<input[i].name<<" pays "<<ansgraph[i][j].first<<" to "<<input[j].name<<" via "<<ansgraph[i][j].second<<endl; 
                }
                else{
                    ansgraph[j][i].first -= ansgraph[i][j].first;
                    ansgraph[i][j].first = 0;
                    cout<<"         "<<input[j].name<<" pays "<<ansgraph[j][i].first<<" to "<<input[i].name<<" via "<<ansgraph[j][i].second<<endl;
                }
            }

            else if(ansgraph[i][j].first != 0){
                cout<<"         "<<input[i].name<<" pays "<<ansgraph[i][j].first<<" to "<<input[j].name<<" via "<<ansgraph[i][j].second<<endl;
                
            }

            else if(ansgraph[j][i].first !=0){
                cout<<"         "<<input[j].name<<" pays "<<ansgraph[j][i].first<<" to "<<input[i].name<<" via "<<ansgraph[j][i].second<<endl;
            }

            ansgraph[i][j].first = 0;
            ansgraph[j][i].first = 0;
        }
    }
    cout<<endl;
}

void CashFlowMinimizer(int numpeople , people *input ,unordered_map<string,int>& indexOf ,int maxUPI, 
int numTransactions , vector<vector<int>> & graph){

    people netAmount[numpeople];

    for(int p = 0; p< numpeople ; p++){
        netAmount[p].name = input[p].name;
        netAmount[p].UPIs = input[p].UPIs;   
    }

      for(int i = 0; i<numpeople ; i++){
           for(int j =0 ; j<numpeople ;j++){
               netAmount[i].NetAmount += (graph[j][i] - graph[i][j]) ;
            }
        } 

    vector<vector<pair<int ,string>>> ansGraph(numpeople , vector<pair<int , string>>(numpeople , {0,""}));

    int skips = 0;

    for(int i =0 ; i< numpeople ; i++){
        if(netAmount[i].NetAmount == 0) skips++;
    }

    while(skips != numpeople){
        int minInd = minIndex(netAmount,numpeople);
        pair<int,string> maxPair = validMax(netAmount,numpeople,minInd,input,maxUPI);
        int maxInd = maxPair.first;

        if(maxInd == -1){
            int newmaxInd = maxIndex(netAmount,numpeople);
            

            (ansGraph[minInd][0].first) += abs(netAmount[minInd].NetAmount);
            (ansGraph[minInd][0].second) = *(input[minInd].UPIs.begin());

            (ansGraph[0][newmaxInd].first) += abs(netAmount[minInd].NetAmount);
            (ansGraph[0][newmaxInd].second) = *(input[newmaxInd].UPIs.begin());

            netAmount[newmaxInd].NetAmount += netAmount[minInd].NetAmount;
            netAmount[minInd].NetAmount = 0;

            if(netAmount[minInd].NetAmount == 0) skips++;
            if(netAmount[newmaxInd].NetAmount == 0) skips++; 
        }

        else{
             
            int transactionAmount = min(abs(netAmount[minInd].NetAmount) , netAmount[maxInd].NetAmount);

            (ansGraph[minInd][maxInd].first) += transactionAmount;
            (ansGraph[minInd][maxInd].second) = maxPair.second;

            netAmount[minInd].NetAmount += transactionAmount;
            netAmount[maxInd].NetAmount -= transactionAmount;

            if(netAmount[minInd].NetAmount == 0) skips++;
            if(netAmount[maxInd].NetAmount == 0) skips++;
        }
    }

    print(ansGraph,numpeople,input);


return;
}


int main()
{
    int numPeople;
    cout<<"   _________________________________________________________________________"<<endl<<endl;
    cout<<"                        WELCOME TO CASH FLOW MINIMIZER                      "<<endl;
    cout<<"   _________________________________________________________________________"<<endl<<endl;
    cout<<"           This application reduces the number of transacations among       "<<endl;
    cout<<"         a pool of people who use different modes of Payment Interface.     "<<endl<<endl;
    cout<<"      There is 1 TREASURER (having access to all Payment Interface) to act  "<<endl;
    cout<<"      as a Middle Man between individuals with no commom Payment Interface. "<<endl;
    cout<<"   _________________________________________________________________________"<<endl<<endl;
    cout<<"                 Enter the Number of People (including Treasurer)           "<<endl;
    cout<<"                     participating in the transaction: "; cin>>numPeople;
    cout<<"   _________________________________________________________________________"<<endl<<endl;

    people input[numPeople];
    unordered_map<string , int> indexOf;
    cout<<"               Enter the details of people and transaction as stated.       "<<endl<<endl;
    cout<<"            FULL_NAME   NUMBER_OF_PAYMENT_INTERFACE  NAME_OF_INTERFACES     "<<endl<<endl;
    cout<<"              Person's name and name of individual payment interfaces       "<<endl;
    cout<<"                             should NOT contain spaces.                     "<<endl;
    cout<<"   _________________________________________________________________________"<<endl<<endl; 

    int maxUPI;
    for(int i =0 ; i<numPeople ;i++){
        if(i == 0){
    cout<<"        Details of Treasurer:";
           
        }
        else {
    cout<<"        Details of Person:";        
        }

        cin>>input[i].name;
        cin>>input[i].number_of_UPI;

        if(i==0) maxUPI = input[i].number_of_UPI;
        string temp;
        while(input[i].number_of_UPI --){
            cin>>temp;
            input[i].UPIs.insert(temp);
        }

        indexOf[input[i].name] = i ;
    }
    cout<<"   _________________________________________________________________________"<<endl<<endl; 
    int numTransactions;
    vector<vector<int>> graph (numPeople , vector<int>(numPeople , 0));

    cout<<"                         Enter Number of Transactions:"; cin>>numTransactions;
    cout<<"                     Enter Transaction details as stated.                   "<<endl<<endl;
    cout<<"                     DEBTOR_NAME   CREDITOR_NAME   AMOUNT                   "<<endl<<endl;

    for(int i =0 ;i < numTransactions ;i++){
    cout<<"        Transaction "<< i+1 << " Details:";
    string s1,s2;
    int amount;
    cin>>s1>>s2>>amount;
    graph[indexOf[s1]][indexOf[s2]] = amount ;
    }
    cout<<"   _________________________________________________________________________"<<endl<<endl;
    CashFlowMinimizer(numPeople,input,indexOf,maxUPI,numTransactions,graph);
    return 0;
}
