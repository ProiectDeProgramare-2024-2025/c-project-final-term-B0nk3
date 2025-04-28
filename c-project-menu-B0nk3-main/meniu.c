#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nume[100];
    int an;
    int inchiriata;
} Masina;

Masina *masini;
int numarMasini = 0;

void citireMasiniDinFisier() {
    FILE *fisier = fopen("Masini.txt", "r");
    if (fisier == NULL) {
        printf("Fisierul Masini.txt nu exista. Se creaza unul nou.\n");
        fisier = fopen("Masini.txt", "w");
        fprintf(fisier, "0\n");
        fclose(fisier);
        fisier = fopen("Masini.txt", "r");
    }

    fscanf(fisier, "%d", &numarMasini);
    fgetc(fisier);
    masini = malloc(numarMasini * sizeof(Masina));

    for (int i = 0; i < numarMasini; i++) {
        fgets(masini[i].nume, 100, fisier);
        masini[i].nume[strcspn(masini[i].nume, "\n")] = 0;
        
        char buffer[150];
        strcpy(buffer, masini[i].nume);
        char *p = strrchr(buffer, ' ');
        if (p == NULL) {
            printf("Eroare de format in fisier.\n");
            exit(1);
        }
        masini[i].inchiriata = atoi(p + 1);
        *p = 0;
        p = strrchr(buffer, ' ');
        if (p == NULL) {
            printf("Eroare de format in fisier.\n");
            exit(1);
        }
        masini[i].an = atoi(p + 1);
        *p = 0;
        strcpy(masini[i].nume, buffer);
    }

    fclose(fisier);
}

void salveazaMasiniInFisier() {
    FILE *fisier = fopen("Masini.txt", "w");
    fprintf(fisier, "%d\n", numarMasini);
    for (int i = 0; i < numarMasini; i++) {
        fprintf(fisier, "%s %d %d\n", masini[i].nume, masini[i].an, masini[i].inchiriata);
    }
    fclose(fisier);
}

void afiseazaMeniu() {
    system("cls");
    printf("\n===== Meniu Inchirieri Auto =====\n");
    printf("1. Afisare masini disponibile\n");
    printf("2. Inchiriere masina\n");
    printf("3. Returnare masina\n");
    printf("4. Adaugare masina noua\n");
    printf("5. Iesire\n");
    printf("Alegeti o optiune: ");
}

void afiseazaMasiniDisponibile() {
    system("cls");
    printf("\nMasini disponibile:\n");
    for (int i = 0; i < numarMasini; i++) {
        if (masini[i].inchiriata == 0) {
            printf("\033[0;33m%d. \033[0m \033[1;32m%s \033[0m \033[1;35m(%d) \033[0m\n", i + 1, masini[i].nume, masini[i].an);
        }
    }
    printf("\nApasati ENTER pentru a continua...");
    getchar();
}
void afiseazaMasiniInchiriate() {
    system("cls");
    printf("\nMasini inchiriate:\n");
    for (int i = 0; i < numarMasini; i++) {
        if (masini[i].inchiriata == 1) {
            printf("\033[0;33m%d. \033[0m \033[1;32m%s \033[0m \033[1;35m(%d) \033[0m\n", i + 1, masini[i].nume, masini[i].an);
        }
    }
    printf("\nApasati ENTER pentru a continua...");
    getchar();
}
void inchiriereMasina() {
    system("cls");
    afiseazaMasiniDisponibile();
    printf("\nIntroduceti numarul masinii pe care doriti sa o inchiriati: ");
    int alegere;
    scanf("%d", &alegere);
    getchar();

    if (alegere < 1 || alegere > numarMasini || masini[alegere - 1].inchiriata == 1) {
        printf("Optiune invalida sau masina deja inchiriata!\n");
    } else {
        masini[alegere - 1].inchiriata = 1;
        printf("Ati inchiriat masina: %s (%d)\n", masini[alegere - 1].nume, masini[alegere - 1].an);
        salveazaMasiniInFisier();
    }

    printf("\nApasati ENTER pentru a continua...");
    getchar();
}

void returnareMasina() {
    system("cls");
    afiseazaMasiniInchiriate();
    int alegere;
    scanf("%d", &alegere);
    getchar();

    if (alegere < 1 || alegere > numarMasini || masini[alegere - 1].inchiriata == 0) {
        printf("Optiune invalida sau masina nu este inchiriata!\n");
    } else {
        masini[alegere - 1].inchiriata = 0;
        printf("Ati returnat masina: %s (%d)\n", masini[alegere - 1].nume, masini[alegere - 1].an);
        salveazaMasiniInFisier();
    }

    printf("\nIntroduceti numarul masinii returnate:");
    getchar();
}

void adaugareMasinaNoua() {
    system("cls");
    printf("\nIntroduceti numele masinii: ");
    char numeNou[100];
    fgets(numeNou, sizeof(numeNou), stdin);
    numeNou[strcspn(numeNou, "\n")] = 0;

    printf("Introduceti anul fabricatiei: ");
    int anNou;
    scanf("%d", &anNou);
    getchar();

    masini = realloc(masini, (numarMasini + 1) * sizeof(Masina));
    strcpy(masini[numarMasini].nume, numeNou);
    masini[numarMasini].an = anNou;
    masini[numarMasini].inchiriata = 0;
    numarMasini++;

    salveazaMasiniInFisier();

    printf("Masina a fost adaugata cu succes!\n");
    printf("\nApasati ENTER pentru a continua...");
    getchar();
}

void elibereazaMemorie() {
    free(masini);
}

int main() {
    citireMasiniDinFisier();
    int optiune;
    do {
        afiseazaMeniu();
        scanf("%d", &optiune);
        getchar();

        switch (optiune) {
            case 1:
                afiseazaMasiniDisponibile();
                break;
            case 2:
                inchiriereMasina();
                break;
            case 3:
                returnareMasina();
                break;
            case 4:
                adaugareMasinaNoua();
                break;
            case 5:
                printf("Iesire din program.\n");
                break;
            default:
                printf("Optiune invalida! Incercati din nou.\n");
                printf("\nApasati ENTER pentru a continua...");
                getchar();
        }
    } while (optiune != 5);

    elibereazaMemorie();
    return 0;
}
