#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

struct coordinate
{
    long long int x;
    long long int y;
};

int n, order[12], ans = 0;
coordinate coordinates[12];
map<long long int, int> yandnum;

void recursion(int count, int num1, int num2, bool used[]);
bool check();

int main() {
    cout << "Waiting for inputs ..." << endl;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> coordinates[i].x >> coordinates[i].y;
        yandnum[coordinates[i].y]++;
    }

    bool used[12];
    for (int i = 0; i < 12; i++) {
        used[i] = false;
    }

    for (int i = 1; i < n; i++) {
        recursion(0, 0, i, used);
    }
    cout << ans << endl;

    return 0;
}

void recursion(int count, int num1, int num2, bool used[]) {
    order[count] = num1;
    order[count + 1] = num2;

    if (count + 2 == n) {
        if (check() == true) {
            ans++;
        }
        return;
    }

    used[num1] = true;
    used[num2] = true;

    for (int i = num1 + 1; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (used[i] == false && used[j] == false) {
                if (i > num1) {
                    recursion(count + 2, i, j, used);
                }
            }
        }
    }

    used[num1] = false;
    used[num2] = false;
}

bool check() {
    int visited[12];
    coordinate cur;
    int curi;

    for (int i = 0; i < 12; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        bool escape = false;
        cur = coordinates[i];
        curi = i;

        while (escape == false) {
            visited[curi]++;
            int realindex = i;

            for (int j = 0; j < n; j++) {
                if (curi == order[j]) {
                    realindex = j;
                }
            }

            if (realindex % 2 == 0) {
                cur = coordinates[order[realindex + 1]];
                curi = order[realindex + 1];
            } else {
                cur = coordinates[order[realindex - 1]];
                curi = order[realindex - 1];
            }

            visited[curi]++;

            if (yandnum[cur.y] >= 2) { 
                // guards against wormhole between wormhole pair
                long long int minx = 1000000001;
                int index = -1;
                for (int j = 0; j < n; j++) {
                    if (coordinates[j].y == cur.y) {
                        if (coordinates[j].x > cur.x && coordinates[j].x < minx) {
                            minx = coordinates[j].x;
                            index = j;
                        }
                    }
                }

                if (index == -1) {
                    escape = true;
                    break;
                } else {
                    cur = coordinates[index];
                    curi = index;
                }

                if (visited[curi] >= 2) {
                    return true;
                }
            } else {
                escape = true;
            }
        }

        for (int j = 0; j < n; j++) {
            visited[j] = 0;
        }
    }

    return false;
}