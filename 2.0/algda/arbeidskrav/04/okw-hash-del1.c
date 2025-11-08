#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 127  // Size of the hash table (prime number for better distribution)

typedef struct Entry {
    char *key;
    char *value;
    struct Entry *next;
} Entry;

Entry *hashTable[TABLE_SIZE];

// Global variables for statistics
int totalCollisions = 0;
int totalEntries = 0;

// Hash function that weights character positions differently
unsigned int hash(char *key) {
    unsigned int hash = 5381;  // Prime number seed
    int i = 0;
    
    // A variation of the djb2 algorithm with position weighting
    while (key[i]) {
        hash = ((hash << 5) + hash) + key[i] * (i + 1);
        i++;
    }
    return hash % TABLE_SIZE;
}

// Insert key-value pair into the hash table
void insert(char *key, char *value) {
    unsigned int index = hash(key);
    
    // Check for collision
    if (hashTable[index] != NULL) {
        totalCollisions++;
        printf("Collision detected: %-38s %-38s [%u]\n", 
               key, hashTable[index]->key, index);
    }

    // Create new entry with collision handling
    Entry *newEntry = malloc(sizeof(Entry));
    if (!newEntry) {
        printf("Memory allocation failed\n");
        return;
    }
    
    // New entry points to the current head of the chain
    newEntry->key = strdup(key);
    newEntry->value = strdup(value);
    newEntry->next = hashTable[index];
    hashTable[index] = newEntry;
    totalEntries++;
}

// Search for a key in the hash table
char* search(char *key) {
    unsigned int index = hash(key);
    Entry *entry = hashTable[index];
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;  // Not found
}

// Delete a key from the hash table
void delete(char *key) {
    unsigned int index = hash(key);
    Entry *entry = hashTable[index];
    Entry *prev = NULL;
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                hashTable[index] = entry->next;
            }
            free(entry->key);
            free(entry->value);
            free(entry);
            totalEntries--;
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

// Free the entire hash table
void freeHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *entry = hashTable[i];
        while (entry) {
            Entry *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
        hashTable[i] = NULL;  // Reset to NULL
    }
    totalEntries = 0;
    totalCollisions = 0;
}

// Function to read names from file
void readNamesFromFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file '%s'\n", filename);
        printf("Please make sure the file exists in the current directory.\n\n");
        return;
    }
    
    char name[256];
    int lineCount = 0;
    
    printf("Reading names from file '%s'\n\n", filename);
    
    while (fgets(name, sizeof(name), file)) {
        // Remove newline character
        name[strcspn(name, "\n")] = '\0';
        
        // Skip empty lines
        if (strlen(name) == 0) {
            continue;
        }
        
        // Insert name as both key and value
        insert(name, name);
        lineCount++;
    }
    
    fclose(file);
    printf("Successfully read %d names from file.\n\n", lineCount);
}

// Function to display hash table statistics
void displayStatistics() {
    printf("=== HASH TABLE STATISTICS ===\n");
    printf("Table size: %d\n", TABLE_SIZE);
    printf("Total entries: %d\n", totalEntries);
    printf("Total collisions: %d\n", totalCollisions);
    
    if (totalEntries > 0) {
        double loadFactor = (double)totalEntries / TABLE_SIZE;
        double collisionRate = (double)totalCollisions / totalEntries * 100;
        double avgCollisionsPerPerson = (double)totalCollisions / totalEntries;
        
        printf("Load factor: %.3f\n", loadFactor);
        printf("Collision rate: %.2f%%\n", collisionRate);
        printf("Average collisions per person: %.3f\n", avgCollisionsPerPerson);
    }
    
    // Count non-empty slots
    int usedSlots = 0;
    int maxChainLength = 0;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != NULL) {
            usedSlots++;
            
            // Count chain length
            int chainLength = 0;
            Entry *entry = hashTable[i];
            while (entry) {
                chainLength++;
                entry = entry->next;
            }
            
            if (chainLength > maxChainLength) {
                maxChainLength = chainLength;
            }
        }
    }
    
    printf("Used slots: %d/%d (%.1f%%)\n", usedSlots, TABLE_SIZE, 
           (double)usedSlots / TABLE_SIZE * 100);
    printf("Maximum chain length: %d\n", maxChainLength);
    printf("==============================\n\n");
}

// Function to display the hash table contents.
void displayHashTable() {
    printf("=== HASH TABLE CONTENTS ===\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != NULL) {
            printf("Index %d: ", i);
            Entry *entry = hashTable[i];
            while (entry) {
                printf("'%s'", entry->key);
                if (entry->next) {
                    printf(" -> ");
                }
                entry = entry->next;
            }
            printf("\n");
        }
    }
    printf("===========================\n\n");
}

// Function to test specific names (for demonstration)
void testSpecificNames() {
    printf("=== TESTING SPECIFIC NAMES ===\n");
    
    // Test names that might cause collisions
    char *testNames[] = {"Caro", "Cora", "Anna", "Nana", "Ole", "Leo"};
    int numTests = sizeof(testNames) / sizeof(testNames[0]);
    
    for (int i = 0; i < numTests; i++) {
        unsigned int hashValue = hash(testNames[i]);
        printf("'%s' -> hash: %u\n", testNames[i], hashValue);
    }
    printf("\n");
}

int main() {
    // Initialize hash table to NULL
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
    
    printf("=== HASH TABLE IMPLEMENTATION ===\n");
    printf("Table size: %d\n\n", TABLE_SIZE);
    
    // Test anagram handling
    testSpecificNames();
    
    // Try to read names from file
    printf("=== READING FROM FILE ===\n");
    readNamesFromFile("navn.txt");
    
    // Display final statistics
    displayStatistics();
    
    // Uncomment the line below to see the full hash table contents
    // displayHashTable();
    
    // Test search functionality
    printf("=== TESTING SEARCH ===\n");
    char *searchName = "Ole-Kristian,Wigum";
    char *result = search(searchName);
    if (result) {
        printf("Found: '%s'\n", result);
    } else {
        printf("Warning: '%s' not found\n", searchName);
    }
    
    searchName = "NonExistent";
    result = search(searchName);
    if (result) {
        printf("Found: '%s'\n", result);
    } else {
        printf("Warning: '%s' not found\n", searchName);
    }
    printf("\n");
    
    // Clean up
    printf("Cleaning up memory...\n");
    freeHashTable();
    printf("Program completed successfully.\n");
    
    return 0;
}