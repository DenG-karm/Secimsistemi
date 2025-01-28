
#include <stdio.h>
#include <string.h>

#define MAX_C 11
typedef struct Candidate {
    char name[50];
    int votes;
    char symbol;
} Candidate;
Candidate allCandidates[MAX_C];
int candidateCount = 0;
char symbols[10]
    = { '!', '@', '#', '$', '%', '^', '&', '*', '~', '+' };
int symbolTaken[11];

void fillCandidate(int);
void displayAllCandidates();
void getVotes(int);
void getResults();

int main()
{
    for (int i = 0; i < 11; i++) {
        symbolTaken[i] = 0;
    }

    printf("Aday sayisini giriniz: ");
    scanf("%d", &candidateCount);
    if (candidateCount >= MAX_C) {
        printf("Aday sayisi 10'dan fazla olamaz.\n Program tekrarlaniyor..\n\n");
        return 0;
    }

    for (int i = 0; i < candidateCount; i++) {
        fillCandidate(i);
    }

    int numVoters;
    printf("Secmen sayisini giriniz: ");
    scanf("%d", &numVoters);

    for (int i = 0; i < numVoters; i++) {
        getVotes(i);
    }

    getResults();

    return 0;
}

void fillCandidate(int cNum)
{
    printf("Mevcut semboller: \n");
    for (int j = 0; j < 10; j++) {
        if (symbolTaken[j] == 1)
            continue;
        printf("%d  %c\n", j + 1, symbols[j]);
    }

    int num = 0;

    printf("%d adayinin sembolunu giriniz: ",cNum + 1);
    scanf("%d", &num);

    if (num <= 0 || num > 10 || symbolTaken[num - 1] == 1) {
        printf("Bu sembol bulunmamakta. Baska bir sembol seciniz..\n");
        num = 0;
        fillCandidate(cNum);
    }
    else {
        symbolTaken[num - 1] = 1;
        allCandidates[cNum].symbol = symbols[num - 1];
        printf("%d adayinin ismini giririnz : ",cNum + 1);
        scanf("%s", allCandidates[cNum].name);

        allCandidates[cNum].votes = 0;
    }
}

void displayAllCandidates()
{
    if (!allCandidates || !candidateCount) {
        perror("Gecersiz secim..Tekrar deneyiniz!\n");
        return;
    }

    for (int j = 0; j < candidateCount; j++) {
        printf("%s\t\t", allCandidates[j].name);
    }
    printf("\n");
    for (int j = 0; j < candidateCount; j++) {
        printf("%3c\t\t\t", allCandidates[j].symbol);
    }
    printf("\n");
}

void getVotes(int voterCount)
{
    displayAllCandidates();
    printf("Secmen %d, seciminizi yapiniz (1-%d): ",
           voterCount + 1, candidateCount);
    int choice;
    scanf("%d", &choice);

    if (choice >= 1 && choice <= candidateCount) {
        allCandidates[choice - 1].votes++;
    }
    else {
        printf("Gecersiz secim..Tekrar deneyiniz!\n");
        getVotes(voterCount);
    }
}

void getResults()
{
    int maxVotes = 0;
    int winnerIndex = -1;
    int winnerFrequency = 0;
    for (int i = 0; i < candidateCount; i++) {
        if (allCandidates[i].votes > maxVotes) {
            maxVotes = allCandidates[i].votes;
            winnerIndex = i;
        }
    }

    for (int i = 0; i < candidateCount; i++) {
        if (allCandidates[i].votes == maxVotes) {
            winnerFrequency++;
        }
    }

    printf("\n-----SONUC-----\n");

    if (winnerFrequency > 1) {
        printf("Hicbir adayin oy üstünlügü yok\n");
    }
    else if (winnerIndex != -1) {
        printf("Kazanan: %s\nAday sembolü: "
               "%c\n %d oyla!\n",
               allCandidates[winnerIndex].name,
               allCandidates[winnerIndex].symbol, maxVotes);
    }
    else {
        printf("Kazanan yok\n");
    }
}