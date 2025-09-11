#include <stdio.h>
#include <math.h>

// Fakultet-funksjon
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++)
        result *= i;
    return result;
}

// Binomisk sannsynlighet: P(X = k)
double binom_prob(int n, int k, double p) {
    unsigned long long comb = factorial(n) / (factorial(k) * factorial(n - k));
    return comb * pow(p, k) * pow(1 - p, n - k);
}

int main() {
    int n = 20;
    double p = 0.4;
    double cum_prob = 0.0;

    // Summerer sannsynligheten for X <= 8
    for (int k = 0; k <= 8; k++) {
        cum_prob += binom_prob(n, k, p);
    }

    printf("P(X <= 8) = %.4f\n", cum_prob);

    return 0;
}
