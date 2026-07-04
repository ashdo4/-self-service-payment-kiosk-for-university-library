#include<stdio.h>

extern int s;

void menu(){
    printf("\n\nenter the service you want\n");
    printf("1 for Fine Payment\n");
    printf("2 for Book Reservation\n");
    printf("3 for Membership Renewal\n");
    printf("4 for Lost Library Card Replace\n");
    printf("5 for Exit\n");
    printf("\nenter your choice:");
    scanf("%d",&s);
}