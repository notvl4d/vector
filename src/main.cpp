#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int noduri, muchii, cost, costuri[200][200], x, y;
int nod_start, nr_interese, interese[200];

int vizitat[200];
int solutie[200], cost_solutie = 0, cost_minim, lungime_solutie;

bool citit_din_fisier = false; // retine sursa de citire

// ================= INITIALIZARE =================

void initializare() {
    for(int i = 1; i <= 200; i++)
        for(int j = 1; j <= 200; j++)
            costuri[i][j] = 0;

    cost_minim = 1000000000;
    lungime_solutie = 0;
}

// ================= CITIRE =================

void citire_din_fisier() {
    initializare();
    citit_din_fisier = true;

    fin >> noduri >> muchii;
    for(int i = 1; i <= muchii; i++) {
        fin >> x >> y >> cost;
        costuri[x][y] = costuri[y][x] = cost;
    }

    fin >> nod_start >> nr_interese;
    for(int i = 1; i <= nr_interese; i++)
        fin >> interese[i];
}

void citirea_de_la_tastatura() {
    initializare();
    citit_din_fisier = false;

    cin >> noduri >> muchii;
    for(int i = 1; i <= muchii; i++) {
        cin >> x >> y >> cost;
        costuri[x][y] = costuri[y][x] = cost;
    }

    cin >> nod_start >> nr_interese;
    for(int i = 1; i <= nr_interese; i++)
        cin >> interese[i];
}

// ================= BACKTRACKING =================

bool OK(int k) {
    if(k > 1 && costuri[vizitat[k-1]][vizitat[k]] == 0)
        return false;

    for(int i = 1; i < k; i++)
        if(vizitat[i] == vizitat[k])
            return false;

    return true;
}

bool Solutie(int k) {
    cost_solutie = 0;
    bool freq[201] = {0};

    for(int i = 1; i <= nr_interese; i++)
        freq[interese[i]] = 1;

    for(int i = 1; i <= k; i++) {
        if(freq[vizitat[i]] == 1)
            freq[vizitat[i]] = 0;

        if(i > 1)
            cost_solutie += costuri[vizitat[i-1]][vizitat[i]];
    }

    for(int i = 1; i <= 200; i++)
        if(freq[i] == 1)
            return false;

    if(costuri[vizitat[k]][vizitat[1]] == 0)
        return false;

    cost_solutie += costuri[vizitat[k]][vizitat[1]];

    if(cost_solutie < cost_minim) {
        cost_minim = cost_solutie;
        return true;
    }

    return false;
}

void Salvare(int k) {
    for(int i = 1; i <= k; i++)
        solutie[i] = vizitat[i];
    lungime_solutie = k;
}

void Back(int k) {
    for(int i = 1; i <= noduri; i++) {
        vizitat[k] = i;

        if(OK(k)) {
            if(Solutie(k))
                Salvare(k);
            else
                Back(k + 1);
        }
    }
}

// ================= AFISARE =================

void afisare_rezultat() {
    if(lungime_solutie == 0) {
        if(citit_din_fisier)
            fout << "Nu exista solutie\n";
        else
            cout << "Nu exista solutie\n";
        return;
    }

    if(citit_din_fisier) {
        for(int i = 1; i <= lungime_solutie; i++)
            fout << solutie[i] << ' ';
        fout << solutie[1] << '\n';
        fout << "Cost: " << cost_minim << '\n';
        cout << "Rezultatul a fost salvat in output.txt\n";
    } else {
        for(int i = 1; i <= lungime_solutie; i++)
            cout << solutie[i] << ' ';
        cout << solutie[1] << '\n';
        cout << "Cost: " << cost_minim << '\n';
    }
}

// ================= MAIN =================

int main() {
    int menu;

    do {
        cout << "\nMENIU\n";
        cout << "1. Citire din fisier (afisare in fisier)\n";
        cout << "2. Citire de la tastatura (afisare pe ecran)\n";
        cout << "3. Rezolvare\n";
        cout << "4. Afisare rezultat\n";
        cout << "5. Iesire\n";
        cout << "Optiune: ";
        cin >> menu;

        switch(menu) {
            case 1:
                citire_din_fisier();
                cout << "Date citite din fisier. Rezultatul va fi afisat in output.txt\n";
                break;

            case 2:
                cout << "Introduceti datele:\n";
                citirea_de_la_tastatura();
                cout << "Date citite de la tastatura. Rezultatul va fi afisat pe ecran\n";
                break;

            case 3:
                if(nod_start == 0) {
                    cout << "Eroare: cititi datele mai intai (optiunea 1 sau 2)!\n";
                    break;
                }
                vizitat[1] = nod_start;
                Back(2);
                cout << "Rezolvare finalizata. Alegeti optiunea 4 pentru afisare.\n";
                break;

            case 4:
                afisare_rezultat();
                break;

            case 5:
                break;

            default:
                cout << "Optiune invalida\n";
        }

    } while(menu != 5);

    fin.close();
    fout.close();

    return 0;
}
