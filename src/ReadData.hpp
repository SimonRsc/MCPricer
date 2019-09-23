#ifndef MC_PRICER_READDATA_HPP
#define MC_PRICER_READDATA_HPP

#include <cstring>
#include <string>
#include "Option.hpp"
#include "BlackScholesModel.hpp"

using namespace std;

class ReadData {
private:
    Option *option; /*! pointeur vers l'option lue' */
    BlackScholesModel *model; /*! pointeur vers le modèle lu' */
    long n_samples; /*! nombre de tirages Monte Carlo */

public:
    /**
     * Constructeur permettant d'initialiser tous les attributs (option, model et n_samples)
     *
     * @param[in] fileName Nom du fichier .dat dans lequel sont stockées les informations à lire pour la simulation
     */
    ReadData(char *fileName);

    ~ReadData();

    /**
     * Renvoie un pointeur sur l'option lue
     */
    Option* getOption();

    /**
     * Renvoie un pointeur sur le modèle lu
     */
    BlackScholesModel* getModel();

    /**
     * Renvoie le nombre de tirages de Monte Carlo
     */
    long getNombreSample();
};


#endif //MC_PRICER_READDATA_HPP
