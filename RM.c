#include<stdio.h>

#define MAX_ORDERS 100

int Order_Numbers[MAX_ORDERS];
int Quantities[MAX_ORDERS];

int Order_Hours[MAX_ORDERS];
int Order_Minutes[MAX_ORDERS];
int Order_AM_PMs[MAX_ORDERS];

int Serve_Hours[MAX_ORDERS];
int Serve_Minutes[MAX_ORDERS];
int Serve_AM_PMs[MAX_ORDERS];

int Time_To_Serve[MAX_ORDERS];

int Order_Count = 0;

// Function Prototypes
void get_user_action(int *Selected_Option);
void Register_Order(int *, int *, int *, int *, int *, int *, int *, int *, int *, int *);
void Remove_Order(int *, int *, int *, int *, int *, int *, int *, int *, int *, int *);
void Display_All_Orders(int *, int *, int *, int *, int *, int *, int *, int *, int *, int *);
void Search_By_Order_Number(int *, int *, int *, int *, int *, int *, int *, int *, int *, int *);
void Update_Order_Time(int *, int *, int *, int *, int *, int *, int *, int *, int *, int *);

int main() {
    int Selected_Option;

    printf("=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=..=.=.=.\n");
    printf("                WELCOME TO THE RESTAURANT MANAGEMENT SYSTEM                   \n");
    printf("=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=..=.=.=.\n");

    do {
        get_user_action(&Selected_Option);
    } while (Selected_Option != 6);

    return 0;
}

void get_user_action(int *Selected_Option) {
    printf("\n\n=.=.=.=.=.=.=.=.=.= MENU =.=.=.=.=.=.=.=.=.=\n\n");
    printf("1. Register New Order\n");
    printf("2. Remove Order\n");
    printf("3. Display All Orders\n");
    printf("4. Search By Order Number\n");
    printf("5. Update Serve Or Order Time\n");
    printf("6. Exit\n");
    printf("Choose any of the option: ");
    scanf("%d", Selected_Option);

    if (*Selected_Option == 1) {
        printf("Register Order Selected.\n");
        Register_Order(Order_Numbers, Quantities, Order_Hours, Order_Minutes, Order_AM_PMs,
                       Serve_Hours, Serve_Minutes, Serve_AM_PMs, Time_To_Serve, &Order_Count);
    } else if (*Selected_Option == 2) {
        printf("Remove Order Selected.\n");
        Remove_Order(Order_Numbers, Quantities, Order_Hours, Order_Minutes, Order_AM_PMs,
                     Serve_Hours, Serve_Minutes, Serve_AM_PMs, Time_To_Serve, &Order_Count);
    } else if (*Selected_Option == 3) {
        printf("Display All Orders Selected.\n");
        Display_All_Orders(Order_Numbers, Quantities, Order_Hours, Order_Minutes, Order_AM_PMs,
                           Serve_Hours, Serve_Minutes, Serve_AM_PMs, Time_To_Serve, &Order_Count);
    } else if (*Selected_Option == 4) {
        printf("Search By Order Number Selected.\n");
        Search_By_Order_Number(Order_Numbers, Quantities, Order_Hours, Order_Minutes, Order_AM_PMs,
                               Serve_Hours, Serve_Minutes, Serve_AM_PMs, Time_To_Serve, &Order_Count);
    } else if (*Selected_Option == 5) {
        printf("Update Time Selected.\n");
        Update_Order_Time(Order_Numbers, Quantities, Order_Hours, Order_Minutes, Order_AM_PMs,
                          Serve_Hours, Serve_Minutes, Serve_AM_PMs, Time_To_Serve, &Order_Count);
    } else if (*Selected_Option == 6) {
        printf("Exiting Program. Goodbye .......\n");
    } else {
        printf("Invalid Option. Please Try Again\n");
    }
}

void Register_Order(int *Order_Numbers, int *Quantities, int *Order_Hours, int *Order_Minutes, int *Order_AM_PMs,
                    int *Serve_Hours, int *Serve_Minutes, int *Serve_AM_PMs, int *Time_To_Serve, int *Order_Count) {
    if (*Order_Count >= MAX_ORDERS) {
        printf("Sorry. Order Limit Reached.\n");
        return;
    }

    int insert = *Order_Count;
    printf("Enter Order Number: ");
    scanf("%d", &Order_Numbers[insert]);

    for (int i = 0; i < *Order_Count; i++) {
        if (Order_Numbers[i] == Order_Numbers[insert]) {
            printf("Order Number Already Exists\n");
            return;
        }
    }

    printf("Enter Quantity: ");
    scanf("%d", &Quantities[insert]);

    printf("Enter Order Time (Hour Minute AM/PM):\n[AM=0, PM=1]: ");
    scanf("%d %d %d", &Order_Hours[insert], &Order_Minutes[insert], &Order_AM_PMs[insert]);

    if (Order_Hours[insert] < 1 || Order_Hours[insert] > 12 || Order_Minutes[insert] < 0 || Order_Minutes[insert] > 59 ||
        (Order_AM_PMs[insert] != 0 && Order_AM_PMs[insert] != 1)) {
        printf("INVALID ORDER TIME, Sir\n");
        return;
    }

    printf("Enter Serve Time (Hour Minute AM/PM):\n[AM=0, PM=1]: ");
    scanf("%d %d %d", &Serve_Hours[insert], &Serve_Minutes[insert], &Serve_AM_PMs[insert]);

    if (Serve_Hours[insert] < 1 || Serve_Hours[insert] > 12 || Serve_Minutes[insert] < 0 || Serve_Minutes[insert] > 59 ||
        (Serve_AM_PMs[insert] != 0 && Serve_AM_PMs[insert] != 1)) {
        printf("INVALID SERVE TIME, Sir\n");
        return;
    }

    int Order_Total_Min = ((Order_Hours[insert] % 12) + Order_AM_PMs[insert] * 12) * 60 + Order_Minutes[insert];
    int Serve_Total_Min = ((Serve_Hours[insert] % 12) + Serve_AM_PMs[insert] * 12) * 60 + Serve_Minutes[insert];
    int Difference = Serve_Total_Min - Order_Total_Min;

    if (Difference < 0) {
        printf("Serve Time Can't Be Earlier Than Order Time.\n");
        return;
    }

    Time_To_Serve[insert] = Difference;
    (*Order_Count)++;

    printf("Sir, Your Order Registered Successfully\n");
}

void Remove_Order(int *Order_Numbers, int *Quantities, int *Order_Hours, int *Order_Minutes, int *Order_AM_PMs,
                  int *Serve_Hours, int *Serve_Minutes, int *Serve_AM_PMs, int *Time_To_Serve, int *Order_Count) {
    if (*Order_Count == 0) {
        printf("THERE ARE NO ORDERS TO REMOVE.\n");
        return;
    }

    int Order_Number_To_Remove;
    printf("Enter The Order Number To Remove: ");
    scanf("%d", &Order_Number_To_Remove);

    int Index_To_Remove = -1;
    for (int i = 0; i < *Order_Count; i++) {
        if (Order_Numbers[i] == Order_Number_To_Remove) {
            Index_To_Remove = i;
            break;
        }
    }

    if (Index_To_Remove == -1) {
        printf("Order Not Found.\n");
        return;
    }

    for (int i = Index_To_Remove; i < (*Order_Count - 1); i++) {
        Order_Numbers[i] = Order_Numbers[i + 1];
        Quantities[i] = Quantities[i + 1];
        Order_Hours[i] = Order_Hours[i + 1];
        Order_Minutes[i] = Order_Minutes[i + 1];
        Order_AM_PMs[i] = Order_AM_PMs[i + 1];
        Serve_Hours[i] = Serve_Hours[i + 1];
        Serve_Minutes[i] = Serve_Minutes[i + 1];
        Serve_AM_PMs[i] = Serve_AM_PMs[i + 1];
        Time_To_Serve[i] = Time_To_Serve[i + 1];
    }

    (*Order_Count)--;
    printf("Sir, Your Order Is Removed Successfully.\n");
}

void Display_All_Orders(int *Order_Numbers, int *Quantities, int *Order_Hours, int *Order_Minutes, int *Order_AM_PMs,
                        int *Serve_Hours, int *Serve_Minutes, int *Serve_AM_PMs, int *Time_To_Serve, int *Order_Count) {
    if (*Order_Count == 0) {
        printf("NO ORDERS TO DISPLAY.\n");
        return;
    }

    printf("=.=.=.=.=.=.= ALL ORDERS =.=.=.=.=.=.=\n");

    for (int i = 0; i < *Order_Count; i++) {
        printf("<> Order Number : %d\n", Order_Numbers[i]);
        printf("   Quantity     : %d\n", Quantities[i]);
        printf("   Order Time   : %02d:%02d %s\n", Order_Hours[i], Order_Minutes[i], Order_AM_PMs[i] == 0 ? "AM" : "PM");
        printf("   Serve Time   : %02d:%02d %s\n", Serve_Hours[i], Serve_Minutes[i], Serve_AM_PMs[i] == 0 ? "AM" : "PM");
        printf("   Time To Serve: %d Minutes\n", Time_To_Serve[i]);
    }
}

void Search_By_Order_Number(int *Order_Numbers, int *Quantities, int *Order_Hours, int *Order_Minutes, int *Order_AM_PMs,
                            int *Serve_Hours, int *Serve_Minutes, int *Serve_AM_PMs, int *Time_To_Serve, int *Order_Count) {
    int Search_Number;
    printf("Enter Order Number To Search: ");
    scanf("%d", &Search_Number);

    int found = 0;

    for (int i = 0; i < *Order_Count; i++) {
        if (Order_Numbers[i] == Search_Number) {
            printf("Order Found:\n");
            printf("Order Number : %d\n", Order_Numbers[i]);
            printf("Quantity     : %d\n", Quantities[i]);
            printf("Order Time   : %02d:%02d %s\n", Order_Hours[i], Order_Minutes[i], Order_AM_PMs[i] == 0 ? "AM" : "PM");
            printf("Serve Time   : %02d:%02d %s\n", Serve_Hours[i], Serve_Minutes[i], Serve_AM_PMs[i] == 0 ? "AM" : "PM");
            printf("Time To Serve: %d Minutes\n", Time_To_Serve[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("Order Not Found.\n");
    }
}

void Update_Order_Time(int *Order_Numbers, int *Quantities, int *Order_Hours, int *Order_Minutes, int *Order_AM_PMs,
                       int *Serve_Hours, int *Serve_Minutes, int *Serve_AM_PMs, int *Time_To_Serve, int *Order_Count) {
    int Number;
    printf("Enter Order Number To Update: ");
    scanf("%d", &Number);

    int found = 0, Hours, Minutes, AM_PM;

    for (int i = 0; i < *Order_Count; i++) {
        if (Order_Numbers[i] == Number) {
            found = 1;

            printf("Enter New Order Time (Hour Minute AM/PM): ");
            scanf("%d %d %d", &Hours, &Minutes, &AM_PM);
            if (Hours >= 1 && Hours <= 12 && Minutes >= 0 && Minutes <= 59 && (AM_PM == 0 || AM_PM == 1)) {
                Order_Hours[i] = Hours;
                Order_Minutes[i] = Minutes;
                Order_AM_PMs[i] = AM_PM;
            } else {
                printf("Invalid Order Time Format\n");
                return;
            }

            printf("Enter New Serve Time (Hour Minute AM/PM): ");
            scanf("%d %d %d", &Hours, &Minutes, &AM_PM);
            if (Hours >= 1 && Hours <= 12 && Minutes >= 0 && Minutes <= 59 && (AM_PM == 0 || AM_PM == 1)) {
                Serve_Hours[i] = Hours;
                Serve_Minutes[i] = Minutes;
                Serve_AM_PMs[i] = AM_PM;
            } else {
                printf("Invalid Serve Time Format\n");
                return;
            }

            int Order_Total_Min = ((Order_Hours[i] % 12) + Order_AM_PMs[i] * 12) * 60 + Order_Minutes[i];
            int Serve_Total_Min = ((Serve_Hours[i] % 12) + Serve_AM_PMs[i] * 12) * 60 + Serve_Minutes[i];
            Time_To_Serve[i] = Serve_Total_Min - Order_Total_Min;

            if (Time_To_Serve[i] < 0) {
                printf("Serve Time Can't Be Earlier Than Order Time.\n");
            } else {
                printf("Time Updated Successfully.\n");
            }
        }
    }

    if (!found) {
        printf("Order Not Found.\n");
    }
}
