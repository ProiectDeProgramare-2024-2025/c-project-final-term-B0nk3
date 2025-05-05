#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char marca[50];
    char model[50];
    int an;
    int capacitate;
    int inchiriata;
} Masina;

Masina *masini;
int numarMasini = 0;

void citireMasiniDinFisier() {
    FILE *fisier = fopen("Masini.txt", "r");
    if (fisier == NULL) {
        fisier = fopen("Masini.txt", "w");
        fprintf(fisier, "0\n");
        fclose(fisier);
        fisier = fopen("Masini.txt", "r");
    }

    fscanf(fisier, "%d", &numarMasini);
    masini = malloc(numarMasini * sizeof(Masina));
    for (int i = 0; i < numarMasini; i++) {
        fscanf(fisier, "%s %s %d %d %d", masini[i].marca, masini[i].model, &masini[i].an, &masini[i].capacitate, &masini[i].inchiriata);
    }

    fclose(fisier);
}

void salveazaMasiniInFisier() {
    FILE *fisier = fopen("Masini.txt", "w");
    fprintf(fisier, "%d\n", numarMasini);
    for (int i = 0; i < numarMasini; i++) {
        fprintf(fisier, "%s %s %d %d %d\n", masini[i].marca, masini[i].model, masini[i].an, masini[i].capacitate, masini[i].inchiriata);
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
    printf("5. Cautare masina\n");
    printf("6. Modificare masina\n");
    printf("7. Stergere masina\n");
    printf("8. Iesire\n");
    printf("Alegeti o optiune: ");
}

void afiseazaMasiniDisponibile() {
    system("cls");
    printf("\nMasini disponibile:\n");
    for (int i = 0; i < numarMasini; i++) {
        if (masini[i].inchiriata == 0) {
            printf("\033[0;33m%d. \033[0m \033[1;32m%s %s \033[0m \033[1;35m(%d, %dcc) \033[0m\n", i + 1, masini[i].marca, masini[i].model, masini[i].an, masini[i].capacitate);
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
            printf("\033[0;33m%d. \033[0m \033[1;32m%s %s \033[0m \033[1;35m(%d, %dcc) \033[0m\n", i + 1, masini[i].marca, masini[i].model, masini[i].an, masini[i].capacitate);
        }
    }
    printf("\nApasati ENTER pentru a continua...");
    getchar();
}

void inchiriereMasina() {
    system("cls");
    int map[100];
    int contor = 0;

    printf("\nMasini disponibile:\n");
    for (int i = 0; i < numarMasini; i++) {
        if (masini[i].inchiriata == 0) {
            contor++;
            printf("\033[0;33m%d. \033[0m \033[1;32m%s %s \033[0m \033[1;35m(%d, %dcc) \033[0m\n", contor, masini[i].marca, masini[i].model, masini[i].an, masini[i].capacitate);
            map[contor] = i;
        }
    }

    if (contor == 0) {
        printf("Nu exista masini disponibile.\n");
        printf("\nApasati ENTER pentru a continua...");
        getchar();
        return;
    }

    printf("\nIntroduceti numarul masinii pe care doriti sa o inchiriati: ");
    int alegere;
    scanf("%d", &alegere);
    getchar();

    if (alegere < 1 || alegere > contor) {
        printf("Optiune invalida!\n");
    } else {
        int indexReal = map[alegere];
        masini[indexReal].inchiriata = 1;
        printf("Ati inchiriat masina: %s %s (%d)\n", masini[indexReal].marca, masini[indexReal].model, masini[indexReal].an);
        salveazaMasiniInFisier();
    }

    printf("\nApasati ENTER pentru a continua...");
    getchar();
}

void returnareMasina() {
    system("cls");
    int map[100];
    int contor = 0;

    printf("\nMasini inchiriate:\n");
    for (int i = 0; i < numarMasini; i++) {
        if (masini[i].inchiriata == 1) {
            contor++;
            printf("\033[0;33m%d. \033[0m \033[1;32m%s %s \033[0m \033[1;35m(%d, %dcc) \033[0m\n", contor, masini[i].marca, masini[i].model, masini[i].an, masini[i].capacitate);
            map[contor] = i;
        }
    }

    if (contor == 0) {
        printf("Nu exista masini inchiriate.\n");
        printf("\nApasati ENTER pentru a continua...");
        getchar();
        return;
    }

    printf("\nIntroduceti numarul masinii pe care doriti sa o returnati: ");
    int alegere;
    scanf("%d", &alegere);
    getchar();

    if (alegere < 1 || alegere > contor) {
        printf("Optiune invalida!\n");
    } else {
        int indexReal = map[alegere];
        masini[indexReal].inchiriata = 0;
        printf("Ati returnat masina: %s %s (%d)\n", masini[indexReal].marca, masini[indexReal].model, masini[indexReal].an);
        salveazaMasiniInFisier();
    }

    printf("\nApasati ENTER pentru a continua...");
    getchar();
}
void modificaMasina() {
    system("cls");
    printf("\n=== Modificare masina ===\n");

    if (numarMasini == 0) {
        printf("Nu exista masini in sistem.\n");
        printf("\nApasati ENTER pentru a continua...");
        getchar();
        return;
    }

    for (int i = 0; i < numarMasini; i++) {
        printf("%d. %s %s (%d, %d cmc) - %s\n", 
            i + 1,
            masini[i].marca,
            masini[i].model,
            masini[i].an,
            masini[i].capacitate,
            masini[i].inchiriata ? "Inchiriata" : "Disponibila"
        );
    }

    printf("\nIntroduceti numarul masinii de modificat: ");
    int alegere;
    scanf("%d", &alegere);
    getchar();

    if (alegere < 1 || alegere > numarMasini) {
        printf("Optiune invalida!\n");
        printf("\nApasati ENTER pentru a continua...");
        getchar();
        return;
    }

    int index = alegere - 1;

    printf("\nIntroduceti noua marca: ");
    fgets(masini[index].marca, sizeof(masini[index].marca), stdin);
    masini[index].marca[strcspn(masini[index].marca, "\n")] = 0;

    printf("Introduceti noul model: ");
    fgets(masini[index].model, sizeof(masini[index].model), stdin);
    masini[index].model[strcspn(masini[index].model, "\n")] = 0;

    printf("Introduceti noul an: ");
    scanf("%d", &masini[index].an);
    getchar();

    printf("Introduceti noua capacitate cilindrica (cmc): ");
    scanf("%d", &masini[index].capacitate);
    getchar();

    printf("Este masina inchiriata? (0 = Nu, 1 = Da): ");
    scanf("%d", &masini[index].inchiriata);
    getchar();

    salveazaMasiniInFisier();

    printf("Masina a fost modificata cu succes!\n");
    printf("\nApasati ENTER pentru a continua...");
    getchar();
}


void adaugareMasinaNoua() {
    system("cls");
    char marca[50], model[50];
    int an, capacitate;

    printf("Introduceti marca masinii: ");
    fgets(marca, sizeof(marca), stdin);
    marca[strcspn(marca, "\n")] = 0;

    printf("Introduceti modelul masinii: ");
    fgets(model, sizeof(model), stdin);
    model[strcspn(model, "\n")] = 0;

    printf("Introduceti anul fabricatiei (ex: 2010): ");
    scanf("%d", &an); getchar();
    if (an < 1950 || an > 2025) {
        printf("An invalid!\n");
        return;
    }

    printf("Introduceti capacitatea cilindrica (ex: 1600): ");
    scanf("%d", &capacitate); getchar();
    if (capacitate < 500 || capacitate > 7000) {
        printf("Capacitate cilindrica invalida!\n");
        return;
    }

    masini = realloc(masini, (numarMasini + 1) * sizeof(Masina));
    strcpy(masini[numarMasini].marca, marca);
    strcpy(masini[numarMasini].model, model);
    masini[numarMasini].an = an;
    masini[numarMasini].capacitate = capacitate;
    masini[numarMasini].inchiriata = 0;
    numarMasini++;
    salveazaMasiniInFisier();

    printf("Masina a fost adaugata cu succes!\n");
    printf("\nApasati ENTER pentru a continua...");
    getchar();
}
void stergeMasina() {
    system("cls");
    printf("\n=== Stergere masina ===\n");

    if (numarMasini == 0) {
        printf("Nu exista masini in sistem.\n");
        printf("\nApasati ENTER pentru a continua...");
        getchar();
        return;
    }

    for (int i = 0; i < numarMasini; i++) {
        printf("%d. %s %s (%d, %d cmc) - %s\n", 
            i + 1,
            masini[i].marca,
            masini[i].model,
            masini[i].an,
            masini[i].capacitate,
            masini[i].inchiriata ? "Inchiriata" : "Disponibila"
        );
    }

    printf("\nIntroduceti numarul masinii de sters: ");
    int alegere;
    scanf("%d", &alegere);
    getchar();

    if (alegere < 1 || alegere > numarMasini) {
        printf("Optiune invalida!\n");
        printf("\nApasati ENTER pentru a continua...");
        getchar();
        return;
    }

    int index = alegere - 1;
    for (int i = index; i < numarMasini - 1; i++) {
        masini[i] = masini[i + 1];
    }

    numarMasini--;
    masini = realloc(masini, numarMasini * sizeof(Masina));
    salveazaMasiniInFisier();

    printf("Masina a fost stearsa cu succes.\n");
    printf("\nApasati ENTER pentru a continua...");
    getchar();
}

void cautareMasina() {
    system("cls");
    char cauta[50];
    printf("Introduceti marca sau modelul pentru cautare: ");
    fgets(cauta, sizeof(cauta), stdin);
    cauta[strcspn(cauta, "\n")] = 0;

    int gasit = 0;
    for (int i = 0; i < numarMasini; i++) {
        if (strstr(masini[i].marca, cauta) || strstr(masini[i].model, cauta)) {
            gasit = 1;
            printf("\033[1;32m%s %s\033[0m - \033[1;35m%d, %dcc\033[0m [%s]\n",
                   masini[i].marca, masini[i].model,
                   masini[i].an, masini[i].capacitate,
                   masini[i].inchiriata ? "inchiriata" : "disponibila");
        }
    }

    if (!gasit)
        printf("Nu s-au gasit masini cu criteriile introduse.\n");

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
                cautareMasina();
                break;
            case 6:
                modificaMasina();
                break;
                case 7:
                stergeMasina();
                break;
            case 8:
                printf("Iesire din program.\n");
                break;
            default:
                printf("Optiune invalida! Incercati din nou.\n");
                printf("\nApasati ENTER pentru a continua...");
                getchar();
        }
    } while (optiune != 8);

    elibereazaMemorie();
    return 0;
}
