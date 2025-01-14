#include <iostream>

#include "sales.hxx"

int main(void)
{
    using std::cout;
    using std::cin;
    using std::endl;

    double vals1[12] = {
        1220, 1100, 1122, 2212, 1232, 2334,
        2884, 2393, 2933, 3544, 3845, 3333
    };

    double vals2[12] = {
        12, 11, 22, 21, 32, 34,
        28, 29, 33, 29, 32, 35
    };

    Sales sales(2011, vals1, 12);

    LabeledSales sales2("Blogstar", 2012, vals2, 12);

    cout<<"First try block: \n";

    try{
        int i;
        cout<<"Year = "<<sales.Year()<<endl;
        for(i=0; i<12; ++i)
        {
            cout<<sales[i]<<' ';
            if(i%6 == 5)
                cout<<endl;
        }
        cout<<"Year = "<<sales2.Year()<<endl;
        cout<<"Label = "<<sales2.Label()<<endl;
        for(i=0; i<=12; i++)
        {
            cout<<sales2[i]<<" ";
            if(i%6 == 5)
                cout<<endl;
        }
        cout<<"End of tyr block 1.\n";
    }
    catch(LabeledSales::nbad_index &bad)
    {
        cout<<bad.what();
        cout<<"Company: "<<bad.label_val()<<endl;
        cout<<"bad index: "<<bad.bi_val()<<endl;
    }
    catch(Sales::bad_index &bad)
    {
        cout<<bad.what();
        cout<<"bad index: "<<bad.bi_val()<<endl;
    }

    
}