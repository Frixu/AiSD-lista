#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

typedef struct el_listy {
    int klucz;
    struct el_listy* nast;
} LISTA, * LISTAWSK;

int przegladanie(LISTA* p) {
    int licznik = 0;
    while (p != NULL) {
        p = p->nast;
        if (p != NULL) {
            licznik++;
            printf("klucz=%d licznik=%d\n", p->klucz, licznik);
        }
    }
    return licznik;
}

void dodaj_za(LISTA* p, int k) {
    LISTA* pom;
    pom = (LISTAWSK)malloc(sizeof(LISTA));
    pom->klucz = k;
    pom->nast = p->nast;
    p->nast = pom;
}

void dodaj_przed(LISTA* p, int k) {
    LISTA* pom;
    pom = (LISTAWSK)malloc(sizeof(LISTA));
    pom->klucz = p->klucz;
    pom->nast = p->nast;
    p->klucz = k;
    p->nast = pom;
}

void usun_nast(LISTA* p) {
    LISTA* pom;
    if (p->nast != NULL) {
        pom = p->nast;
        p->nast = pom->nast;
        free(pom);
    }
    else {
        printf("nie ma nastepnego\n");
    }
}

void usun(LISTA* glowa, LISTA* p) {
    LISTA* pom;
    pom = p->nast;
    if (pom == NULL) {
        pom = glowa;
        p = pom->nast;
        while (p->nast != NULL) {
            p = p->nast;
            pom = pom->nast;
        }
        pom->nast = NULL;
    }
    else {
        *p = *pom;
    }
    free(pom);
}

LISTA* szukaj(LISTA* p, int k) {
    while (p != NULL) {
        if (p->nast == NULL) return NULL;
        else {
            p = p->nast;
            if (p->klucz == k) return p;
        }
    }
    return NULL;
}

int liczrek(LISTA* p) {
    if (p->nast == NULL) return 0;
    else {
        return 1 + liczrek(p->nast);
    }
}

void przeglrewrek(LISTA* p) {
    if (p != NULL) {
        przeglrewrek(p->nast);
        printf("%d\n", p->klucz);
    }
}

void przeglrek(LISTA* p) {
    if (p != NULL) {
        printf("%d\n", p->klucz);
        przeglrek(p->nast);
    }
}

int maxrek(LISTA* p) {
    int max;
    if (p == NULL)
        return 0;
    if (p->nast == NULL)
        return p->klucz;
    max = maxrek(p->nast);
    if (p->klucz > max)
        return p->klucz;
    else
        return max;
}

LISTAWSK odwroc(LISTA* p) {
    LISTAWSK w3, w2 = p, w1 = NULL;
    while (w2 != NULL) {
        w3 = w2->nast;
        w2->nast = w1;
        w1 = w2;
        w2 = w3;
    }
    return w1;
}

void zamien(int x, int y, LISTA* glowa) {
    LISTA* p = glowa;
    while (p != NULL && p->klucz != x) {
        p = p->nast;
    }
    if (p != NULL) {
        p->klucz = y;
    }
}

int usunx(LISTA* p, int x) {
    LISTA* prev = NULL;
    LISTA* current = p;
    while (current != NULL && current->klucz != x) {
        prev = current;
        current = current->nast;
    }
    if (current != NULL) {
        if (prev != NULL) {
            prev->nast = current->nast;
        }
        else {
            p = current->nast;
        }
        free(current);
        return 1;
    }
    return 0;
}

int usun2x(LISTA* p, int x) {
    LISTA* prev = NULL;
    LISTA* current = p;
    while (current != NULL && current->klucz != x) {
        prev = current;
        current = current->nast;
    }
    if (current != NULL) {
        if (prev != NULL) {
            prev->nast = current->nast;
        }
        else {
            p = current->nast;
        }
        free(current);
        return 1;
    }
    return 0;
}

void dodaj_sort(int x, LISTA* g) {
    LISTA* new_node = (LISTA*)malloc(sizeof(LISTA));
    new_node->klucz = x;
    new_node->nast = NULL;

    LISTA* current = g;
    LISTA* prev = NULL;

    while (current != NULL && current->klucz < x) {
        prev = current;
        current = current->nast;
    }

    if (prev == NULL) {
        new_node->nast = g;
        g = new_node;
    }
    else {
        prev->nast = new_node;
        new_node->nast = current;
    }
}

void zwolnij_liste(LISTA* glowa) {
    LISTA* pom;
    while (glowa != NULL) {
        pom = glowa;
        glowa = glowa->nast;
        free(pom);
    }
}

void sortuj(LISTA* glowa) {
    if (glowa == NULL || glowa->nast == NULL) {
        return;
    }

    LISTA* sorted = NULL;

    while (glowa != NULL) {
        LISTA* current = glowa;
        glowa = glowa->nast;

        if (sorted == NULL || sorted->klucz >= current->klucz) {
            current->nast = sorted;
            sorted = current;
        }
        else {
            LISTA* tmp = sorted;
            while (tmp->nast != NULL && tmp->nast->klucz < current->klucz) {
                tmp = tmp->nast;
            }
            current->nast = tmp->nast;
            tmp->nast = current;
        }
    }

    glowa = sorted;
}

void wyswietl_menu() {
    printf("Menu:\n");
    printf("1. Dodaj element za\n");
    printf("2. Dodaj element przed\n");
    printf("3. Usuń następny element\n");
    printf("4. Usuń element\n");
    printf("5. Szukaj elementu\n");
    printf("6. Przeglądaj listę\n");
    printf("7. Odwróć listę\n");
    printf("8. Dodaj posortowany element\n");
    printf("9. Sortuj listę\n");
    printf("0. Wyjście\n");
}

int main(int argc, char* argv[]) {
    int k, wybor, element;
    LISTA* glowa, * ost, * znal;
    LISTA* pom;

    glowa = NULL;
    pom = (LISTA*)malloc(sizeof(LISTA));
    pom->klucz = 0;
    pom->nast = NULL;
    glowa = pom;
    ost = glowa;

    do {
        wyswietl_menu();
        printf("Wybierz opcję: ");
        scanf("%d", &wybor);

        switch (wybor) {
        case 1:
            printf("Podaj klucz nowego elementu: ");
            scanf("%d", &element);
            dodaj_za(ost, element);
            ost = ost->nast;
            break;
        case 2:
            printf("Podaj klucz nowego elementu: ");
            scanf("%d", &element);
            dodaj_przed(ost, element);
            break;
        case 3:
            usun_nast(ost);
            break;
        case 4:
            printf("Podaj klucz elementu do usunięcia: ");
            scanf("%d", &element);
            znal = szukaj(glowa, element);
            if (znal != NULL) {
                usun(glowa, znal);
            }
            else {
                printf("Element nie znaleziony.\n");
            }
            break;
        case 5:
            printf("Podaj klucz szukanego elementu: ");
            scanf("%d", &element);
            znal = szukaj(glowa, element);
            if (znal != NULL) {
                printf("Znaleziono element: klucz = %d\n", znal->klucz);
            }
            else {
                printf("Element nie znaleziony.\n");
            }
            break;
        case 6:
            printf("Przeglądanie listy: %d\n", przegladanie(glowa));
            break;
        case 7:
            glowa->nast = odwroc(glowa->nast);
            printf("Lista została odwrócona.\n");
            break;
        case 8:
            printf("Podaj klucz nowego elementu: ");
            scanf("%d", &element);
            dodaj_sort(element, glowa);
            break;
        case 9:
            sortuj(glowa);
            printf("Lista została posortowana.\n");
            break;
        case 0:
            printf("Zamykanie programu.\n");
            break;
        default:
            printf("Niepoprawna opcja.\n");
        }
    } while (wybor != 0);

    zwolnij_liste(glowa);
    return 0;
}
