#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

void ToutesLesPermutations(vector<string> &vecteurDeNomsDeVille, int debut, int fin)
{
    if (debut == fin)
    {
        for (const auto &nom : vecteurDeNomsDeVille)
            cout << nom << " ";
        cout << endl;
    }
    else
    {
        for (int i = debut; i <= fin; i++)
        {
            swap(vecteurDeNomsDeVille[debut], vecteurDeNomsDeVille[i]);
            ToutesLesPermutations(vecteurDeNomsDeVille, debut + 1, fin);
            swap(vecteurDeNomsDeVille[debut], vecteurDeNomsDeVille[i]);
        }
    }
}

int main()
{
    /*     string villes = "AB";
        string villes2 = "ABCD";
        string villes3 = "ALGORITHME";
        ToutesLesPermutations(villes, 0, villes.size()- 1);
        ToutesLesPermutations(villes2, 0, villes.size()- 1);
        ToutesLesPermutations(villes3, 0, villes.size()- 1);
    */

    srand(time(0));

    constexpr int codeASCIIde_a = 97;
    constexpr int codeASCIIde_A = 65;
    constexpr int nombreDeLettres = 26;
    constexpr int tailleMinNomVille = 4;
    constexpr int tailleMaxNomVille = 12;
    constexpr int grainePourLeRand = 1;
    constexpr int nombreDeVilles = 5;
    constexpr int nombreCombinaisons = 24;
    constexpr int tailleCoteCarte = 100;
    int nbVilles = 5;

    vector<string> vecteurDeNomsDeVille;
    vector<tuple<int, int, int>> localisations;

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
        localisations.push_back(monTuple);
    }

    for (int i = 0; i < nbVilles; i++)
    {
        cout << "Ville : " << vecteurDeNomsDeVille[i] << ", Localisation : (" << get<1>(localisations[i]) << ", " << get<2>(localisations[i]) << ")" << endl;
    }

    return 0;
}