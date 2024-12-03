#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10007

typedef struct {
    int key;
    int count;
} HashEntry;

HashEntry *hashTable[TABLE_SIZE];

unsigned int hash(int key) {
    return key % TABLE_SIZE;
}

void insert(int key) {
    unsigned int index = hash(key);

    // If DNE, create a new one
    if (hashTable[index] == NULL) {
        hashTable[index] = (HashEntry *)malloc(sizeof(HashEntry));
        hashTable[index]->key = key;
        hashTable[index]->count = 1;
    } else {
        // increment its count
        if (hashTable[index]->key == key) {
            hashTable[index]->count++;
        } else {
            // If collision, linear probing
            unsigned int originalIndex = index;
            index = (index + 1) % TABLE_SIZE;
            while (index != originalIndex && hashTable[index] != NULL && hashTable[index]->key != key) {
                index = (index + 1) % TABLE_SIZE;
            }
            if (hashTable[index] == NULL) {
                hashTable[index] = (HashEntry *)malloc(sizeof(HashEntry));
                hashTable[index]->key = key;
                hashTable[index]->count = 1;
            } else {
                hashTable[index]->count++;
            }
        }
    }
}

int lookup(int key) {
    unsigned int index = hash(key);

    unsigned int originalIndex = index;
    while (hashTable[index] != NULL) {
        if (hashTable[index]->key == key) {
            return hashTable[index]->count;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            break;
        }
    }

    return 0;
}

void similarity(int l1[], int l2[], int size) {
    int similarity = 0;
    for (int i = 0; i < size; i++) {
        insert(l2[i]);
    }
    for (int i = 0; i < size; i++) {
        int freq = lookup(l1[i]);
        printf("%d %d\n", l1[i], freq);
        similarity += l1[i] * freq;
    }
    printf("Similarity: %d\n", similarity);
}

int main() {
    FILE *file = fopen("day1.txt", "r");
    int size = 1000;
    int distance_sum = 0;

    // store input in two lists
    int l1[size], l2[size];
    int i = 0;
    while (fscanf(file, "%d %d", &l1[i], &l2[i]) != EOF) {
        i++;
    }

    // sort two lists
    int j, temp;
    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (l1[i] > l1[j]) {
                temp = l1[i];
                l1[i] = l1[j];
                l1[j] = temp;
            }
            if (l2[i] > l2[j]) {
                temp = l2[i];
                l2[i] = l2[j];
                l2[j] = temp;
            }
        }
    }

    // calculate distance sum
    for (i = 0; i < size; i++) {
        int d = l2[i] - l1[i];
        if (d < 0) {
            d = -d;
        }
        distance_sum += d;
        printf("%d %d %d\n", l1[i], l2[i], d);
    }
    printf("Distance sum: %d\n", distance_sum);

    fclose(file);

    similarity(l1, l2, size);
}
