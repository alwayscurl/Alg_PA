#include <iostream>
#include <fstream>
#include <vector>
//#include <algorithm>
using namespace std;

void output_chord_endpoint(int i, int k, int &node_num, int** &chosen_chord, vector<vector<int>>& chosen_chord_endpoint){
    if(i >= k){
        return;
    }
    int j = chosen_chord[i][node_num-k-1];
    if(j != -1){
        //cout << "pushback i:" << i << " j:" << j << endl;
        chosen_chord_endpoint.push_back({i, j});
        output_chord_endpoint(i+1, j-1, node_num, chosen_chord, chosen_chord_endpoint);
        output_chord_endpoint(j+1, k, node_num, chosen_chord, chosen_chord_endpoint);
    }
    else{
        output_chord_endpoint(i+1, k, node_num, chosen_chord, chosen_chord_endpoint);
    }
}

int Maximum_chords(int i, int k, int &node_num, int* chord_endpoint, int** &max_subchordnum, int** &chosen_chord){
    if(i > k){
        return 0;
    }
    if(max_subchordnum[i][node_num-1-k] != -1){
        return max_subchordnum[i][node_num-1-k];
    }   //have calculated data

    /*
    if(i == k){
        max_subchordnum[i][node_num-1-k] = 0;
        return 0;
    }
    */
    
    if(chord_endpoint[i] < i){
        max_subchordnum[i][node_num-1-k] = Maximum_chords(i+1, k, node_num, chord_endpoint, max_subchordnum, chosen_chord);
        return max_subchordnum[i][node_num-1-k];
    }
    int j = chord_endpoint[i];
    //cout << "j:" << j << endl;
    if(j > k){
        max_subchordnum[i][node_num-1-k] = Maximum_chords(i+1, k, node_num, chord_endpoint, max_subchordnum, chosen_chord);
    }
    else if(j == k){
        max_subchordnum[i][node_num-1-k] = 1 + Maximum_chords(i+1, j-1, node_num, chord_endpoint, max_subchordnum, chosen_chord);
        chosen_chord[i][node_num-k-1] = j;
    }
    else{
        if(Maximum_chords(i+1, j-1, node_num, chord_endpoint, max_subchordnum, chosen_chord) + Maximum_chords(j+1, k, node_num, chord_endpoint, max_subchordnum, chosen_chord)+ 1 > 
        Maximum_chords(i+1, k, node_num, chord_endpoint, max_subchordnum, chosen_chord)){
            max_subchordnum[i][node_num-1-k] = Maximum_chords(i+1, j-1, node_num, chord_endpoint, max_subchordnum, chosen_chord) + Maximum_chords(j+1, k, node_num, chord_endpoint, max_subchordnum, chosen_chord)+ 1;
            chosen_chord[i][node_num-k-1] = j;
            //cout << "chosen_chord i, k, node_num-k-1:" << i << "," << k << "," << node_num-k-1 << " j:" << j << endl;
        }
        else{
            max_subchordnum[i][node_num-1-k] = Maximum_chords(i+1, k, node_num, chord_endpoint, max_subchordnum, chosen_chord);
        }
    }
    //cout << "i:" << i << " k:" << k << " return value:" << max_subchordnum[i][k] << endl;
    return max_subchordnum[i][node_num-1-k];
}


void Maximum_planar_subset(int &node_num, int* chord_endpoint, int** max_subchordnum, int** chosen_chord, int& max_chord_num){
    max_chord_num = Maximum_chords(0, node_num-1, node_num, chord_endpoint, max_subchordnum, chosen_chord);
}


int main(int argc, char* argv[]){
    
    if(argc != 3){
        cout << "error input" << endl;
        return 0;
    }

    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    //input
    int endpoint1, endpoint2;
    int node_num;
    //unordered_map<int, int> chord_endpoint;

    fin >> node_num;
    int* chord_endpoint = new int[node_num];
    for(int i=0;i<node_num/2;i++){
        fin >> endpoint1 >> endpoint2;
        //if(endpoint1 < endpoint2){
        chord_endpoint[endpoint1] = endpoint2;
            //cout << chord_endpoint[endpoint1] << endl;
        //}
        //else{
        chord_endpoint[endpoint2] = endpoint1;
            //cout << chord_endpoint[endpoint2] << endl;
        //}
    }

    //DP table
    int** max_subchordnum = new int* [node_num];
    for(int i=0;i<node_num;i++){
        max_subchordnum[i] = new int[node_num-i]();
        for (int j=0;j<node_num-i-1;j++){
            max_subchordnum[i][j] = -1;
        }
    }
    int** chosen_chord = new int* [node_num-1];
    for(int i=0;i<node_num-1;i++){
        chosen_chord[i] = new int[node_num-i-1]();
        for (int j=0;j<node_num-i-1;j++){
            chosen_chord[i][j] = -1;
        }
    }
    
    //output
    int max_chord_num;   //maximum number of chords

    Maximum_planar_subset(node_num, chord_endpoint, max_subchordnum, chosen_chord, max_chord_num);
    cout << "max_chord_num: " << max_chord_num << endl;

    vector<vector<int>> chosen_chord_endpoint(0, vector<int>(2, -1));   //output node of chosen chord
    
    output_chord_endpoint(0, node_num-1, node_num, chosen_chord, chosen_chord_endpoint);

    delete [] max_subchordnum;
    delete [] chosen_chord;
    fout << max_chord_num << endl;
    for(int i=0;i<max_chord_num;i++){
        fout << chosen_chord_endpoint[i][0] << " " << chosen_chord_endpoint[i][1] << endl;
    }
    fin.close();
    fout.close();
    return 0;
}