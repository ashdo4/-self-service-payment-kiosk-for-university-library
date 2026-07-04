#include<stdio.h>

#define M_500 0
#define M_200 1
#define M_100 2
#define M_50 3
#define M_20 4

extern int b_slots,c_slots, renewals,change_inv[];
extern float temp_fine,temp_card_fee, temp_renew_fee, temp_book_fee;
extern int successful_trans;

void trans_display(){
    printf("Remaining reservation slots   : %d\n",b_slots);
    printf("Remaining card replacements   : %d\n",c_slots);
    printf("Remaining renewals            : %d\n\n",renewals);
    printf("  Rs. 500: %d | Rs. 200: %d | Rs. 100: %d | Rs. 50: %d | Rs. 20: %d\n",
           change_inv[M_500], change_inv[M_200], change_inv[M_100], change_inv[M_50], change_inv[M_20]);
           printf("=========================================\n");

}

void daily_report(){
    float total_fee=0;
    total_fee= temp_fine + temp_book_fee+ temp_renew_fee+ temp_card_fee;
    printf("\n\nDAILY REPORT\n"); 
    printf("\nNumber of successful transactions : %d\n\n",successful_trans);
    
    printf("Revenue  by service type\n");
    printf("Fine payments         : %.2f\n",temp_fine);
    printf("Book Reservations     : %.2f\n",temp_book_fee);
    printf("Membership Renewals   : %.2f\n",temp_renew_fee);
    printf("Card Replacements     : %.2f\n",temp_card_fee);
    printf("Total Revenue         : %.2f\n",total_fee);
    printf("=========================================\n");
    printf("=========================================\n");
    
}