
class Account
{

protected:
    double balance;
    int dep;
    int Withdrawl;
    double AnnRate;
    double MSC;

public:
    Account(double bal, double rate)
    {
        balance = bal;
        AnnRate = rate;
        dep = 0;
        Withdrawl = 0;
        MSC = 0;
    }

    virtual void deposit(double amount)
    {
        balance += amount;
        if (amount > 0){
            dep += 1;
        }else{
            dep = dep;
        }
    }

    virtual void withdraw(double amount)
    {
        balance -= amount;
        if (amount > 0){
            Withdrawl += 1;
        }else{
            Withdrawl = Withdrawl;
        }
        
    }

    virtual void calcint()
    {
        double Monthlyrate = (AnnRate / 12);
        double MonthlyInterest = balance * Monthlyrate;
        balance = balance + MonthlyInterest;

    }

    virtual void monthlyProc()
    {
        balance -= MSC;
        calcint();
        dep = 0;
        Withdrawl = 0;
        MSC = MSC;
    }

    double getbalance()
    {
        return balance;
    }

    int getdep()
    {
        return dep;
    }

    int getWithdrawl()
    {
        return Withdrawl;
    }

    double getMonthleServiceCharge()
    {
        return MSC;
    }
};

#include <iostream>

using namespace std;
class SavingAccount : public Account
{
private:
    bool status;

public:

    SavingAccount(double bal = 0 , double rate = 0): Account(bal,rate)
    {

    }

    bool checkStatus()
    {
        if (Account::balance < 25.0)
            return false;
        else
            return true;
    }

    void withdraw(double amount)
    {
        if (checkStatus())
        {
            Account::withdraw(amount);
        }
    }

    void deposit(double amount)
    {
        if (checkStatus() == false)
        {
            if (Account::balance + amount > 25)
                status = true;
        }
        Account::deposit(amount);
    }

    void monthlyProc()
    {
        if (Account::Withdrawl > 4)
        {
            Account::MSC += 1;
            Account::balance -= 1;
            if (Account::balance < 25)
                status = false;
        }
    }
};

class CheckingAccount: public Account
{
public:
    CheckingAccount(double bal = 0, double rate = 0) : Account(bal, rate)
    {

    }

    void withdraw(double amount)
    {
        if (balance - amount < 0)
        {
            MSC += 15;
            balance -= 15;
        }
        else
            Account::withdraw(amount);
    }

    void monthlyProc()
    {
        MSC += 5;
        MSC += 0.10*Withdrawl;
    }
};

using namespace std;
int main()
{
    int op;
    double monthStartBalance;
    Account *saving = new SavingAccount();
    Account *checking = new CheckingAccount();

    do{
        cout << "Bank account menu" << '\n' <<
        "1. Savings account deposits:" << '\n'<<
        "2. Savings account withdraw:" << '\n' <<
        "3. Checking account deposits:" << '\n' <<
        "4. Checking account withdraw:" << '\n' <<
        "5. Monthly statistics calculation:" << '\n' <<
        "6. Statistics print:" << '\n' <<
        "7. Exit" << '\n';

        cin >> op;

        switch (op)
        {
            case 1:{
                double depositAmount;
                cout << "Saving Account" << '\n' << endl;

                cout << "Enter deposit amount: ";
                cin >> depositAmount;
                saving->deposit(depositAmount);
                if (monthStartBalance == 0){
                    monthStartBalance = depositAmount;
                }else{
                    monthStartBalance = saving->getbalance();
                }
            break;

            }
            case 2:{
                double withdrawAmount;
                cout << "Saving Account" << '\n' << endl;

                cout << "Enter withdrawl amount: ";
                cin >> withdrawAmount;
                cout << '\n';
                saving->withdraw(withdrawAmount);
            break;
            }

            case 3:{
                double depositAmount;
                cout << "Checking Account" << '\n' << endl;
                cout << "Enter deposit amount: ";
                cin >> depositAmount;

                checking->deposit(depositAmount);
                if (monthStartBalance == 0){
                    monthStartBalance = depositAmount;
                }else{
                    monthStartBalance = saving->getbalance();
                }
            break;
            }

            case 4:{
                double withdrawAmount;
                cout << "Checking Account" << '\n' << endl;

                cout << "Enter withdrawl amount: ";
                cin >> withdrawAmount;
                cout << '\n';
                checking->withdraw(withdrawAmount);
            break;
            }
            
            case 5:{
                cout << "Monthly service charge (Saving): " << saving->getMonthleServiceCharge() << endl;
                cout << "Monthly service charge (Checking): " << checking->getMonthleServiceCharge() << endl;
            break;
            }

            case 6:{
                cout << "Saving Account" << '\n';
                cout << "Beginning balance: " << monthStartBalance << endl;
                cout << "No. of deposts: " << saving->getdep() << endl;
                cout << "No of withdrawls: " << saving->getWithdrawl() << endl;
                cout << "Ending balance: " << saving->getbalance() << '\n' << endl;

                cout << "Checking Account" << '\n';
                cout << "Beginning balance: " << monthStartBalance << endl;
                cout << "No. of deposts: " << checking->getdep() << endl;
                cout << "No of withdrawls: " << checking->getWithdrawl() << endl;
                cout << "Ending balance: " << checking->getbalance() << '\n' << endl;

            break;

            }
            
    }
    
            
} while (op != 7);
    
return 0;
}
