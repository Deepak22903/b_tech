#include <iostream>
#include <stdexcept>

using namespace std;

class Bank_Account{
    private :
    double balance;

    public:
    Bank_Account(double b){
        balance = b;
    }

    void deposit(double amount){
        if(amount < 0){
            throw invalid_argument("Invalid Amount");
        }else{
            balance = balance + amount;
            cout << "Deposit Successfull" << endl;
        }
    }

    void withdraw(double amount){
        if(amount > balance){
            throw invalid_argument("Invalid Amount");
        }else{
            balance = balance - amount;
            cout << "Withrawl Successfull" << endl;
        }
    }

    double getBalance(){
        return balance;
    }
};

int main(){
    Bank_Account acc1(0);
    double depo_ammount, with_ammount;

    try{
        cout << "Balance = " << acc1.getBalance() << endl;
        cout << "Enter deposit Ammount: ";
        cin >> depo_ammount;
        acc1.deposit(depo_ammount);

        cout << "Enter Withdraw Ammount: ";
        cin >> with_ammount;
        acc1.withdraw(with_ammount);
    }catch(exception& e){
        cout << e.what() << endl;
    }

    return 0;
}