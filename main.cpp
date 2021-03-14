#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <queue>
#include <random>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

void afisare(vector <long long> v)
{
    for(long long i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

void test(vector <long long> v)
{
    long long ok = 0;
    for( long long i = 0; i < v.size() - 1; i++)
    {
        if (v[i] > v[i+1])
            ok++;
    }
    if (ok == 0)
        cout<<"TEST PASSED";
    else cout<<"TEST FAILED";
}



void BubbleSort (vector <long long> &v)

{
    long long i, j;

    for (i = 0; i < v.size()-1; i++)
        for(j = 0; j < v.size()-i-1; j++)

            if (v[j] > v[j+1])
                swap(v[j], v[j+1]);

}

void CountSort( vector <long long> &v, long long nr_elem, long long nr_max)
{
    vector <long long> frecv(nr_max+1);
    long long i;

    for( i=0;i<nr_elem;i++)
    {
        frecv[v[i]]++;
    }

    long long j=0;

    v.clear();

    for(i=0;i<=nr_max;i++)
    {
        if (frecv[i]!=0)
        {
            while(frecv[i]!=0)
            {
                v.push_back(i);
                frecv[i]--;
            }
        }
    }
}


void merge( vector <long long> &v, long long l, long long m, long long r)
{
    long long i, j, k, sizeL, sizeR;

    sizeL = m - l + 1;      //setez marimea subvectorilor
    sizeR = r - m;

    vector <long long> vecL(sizeL);
    vector <long long> vecR(sizeR);

    for (i = 0; i < sizeL; i++)     //pun elementele in subvectori
        vecL[i] = v[l+i];
    for (j = 0; j < sizeR; j++)
        vecR[j] = v[m+1+j];

    i = 0;
    j = 0;
    k = l;

    while (i < sizeL && j < sizeR)      //merge-uiesc cei 2 subvectori in cel principal
    {
        if(vecL[i] <= vecR[j])
        {
            v[k] = vecL[i];
            i++;
        }
        else
        {
            v[k] = vecR[j];
            j++;
        }
        k++;
    }
    while (i < sizeL)       //pun elementele ramase in vectorul principal
    {
        v[k] = vecL[i];
        i++;
        k++;
    }

    while (j < sizeR)
    {
        v[k]=vecR[j];
        j++;
        k++;
    }
}

void MergeSort( vector <long long> &v, long long l, long long r)
{

    long long m;
    if(l < r)
    {
        m = l + (r-l)/2;

        MergeSort(v, l, m);
        MergeSort(v, m+1, r);
        merge(v, l, m, r);
    }
}




int mediana3 (vector <long long> &v, long long p, long long r)
{
    long long x = v[p],
              y = v[(r-p)/2+p],
              z = v[r-1],
              i = p-1,
              j = r,
              aux;

    if(y > x && y < z || y > z && y < x) x = y;
    else if (z > x && z < y || z > y && z < x) x = z;
    while (1)
    {
        do
        {
            j--;
        }
        while (v[j] > x);

        do
        {
            i++;
        }
        while (v[i] < x);
        if (i < j) {
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
        else return j + 1;
    }
}


void quickSort ( vector <long long> &v, long long l, long long r)
{
    long long piv;
    if (r - l >= 2)
    {
        piv = mediana3(v,l , r);
        quickSort(v, l, piv);
        quickSort(v, piv, r);
    }
}


void radixSort (vector <long long> &v, long long l, long long r)  //radix cu baza 2^8
{

    queue <long long> c[256];
    long long maxi = v[l],
              i,
              j,
              putere = 0,
              stop = 1 << 56,
              t;
    for (i = l + 1; i <= r; i++)
        if (v[i] > maxi)
            maxi = v[i];

    if (maxi >= stop)
        putere = 64;
    else
        while (maxi >= 1 << putere)
            putere += 8;

    for (j = 0; j < putere; j += 8)
    {
        for (i = l; i <= r; i++)
            c[(v[i] >> j) & 255].push(v[i]);
        t = l;
        for (i = 0; i < 256; i++)
            while (!c[i].empty())
            {
                v[t] = c[i].front();
                t++;
                c[i].pop();
            }
    }
}

void generare(vector<long long> &v, long long nr_numere, long long nr_maxim)
{
        random_device rd;
    mt19937::result_type seed = rd() ^ (
            (mt19937::result_type)
            chrono::duration_cast<chrono::seconds>(
                chrono::system_clock::now().time_since_epoch()
                ).count() +
            (mt19937::result_type)
            chrono::duration_cast<chrono::microseconds>(
                chrono::high_resolution_clock::now().time_since_epoch()
                ).count() );

    mt19937 gen(seed);
    uniform_int_distribution<unsigned> distrib(0, nr_maxim);

    for( unsigned long j = 0; j < nr_numere; ++j )
    {
        v.push_back(distrib(gen));
    }
}

void vecConstant (vector <long long> &v, long long nr_numere, long long numar)
{
    long long i;
    for (i = 0; i < nr_numere; i++)
        v.push_back(numar);
}



int main()
{
    long long n, nr_max;
    vector <long long> vec;

    cout<<"TESTUL 1"<<endl;

    cout<<"n = 10, numarul maxim = 9"<<endl;
    n = 10;
    nr_max = n - 1;

    generare(vec, n, nr_max);
    cout<<"BubbleSort se realizeaza in ";

    auto start = high_resolution_clock::now();
    BubbleSort(vec);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    cout<<duration.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"CountSort se realizeaza in ";

    auto start1 = high_resolution_clock::now();
    CountSort(vec, n, n-1);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1-start1);
    cout<<duration1.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"MergeSort se realizeaza in ";

    auto start2 = high_resolution_clock::now();
    MergeSort(vec, 0, n);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2-start2);
    cout<<duration2.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"QuickSort se realizeaza in ";

    auto start3 = high_resolution_clock::now();
    quickSort(vec, 0, n);
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3-start3);
    cout<<duration3.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"RadixSort se realizeaza in ";

    auto start4 = high_resolution_clock::now();
    radixSort(vec, 0, n);
    auto stop4 = high_resolution_clock::now();
    auto duration4 = duration_cast<microseconds>(stop4-start4);
    cout<<duration4.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec,n,nr_max);

    cout<<"STL sort se realizeaza in ";

    auto start51 = high_resolution_clock::now();
    sort(vec.begin(), vec.end());
    auto stop51 = high_resolution_clock::now();
    auto duration51 = duration_cast<microseconds>(stop51-start51);
    cout<<duration51.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);
    vec.clear();
    cout<<endl<<endl;
    cout<<"*****************************"<<endl<<endl;

    cout<<"TESTUL 2"<<endl;


    cout<<"n = 100, numarul maxim = 99"<<endl;
    n = 100;
    nr_max = n - 1;

    generare(vec, n, nr_max);

    cout<<"BubbleSort se realizeaza in ";

    auto start5 = high_resolution_clock::now();
    BubbleSort(vec);
    auto stop5 = high_resolution_clock::now();
    auto duration5 = duration_cast<microseconds>(stop5-start5);
    cout<<duration5.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"CountSort se realizeaza in ";

    auto start6 = high_resolution_clock::now();
    CountSort(vec, n, n-1);
    auto stop6 = high_resolution_clock::now();
    auto duration6 = duration_cast<microseconds>(stop6-start6);
    cout<<duration6.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"MergeSort se realizeaza in ";

    auto start7 = high_resolution_clock::now();
    MergeSort(vec, 0, n);
    auto stop7 = high_resolution_clock::now();
    auto duration7 = duration_cast<microseconds>(stop7-start7);
    cout<<duration7.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"QuickSort se realizeaza in ";

    auto start8 = high_resolution_clock::now();
    quickSort(vec, 0, n);
    auto stop8 = high_resolution_clock::now();
    auto duration8 = duration_cast<microseconds>(stop8-start8);
    cout<<duration8.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"RadixSort se realizeaza in ";

    auto start9 = high_resolution_clock::now();
    radixSort(vec, 0, n);
    auto stop9 = high_resolution_clock::now();
    auto duration9 = duration_cast<microseconds>(stop9-start9);
    cout<<duration9.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec,n,nr_max);

    cout<<"STL sort se realizeaza in ";

    auto start50 = high_resolution_clock::now();
    sort(vec.begin(), vec.end());
    auto stop50 = high_resolution_clock::now();
    auto duration50 = duration_cast<microseconds>(stop50-start50);
    cout<<duration50.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);
    vec.clear();
    cout<<endl<<endl;
        cout<<"*****************************"<<endl<<endl;

    cout<<"TESTUL 3"<<endl;

    cout<<"n = 1000, numarul maxim = 999"<<endl;
    n = 1000;
    nr_max = n - 1;

    generare(vec, n, nr_max);

    cout<<"BubbleSort se realizeaza in ";

    auto start10 = high_resolution_clock::now();
    BubbleSort(vec);
    auto stop10 = high_resolution_clock::now();
    auto duration10 = duration_cast<microseconds>(stop10-start10);
    cout<<duration10.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"CountSort se realizeaza in ";

    auto start11 = high_resolution_clock::now();
    CountSort(vec, n, n-1);
    auto stop11 = high_resolution_clock::now();
    auto duration11 = duration_cast<microseconds>(stop11-start11);
    cout<<duration11.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"MergeSort se realizeaza in ";

    auto start12 = high_resolution_clock::now();
    MergeSort(vec, 0, n);
    auto stop12 = high_resolution_clock::now();
    auto duration12 = duration_cast<microseconds>(stop12-start12);
    cout<<duration12.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"QuickSort se realizeaza in ";

    auto start13 = high_resolution_clock::now();
    quickSort(vec, 0, n);
    auto stop13 = high_resolution_clock::now();
    auto duration13 = duration_cast<microseconds>(stop13-start13);
    cout<<duration13.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"RadixSort se realizeaza in ";

    auto start14 = high_resolution_clock::now();
    radixSort(vec, 0, n);
    auto stop14 = high_resolution_clock::now();
    auto duration14 = duration_cast<microseconds>(stop14-start14);
    cout<<duration14.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec,n,nr_max);

    cout<<"STL sort se realizeaza in ";

    auto start49 = high_resolution_clock::now();
    sort(vec.begin(), vec.end());
    auto stop49 = high_resolution_clock::now();
    auto duration49 = duration_cast<microseconds>(stop49-start49);
    cout<<duration49.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);
    vec.clear();
    cout<<endl<<endl;
            cout<<"*****************************"<<endl<<endl;

    cout<<"TESTUL 4"<<endl;

    cout<<"n = 10000, numarul maxim = 9999"<<endl;
    n = 10000;
    nr_max = n-1;

    generare(vec, n, nr_max);

    cout<<"BubbleSort se realizeaza in ";

    auto start15 = high_resolution_clock::now();
    BubbleSort(vec);
    auto stop15 = high_resolution_clock::now();
    auto duration15 = duration_cast<microseconds>(stop15-start15);
    cout<<duration15.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"CountSort se realizeaza in ";

    auto start16 = high_resolution_clock::now();
    CountSort(vec, n, n-1);
    auto stop16 = high_resolution_clock::now();
    auto duration16 = duration_cast<microseconds>(stop16-start16);
    cout<<duration16.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"MergeSort se realizeaza in ";

    auto start17 = high_resolution_clock::now();
    MergeSort(vec, 0, n);
    auto stop17 = high_resolution_clock::now();
    auto duration17 = duration_cast<microseconds>(stop17-start17);
    cout<<duration17.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"QuickSort se realizeaza in ";

    auto start18 = high_resolution_clock::now();
    quickSort(vec, 0, n);
    auto stop18 = high_resolution_clock::now();
    auto duration18 = duration_cast<microseconds>(stop18-start18);
    cout<<duration18.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"RadixSort se realizeaza in ";

    auto start19 = high_resolution_clock::now();
    radixSort(vec, 0, n);
    auto stop19 = high_resolution_clock::now();
    auto duration19 = duration_cast<microseconds>(stop19-start19);
    cout<<duration19.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec,n,nr_max);

    cout<<"STL sort se realizeaza in ";

    auto start48 = high_resolution_clock::now();
    sort(vec.begin(), vec.end());
    auto stop48 = high_resolution_clock::now();
    auto duration48 = duration_cast<microseconds>(stop48-start48);
    cout<<duration48.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);
    vec.clear();
    cout<<endl<<endl;
                cout<<"*****************************"<<endl<<endl;

    cout<<"TESTUL 5"<<endl;


    cout<<"n = 10^5, numarul maxim = 10^5-1"<<endl;
    n = 100000;
    nr_max = n-1;

    generare(vec, n, nr_max);

    cout<<"BubbleSort se realizeaza in ";

    auto start20 = high_resolution_clock::now();
    BubbleSort(vec);
    auto stop20 = high_resolution_clock::now();
    auto duration20 = duration_cast<microseconds>(stop20-start20);
    cout<<duration20.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"CountSort se realizeaza in ";

    auto start21 = high_resolution_clock::now();
    CountSort(vec, n, n-1);
    auto stop21 = high_resolution_clock::now();
    auto duration21 = duration_cast<microseconds>(stop21-start21);
    cout<<duration21.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"MergeSort se realizeaza in ";

    auto start22 = high_resolution_clock::now();
    MergeSort(vec, 0, n);
    auto stop22 = high_resolution_clock::now();
    auto duration22 = duration_cast<microseconds>(stop22-start22);
    cout<<duration22.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"QuickSort se realizeaza in ";

    auto start23 = high_resolution_clock::now();
    quickSort(vec, 0, n);
    auto stop23 = high_resolution_clock::now();
    auto duration23 = duration_cast<microseconds>(stop23-start23);
    cout<<duration23.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"RadixSort se realizeaza in ";

    auto start24 = high_resolution_clock::now();
    radixSort(vec, 0, n);
    auto stop24 = high_resolution_clock::now();
    auto duration24 = duration_cast<microseconds>(stop24-start24);
    cout<<duration24.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec,n,nr_max);

    cout<<"STL sort se realizeaza in ";

    auto start47 = high_resolution_clock::now();
    sort(vec.begin(), vec.end());
    auto stop47 = high_resolution_clock::now();
    auto duration47 = duration_cast<microseconds>(stop47-start47);
    cout<<duration47.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);
    vec.clear();
    cout<<endl<<endl;
                    cout<<"*****************************"<<endl<<endl;

    cout<<"TESTUL 6"<<endl;

    cout<<"n = 10^6, numarul maxim = 10^6-1"<<endl;
    n = 1000000;
    nr_max = n - 1;

    cout<<"BubbleSort nu poate sorta atatea numere intr-un timp rezonabil.";

    cout<<endl<<endl;

    generare(vec, n, nr_max);

    cout<<"CountSort se realizeaza in ";

    auto start25 = high_resolution_clock::now();
    CountSort(vec, n, n-1);
    auto stop25 = high_resolution_clock::now();
    auto duration25 = duration_cast<microseconds>(stop25-start25);
    cout<<duration25.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"MergeSort se realizeaza in ";

    auto start26 = high_resolution_clock::now();
    MergeSort(vec, 0, n);
    auto stop26 = high_resolution_clock::now();
    auto duration26 = duration_cast<microseconds>(stop26-start26);
    cout<<duration26.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"QuickSort se realizeaza in ";

    auto start27 = high_resolution_clock::now();
    quickSort(vec, 0, n);
    auto stop27 = high_resolution_clock::now();
    auto duration27 = duration_cast<microseconds>(stop27-start27);
    cout<<duration27.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"RadixSort se realizeaza in ";

    auto start28 = high_resolution_clock::now();
    radixSort(vec, 0, n);
    auto stop28 = high_resolution_clock::now();
    auto duration28 = duration_cast<microseconds>(stop28-start28);
    cout<<duration28.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec,n,nr_max);

    cout<<"STL sort se realizeaza in ";

    auto start46 = high_resolution_clock::now();
    sort(vec.begin(), vec.end());
    auto stop46 = high_resolution_clock::now();
    auto duration46 = duration_cast<microseconds>(stop46-start46);
    cout<<duration46.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);
    vec.clear();
    cout<<endl<<endl;
                        cout<<"*****************************"<<endl<<endl;

    cout<<"TESTUL 7"<<endl;

    cout<<"n = 10^7, numarul maxim = 10^7-1"<<endl;
    n = 10000000;
    nr_max = n - 1;

    cout<<"BubbleSort nu poate sorta atatea numere intr-un timp rezonabil.";

    cout<<endl<<endl;

    generare(vec, n, nr_max);

    cout<<"CountSort se realizeaza in ";

    auto start29 = high_resolution_clock::now();
    CountSort(vec, n, n-1);
    auto stop29 = high_resolution_clock::now();
    auto duration29 = duration_cast<microseconds>(stop29-start29);
    cout<<duration29.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"MergeSort se realizeaza in ";

    auto start30 = high_resolution_clock::now();
    MergeSort(vec, 0, n);
    auto stop30 = high_resolution_clock::now();
    auto duration30 = duration_cast<microseconds>(stop30-start30);
    cout<<duration30.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"QuickSort se realizeaza in ";

    auto start31 = high_resolution_clock::now();
    quickSort(vec, 0, n);
    auto stop31 = high_resolution_clock::now();
    auto duration31 = duration_cast<microseconds>(stop31-start31);
    cout<<duration31.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"RadixSort se realizeaza in ";

    auto start32 = high_resolution_clock::now();
    radixSort(vec, 0, n);
    auto stop32 = high_resolution_clock::now();
    auto duration32 = duration_cast<microseconds>(stop32-start32);
    cout<<duration32.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec,n,nr_max);

    cout<<"STL sort se realizeaza in ";

    auto start45 = high_resolution_clock::now();
    sort(vec.begin(), vec.end());
    auto stop45 = high_resolution_clock::now();
    auto duration45 = duration_cast<microseconds>(stop45-start45);
    cout<<duration45.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);
    vec.clear();
    cout<<endl<<endl;
                            cout<<"*****************************"<<endl<<endl;

    cout<<"TESTUL 8"<<endl;

    cout<<"n = 10^3, numarul maxim = 10^5-1"<<endl;
    n = 1000;
    nr_max = 99999;

    generare(vec, n, nr_max);

    cout<<"BubbleSort se realizeaza in ";

    auto start33 = high_resolution_clock::now();
    BubbleSort(vec);
    auto stop33 = high_resolution_clock::now();
    auto duration33 = duration_cast<microseconds>(stop33-start33);
    cout<<duration33.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"CountSort se realizeaza in ";

    auto start34 = high_resolution_clock::now();
    CountSort(vec, n, 99999);
    auto stop34 = high_resolution_clock::now();
    auto duration34 = duration_cast<microseconds>(stop34-start34);
    cout<<duration34.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"MergeSort se realizeaza in ";

    auto start35 = high_resolution_clock::now();
    MergeSort(vec, 0, n);
    auto stop35 = high_resolution_clock::now();
    auto duration35 = duration_cast<microseconds>(stop35-start35);
    cout<<duration35.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"QuickSort se realizeaza in ";

    auto start36 = high_resolution_clock::now();
    quickSort(vec, 0, n);
    auto stop36 = high_resolution_clock::now();
    auto duration36 = duration_cast<microseconds>(stop36-start36);
    cout<<duration36.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"RadixSort se realizeaza in ";

    auto start37 = high_resolution_clock::now();
    radixSort(vec, 0, n);
    auto stop37 = high_resolution_clock::now();
    auto duration37 = duration_cast<microseconds>(stop37-start37);
    cout<<duration37.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec,n,nr_max);

    cout<<"STL sort se realizeaza in ";

    auto start44 = high_resolution_clock::now();
    sort(vec.begin(), vec.end());
    auto stop44 = high_resolution_clock::now();
    auto duration44 = duration_cast<microseconds>(stop44-start44);
    cout<<duration44.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);
    vec.clear();
    cout<<endl<<endl;
                                cout<<"*****************************"<<endl<<endl;

    cout<<"TESTUL 9"<<endl;

    cout<<"n = 10^2, numarul maxim = 10^8"<<endl;
    n = 100;
    nr_max = 99999999;

    generare(vec, n, nr_max);

    cout<<"BubbleSort se realizeaza in ";

    auto start38 = high_resolution_clock::now();
    BubbleSort(vec);
    auto stop38 = high_resolution_clock::now();
    auto duration38 = duration_cast<microseconds>(stop38-start38);
    cout<<duration38.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"CountSort se realizeaza in ";

    auto start39 = high_resolution_clock::now();
    CountSort(vec, n, 100000000);
    auto stop39 = high_resolution_clock::now();
    auto duration39 = duration_cast<microseconds>(stop39-start39);
    cout<<duration39.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"MergeSort se realizeaza in ";

    auto start40 = high_resolution_clock::now();
    MergeSort(vec, 0, n);
    auto stop40 = high_resolution_clock::now();
    auto duration40 = duration_cast<microseconds>(stop40-start40);
    cout<<duration40.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"QuickSort se realizeaza in ";

    auto start41 = high_resolution_clock::now();
    quickSort(vec, 0, n);
    auto stop41 = high_resolution_clock::now();
    auto duration41 = duration_cast<microseconds>(stop41-start41);
    cout<<duration41.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec, n, nr_max);

    cout<<"RadixSort se realizeaza in ";

    auto start42 = high_resolution_clock::now();
    radixSort(vec, 0, n);
    auto stop42 = high_resolution_clock::now();
    auto duration42 = duration_cast<microseconds>(stop42-start42);
    cout<<duration42.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    generare(vec,n,nr_max);

    cout<<"STL sort se realizeaza in ";

    auto start43 = high_resolution_clock::now();
    sort(vec.begin(), vec.end());
    auto stop43 = high_resolution_clock::now();
    auto duration43 = duration_cast<microseconds>(stop43-start43);
    cout<<duration43.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);
    cout<<"*****************************"<<endl<<endl;
    vec.clear();
    cout<<endl<<endl;
    cout<<"TESTUL 10"<<endl;
    cout<<"Vector constant, n = 10^5, numarul = 33"<<endl;
    n = 100000;
    nr_max = 33;
    vecConstant(vec, n, nr_max);

    cout<<"BubbleSort se realizeaza in ";

    auto start52 = high_resolution_clock::now();
    BubbleSort(vec);
    auto stop52 = high_resolution_clock::now();
    auto duration52 = duration_cast<microseconds>(stop52-start52);
    cout<<duration52.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    vecConstant(vec, n, nr_max);

    cout<<"CountSort se realizeaza in ";

    auto start53 = high_resolution_clock::now();
    CountSort(vec, n, nr_max);
    auto stop53 = high_resolution_clock::now();
    auto duration53 = duration_cast<microseconds>(stop53-start53);
    cout<<duration53.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    vecConstant(vec, n, nr_max);

    cout<<"MergeSort se realizeaza in ";

    auto start54 = high_resolution_clock::now();
    MergeSort(vec, 0, n);
    auto stop54 = high_resolution_clock::now();
    auto duration54 = duration_cast<microseconds>(stop54-start54);
    cout<<duration54.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    vecConstant(vec, n, nr_max);

    cout<<"QuickSort se realizeaza in ";

    auto start55 = high_resolution_clock::now();
    quickSort(vec, 0, n);
    auto stop55 = high_resolution_clock::now();
    auto duration55 = duration_cast<microseconds>(stop55-start55);
    cout<<duration55.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    vecConstant(vec, n, nr_max);

    cout<<"RadixSort se realizeaza in ";

    auto start56 = high_resolution_clock::now();
    radixSort(vec, 0, n);
    auto stop56 = high_resolution_clock::now();
    auto duration56 = duration_cast<microseconds>(stop56-start56);
    cout<<duration56.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();

    vecConstant(vec, n, nr_max);

    cout<<"STL Sort se realizeaza in ";

    auto start57 = high_resolution_clock::now();
    sort(vec.begin(), vec.end());
    auto stop57 = high_resolution_clock::now();
    auto duration57 = duration_cast<microseconds>(stop57-start57);
    cout<<duration57.count()/1000000.000000000000<<" secunde " <<endl;

    test(vec);

    cout<<endl<<endl;

    vec.clear();


    return 0;
}

