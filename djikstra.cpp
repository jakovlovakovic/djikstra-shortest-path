#include <iostream>
#include <math.h>
#include <cstdint>
#include <vector>
#include <list>

using namespace std;

uint64_t betterPow(uint64_t a, uint64_t b) {
    uint64_t res = 1;
    for(int i = 0; i < b; i++) {
        res = res * a;
    }
    return res;
}

uint64_t f(int a, int b, int c, int i, int j) {
    if(i < j) swap(i, j);
    uint64_t op1 = (i - j) % c;
    uint64_t op2 = betterPow(a, op1);
    uint64_t op3 = b * betterPow(i - j, 2);
    return op2 + op3 - 1;
}

uint64_t djikstra(vector<vector<uint64_t>>& arr, int n, int k, int l) {
    vector<bool> found; vector<int> prev; vector<uint64_t> distance;
    list<int> q;
    for(int i = 0; i < n; i++) {
        found.push_back(false);
        prev.push_back(-1);
        distance.push_back(numeric_limits<uint64_t>::max());
        q.push_back(i);
    }
    distance[k] = 0;
    while(!q.empty()) {
        int min; bool flag = true;
        for (int i : q) {
            if(flag) {
                min = i;
                flag = false;
            }
            if(distance[i] < distance[min]) min = i;
        }
        found[min] = true;
        q.remove(min);
        for(int i = 0; i < n; i++) {
            if(i != min && found[i] == false) {
                uint64_t alt = distance[min] + arr[min][i];
                if(alt < distance[i]) {
                    distance[i] = alt;
                    prev[i] = min;
                }
            }
        }
    }
    return distance[l];
}

int main(void) {
    int n, a, b, c, k, l;
    cout << "Unesite prirodan broj n: "; cin >> n; cout << endl;
    cout << "Unesite prirodan broj a: "; cin >> a; cout << endl;
    cout << "Unesite prirodan broj b: "; cin >> b; cout << endl;
    cout << "Unesite prirodan broj c: "; cin >> c; cout << endl;
    cout << "Unesite vrh k: "; cin >> k; cout << endl;
    cout << "Unesite vrh l: "; cin >> l; cout << endl;
    vector<vector<uint64_t>> arr;
    for(int i = 0; i < n ; i++) {
        vector<uint64_t> row;
        for(int j = 0; j < n ; j++) {
            row.push_back(f(a, b, c, i, j));
        }
        arr.push_back(row);
    }
    cout << "Udaljenost vrhova k i l je " << djikstra(arr, n, k, l);
    return 0;
}