#include <stdio.h>

int main() {
    int coins[] = {25, 10, 5, 1}; // Coin denominations
    int n = sizeof(coins)/sizeof(coins[0]);
    int amount = 63;               // Amount to change

    printf("Coins used to make %d: ", amount);

    for(int i=0; i<n; i++){
        while(amount >= coins[i]){
            amount -= coins[i];
            printf("%d ", coins[i]);
        }
    }
    printf("\n");
    return 0;
}
