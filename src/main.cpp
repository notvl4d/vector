#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

int noduri,muchii,cost,costuri[200][200],x,y;
int nod_start, nr_interese, interese[200];
int vizitat[200];
int solutie[200], cost_solutie=0,cost_minim, lungime_solutie;
void citire()
{
	//citirea datelor din input.txt
	fin>>noduri>>muchii;
	for(int i=1; i<=muchii; i++)
	{
		fin>>x>>y>>cost;
		costuri[x][y]=costuri[y][x]=cost;
	}

	fin>>nod_start>>nr_interese;
	for(int i=1; i<=nr_interese; i++)
		fin>>interese[i];

}

bool OK(int k) {
    //verificam daca exista muchie intre nodurile vizitate si daca k>1
    if(costuri[vizitat[k-1]][vizitat[k]]==0 && k>1)return 0;   
    //verificam sa fie un nod vizitat o singura data 
    for(int i=1;i<k;i++)
        if(vizitat[i]==vizitat[k])
            return 0;
    return 1;
}

bool Solutie(int k) {
    //verificam daca toate nodurile de interes au fost vizitate si daca costul solutiei este minim
    cost_solutie=0;
    bool freq[200] = {0}; 
    for(int i = 1; i <= nr_interese; i++)
        freq[interese[i]] = 1;
    for(int i = 1; i <= k; i++){
        if(freq[vizitat[i]] == 1) freq[vizitat[i]] = 0;
        if(i>1)
            cost_solutie+=costuri[vizitat[i-1]][vizitat[i]];   
    }
    for(int i = 1; i <= 200; i++)
        if(freq[i] == 1) return 0;
    if(costuri[vizitat[k]][vizitat[1]] == 0) return 0; 
        cost_solutie+=costuri[vizitat[k]][vizitat[1]];
    if(!cost_minim)
        cost_minim=cost_solutie;
    else if(cost_solutie<cost_minim)
        cost_minim=cost_solutie;
    else return 0;
    return 1;
}

void Salvare(int k)
{
    //salvam solutia gasita
    for(int i=1;i<=k;i++)
        solutie[i]=vizitat[i];
    lungime_solutie=k;
}
void Back(int k)
{
	for(int i=1; i<=noduri; i++)
	{
		vizitat[k]=i;
		if(OK(k))
			if(Solutie(k))
				Salvare(k);
			else
				Back(k+1);
	}

}

int main()
{
	citire();
	vizitat[1]=nod_start;
	Back(2);
    //afisam solutia in output.txt
	for(int i=1;i<=lungime_solutie;i++)
	    fout<<solutie[i]<<' ';
    fout<<solutie[1];
    
	fin.close();
	fout.close();
	return 0;
}