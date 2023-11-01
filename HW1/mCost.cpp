#include <iostream>

using namespace std;

int l[100000], r[100000], proceeding = 0;
int calculateCost (int a[], int start, int end) {
    if (start == end) return 0;
    
    int mean, lastProceedingM=0, numberOfLeftOne=0, numberOfRightZero=0;
    mean = (start + end) / 2;
    for (int i = start-1; i <= mean-1; i++) {
        if (a[i] == 1) numberOfLeftOne++;
    }
    for (int i = mean; i <= end-1; i++) {
        if (a[i] == 0) numberOfRightZero++;
    }
    if (numberOfRightZero != 0 && numberOfLeftOne != 0) {
        lastProceedingM = numberOfLeftOne + numberOfRightZero;
        l[proceeding] = mean - numberOfLeftOne + 1;
        r[proceeding] = mean + numberOfRightZero;
        proceeding++;
    }
    return calculateCost(a, start, mean) + calculateCost(a, mean+1, end) + lastProceedingM;
}
int main()
{
    int n, cost, a[100000];
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    cost = calculateCost(a, 1, n);
    
    if (cost > 20*n) {
        cout << -1;
    } else {
       cout << proceeding << endl;
       for (int i = proceeding-1; i >= 0; i--) {
           cout << l[i] << "\t" << r[i] << endl;
       }
    }
    
    return 0;
}
