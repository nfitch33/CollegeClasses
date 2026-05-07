// This is my array version of the project

#include <bits/stdc++.h>
using namespace std;

int beginner = - 1;

void path(int current, vector<int> beginners, vector<string> cities){
    if(current == beginner){
        return;
    }
    path(beginners[current], beginners, cities);
    cout << cities.at(current) << " ";
}
void solution(vector<int> distance, vector<int> beginners, vector<string> cities){
    int last = distance.size() - 1;
    path(last, beginners, cities);
    cout << distance[last];
}
void dijkstra(vector<vector<int>> matrix, int start, vector<string> cities){
    int num = matrix[0].size();
    vector<int> minimum(num);
    vector<bool> add(num);
    for(int i = 0; i < num; i++){
        minimum[i] = INT_MAX;
        add[i] = false;
    }
    minimum[start] = 0;
    vector<int> beginners(num);
    beginners[start] = beginner;
    for(int i = 1; i < num; i++){
        int closest = -1;
        int min = INT_MAX;
        for(int i = 0; i < num; i++){
            if(!add[i] && minimum[i] < min){
                closest = i;
                min = minimum[i];
            }
        }
        add[closest] = true;
        for(int i = 0; i < num; i++){
            int distance = matrix[closest][i];
            if(distance > 0 && ((min + distance) < minimum[i])){
                beginners[i] = closest;
                minimum[i] = min + distance;
            }
        }
    }
    solution(minimum, beginners, cities);
}
int main(){
    int x;
    cin >> x;
    for(int i = 0; i < x; i++){
        int y;
        cin >> y;
        cin >> ws;
        vector<vector<int>> matrix;
        matrix.resize(y);
        vector<string> cities;
        for(int j = 0; j < y; j++){
            string tmp;
            getline(cin, tmp);
            cities.push_back(tmp);
        }
        for(int j = 0; j < y; j++){
            for(int k = 0; k < y; k++){
                int z;
                cin >> z;
                matrix[j].push_back(z);
            }
        }
        dijkstra(matrix, 0, cities);
        cout << endl;
    }
    return 0;
}