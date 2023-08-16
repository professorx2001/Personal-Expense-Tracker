#include<iostream>
#include<vector>
#include<fstream>

using namespace std;
//declaration to tell class method that this function exists down below.
void writeInFile(int,int);

class Type{
    private:
    int balance;
    public:
    int getBalance(){
        return balance;
    }
    void add(int index){
        int amount;
        cout<<"Enter the amount"<<endl;
        cin>>amount;
        balance += amount;
        writeInFile(balance, index);
        cout<<"Your Rs "<<amount<<" is added to your respective account"<<endl;
    }
    void deduct(int index){
        int amount;
        cout<<"Enter the amount"<<endl;
        cin>>amount;
        balance -= amount;
        writeInFile(balance, index);
        cout<<"Your Rs "<<amount<<" is deducted from your respective account"<<endl;
    }
    Type(int amount){
        balance = amount;
    }
};

char bankMenu(bool extra){
    char usrInput;

    cout<<"Choose a option to continue"<<endl;
    cout<<"[C]ash for Cash"<<endl;
    cout<<"[S]bi for State bank of India"<<endl;
    cout<<"[H]dfc for Housing Development Finance Corporation"<<endl;
    if(extra == true)
    cout<<"[T]otal Balance"<<endl;

    cin>>usrInput;
    return usrInput;
}


char operationMenu(){
    char userChoiceInput;

    cout<<"Choose a option to continue "<<endl;
    cout<<"[+] to Add "<<endl;
    cout<<"[-] to Deduct "<<endl;
    cout<<"[=] to view Balance "<<endl;
    cin>>userChoiceInput;
    return userChoiceInput;
}


void writeInFile(int amount, int index){
    vector<string>v;
    string dummyLine;
    ifstream read;
    read.open("expense.txt");

    while(!read.eof()){
        getline(read, dummyLine);
        v.push_back(dummyLine);
    }
    read.close();

    string newAmount = to_string(amount);
    v[index] = newAmount;

    ofstream write("expense.txt");
    for(int i=0; i<v.size(); i++){
        write << v[i]<< endl;
    }
}

int main(){

    string dummyLine;
    ifstream read("expense.txt");

    int cashBalance;
    read>>cashBalance;

    int sbiBalance;
    getline(read, dummyLine); //just used to goto second line
    read>>sbiBalance;


    int hdfcBalance;
    getline(read, dummyLine); //just used to goto third line
    read>>hdfcBalance;

    read.close();

    Type sbi(sbiBalance);
    Type hdfc(hdfcBalance);
    Type cash(cashBalance);


    switch (operationMenu()){
    char c;
    case '+':
        c = bankMenu(false);
        if(c =='c' || c =='C')
            cash.add(0); 
// 1st line in expense.txt contains cash balance and vector is 0 indexed so passing 0

        else if(c =='s' || c =='S')
            sbi.add(1);
// 2nd line in expense.txt contains SBI balance and vector is 0 indexed so passing 1

        else if(c =='h' || c =='H')
            hdfc.add(2);
// 3rd line in expense.txt contains HDFC balance and vector is 0 indexed so passing 2

        else 
        cout<<"Please choose correct option."<<endl;
        break;

    case '-':
        c = bankMenu(false);
        if(c =='c' || c =='C')
            cash.deduct(0);

        else if(c =='s' || c =='S')
            sbi.deduct(1);

        else if(c =='h' || c =='H')
            hdfc.deduct(2);

        else 
        cout<<"Please choose correct option."<<endl;
        break;

    case '=':
    c = bankMenu(true);
        if(c =='s' || c =='S') 
        cout<<sbiBalance;

        else if(c =='h' || c =='H') 
        cout<<hdfcBalance;

        else if(c =='c' || c =='C') 
        cout<<cashBalance;

        else if(c =='t' || c =='T')
        cout<<sbiBalance+hdfcBalance+cashBalance<<endl;
        else
        cout<<"You chose incorrect option."<<endl;
        break;

    default:
        cout<<"You chose incorrect option."<<endl;
        break;

    }
    return 0;
}