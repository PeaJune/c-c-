#include <iostream>
#include "brass.hxx"

using std::cout;
using std::endl;
using std::string;

typedef std::ios_base::fmtflags format;
typedef std::streamsize precis;
format setFormat();
void restore(format f, precis p);

Brass::Brass(const string &s, long an, double bal)
{
    fullName = s;
    acctNum = an;
    balance = bal;
}

void Brass::Deposit(double amt)
{
    if(amt < 0)
        cout<<"Negative deposit not allowed; "
            <<"deposit is cancelled.\n";
    else
    {
        balance += amt;
    }
}

void Brass::WithDraw(double amt)
{
    format initialState = setFormat();
    precis prec = cout.precision(2);

    if(amt < 0)
        cout<<"WithDraw amount musb be positive; "
            <<"WithDraw canceled.\n";
        else if (amt <= balance)
        {
            balance -= amt;
        }else
        {
            cout<<"WithDraw amount of $"<<amt
                <<" exceeds your balance.\n"
                <<"Withdraw canceled.\n";
                restore(initialState, prec);
        }
}

double Brass::Balance()const
{
    return balance;
}

void Brass::ViewAcct()const
{
    format initialState = setFormat();
    precis prec = cout.precision(2);

    cout<<"Client: "<<fullName<<endl;
    cout<<"Accout Number: "<<acctNum<<endl;
    cout<<"Balance: $"<<balance<<endl;

    restore(initialState, prec);
}


BrassPlus::BrassPlus(const string &s, long an, double bal,
                    double ml, double r) : Brass(s, an, bal)
{
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

BrassPlus::BrassPlus(const Brass &ba, double ml, double r) : Brass(ba)
{
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

void BrassPlus::ViewAcct()const
{
    format initialState = setFormat();
    precis prec = cout.precision(2);

    Brass::ViewAcct();
    cout<<"Maxinum load: $"<<maxLoan<<endl;
    cout<<"Owed to bank: $"<<owesBank<<endl;
    cout.precision(3);
    cout<<"Loan Rate: "<<100*rate<<"%\n";
    restore(initialState, prec);
}

void BrassPlus::WithDraw(double amt)
{
    format initialState = setFormat();
    precis prec = cout.precision(2);

    double bal = Balance();
    if(amt < bal)
        Brass::WithDraw(amt);
    else if (amt <= bal+maxLoan-owesBank)
    {
        double advance = amt - bal;
        owesBank += advance *(1.0 + rate);
        cout<<"Bank advance: $"<<advance<<endl;
        cout<<"Finance charge: $"<<advance*rate<<endl;
        Deposit(advance);
        Brass::WithDraw(amt);
    }else
    {
        cout<<"Credit limit exceeded, Transaction cancelld.\n";
    }

    restore(initialState, prec);
}

format setFormat()
{
    return cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
}

void restore(format f, precis p)
{
    cout.setf(f, std::ios_base::floatfield);
    cout.precision(p);
}
