#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 // Buffer size for reading/writing files to speed up I/O operations (not using essesivly fwrite/fread)
#define BUFFER_SIZE 1024

// ==== Data structures ====

// Huffman node structure
typedef struct HuffmanNode {
    unsigned char character;
    int frequency;
    struct HuffmanNode* left;
    struct HuffmanNode* right;
} HuffmanNode;

// Structure to store Huffman codes
typedef struct {
    char* code; // Represents the bit string for the code
    int length; // Length of the code in bits
} HuffmanCode;

// ==== Function prototypes ====

HuffmanNode* create_node(unsigned char character, int frequency);
HuffmanNode* build_huffman_tree(int frequencies[256]);
void generate_codes(HuffmanNode* root, HuffmanCode codes[256], char* current_code, int depth);
void count_frequencies(FILE* file, int frequencies[256]);
void compress_file(FILE* input, FILE* output, HuffmanCode codes[256], int frequencies[256]);
void free_tree(HuffmanNode* node);
int compare_nodes(const void* a, const void* b);

// ==== Main function ====

int main(int argc, char *argv[]) {

    // Missing argument check
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename> [--mkdir]\n", argv[0]);
        return 1;
    }

    // Check for optional --mkdir flag
    int use_mkdir = 0;
    if (argc >= 3 && strcmp(argv[2], "--mkdir") == 0) {
        use_mkdir = 1;
    }

    // Open file for reading
    FILE *file = fopen(argv[1], "rb"); // Binary mode
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    // 1: Count frequencies
    int frequencies[256] = {0};
    count_frequencies(file, frequencies);

    // 2: Build Huffman tree
    HuffmanNode* root = build_huffman_tree(frequencies);
    if (!root) { // Handle empty file case
        fprintf(stderr, "Failed to build Huffman tree\n");
        fclose(file);
        return 1;
    }

    // 3: Generate Huffman codes (each code replaces a character)
    HuffmanCode codes[256]; // Array with 256 elements, can only handle language with 256 unique characters
    for (int i = 0; i < 256; i++) {
        codes[i].code = NULL; // Initialize code pointers
        codes[i].length = 0;  // Initialize lengths
    }
    
    char temp_code[256];
    generate_codes(root, codes, temp_code, 0); // Generate codes (character to binary string)

    // 4: Create output filename - keep original extension and add .huff
    char output_filename[256];
    
    // Include export_comp/ prefix if --mkdir flag is used
    if (use_mkdir) {
        // Extract directory path from input file
        char* input_dir = strdup(argv[1]);
        char* last_slash = strrchr(input_dir, '/');
        char* filename_only = argv[1];
        
        // If there is a directory in the path
        if (last_slash) {
            *last_slash = '\0';  // Split directory and filename
            filename_only = last_slash + 1;
            
            // Create export_comp directory in same location as input file
            char mkdir_cmd[512];
            #ifdef _WIN32
                snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir \"%s\\export_comp\" 2>nul", input_dir);
            #else
                snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir -p \"%s/export_comp\"", input_dir);
            #endif
            system(mkdir_cmd);
            
            snprintf(output_filename, sizeof(output_filename), "%s/export_comp/%s.huff", input_dir, filename_only);

        // Create the output directory if it doesn't exist
        } else {
            // No directory in path, create export_comp in current directory
            #ifdef _WIN32
                system("mkdir export_comp 2>nul");
            #else
                system("mkdir -p export_comp");
            #endif
            snprintf(output_filename, sizeof(output_filename), "export_comp/%s.huff", filename_only);
        }
        free(input_dir);

    // Create output filename without export_comp/ prefix
    } else {
        snprintf(output_filename, sizeof(output_filename), "%s.huff", argv[1]);
    }
    
    // Step 5: Compress and write to output file
    FILE *output = fopen(output_filename, "wb"); // Binary mode (write binary)
    if (!output) {  // Handle file creation error
        perror("Failed to create output file");
        fclose(file);
        free_tree(root);
        return 1;
    }
    
    compress_file(file, output, codes, frequencies); // Compress and write to output
    
    // Cleanup
    fclose(file);
    fclose(output);
    free_tree(root);
    
    // Free allocated code strings
    for (int i = 0; i < 256; i++) {
        if (codes[i].code) {
            free(codes[i].code);
        }
    }
    
    printf("File compressed successfully to %s\n", output_filename);
    return 0;
}

// ==== Implementation of functions ====

HuffmanNode* create_node(unsigned char character, int frequency) {
    HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    if (!node) return NULL; // Memory allocation failed
    
    node->character = character; // Set character of the node
    node->frequency = frequency; // High frequency = High priority (how many of that char it found)
    node->left = NULL;           // Initialize left child
    node->right = NULL;          // Initialize right child
    return node;
}

// Count frequency of each byte in the file (0-255)
void count_frequencies(FILE* file, int frequencies[256]) {
    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;
    
    // Reset file pointer to beginning
    fseek(file, 0, SEEK_SET);

    // Read file in chunks to count frequencies
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        for (size_t i = 0; i < bytes_read; i++) {
            frequencies[buffer[i]]++;
        }
    }
}

// Compare function for sorting nodes by frequency (used in qsort)
int compare_nodes(const void* a, const void* b) {
    HuffmanNode* nodeA = *(HuffmanNode**)a;
    HuffmanNode* nodeB = *(HuffmanNode**)b;
    return nodeA->frequency - nodeB->frequency; // Ascending order
}

// Build Huffman tree using a simple array-based priority queue
HuffmanNode* build_huffman_tree(int frequencies[256]) {
    // Count how many characters have frequency > 0
    int char_count = 0;
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            char_count++;
        }
    }
    
    if (char_count == 0) return NULL; // No characters to encode
    if (char_count == 1) {
        // Special case: only one character
        for (int i = 0; i < 256; i++) {
            if (frequencies[i] > 0) {
                return create_node((unsigned char)i, frequencies[i]);
            }
        }
    }

    // char_count >= 2 from here on
    
    // Create array of nodes
    HuffmanNode** nodes = (HuffmanNode**)malloc(char_count * sizeof(HuffmanNode*));
    if (!nodes) return NULL;
    
    // Fill array with leaf nodes (characters with frequency > 0)
    int index = 0;
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            nodes[index++] = create_node((unsigned char)i, frequencies[i]);
        }
    }
    
    // Build tree bottom-up
    int active_nodes = char_count;
    while (active_nodes > 1) {
        // Sort nodes by frequency
        qsort(nodes, active_nodes, sizeof(HuffmanNode*), compare_nodes);
        
        // Take two nodes with lowest frequency
        HuffmanNode* left = nodes[0];
        HuffmanNode* right = nodes[1];

        // Create new internal node (parent)
        HuffmanNode* parent = create_node(0, left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        
        // Replace first two nodes with the new parent
        nodes[0] = parent;
        // Shift remaining nodes
        for (int i = 1; i < active_nodes - 1; i++) {
            nodes[i] = nodes[i + 1];
        }
        active_nodes--; // Reduce active node count
    }
    
    // The remaining node is the root
    HuffmanNode* root = nodes[0];
    free(nodes);
    return root;
}

// Generate Huffman codes recursively
void generate_codes(HuffmanNode* root, HuffmanCode codes[256], char* current_code, int depth) {
    if (!root) return;
    
    // If it's a leaf node
    if (!root->left && !root->right) {

        // Leaf node found
        if (depth == 0) {
            // Special case: single character file
            codes[root->character].code = malloc(2);
            strcpy(codes[root->character].code, "0");
            codes[root->character].length = 1;

        // Normal case: multiple characters
        } else {
            codes[root->character].code = malloc(depth + 1);
            strncpy(codes[root->character].code, current_code, depth);
            codes[root->character].code[depth] = '\0';
            codes[root->character].length = depth;
        }
        return;
    }
    
    // Traverse left ( <- add '0')
    if (root->left) {
        current_code[depth] = '0';
        generate_codes(root->left, codes, current_code, depth + 1);
    }
    
    // Traverse right ( -> add '1')
    if (root->right) {
        current_code[depth] = '1';
        generate_codes(root->right, codes, current_code, depth + 1);
    }
}

// Compress the file and write to output
void compress_file(FILE* input, FILE* output, HuffmanCode codes[256], int frequencies[256]) {
    // Write frequency table first (header)
    fwrite(frequencies, sizeof(int), 256, output);
    
    // Reset input file pointer
    fseek(input, 0, SEEK_SET);

    // Read file in chunks to count frequencies
    unsigned char input_buffer[BUFFER_SIZE];
    unsigned char output_buffer[BUFFER_SIZE];
    int output_pos = 0;
    unsigned char bit_buffer = 0;
    int bits_in_buffer = 0;
    
    size_t bytes_read; // set of bytes read

    // Read input file in chunks
    while ((bytes_read = fread(input_buffer, 1, BUFFER_SIZE, input)) > 0) { // While there are bytes to read
        for (size_t i = 0; i < bytes_read; i++) {
            unsigned char byte = input_buffer[i]; // Get the byte
            char* code = codes[byte].code;        // Get the corresponding Huffman code
            
            if (!code) continue; // Skip if no code just in case
            
            // Write each bit of the code
            for (int j = 0; j < codes[byte].length; j++) {
                // Add bit to buffer
                bit_buffer = (bit_buffer << 1) | (code[j] - '0');
                bits_in_buffer++;
                
                // If buffer is full, write to output (next byte)
                if (bits_in_buffer == 8) {
                    output_buffer[output_pos++] = bit_buffer;
                    bit_buffer = 0;
                    bits_in_buffer = 0;

                    // Flush output buffer if full (BUFFER_SIZE reached)
                    if (output_pos >= BUFFER_SIZE) {
                        fwrite(output_buffer, 1, output_pos, output);
                        output_pos = 0;
                    }
                }
            }
        }
    }
    
    // Handle remaining bits after file reading
    if (bits_in_buffer > 0) {
        bit_buffer <<= (8 - bits_in_buffer);
        output_buffer[output_pos++] = bit_buffer;
    }
    
    // Write remaining output buffer
    if (output_pos > 0) {
        fwrite(output_buffer, 1, output_pos, output);
    }
}

// Free the Huffman tree memory
void free_tree(HuffmanNode* node) {
    if (!node) return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}