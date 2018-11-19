#include<iostream>
#include<string>
#include<fstream>
#include<math.h>
#include<bits/stdc++.h>
//transpunere in caractere normale

using namespace std;
const int MAX_STATII=200;
const double R = 6373.0;
const double RADIANS=0.0174533;
int N;
double TIMP;
//Definire constante masina
// Viteza- 50km/h
//Capacitatea bateriei in KWh- 100
//Capacitatea bateriei in km- 570
//Capacitatea bateriei in minute- 684
//Capacitatea bateriei in ore- 11.4
float viteza =50;
float cap_kwh=100;
float cap_kwh_consum = 0.175;
float cap_km=570;
float cap_min=684;
float cap_ore=11.4;

ofstream debugout("debug.txt");

//Definire statie de incarcare proprietati
//Rata de incarcare 50 kW/h
//Rata de incarcare 0.83 kW/min
float charging_rate_ore=50;
float charging_rate_min=0.83;

struct oras{
    string nume;
    double lat,lng;
}p,d,mij;

struct best_path{
        int nr_max_st;
        int nr_min_si;
        int timp; //minute
}b_p;
struct statie{
    int nr;
    string ID,tip,titlu,adresa;
    double lat,lng;
    //float charging_rate_min=
};

struct state{
    int nod;
    //statie curr;
    double battery;
    double time;
};
vector<state> Drum;
vector <statie>V;
double M_DIST[MAX_STATII][MAX_STATII];
double M_TIME[MAX_STATII][MAX_STATII];
double M_CONS[MAX_STATII][MAX_STATII];
bool vis[1000];
double distanta(double lat1, double lon1, double lat2, double lon2 ){


    lat1 = RADIANS * lat1;
    lon1 = RADIANS * lon1;
    lat2 = RADIANS * lat2;
    lon2 = RADIANS * lon2;

    double dlon = lon2 - lon1;
    double dlat = lat2 - lat1;

    double a = (sin(dlat / 2)*sin(dlat / 2)) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c;
}

void citire_fisier(){
    statie x;
    int nr;
    string ID,tip,titlu,adresa;
    double lat, lng;
    ifstream fin("data.txt");
    ifstream gin("user_parsed_input.txt");
    int k=0;
    getline(gin,titlu);
    gin>>lat>>lng;
    if(k==0){
            x.nr=0;
            x.ID="0000";
            x.tip="plecare";
            x.titlu=titlu;
        x.adresa="none";
        x.lat=lat;
        x.lng=lng;
        V.push_back(x);
        }
        //getline(gin,titlu);
        getline(gin,titlu);
        getline(gin,titlu);
        cout << titlu;
        gin >> lat>>lng;
        x.nr=1;
            x.ID="0001";
            x.tip="destinatie";

    x.titlu=titlu;
        x.adresa="none";
        x.lat=lat;
        x.lng=lng;
        V.push_back(x);
  
    gin>>TIMP;
    
    //cout << TIMP<<"-----------";

    mij.lat=(V[1].lat+V[0].lat)/2;
    mij.lng=(V[1].lng+V[0].lng)/2;
    double diametrul=distanta(V[0].lat,V[0].lng,V[1].lat,V[1].lng);
    double raza=diametrul/2;
    //cout<<diametrul<<endl;
    k=2;
    while(fin>>nr>>ID>>tip>>titlu>>adresa>>lat>>lng){
        x.nr=nr;
        x.ID=ID;
        x.tip=tip;
        x.titlu=titlu;
        x.adresa=adresa;
        x.lat=lat;
        x.lng=lng;
        double dist=distanta(x.lat,x.lng,mij.lat,mij.lng);
        //cout<<dist<<"  "<<x.titlu<<endl;
        if (dist<=(raza+5)){
               V.push_back(x);
            }
        k++;
        }
        N = V.size();
        N--;
        int i = 0;
        swap(V[1], V[V.size() - 1]);
        for(auto &x:V){
            x.nr = i++;
            //cout<<"Nr: "<<x.nr<<"   "<<" tip: "<<x.tip<<" titlu:  "<<x.titlu<<"  lat: "<<x.lat<<"  lng:"<<x.lng<<endl;
        }
        // for(auto x:V){
        //     cout<<"Nr: "<<x.nr<<"   "<<" tip: "<<x.tip<<" titlu:  "<<x.titlu<<"  lat: "<<x.lat<<"  lng:"<<x.lng<<endl;
        // }
    }

void matrice_distante(){
    for(int i=0;i<=N;i++)
        for(int j=0;j<=N;j++)
            if(i==j)
                M_DIST[i][i]=0;
            else{
                double dist=distanta(V[i].lat,V[i].lng,V[j].lat,V[j].lng);
                M_DIST[i][j]=dist;
                M_TIME[i][j] = double(1.0*dist)/viteza;
                M_CONS[i][j] = double(dist)*cap_kwh_consum;

            }
    // cout<<endl<<endl<<endl<<endl;
    // int j;
    // for(int i=0;i<N;i++){
    //     for(int j=0;j<N;j++){
    //         cout<<M_DIST[i][j]<<" ";
    //     }
    //     cout<<endl;
    //     }
    
}


vector<vector<state> > SOLUTIONS;

bool state_comparator(state a, state b){
    return a.nod > b.nod;
}

void calc_best_graph(state curr_state, double coef){
    // vis[curr_state.nod] = 1;
    // //vis[N] = 0;
    // Drum.push_back(curr_state);

    for(auto it:Drum){
            debugout << it.nod << " ";
            

        }
        debugout << "   nod == "<< curr_state.nod << " " <<vis[N];
        debugout << endl;
        
    if (Drum.back().nod == N ){
        //aici verifici solutia
        // for(auto it:Drum){
        //     cout << it.nod << " ";

        // }
        // cout << endl;
        vis[N] = 0;
        //V.pop_back();
        return ;
    }
    if (curr_state.battery <= coef*cap_kwh && abs(curr_state.time - TIMP) 
                > (cap_kwh - curr_state.battery)*viteza ) {
                    curr_state.time -= (cap_kwh - curr_state.battery)*viteza;
                    curr_state.battery = cap_kwh;
                    

    }
    for (int i = 0; i <= N;i++){
        
    //cout << i << " " << curr_state.time + M_TIME[curr_state.nod][i] << " " <<curr_state.battery - M_CONS[curr_state.nod][i]<<" ";
        if (!vis[i] && curr_state.time + M_TIME[curr_state.nod][i] <= TIMP 
            && curr_state.battery - M_CONS[curr_state.nod][i] >=0 ){
                state next_state;
                next_state.nod = i;
                next_state.time += M_TIME[curr_state.nod][i];
                next_state.battery -= M_CONS[curr_state.nod][i];
                Drum.push_back(next_state);
                vis[next_state.nod] = 1;
                if (next_state.nod == N){
                    debugout << "am gasit solutie" << endl;
                    //sort(Drum.begin(), Drum.end(), state_comparator);
                    if (Drum[0].nod == Drum[1].nod) Drum.erase(Drum.begin());
                    SOLUTIONS.push_back(Drum);
                }
                calc_best_graph(next_state, coef);
                Drum.pop_back();
                vis[next_state.nod] = 0;
            }
    }
    // Drum.pop_back();
    // vis[curr_state.nod] = 0;

}

int rate_solution(vector<state> v){
    int sum = 0;
    for(auto it:v) if (V[it.nod].tip == "attraction") sum += 5;
    //else sum-=2;
    return sum;
}

bool comp(vector<state> a, vector<state> b){
    return a.size() > b.size();
}
ofstream fout("final_output.txt");
int main(){

    citire_fisier();
    matrice_distante();
    for(double coef = 0.05; coef < 1;coef+=0.05){
        Drum.clear();
        memset(vis, 0, sizeof vis);
        state initial;
        initial.nod = 0;
        initial.time = 0;
        initial.battery = 100;
        //vis[0] = 1;
        Drum.push_back(initial);
        calc_best_graph(initial, coef);
    }
    if (SOLUTIONS.size() == 0) {
        fout <<V[0].titlu << " " << V[0].adresa << endl;
        fout << V.back().titlu << " " << V.back().adresa<<endl;

        return 0;
    }
    debugout << SOLUTIONS.size()<<endl;
    vector<state> bestsolution, longestsolution;
    
    size_t maxlen = SOLUTIONS[0].size();
    int best_rate = maxlen;
    for (auto it:SOLUTIONS){
        if (it.size() > maxlen){
            maxlen = it.size();
            longestsolution = it;

        }
        //cout << it.size() << " " << best_rate<<endl;
        if (rate_solution(it) > best_rate) {
            best_rate = rate_solution(it);//rate_solution(it);
            bestsolution = it;
        }
        for (auto temp:it){
            debugout << temp.nod << " ";

        }
        debugout << endl;
        //cout << rate_solution(it)<<endl;
    }
    
    cout << maxlen << " " << best_rate;
    V.front().adresa = "Romania";
    V.back().adresa = "Romania";
    for(int i = 0; i < V.size();i++) {
        //cout << it.nr << " " << it.titlu<<endl;
            replace(V[i].titlu.begin(),V[i].titlu.end(),'_',' ');
            replace(V[i].adresa.begin(), V[i].adresa.end(),'_',' ');
        }
    sort(SOLUTIONS.begin(), SOLUTIONS.end(), comp);
        cout <<SOLUTIONS[0].size();
    int k = 0;
    for (auto it:SOLUTIONS[0]) {
        if (k == 0 || k == SOLUTIONS[0].size() - 1){
            fout << V[it.nod].titlu << " " << V[it.nod].adresa << endl; 
        } else 
        fout << V[it.nod].titlu << " " << V[it.nod].adresa << " "<<V[it.nod].tip<< endl;
        k++;

    }
    
    //cout << SOLUTIONS.size();

return 0;
}


