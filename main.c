#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define CYAN "\033[36m"
#define BOLD    "\033[1m"
#define GOLD    "\033[38;5;220m"
#define SILVER  "\033[38;5;250m"
#define BRONZE  "\033[38;5;166m"
#define RESET   "\033[0m"
typedef struct player {
    char name[20],istoric[100][100];
    int won,lost,nr_meciuri_jucate;
};
struct player players[100];
typedef struct games {
    char name1[20],name2[20];
    int score1,score2;
};
struct games games[100];
int nr_jucate = 0;
// afiseaza meniul principal
// poz reprezinta care optiune e highlited
void menu(int poz) {
    system("cls");
    int number = 5;
    char options[][20] = {"Introdu un meci nou", "Clasament", "Jucatori", "Istoric meciuri", "Exit"};
    printf("\t-------BINE AI VENIT!-------\n");
    for (int i = 0 ; i < number ; i++) {
        if (poz == i + 1)
            printf("%s-->%s\t%s\n", GREEN, RESET, options[i]);
        else
            printf("\t%s\n", options[i]);
    }
    printf("\t----------------------------\n");
}

//  actualizeaza fisierul cu datele nou introduse
void file_uptade(int n) {
    FILE *f;
    f = fopen("D:\\Proiect de programare\\Proiect 1\\date.txt", "w");
    fprintf(f, "%d\n", n);
    for (int i = 0 ; i < n ; i++) {
        fprintf(f, "%s\n", players[i].name);
    }
    fprintf(f,"%d\n",nr_jucate);
    for (int i = 0 ; i < nr_jucate ; i++) {
        fprintf(f, "%s\n", games[i].name1);
        fprintf(f, "%d\n", games[i].score1);
        fprintf(f, "%s\n", games[i].name2);
        fprintf(f, "%d\n", games[i].score2);
    }
    fclose(f);
}

//afiseaza submeniul in care se pot introduce meciuri noi
//n reprezinta numarul de jucatori
void submeniu_meci_nou(int n) {
    system("cls");
    printf("\t------INTRODU UN MECI NOU-------\n");
    char options[][100] = {"Introdu primul jucator", "Introdu numarul de puncte al primului jucator", "Introdu al doilea jucator", "Introdu numarul de puncte al celui de al doilea jucator"};
    char n1[20],n2[20],s1[10],s2[10];
        for (int i = 0; i < 4; i++) {
            printf("\t%s\n", options[i]);
            if (i == 0) // primul jucator
            {
                scanf("%s", n1);
                strcpy(games[nr_jucate].name1,n1);
            }
            else if (i == 1) { // scor primul jucator
                scanf("%s", s1);
                games[nr_jucate].score1 = atoi(s1);
            }
            else if (i == 2) // al doilea jucator
            {
                scanf("%s", n2);
                strcpy(games[nr_jucate].name2,n2);
            }
            else if (i == 3) {
                scanf("%s", s2); // scor al doilea jucator
                games[nr_jucate].score2 = atoi(s2);
            }
            if (i == 1) {
                for (int j = 0; j < strlen(s1); j++) {
                    if (s1[0] == '-') {
                        printf("Scorul nu poate fi mai mic decat 0");
                        _sleep(2000);
                        return;
                    }
                    else if (!isdigit(s1[j])) {
                        printf("Scorul trebuie sa fie o cifra");
                        _sleep(2000);
                        return;
                    }
                }

            }
            else if (i == 3) {
                for (int j = 0; j < strlen(s2); j++)
                    if (s2[0] == '-') {
                        printf("Scorul nu poate fi mai mic decat 0");
                        _sleep(2000);
                        return;
                    }
                    else if (!isdigit(s2[j])) {
                        printf("Scorul trebuie sa fie o cifra");
                        _sleep(2000);
                        return;
                    }
            }
            }
    int ok = 0;
    int scor1 = atoi(s1);
    int scor2 = atoi(s2);
    if (scor1 == scor2) { // scorurile nu pot fi egale
        printf("Meciul nu se poate termina cu scor de egalitate");
        _sleep(2000);
        return;
    }
    for (int i = 0 ; i < 4 ; i++) {
        if (strcmp(n1, players[i].name) == 0 || strcmp(n2, players[i].name) == 0)
            ok++; // verificam ca ambele nume pe care le-am introdus sa faca parte din lista de jucatori
    }
    if (ok==2) {
        if (scor1 < scor2) {
            for (int i = 0 ; i < n ; i++) {
                if (strcmp(n1, players[i].name) == 0) {
                    players[i].lost++;
                    players[i].nr_meciuri_jucate++;
                    ok++;
                }
                if (strcmp(n2, players[i].name) == 0) {
                    players[i].won++;
                    players[i].nr_meciuri_jucate++;
                    ok++;
                }
            }
        }
        else {
            for (int i = 0 ; i < n ; i++) {
                if (strcmp(n1, players[i].name) == 0) {
                    players[i].won++;
                    players[i].nr_meciuri_jucate++;
                    ok++;
                }
                if (strcmp(n2, players[i].name) == 0) {
                    players[i].lost++;
                    players[i].nr_meciuri_jucate++;
                    ok++;
                }
            }
        }
        printf("Adaugat cu succes");
        nr_jucate++;
        file_uptade(n);
    }
    else if (ok == 1) {
        printf("Unul din numele introduse nu s-a regasit in lista cu participanti");
        Sleep(2000);
    }
    else {
        printf("Nici unul din numele introduse nu s-a regasit in lista cu participanti");
        Sleep(2000);
    }
}

//face o sortare in functie de numarul de victorii si afiseaza clasamentul
void sumbeniu_clasament(int n) {
    system("cls");
    printf("\t------CLASAMENT-------\n");
    struct player clasament[n];
    for (int i = 0 ; i < n ; i++) {
        clasament[i] = players[i];
    }
    for (int i = 0 ; i < n ; i++) {
        for (int j = i+1 ; j < n ; j++) {
            if (clasament[i].won < clasament[j].won) {
                struct player temp = clasament[i];
                clasament[i] = clasament[j];
                clasament[j] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            printf("\t%s%d.%s%s\n", GOLD, i+1, clasament[i].name, RESET);
        } else if (i == 1) {
            printf("\t%s%d.%s%s\n", SILVER, i+1, clasament[i].name, RESET);
        } else if (i == 2) {
            printf("\t%s%d.%s%s\n", BRONZE, i+1, clasament[i].name, RESET);
        } else {
            printf("\t%d.%s\n", i+1, clasament[i].name);
        }
    }
    printf("\t------Apasa enter pentru a te intoarce la meniul principal------");
    char c;
    scanf("%c", &c);
}

//arata toti jucatorii inscrisi in turneul si bilantul lor de meciuri castigate/pierdute
void submeniu_jucatori(int n) {
    system("cls");
    printf("\t------JUCATORI-------\n");
    for (int i = 0 ; i < n ; i++) {
        printf("\t%s\t", players[i].name);

        printf("%sMeciuri castigate:%s %s%d%s\t",
            GREEN, RESET, BOLD, players[i].won, RESET);

        printf("%sMeciuri pierdute:%s %s%d%s\n",
            RED, RESET, BOLD, players[i].lost, RESET);    }
    printf("\n\t------Apasa enter pentru a te intoarce la meniul principal------");
    char c;
    scanf("%c", &c);

}
//arata istoricul de meciuri al unui jucator transmis de la tastatura
void submeniu_istoric_meciuri() {
    system("cls");
    printf("\t------ISTORIC MECIURI-------\n");
    printf("\tIntrodu numele jucatorului caruia vrei sa vezi istoricul meciurilor\n");

    char nume[100];
    scanf("%s", nume);

    int gasit = 0;
    for (int i = 0; i < nr_jucate; i++) {
        // verificăm dacă e numele introdus
        int match1 = strcmp(nume, games[i].name1) == 0;
        int match2 = strcmp(nume, games[i].name2) == 0;

        if (match1 || match2) {
            printf("\t");

            if (match1)
                printf("%s%s%s", CYAN, games[i].name1, RESET);
            else
                printf("%s", games[i].name1);

            printf(": %d - ", games[i].score1);

            if (match2)
                printf("%s%s%s", CYAN, games[i].name2, RESET);
            else
                printf("%s", games[i].name2);

            printf(": %d\n", games[i].score2);

            gasit = 1;
        }
    }

    if (!gasit)
        printf("\tNu s-au gasit meciuri pentru jucatorul '%s'.\n", nume);

    printf("\t------Apasa enter pentru a te intoarce la meniul principal------");
    getchar();
    getchar();
}


void accesare_meniu(int n) {
    system("cls");
    int i = 1;
    menu(i);
    int ch;
    while (1) {
        ch = getch();
        switch (ch) {
            case 72: { // up arrow
                if (i > 1)
                    i--;
                menu(i);
                break;
            }
            case 80: { // down arrow
                if (i < 5)
                    i++;
                menu(i);
                break;
            }
            case 13: { // enter
                if (i == 1) {
                    submeniu_meci_nou(n);
                    menu(i);
                }
                if (i == 2) {
                    sumbeniu_clasament(n);
                    menu(i);
                }
                if (i == 3) {
                    submeniu_jucatori(n);
                    menu(i);
                }
                if (i == 4) {
                    submeniu_istoric_meciuri();
                    menu(i);
                }
                if (i == 5) {
                    exit(0);
                }
                break;
            }
        }
    }
}

void citire(FILE *f, int *n) {
    fscanf(f, "%d", n);
    fgetc(f);
    for (int i = 0; i < *n; i++) {
        fgets(players[i].name, 20, f);
        if (players[i].name[strlen(players[i].name) - 1] == '\n')
            players[i].name[strlen(players[i].name) - 1] = '\0';
    }
    fscanf(f, "%d", &nr_jucate);
    fgetc(f);
    char n1[20],n2[20];
    int scor1,scor2;
    for (int i = 0 ; i < nr_jucate ; i++) {
        fgets(n1, 20, f);
        if (n1[strlen(n1) - 1] == '\n')
            n1[strlen(n1) - 1] = '\0';
        strcpy(games[i].name1,n1);
        fscanf(f, "%d", &scor1);
        fgetc(f);
        games[i].score1 = scor1;
        fgets(n2, 20, f);
        if (n2[strlen(n2) - 1] == '\n')
            n2[strlen(n2) - 1] = '\0';
        strcpy(games[i].name2,n2);
        fscanf(f, "%d", &scor2);
        fgetc(f);
        games[i].score2 = scor2;
        if (scor1 < scor2) {
            for (int i = 0 ; i < *n ; i++) {
                if (strcmp(n1, players[i].name) == 0) {
                    players[i].lost++;
                    players[i].nr_meciuri_jucate++;
                }
                if (strcmp(n2, players[i].name) == 0) {
                    players[i].won++;
                    players[i].nr_meciuri_jucate++;
                }
            }
        }
        else if (scor1 > scor2) {
            for (int i = 0 ; i < *n ; i++) {
                if (strcmp(n1, players[i].name) == 0) {
                    players[i].won++;
                    players[i].nr_meciuri_jucate++;
                }
                if (strcmp(n2, players[i].name) == 0) {
                    players[i].lost++;
                    players[i].nr_meciuri_jucate++;
                }
            }
        }
        }
}

int main(void) {

    FILE *f = fopen("D:\\Proiect de programare\\Proiect 1\\date.txt", "r");
    if (f == NULL) {
        printf("Programul nu a putut citi date");
        return 1;
    }
    int n; // numarul de jucatori
    citire(f, &n);
    fclose(f);
    accesare_meniu(n);


    return 0;
}