#include <stdio.h>
#include <time.h>
#include "date_utils.h"

/**
 * Fonction interne pour obtenir le nom du jour en français
 * {int} - wday: Jour de la date courante
 */
static const char* jour_francais(int wday) {
    switch (wday)
    {
    case 0: return "Dimanche";
    case 1: return "Lundi";
    case 2: return "Mardi";
    case 3: return "Mercredi";
    case 4: return "Jeudi";
    case 5: return "Vendredi";
    case 6: return "Samedi";    
    default: return "";
    }
}

/**
 * Fonction interne pour obtenir le mois français
 * {int} - month: Mois de la date courante
 */
static const char* mois_francais(int month) {
    switch (month) {
        case 0: return "Janvier";
        case 1: return "Février";
        case 2: return "Mars";
        case 3: return "Avril";
        case 4: return "Mai";
        case 5: return "Juin";
        case 6: return "Juillet";
        case 7: return "Août";
        case 8: return "Septembre";
        case 9: return "Octobre";
        case 10: return "Novembre";
        case 11: return "Décembre";
        default: return "";
    }
}

void afficher_date() {
    time_t now;
    time(&now);
    
    struct tm *info = localtime(&now);

    const char* jour = jour_francais(info->tm_wday);
    const char* mois = mois_francais(info->tm_mon);

    printf("%s %d %s %d - %02d:%02d:%02d\n",
        jour,
        info->tm_mday,
        mois,
        info->tm_year + 1900,
        info->tm_hour,
        info->tm_min,
        info->tm_sec
    );
}