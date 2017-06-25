#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>

// http://netlib.org/linalg/html_templates/node92.html#SECTION00931200000000000000
// http://netlib.org/linalg/html_templates/node91.html#sparseA
int main() {

    int num_of_ratings = 19;
    int num_of_rows = 6;
    int num_of_cols = 6;

    // CRS
    float rating_scores[] = {10, -2, 3, 9, 3, 7, 8, 7, 3, 8, 7, 5, 8, 9, 9, 13, 4, 2, -1};
    int csr_col_idx[] = {0, 4, 0, 1, 5, 1, 2, 3, 0, 2, 3, 4, 1, 3, 4, 5, 1, 4, 5};
    int csr_row_ptr[] = {0, 2, 5, 8, 12, 16, 19};

    // CCS
    float rating_scores_t[num_of_ratings];
    int ccs_col_ptr[num_of_cols + 1] = {0};
    int ccs_row_idx[num_of_ratings];
    int nn[num_of_cols + 1];

    int k = 0;
    int reverse_row_index[num_of_ratings]; // each value belongs to which row
    for (int i = 0; i < num_of_rows; i++) {
        for (int j = 0; j < csr_row_ptr[i + 1] - csr_row_ptr[i]; j++) {
            reverse_row_index[k] = i;
            k++;
        }
    }

    for (int i = 0; i < num_of_ratings; i++) {
        ccs_col_ptr[csr_col_idx[i] + 1]++;
    }
    for (int i = 1; i <= num_of_cols; i++) {
        ccs_col_ptr[i] += ccs_col_ptr[i - 1];
    }
    memcpy(nn, ccs_col_ptr, sizeof(ccs_col_ptr));

    for (int i = 0; i < num_of_ratings; i++) {
        int x = nn[csr_col_idx[i]];
        nn[csr_col_idx[i]] += 1;
        rating_scores_t[x] = rating_scores[i];
        ccs_row_idx[x] = reverse_row_index[i];
    }

    for (int i = 0; i < num_of_ratings; i++) printf("%2.0f ", rating_scores_t[i]);
    putchar('\n');
    for (int i = 0; i < num_of_ratings; i++) printf("%2d ", ccs_row_idx[i]);
    putchar('\n');
    for (int i = 0; i < num_of_cols + 1; i++) printf("%2d ", ccs_col_ptr[i]);
    putchar('\n');

    return 0;
}