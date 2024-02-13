#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <map>
#include <cmath>

using namespace std;



void AfficherContenuMap(const map<int, tuple<int, int, int>> &maMap)
{
    for (const auto &it : maMap)
    {
        cout << "Clé : " << it.first << ", Valeur : ("
             << get<0>(it.second) << ", "
             << get<1>(it.second) << ", "
             << get<2>(it.second) << ")" << endl;
    }
}

vector<vector<double>> GenererMatriceDistances(const map<string, tuple<int, int, int>> &maMapNomsVillesEtCoordonnees)
{
    int taille = maMapNomsVillesEtCoordonnees.size();
    vector<vector<double>> matriceDistances(taille, vector<double>(taille, 0.0));

    for (auto it1 = maMapNomsVillesEtCoordonnees.begin(); it1 != maMapNomsVillesEtCoordonnees.end(); ++it1)
    {
        for (auto it2 = maMapNomsVillesEtCoordonnees.begin(); it2 != maMapNomsVillesEtCoordonnees.end(); ++it2)
        {
            int index1 = get<0>(it1->second);
            int index2 = get<0>(it2->second);
            int X1 = get<1>(it1->second);
            int Y1 = get<2>(it1->second);
            int X2 = get<1>(it2->second);
            int Y2 = get<2>(it2->second);

            matriceDistances[index1][index2] = sqrt(pow(X1 - X2, 2) + pow(Y1 - Y2, 2));
        }
    }

    return matriceDistances;
}

int calculTotalDistanceTournee(
    vector<string> &vecteurDeNomsDeVille,
    vector<vector<int>> &DIST,
    map<string, tuple<int, int, int>> &maMapNomsVillesEtCoordonnees)
{
    int totalDistance = 0;

    for (int i = 0; i < vecteurDeNomsDeVille.size() - 1; i++)
    {
        int indexVille1 = get<0>(maMapNomsVillesEtCoordonnees[vecteurDeNomsDeVille[i]]);
        int indexVille2 = get<0>(maMapNomsVillesEtCoordonnees[vecteurDeNomsDeVille[i + 1]]);
        totalDistance += DIST[indexVille1][indexVille2];
    }

    // Ajouter la distance pour "boucler la boucle"
    int indexVilleDebut = get<0>(maMapNomsVillesEtCoordonnees[vecteurDeNomsDeVille[0]]);
    int indexVilleFin = get<0>(maMapNomsVillesEtCoordonnees[vecteurDeNomsDeVille[vecteurDeNomsDeVille.size() - 1]]);
    totalDistance += DIST[indexVilleDebut][indexVilleFin];

    return totalDistance;
}


void ToutesLesPermutations(vector<string> &vecteurDeNomsDeVille, int debut, int fin, map<string, tuple<int, int, int>> &maMapNomsVillesEtCoordonnees)
{
    if (debut == fin)
    {
        // Générer la matrice des distances
        vector<vector<double>> DIST = GenererMatriceDistances(maMapNomsVillesEtCoordonnees);

        // Calculer la distance totale de la tournée
        int totalDistance = calculTotalDistanceTournee(vector<string> &vecteurDeNomsDeVille,vector<vector<int>> &DIST,map<string, tuple<int, int, int>> &maMapNomsVillesEtCoordonnees)

        // Ajouter la tournée et sa distance totale à toutesLesTourneesEtLeurDistanceTotale
        toutesLesTourneesEtLeurDistanceTotale.push_back(make_pair(vecteurDeNomsDeVille, totalDistance));

        // Afficher le contenu de la map
        void AfficherContenuMap(const map<int, tuple<int, int, int>> &maMapNomsVillesEtCoordonnees);
    }
    else
    {
        for (int i = debut; i <= fin; i++)
        {
            swap(vecteurDeNomsDeVille[debut], vecteurDeNomsDeVille[i]);
            ToutesLesPermutations(vecteurDeNomsDeVille, debut + 1, fin, maMapNomsVillesEtCoordonnees);
            swap(vecteurDeNomsDeVille[debut], vecteurDeNomsDeVille[i]);
        }
    }
}


int main()
{
    srand(time(0));

    constexpr int tailleMinNomVille = 4;
    constexpr int tailleMaxNomVille = 12;
    constexpr int nombreDeVilles = 5;
    constexpr int tailleCoteCarte = 100;

    vector<string> vecteurDeNomsDeVille;
    map<string, tuple<int, int, int>> maMapNomsVillesEtCoordonnees;

    for (int i = 0; i < nombreDeVilles; i++)
    {
        int nbLettresNomVille = tailleMinNomVille + rand() % (tailleMaxNomVille - tailleMinNomVille + 1);
        string nomVille = "";
        for (int j = 0; j < nbLettresNomVille; j++)
        {
            char lettre = 'a' + rand() % 26;
            if (j == 0)
            {
                lettre = toupper(lettre);
            }
            nomVille += lettre;
        }
        vecteurDeNomsDeVille.push_back(nomVille);
        int X = rand() % tailleCoteCarte;
        int Y = rand() % tailleCoteCarte;
        auto monTuple = make_tuple(i, X, Y);
        maMapNomsVillesEtCoordonnees.insert(maMapNomsVillesEtCoordonnees.begin(), std::pair<string, tuple<int, int, int>>(nomVille, monTuple));
    }

    // Afficher l'index et les coordonnées de chaque ville
    void AfficherContenuMap(const map<int, tuple<int, int, int>> &maMapNomsVillesEtCoordonnees);

    // Générer et afficher la matrice des distances
    vector<vector<double>> DIST = GenererMatriceDistances(maMapNomsVillesEtCoordonnees);
    for (const auto &ligne : DIST)
    {
        for (const auto &distance : ligne)
        {
            cout << distance << " ";
        }
        cout << endl;
    }

    // Afficher toutes les permutations des villes
    if (vecteurDeNomsDeVille.size() <= 3) // Choisissez un n suffisamment petit
    {
        ToutesLesPermutations(vecteurDeNomsDeVille, 0, vecteurDeNomsDeVille.size() - 1, maMapNomsVillesEtCoordonnees);
    }

    return 0;
}

