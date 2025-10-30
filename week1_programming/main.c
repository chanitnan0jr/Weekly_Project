// ================================================================
//  End Credit:
//  Developed by Chanitnan Kitnantakhun (Chanitnan0jr on GitHub)
//  Weekly C Project for ST217 (Statistics)
// ================================================================
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    double *data;
    int n;
    int bin_size;
} Dataset;

double find_mean(Dataset d);
double find_median(Dataset d);
double find_mode(Dataset d);
double find_stddev(Dataset d);
double find_variance(Dataset d);
void histogram(Dataset d);

int main() {
    Dataset d;
    int i;

    scanf("%d", &d.n);

    d.data = (double*) malloc(d.n * sizeof(double));

    for (i = 0; i < d.n; i++) {
        scanf("%lf", &d.data[i]);
    }

    d.bin_size = 10;

    printf("Mean = %.2f\n", find_mean(d));
    printf("Median = %.2f\n", find_median(d));
    printf("Mode = %.2f\n", find_mode(d));
    printf("Standard Deviation = %.2f\n", find_stddev(d));
    printf("Variance = %.2f\n", find_variance(d));

    printf("\nHistogram:\n");
    histogram(d);

    free(d.data);
    return 0;
}

// Mean
double find_mean(Dataset d) {
    double sum = 0;
    int i;
    for (i = 0; i < d.n; i++) sum += d.data[i];
    return sum / d.n;
}

// Median (ตรงนี้จริง ๆ ต้อง sort array copy ก่อนใช้ median)
double find_median(Dataset d) {
    double *copy = malloc(d.n * sizeof(double));
    double median;
    int i;

    memcpy(copy, d.data, d.n * sizeof(double));

    // bubble sort
    for (i = 0; i < d.n - 1; i++) {
        int j;
        for (j = 0; j < d.n - i - 1; j++) {
            if (copy[j] > copy[j+1]) {
                double temp = copy[j];
                copy[j] = copy[j+1];
                copy[j+1] = temp;
            }
        }
    }

    if (d.n % 2 == 0) 
        median = (copy[d.n/2 - 1] + copy[d.n/2]) / 2.0;
    else 
        median = copy[d.n/2];

    free(copy);
    return median;
}

// Mode
double find_mode(Dataset d) {
    double maxValue = d.data[0];
    int maxCount = 1;
    int i, j;

    for (i = 0; i < d.n; i++) {
        int count = 1;
        for (j = i + 1; j < d.n; j++) {
            if (fabs(d.data[j] - d.data[i]) < 1e-9) count++;
        }
        if (count > maxCount) {
            maxCount = count;
            maxValue = d.data[i];
        }
    }
    return maxValue;
}

// Stddev
double find_stddev(Dataset d) {
    double mean = find_mean(d);
    double sum = 0;
    int i;
    for (i = 0; i < d.n; i++) {
        sum += (d.data[i] - mean) * (d.data[i] - mean);
    }
    return sqrt(sum / d.n); 
}

// Variance
double find_variance(Dataset d) {
    double mean = find_mean(d);
    double sum = 0;
    int i;
    for (i = 0; i < d.n; i++) {
        sum += (d.data[i] - mean) * (d.data[i] - mean);
    }
    return sum / d.n;
}

// Histogram
void histogram(Dataset d) {
    double max = d.data[0];
    int i, j;
    for (i = 1; i < d.n; i++) {
        if (d.data[i] > max) max = d.data[i];
    }

    int bin_count = (int)(max / d.bin_size) + 1; // max numer / bin_size = number of bins
    int *freq = (int*) calloc(bin_count, sizeof(int));

    for (i = 0; i < d.n; i++) {
        int bin_index = (int)(d.data[i] / d.bin_size); // determine which bin 0-9 (0), 10-19(1), ...
        freq[bin_index]++;
    }

    for (i = 0; i < bin_count; i++) {
        int start = i * d.bin_size; // start 0, 10, 20, ...
        int end   = start + d.bin_size - 1; // end 9, 19, 29, ...

        printf("%2d-%2d : ", start, end);
        for (j = 0; j < freq[i]; j++) printf("*");
        printf(" (%d)\n", freq[i]);
    }

    free(freq);
}
