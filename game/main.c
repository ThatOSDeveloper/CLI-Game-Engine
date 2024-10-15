#include <api.h> // Player and item structs
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>

Player player;
Items item;

// Function to get a random number in a specified range
int get_random_number(int min, int max) {
    return rand() % (max - min + 1) + min; // Random number between min and max
}

// Function to display the player's money
void check_money() {
    printf("Money: %d\n", player.money);
}

// Function to sell an item
void sell_item(int type, int amount) {
    clearScreen();
    if (amount <= 0) {
        printf("Invalid amount of items.\n");
        return;
    }

    switch (type) {
        case 0: // Common
            if (item.commonitem < amount) {
                printf("Not enough common items to sell.\n");
            } else {
                player.money += amount; // Each common item is worth one
                item.commonitem -= amount; // Reduce inventory
                printf("Sold %d common item(s).\n", amount);
            }
            break;
        case 1: // Uncommon
            if (item.uncommonitem < amount) {
                printf("Not enough uncommon items to sell.\n");
            } else {
                player.money += 3 * amount; // Each uncommon item is worth three
                item.uncommonitem -= amount; // Reduce inventory
                printf("Sold %d uncommon item(s).\n", amount);
            }
            break;
        case 2: // Rare
            if (item.rareitem < amount) {
                printf("Not enough rare items to sell.\n");
            } else {
                player.money += 5 * amount; // Each rare item is worth five
                item.rareitem -= amount; // Reduce inventory
                printf("Sold %d rare item(s).\n", amount);
            }
            break;
        default:
            printf("Invalid item type.\n");
    }
}

// Function to buy an item
void buy_item(int type) {
    clearScreen();
    int base_price;
    switch (type) {
        case 0: // Common
            base_price = 1;
            break;
        case 1: // Uncommon
            base_price = 3;
            break;
        case 2: // Rare
            base_price = 5;
            break;
        default:
            printf("Invalid item type.\n");
            return;
    }

    // Calculate price with random variation
    int variation = get_random_number(1, 3); 
    int price_adjustment = get_random_number(0, 1) == 0 ? variation : -variation;
    int final_price = base_price + price_adjustment;
    if (final_price < 1) final_price = 1; // Ensure price is at least 1

    printf("The price is %d. ", final_price);
    int confirm_buy = 0;

    // Ask for confirmation
    while (1) {
        askintquestion("Are you sure you want to buy this item?", 2, &confirm_buy, "Yes", "No");
        if (confirm_buy >= 0 && confirm_buy <= 1) break; // Break if input is valid
        printf("Invalid input. Please choose 0 for Yes or 1 for No.\n");
    }

    if (confirm_buy == 0) { // User confirmed buying
        if (player.money >= final_price) {
            // Update player's inventory based on item type
            switch (type) {
                case 0:
                    item.commonitem++;
                    break;
                case 1:
                    item.uncommonitem++;
                    break;
                case 2:
                    item.rareitem++;
                    break;
            }
            player.money -= final_price; // Deduct price from player's money
            printf("Purchased item successfully.\n");
        } else {
            printf("Not enough money to buy this item.\n");
        }
    }
}

void list_inventory() {
    printf("Common items: %d\n", item.commonitem);
    printf("Uncommon items: %d\n", item.uncommonitem);
    printf("Rare items: %d\n", item.rareitem);
}

int main() {
    srand(time(NULL)); // Initialize random seed

    // Initialize player and items
    player.money = 10; // Starting money
    item.commonitem = 5; // Starting common items
    item.uncommonitem = 1; // Starting uncommon items
    item.rareitem = 0; // Starting rare items

    printf("Welcome to Survival 101.\n");
    printf("You only have one job: survive and make as much money as you can.\n");

    while (1) {
        int action = 0;

        // Display options without clearing the screen
        printf("\n");
        check_money(); // Display money
        askintquestion("Would you like to", 3, &action, "Sell stuff", "Buy stuff", "Check inventory");
        
        // Debug output to check selected option
        printf("You selected option %d\n", action);

        switch (action) {
            case 0: { // Selling items
                clearScreen();
                int type = 0, amount = 0;
                
                // Ask for type of item to sell
                while (1) {
                    clearScreen();
                    askintquestion("What type of item do you want to sell?", 3, &type, "Common", "Uncommon", "Rare");
                    if (type >= 0 && type <= 2) break; // Break if input is valid
                    printf("Invalid input. Please choose 0, 1, or 2.\n");
                }

                // Ask for amount to sell
                while (1) {
                    clearScreen();
                    askintquestion("What amount do you want to sell?", 1, &amount);
                    if (amount > 0) break; // Break if amount is valid
                    printf("Invalid amount. Please enter a number greater than 0.\n");
                }
                
                sell_item(type, amount); // Sell item based on type and amount
                break;
            }
            case 1: { // Buying items
                clearScreen();
                printf("Welcome to the market, this is where you can buy stuff.\n");
                int type = 0;

                // Ask for type of item to buy
                while (1) {
                    clearScreen();
                    askintquestion("Would you like to buy?", 3, &type, "Common", "Uncommon", "Rare");
                    if (type >= 0 && type <= 2) break; // Break if input is valid
                    printf("Invalid input. Please choose 0, 1, or 2.\n");
                }

                buy_item(type); // Buy item based on type
                break;
            }
            case 2: {
                clearScreen();
                list_inventory();
                sleepFunction(2);
                break;
            }
            default:
                printf("Invalid option selected.\n");
                break;
        }
        clearScreen(); // Clear the screen before the next round
    }

    return 0;
}
