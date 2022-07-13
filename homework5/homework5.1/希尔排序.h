#pragma once

int Shell_swap = 0;
int Shell_com = 0;

void SSwap(int& a, int& b)
{
    int t = a;
    a = b;
    b = t;
    Shell_swap++;
}


void ShellSort(int *arry,int len) 
{
    for (int gap = len / 2; gap > 0; gap /= 2) 
    {
        for (int i = gap; i < len; i++) 
        {
            int j = i;
            while (j - gap >= 0 && arry[j] < arry[j - gap]) 
            {
                Shell_com++;
                SSwap(arry[j], arry[j - gap]);
                j -= gap;
            }
            Shell_com++;
        }
    }


    ////´òÓ¡½á¹û
    //cout << "ShellSort: " << endl;
    //for (int i = 0; i < len; i++)
    //{
    //    cout << arry[i] << " ";
    //}
    //cout << endl << endl;
}





void ShellCount(int& a, int& b)
{
    a = Shell_swap;
    b = Shell_com;
    cout << "ShellCount:" << endl;
    cout << "Swap: " << a << endl;
    cout << "Compare: " << b << endl << endl;
}
