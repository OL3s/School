#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Buffer size for reading/writing files to speed up I/O operations
#define BUFFER_SIZE 1024

// ==== Data structures ====

// Huffman node structure (same as compressor)
typedef struct HuffmanNode {
    unsigned char character;
    int frequency;
    struct HuffmanNode* left;
    struct HuffmanNode* right;
} HuffmanNode;

// ==== Function prototypes ====

HuffmanNode* create_node(unsigned char character, int frequency);
HuffmanNode* build_huffman_tree(int frequencies[256]);
void decompress_file(FILE* input, FILE* output, HuffmanNode* root);
void free_tree(HuffmanNode* node);
int compare_nodes(const void* a, const void* b);

// ==== Main function ====

int main(int argc, char *argv[]) {

    // Missing argument check
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <compressed_file.huff> [--mkdir]\n", argv[0]);
        return 1;
    }

    // Check for optional --mkdir flag
    int use_mkdir = 0;
    if (argc >= 3 && strcmp(argv[2], "--mkdir") == 0) {
        use_mkdir = 1;
    }

    // Open compressed file for reading
    FILE *input_file = fopen(argv[1], "rb"); // Binary mode
    if (!input_file) {
        perror("Failed to open compressed file");
        return 1;
    }

    // 1: Read frequency table from file header
    int frequencies[256];
    if (fread(frequencies, sizeof(int), 256, input_file) != 256) {
        fprintf(stderr, "Failed to read frequency table from compressed file\n");
        fclose(input_file);
        return 1;
    }

    // 2: Build Huffman tree from frequencies
    HuffmanNode* root = build_huffman_tree(frequencies);
    if (!root) {
        fprintf(stderr, "Failed to build Huffman tree\n");
        fclose(input_file);
        return 1;
    }

    // 3: Create output filename - restore original format
    char output_filename[256];
    char* base_name = strdup(argv[1]);      // Duplicate input filename
    
    // Remove .huff extension to restore original filename
    if (strlen(base_name) > 5 && strcmp(base_name + strlen(base_name) - 5, ".huff") == 0) {
        base_name[strlen(base_name) - 5] = '\0';  // Remove .huff extension
    }

    // Include export_decomp/ prefix if --mkdir flag is used
    if (use_mkdir) {
        // Extract directory path from input file
        char* input_dir = strdup(argv[1]);
        char* last_slash = strrchr(input_dir, '/');
        char* filename_only = base_name;
        
        if (last_slash) {
            *last_slash = '\0';  // Split directory and filename
            char* temp_filename = strrchr(base_name, '/');
            filename_only = temp_filename ? temp_filename + 1 : base_name;
            
            // Create export_decomp directory in same location as input file
            char mkdir_cmd[512];
            #ifdef _WIN32
                snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir \"%s\\export_decomp\" 2>nul", input_dir);
            #else
                snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir -p \"%s/export_decomp\"", input_dir);
            #endif
            system(mkdir_cmd);
            
            snprintf(output_filename, sizeof(output_filename), "%s/export_decomp/%s", input_dir, filename_only);
        } else {
            // No directory in path, create export_decomp in current directory
            #ifdef _WIN32
                system("mkdir export_decomp 2>nul");
            #else
                system("mkdir -p export_decomp");
            #endif
            snprintf(output_filename, sizeof(output_filename), "export_decomp/%s", filename_only);
        }
        free(input_dir);
    } else {
        snprintf(output_filename, sizeof(output_filename), "%s", base_name);
    }
    free(base_name);

    // 4: Open output file for writing
    FILE *output_file = fopen(output_filename, "wb"); // Binary mode
    if (!output_file) {
        perror("Failed to create output file");
        fclose(input_file);
        free_tree(root);
        return 1;
    }

    // 5: Decompress and write to output file
    decompress_file(input_file, output_file, root);

    // Cleanup
    fclose(input_file);
    fclose(output_file);
    free_tree(root);

    printf("File decompressed successfully to %s\n", output_filename);
    return 0;
}

// ==== Implementation of functions ====

HuffmanNode* create_node(unsigned char character, int frequency) {
    HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    if (!node) return NULL; // Memory allocation failed
    
    node->character = character; // Set character of the node
    node->frequency = frequency; // Frequency from original file
    node->left = NULL;           // Initialize left child
    node->right = NULL;          // Initialize right child
    return node;
}

// Compare function for sorting nodes by frequency (used in qsort)
int compare_nodes(const void* a, const void* b) {
    HuffmanNode* nodeA = *(HuffmanNode**)a;
    HuffmanNode* nodeB = *(HuffmanNode**)b;
    return nodeA->frequency - nodeB->frequency; // Ascending order
}

// Build Huffman tree using the same algorithm as compressor
HuffmanNode* build_huffman_tree(int frequencies[256]) {
    // Count how many characters have frequency > 0
    int char_count = 0;
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            char_count++;
        }
    }
    
    if (char_count == 0) return NULL; // No characters to decode
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
    
    // Build tree bottom-up (same as compressor)
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

// Decompress the file by traversing the Huffman tree
void decompress_file(FILE* input, FILE* output, HuffmanNode* root) {
    if (!root) return;
    
    // Handle special case: single character file
    if (!root->left && !root->right) {
        // Single character file - write character frequency times
        for (int i = 0; i < root->frequency; i++) {
            fputc(root->character, output);
        }
        return;
    }
    
    unsigned char input_buffer[BUFFER_SIZE];
    unsigned char output_buffer[BUFFER_SIZE];
    int output_pos = 0;
    
    HuffmanNode* current = root;
    size_t bytes_read;
    
    // Read compressed data in chunks
    while ((bytes_read = fread(input_buffer, 1, BUFFER_SIZE, input)) > 0) {
        for (size_t i = 0; i < bytes_read; i++) {
            unsigned char byte = input_buffer[i];
            
            // Process each bit in the byte (from left to right)
            for (int bit = 7; bit >= 0; bit--) {
                int bit_value = (byte >> bit) & 1;
                
                // Navigate tree: 0 = left, 1 = right
                if (bit_value == 0) {
                    current = current->left;
                } else {
                    current = current->right;
                }
                
                // If we reached a leaf node, we found a character
                if (current && !current->left && !current->right) {
                    output_buffer[output_pos++] = current->character;
                    current = root; // Reset to root for next character
                    
                    // Flush output buffer if full
                    if (output_pos >= BUFFER_SIZE) {
                        fwrite(output_buffer, 1, output_pos, output);
                        output_pos = 0;
                    }
                }
                
                // Safety check for malformed data
                if (!current) {
                    fprintf(stderr, "Warning: Invalid bit sequence in compressed data\n");
                    current = root;
                }
            }
        }
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