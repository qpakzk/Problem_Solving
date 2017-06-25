#include <cstdio>

void check_prime(int, bool[]);

int main() {
    int N;
    scanf("%d", &N);

    int max_price = 0;
    int sum_prices = 0;
    int price;
    int candy[10001] = {0};
    for(int i = 0; i < N; i++) {
        scanf("%d", &price);
        if(max_price < price)
            max_price = price;
        sum_prices += price;
        candy[price]++;
    }

/*
    printf("candy : ");
    for(int i = 0; i <= max_price; i++) {
        printf("%d ", candy[i]);
    }
    printf("\n");
*/


    long long S[sum_prices + 1];
    long long S_temp[sum_prices + 1];
    for(int i = 0; i <= sum_prices; i++) {
        S[i] = 0;
        S_temp[i] = 0;
    }

    int turn;
    for(int p = 0; p <= max_price; p++) {
        if(candy[p] == 0)
            continue;
        for(int c = 1; c <= candy[p]; c++)
            S[c * p]++;
        turn = p;
        break;
    }

/*
    for(int i = 0; i <= sum_prices; i++)
        printf("%d ", S[i]);
    printf("\n");
*/

    for(int p = turn + 1; p <= max_price; p++) {
        if(candy[p] == 0)
            continue;
        for(int q = 0; q <= sum_prices;  q++)
            S_temp[q] = S[q];
        for(int c = 1; c <= candy[p]; c++) {
            S_temp[c * p]++;

            int s = 0;
            while(s <= sum_prices) {
                if(S[s] == 0){
                    s++;
                    continue;
                }

                S_temp[c * p + s] += S[s];
                s++;
            }
        }
/*
        for(int i = 0; i <= sum_prices; i++)
            printf("%d ", S_temp[i]);
        printf("\n");

*/
        for(int i = 0; i <= sum_prices; i++)
            S[i] = S_temp[i];
    }



    bool prime[sum_prices + 1];
    prime[0] = false;
    prime[1] = false;
    for(int i = 2; i <= sum_prices; i++)
        prime[i] = true;
    check_prime(sum_prices, prime);

    long long res = 0;
    for(int i = 0; i <= sum_prices; i++) {
        if(prime[i])
            res += S[i];
    }
    printf("%lld\n", res);

    return 0;
}

void check_prime(int number, bool prime[]) {
    for(int i = 2; i * i <= number; i++) {
        if(prime[i]) {
            for(int j = i * 2; j <= number; j += i)
                prime[j] = false;
        }
    }
}