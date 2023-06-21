#include "StrechyArray.h"
#include<string>
#include<fstream>




string* return_uniquestrings(string* S, int ns, int& news)
{
    if (ns > 1)
    {
        news = 0;
        string* temp = nullptr;
        for (int i = 0; i < ns; i++)
        {
            bool ispresent = false;
            for (int x = 0; x < news; x++)
            {
                //ispresent = false;
                if (S[i] == temp[x])
                {
                    ispresent = true;
                    break;
                }

            }
            if (ispresent == false)
            {

                string* temp2 = new string[news + 1];
                for (int z = 0; z < news; z++)
                {
                    temp2[z] = temp[z];
                }
                temp2[news] = S[i];
                delete[]temp;
                temp = temp2;
                news++;
            }
        }
        return temp;
    }
    return S;
}
bool binarysearch(string A[], int si, int ei, string x)
{
    int  mid = (si + ei) / 2;


    //BASE CASE 01
    if (ei <= si)
        return (x == A[mid]) ? true : false;

    //BASE CASE	02 
    if (A[mid] == x)
        return true;

    //RECURSIVE CASES
    if (A[mid] > x)
        return binarysearch(A, si, mid - 1, x);

    if (A[mid] < x)
        return binarysearch(A, mid + 1, ei, x);


}


string* find_intersectionS(string* S1, string* S2, int sz1, int sz2, int& nsz)
{
   
    nsz = 0;
    string* temp = nullptr;

    for (int i = 0; i < sz2; i++)
    {
        if (binarysearch(S1, 0, sz1 - 1, S2[i]))
        {


            string* temp2 = new string[nsz + 1];
            for (int z = 0; z < nsz; z++)
            {
                temp2[z] = temp[z];
            }
            temp2[nsz] = S2[i];
            delete[] temp;
            temp = temp2;
            nsz++;
            

        }
    }
    return temp;

}


template < class T>
void MergeMagic(T* Arr, int s1, int e1, int s2, int e2)
{
    while (true)
    {
        if (s1 > e1 || s2 > e2)
            break;
        if (Arr[s1] > Arr[s2])
        {
            T temp = Arr[s2];
            for (int i = s2; i > s1; i--)
            {
                Arr[i] = Arr[i - 1];
            }
            Arr[s1] = temp;
            s1++;
            e1++;
            s2++;
        }
        else if (Arr[s1] < Arr[s2])
            s1++;
        else if (Arr[s1] == Arr[s2])
        {
            for (int i = s2; i > s1; i--)
            {
                Arr[i] = Arr[i - 1];
            }
            Arr[s1 + 1] = Arr[s1];
            s1++; s1++; e1++;
            s2++;
        }
    }
}

template <class T>
void MergeSort(T* A, int start, int end)
{
    if (start >= end)
        return;
    int middle = (start + end) / 2;
    MergeSort(A, start, middle);
    MergeSort(A, middle + 1, end);
    MergeMagic<T>(A, start, middle, middle + 1, end);
}

void additemtotemp(string*& t, string x, int& s)
{

    string* temp = new string[s + 1]{};
    for (int i = 0; i < s; i++)
    {
        temp[i] = t[i];
    }
    temp[s] = x;
    delete[]t;
    t = temp;
    s++;
}

void AllStringsPossible(string w, StrecthyArray<string>& APS)
{


    int ws = w.length();

    if (ws == 0)
    {

        return;
    }

    //-------reducing the word-----------

    char fl = w[ws - 1];

    string rest = w.substr(0, ws - 1);


    //-------Recursion-----------

    AllStringsPossible(rest, APS);

    //----------------------------------------------------
    //------ REAL DEAL ---------------------
    //--------------------------------------

    int ts = 0;
    string* temp = new string[ts + 1];

    for (int i = 0; i < APS.returnsize(); i++)
    {

        string merge = {};
        merge = fl + APS.returnArr()[i];

        string extra = {};

        //----copy-------
        for (int y = 0; y < merge.length(); y++)
            extra += merge[y];
        //------------------------
        additemtotemp(temp, merge, ts);
        //--------------------------
        for (int x = 1; x < merge.length(); x++)
        {
            swap(merge[0], merge[x]);

            additemtotemp(temp, merge, ts);
            merge = {};
            //---copy----
            for (int y = 0; y < extra.length(); y++)
                merge += extra[y];
        }
    }
    //---ADD to APS-------------
    for (int i = 0; i < ts; i++)
    {
        APS.insertelement(temp[i]);
    }
}

void loadD(string* & d, string  filename)
{
    ifstream rdr(filename);
    string word={};
    for (int i=0; true;i++)
    {
        bool doit= (rdr.peek() == std::ifstream::traits_type::eof());
        if (doit)
        {
            break;
        }
            rdr >> word;
            
            d[i] = (word);
        
    }
}

void display(string* a, int s)
{
    for (int i = 0; i < s; i++)
    {
        cout << "\"" << a[i] << "\""; (i == s - 1) ? cout << "" : cout << endl;
    }cout << endl;
}
void meaningfulwords(string* &d, string* uniques, int sized,int sizu)
{
    int ms = 0;
    string* mwords = find_intersectionS(d, uniques, sized, sizu, ms);
    display(mwords, ms);
}



int main()
{
    int size = 79340;
    string* dictionary = new string[size];
    loadD(dictionary, "dictionary.txt");
   
    string word = "";
   
    cout << "WORD BTA : ";
    cin >> word;
    StrecthyArray<string> R(word);
   
    AllStringsPossible(word, R);
    cout << endl;
    cout << "all possible string dekhni to : " << endl;
    system("pause");
    display(R.returnArr(), R.returnsize());
    string* APS = nullptr; int s = 0;

    //------UNIQUE WALA KAAM-----------
    APS = return_uniquestrings(R.returnArr(), R.returnsize(), s);
    cout << endl << "all unique string dekhni to : " << endl;
    system("pause");
   
    //---------SORTING WALA KAAAM -----------
     MergeSort<string>(APS, 0, s - 1);
     display(APS, s);
    //--------------------------------------
  
   cout <<endl<< "all meaningful string dekhni to : " << endl;
   system("pause");
    meaningfulwords(dictionary, APS,size, s);
}