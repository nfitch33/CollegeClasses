// This is my heap version of the project

#include <bits/stdc++.h>
using namespace std;

int beginner = - 1;
typedef pair<int, int> cord;
void path(int current, cord beginners[], vector<string> cities){
    if(current == beginner){
        return;
    }
    path(beginners[current].second, beginners, cities);
    cout << cities.at(current) << " ";
}
void solution(int size, cord distance[], vector<string> cities){
    int last = size - 1;
    path(last, distance, cities);
    cout << distance[last].first;
}
void dijkstra(vector<vector<int>> matrix, int start, vector<string> cities){
    int num = matrix[0].size();
    priority_queue<cord, vector<cord>, greater<cord>> heap;
    cord distance[num];
    for(int i = 0; i < num; i++){
        distance[i] = make_pair(INT_MAX, beginner);
    }
    heap.push(make_pair(0, start));
    distance[start] = make_pair(0, beginner);
    while(!heap.empty()){
        int x = heap.top().second;
        heap.pop();
        for(int i = 0; i < num; i++){
            int distances = matrix[x][i];
            if(distances > 0 && ((distance[x].first + distances) < distance[i].first)){
                distance[i] = make_pair((distance[x].first + distances), x);
                heap.push(make_pair(distance[i].first, i));
            }
        }
    }
    solution(num, distance, cities);
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