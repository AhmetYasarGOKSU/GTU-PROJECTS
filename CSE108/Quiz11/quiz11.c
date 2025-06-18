#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    double price;
    int quantity;

} Item;

typedef struct {
    Item *item;
    int count;
    int capacity;
} Cart;

Cart initializesShoppingCart() {
    Cart cart;

    printf("Enter initial cart capacity: ");
    scanf("%d", &(cart.capacity));
    cart.count = 0;
    return cart;
}

void addItem(Cart *cart) {
    if (cart->count >= cart->capacity) {
        cart->capacity *= 2;
        cart->item = (Item*)realloc(cart->item, sizeof(Item) * cart->capacity);
        printf("Array resized to capacity: %d\n", cart->capacity);
    }

    printf("Enter item name: ");
    scanf("%s", cart->item[cart->count].name);
    printf("Enter price: ");
    scanf("%lf", &(cart->item[cart->count].price));
    printf("Enter quantity: ");
    scanf("%d", &(cart->item[cart->count].quantity));

    (cart->count)++;

    printf("Item added.\n\n");

}

void removeItem(Cart *cart) {
    char removed_name[40];
    int i, item_index = -1;
    printf("Enter item name to remove: ");
    scanf("%s", removed_name);


    for (i = 0; i < cart->count; i++) {
        if (strcmp(cart->item[i].name, removed_name) == 0) {
            item_index = i;
            break;
        }
    }
    if (item_index == -1) {
        printf("Item could not found!\n");
        return;
    }

    for (i = item_index; i < cart->count-1; i++) {
        cart->item[i] = cart->item[i+1];
    }
    (cart->count)--;

    if (cart->count < cart->capacity / 2) {
        cart->capacity = cart->capacity/2;
        cart->item = (Item*)realloc(cart->item, sizeof(Item) * (cart->capacity/2));
        printf("Array resized to capacity: %d\n", cart->capacity);
    } 

    printf("Item removed.\n\n");
}

void searchItem(Cart *cart) {
    char itemName[40];
    int i, item_index=-1;
    printf("Enter name to search: ");
    scanf("%s", itemName);

    for (i = 0; i < cart->count; i++) {

        if (strcmp(cart->item[i].name, itemName) == 0) {
            item_index = i;
            break;
        }
    }
    if (item_index == -1) {
        printf("Item could not found!\n\n");
        return;
    }
    else {
        printf("Item's index: %d\n", item_index);
        printf("-----------------------------------------------\n");
        printf("Name      Price      Quantity      Subtotal\n");
        printf("-----------------------------------------------\n");
        printf("%s     %.2lf        %d          %.2lf\n\n\n", cart->item[item_index].name, cart->item[item_index].price, cart->item[item_index].quantity, (cart->item[item_index].price * cart->item[item_index].quantity));
    }

}

void displayMenu() {
    printf("1. Add Item\n");
    printf("2. Remove Item\n");
    printf("3. Seach Item\n");
    printf("4. Print Cart\n");
    printf("5. Exit\n\n");
}

void printCarts(Cart *cart) {
    double total_cart_value = 0;
    int item_index;
    printf("-----------------------------------------------\n");
    printf("Name      Price      Quantity      Subtotal\n");
    printf("-----------------------------------------------\n");

    for (item_index = 0; item_index < cart->count; item_index++) {
        printf("%s     %.2lf        %d          %.2lf\n", cart->item[item_index].name, cart->item[item_index].price, cart->item[item_index].quantity, (cart->item[item_index].price * cart->item[item_index].quantity));
        total_cart_value += (cart->item[item_index].price * cart->item[item_index].quantity);

    }
    printf("-----------------------------------------------\n");
    printf("Total Cart Value: %.2lf\n\n\n", total_cart_value);
}

int main() {
    int choice;
    Cart cart;
    cart = initializesShoppingCart();

    cart.item = (Item*)malloc(sizeof(Item) * cart.capacity); 
    displayMenu();
    while (1) {
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addItem(&cart);
            break;
        case 2:
            removeItem(&cart);
            break;
        case 3:
            searchItem(&cart);
            break;
        case 4:
            printCarts(&cart);
            break;
        case 5:
            free(cart.item);
            exit(-1);
            break;

        default:
            break;
        }
    }
}