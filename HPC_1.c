
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

void computeLPSArrayParallel(char *pattern, int m, int *lps) {
    int len = 0;
    lps[0] = 0;  // LPS[0] is always 0

    #pragma omp parallel for shared(lps, pattern)
    for (int i = 1; i < m; i++) {
        while (len > 0 && pattern[len] != pattern[i]) {
            len = lps[len - 1];
        }
        if (pattern[len] == pattern[i]) {
            len++;
        }
        lps[i] = len;
    }
}

void KMPSearch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    // Edge case: Empty pattern
    if (m == 0) {
        printf("Error: Pattern cannot be empty.\n");
        return;
    }

    // Allocate memory for the LPS array
    int *lps = (int *)malloc(m * sizeof(int));
    if (!lps) {
        fprintf(stderr, "Memory allocation for LPS array failed.\n");
        return;
    }

    // Compute the LPS array in parallel
    computeLPSArrayParallel(pattern, m, lps);

    printf("LPS Array: ");
    for (int i = 0; i < m; i++) {
        printf("%d ", lps[i]);
    }
    printf("\n");

    int i = 0;  // Index for text
    int j = 0;  // Index for pattern
    int found = 0;

    // Pattern matching
    while (i < n) {
        // Debugging prints to check values of i and j
        printf("Comparing text[%d] = '%c' with pattern[%d] = '%c'\n", i, text[i], j, pattern[j]);

        if (text[i] == pattern[j]) {
            i++;
            j++;
            printf("Characters match. Incrementing indices: i = %d, j = %d\n", i, j);
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            found = 1;
            j = lps[j - 1];  // Reset j using the LPS array
            printf("Pattern found. Reset j to %d\n", j);
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1];  // Use LPS to shift the pattern
                printf("Mismatch found. Moving j to %d\n", j);
            } else {
                i++;  // Increment i if j is already at 0
                printf("Mismatch found. Moving i to %d\n", i);
            }
        }
    }

    if (!found) {
        printf("Pattern not found in the text.\n");
    }

    // Free allocated memory
    free(lps);
}

int main() {
    char text[100], pattern[100];

    // Input text and pattern
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';  // Remove newline character

    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';  // Remove newline character

    // Perform KMP search
    KMPSearch(text, pattern);

    return 0;
}
