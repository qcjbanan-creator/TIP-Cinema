#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//FUNCTION PROTOTYPES

void displayMovies(string movies[], double prices[], int size);
void displaySchedules(string schedules[], int size);
void displaySeats(bool seats[], int size);
void displaySingleFood(string items[], double prices[], int size);
void displayBundles(string bundles[], double prices[], int size);
double getDiscountRate(int discountChoice);

void displayReceipt(
    string movie,
    string schedules,
    double ticketPrice,
    int quantity,
    int discountChoice,
    string foodname,
    int foodQty,
    double foodTotal,
    string bundleName,
    double bundlePrice,
    double subtotal,
    double discount,
    double total,
    double payment,
    double change,
    int seatNumbers[],
    int seatCount
);

//MAIN FUNCTION

int main() {

    //CONSTANTS

    const int MOVIE_COUNT = 3;
    const int TIME_COUNT = 3;
    const int FOOD_COUNT = 3;
    const int BUNDLE_COUNT = 3;
    const int SEAT_COUNT = 20;

    //ARRAYS

    string movies[MOVIE_COUNT] = {
        "Avengers: Endgame",
        "Inside Out 2",
        "Spider-Man: No Way Home"
    };

    double prices[MOVIE_COUNT] = {
        250.00,
        220.00,
        240.00
    };
    
    string schedules[TIME_COUNT] = {
        "12:00 PM",
        "4:30 PM", 
        "8:00 PM"
    };

    string singleFoodItems[FOOD_COUNT] = {
        "Regular Popcorn",
        "Bottled Soda",
        "Hotdog Sandwich"
    };
    
    double singleFoodPrices[FOOD_COUNT] = {
        80.00,
        50.00,
        75.00
    };
    
    string bundles[BUNDLE_COUNT] = {
        "Solo Combo (Popcorn + Drink)",
        "Pair Combo (Large Popcorn + 2 Drinks)",
        "Family Bundle (2 Large Popcorns + 4 Drinks)"
    };
    
    double bundlePrices[BUNDLE_COUNT] = {
        120.00,
        220.00,
        400.00
    };

    //false = available
    //true = occupied
    bool seats[SEAT_COUNT] = {false};
    int seatNumbers[10];

    //VARIABLES

    int movieChoice;
    int timeChoice;
    int quantity;
    int discountChoice;
    int seatNumber;
    int singleFoodChoice = 0;
    int singleFoodQty = 0;
    int bundleChoice = 0;

    double ticketPrice;
    double subtotal;
    double discountRate;
    double discount;
    double total;
    double payment;
    double change;
    double singleFoodTotal = 0.00;
    double bundlePrice = 0.00;

    //WELCOME SCREEN

    cout << "============================================\n";
    cout << "        CINEMA TICKETING SYSTEM\n";
    cout << "============================================\n";

    //FEATURE 1: DISPLAY MOVIES

    displayMovies(movies, prices, MOVIE_COUNT);

    //MOVIE SELECTION + VALIDATION

    do {

        cout << "\nSelect a movie (1-" << MOVIE_COUNT << "): ";
        cin >> movieChoice;

        if (movieChoice < 1 || movieChoice > MOVIE_COUNT) {
            cout << "Invalid movie choice. Please try again.\n";
        }

    } while (movieChoice < 1 || movieChoice > MOVIE_COUNT);

    //Get selected movie price
    ticketPrice = prices[movieChoice - 1];

    //FEATURE 3: SCHEDULE SELECTION
    displaySchedules(schedules, TIME_COUNT);
    do {
        cout << "\nSelect showtime slot (1-" << TIME_COUNT << "): ";
        cin >> timeChoice;
        
        if (timeChoice < 1 || timeChoice > TIME_COUNT) {
            cout << "Invalid schedule choice. Try again.\n";
        } 
        
    } while (timeChoice < 1 || timeChoice > TIME_COUNT);
    
    //FEATURE 4: TICKET QUANTITY

    do {

        cout << "Enter number of tickets (1-10): ";
        cin >> quantity;

        if (quantity < 1 || quantity > 10) {
            cout << "Invalid quantity. Please enter 1-10.\n";
        }

    } while (quantity < 1 || quantity > 10);

    //FEATURE 5: DISCOUNT SELECTION

    cout << "\n============================================\n";
    cout << "              DISCOUNT TYPE\n";
    cout << "============================================\n";

    cout << "1. No Discount\n";
    cout << "2. Student - 10%\n";
    cout << "3. Senior Citizen - 20%\n";
    cout << "4. PWD - 20%\n";

    do {

        cout << "\nSelect discount type (1-4): ";
        cin >> discountChoice;

        if (discountChoice < 1 || discountChoice > 4) {
            cout << "Invalid discount choice. Please select 1-4.\n";
        }

    } while (discountChoice < 1 || discountChoice > 4);

    //FEATURE 6: SEAT SELECTION

    cout << "\n============================================\n";
    cout << "              SEAT SELECTION\n";
    cout << "============================================\n";

    displaySeats(seats, SEAT_COUNT);

    //Select seats based on quantity
    for (int i = 0; i < quantity; i++) {

        do {

            cout << "Select seat #" << i + 1 << ": ";
            cin >> seatNumber;

            //Check if seat number is valid
            if (seatNumber < 1 || seatNumber > SEAT_COUNT) {

                cout << "Invalid seat number. Choose between 1-20.\n";

            }

            //Check if seat is already occupied
            else if (seats[seatNumber - 1] == true) {

                cout << "Seat is already occupied. Choose another seat.\n";

            }

        } while (
            seatNumber < 1 ||
            seatNumber > SEAT_COUNT ||
            seats[seatNumber - 1] == true
        );

        //Mark seat as occupied
        seats[seatNumber - 1] = true;

        //Store selected seat
        seatNumbers[i] = seatNumber;
    }

    //FEATURE 7: FOOD ITEMS
        
    displaySingleFood(singleFoodItems, singleFoodPrices, FOOD_COUNT);

    do {
        cout << "\nSelect single food item (0 for None): ";
        cin >> singleFoodChoice;

        if (singleFoodChoice < 0 || singleFoodChoice > FOOD_COUNT) {
            cout << "Invalid choice. Select between 0-" << FOOD_COUNT << ".\n";
        }
    } while (singleFoodChoice < 0 || singleFoodChoice > FOOD_COUNT);

    if (singleFoodChoice > 0) {
        do {
            cout << "Enter quantity for " << singleFoodItems[singleFoodChoice - 1] << " (1-5): ";
            cin >> singleFoodQty;

            if (singleFoodQty < 1 || singleFoodQty > 5) {
                cout << "Invalid quantity. Please choose between 1 and 5.\n";
            }
        } while (singleFoodQty < 1 || singleFoodQty > 5);

        singleFoodTotal = singleFoodPrices[singleFoodChoice - 1] * singleFoodQty;
    }
    
    //FEATURE 8: FOOD BUNDLES
     
    displayBundles(bundles, bundlePrices, BUNDLE_COUNT);

    do {
        cout << "\nSelect combo bundle (0 for None): ";
        cin >> bundleChoice;

        if (bundleChoice < 0 || bundleChoice > BUNDLE_COUNT) {
            cout << "Invalid choice. Select between 0-" << BUNDLE_COUNT << ".\n";
        }
    } while (bundleChoice < 0 || bundleChoice > BUNDLE_COUNT);

    if (bundleChoice > 0) {
        bundlePrice = bundlePrices[bundleChoice - 1];
    }
    
    //COMPUTATIONS

    double ticketSubtotal = ticketPrice * quantity;
    
    //Calculate subtotal combining tickets + single food + bundle
    subtotal = ticketSubtotal + singleFoodTotal + bundlePrice;

    //Get discount rate using switch
    discountRate = getDiscountRate(discountChoice);

    //Calculate discount on tickets
    discount = ticketSubtotal * discountRate;

    //Calculate final total
    total = subtotal - discount;

    //PAYMENT

    cout << "\n============================================\n";
    cout << "                  PAYMENT\n";
    cout << "============================================\n";

    cout << "Total Amount: PHP "
         << fixed << setprecision(2)
         << total << endl;

    //Payment validation
    do {
        
        cout << "Enter payment: PHP ";
        cin >> payment;

        if (payment < total) {

            cout << "Insufficient payment!\n";

            cout << "Please enter at least PHP "
                 << fixed << setprecision(2)
                 << total << ".\n";
        }

    } while (payment < total);

    //Calculate change
    change = payment - total;

    //DISPLAY RECEIPT

    string selectedFoodName = (singleFoodChoice > 0) ? singleFoodItems[singleFoodChoice - 1] : "None";
    string selectedBundleName = (bundleChoice > 0) ? bundles[bundleChoice - 1] : "None";

    displayReceipt(
        movies[movieChoice - 1],
        schedules[timeChoice - 1],
        ticketPrice,
        quantity,
        discountChoice,
        selectedFoodName,
        singleFoodQty,
        singleFoodTotal,
        selectedBundleName,
        bundlePrice,
        subtotal,
        discount,
        total,
        payment,
        change,
        seatNumbers,
        quantity
    );

    cout << "\nThank you for using our Cinema Ticketing System!\n";
    cout << "Enjoy the movie!\n";

    return 0;
}


//FUNCTION 1: DISPLAY MOVIES

void displayMovies(string movies[], double prices[], int size) {

    cout << "\n============================================\n";
    cout << "                  MOVIES\n";
    cout << "============================================\n";

    for (int i = 0; i < size; i++) {

        cout << i + 1 << ". "
             << movies[i]
             << " - PHP "
             << fixed << setprecision(2)
             << prices[i]
             << endl;
    }
}

//FUNCTION 2: DISPLAY SHOWTIMES

void displaySchedules(string schedules[], int size) {
    cout << "\n============================================\n";
    cout << "             AVAILABLE SHOWTIMES\n";
    cout << "============================================\n";

    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << schedules[i] << endl;
    }
}


//FUNCTION 3: DISPLAY SEATS

void displaySeats(bool seats[], int size) {

    cout << "\nAvailable Seats:\n\n";

    for (int i = 0; i < size; i++) {

        //Available seat
        if (seats[i] == false) {

            cout << "["
                 << setw(2)
                 << i + 1
                 << "] ";

        }

        //Occupied seat
        else {

            cout << "[XX] ";
        }

        //Create a new row every 5 seats
        if ((i + 1) % 5 == 0) {
            cout << endl;
        }
    }

    cout << "\n";
}


//FUNCTION 4: DISPLAY FOOD ITEMS

void displaySingleFood(string items[], double prices[], int size) {
    cout << "\n============================================\n";
    cout << "                  FOOD ITEMS\n";
    cout << "============================================\n";
    cout << "0. None\n";

    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << items[i] << " - PHP " 
             << fixed << setprecision(2) << prices[i] << endl;
    }
}

//FUNCTION 5: DISPLAY FOOD BUNDLES

void displayBundles(string bundles[], double prices[], int size) {
    cout << "\n============================================\n";
    cout << "               SNACK BUNDLES\n";
    cout << "============================================\n";
    cout << "0. None\n";

    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << bundles[i] << " - PHP " 
             << fixed << setprecision(2) << prices[i] << endl;
    }
}


//FUNCTION 6: GET DISCOUNT RATE

double getDiscountRate(int discountChoice) {

    double discountRate;

    //SWITCH STATEMENT
    switch (discountChoice) {

        case 1:
            //No discount
            discountRate = 0.00;
            break;

        case 2:
            //Student discount
            discountRate = 0.10;
            break;

        case 3:
            //Senior citizen discount
            discountRate = 0.20;
            break;

        case 4:
            //PWD discount
            discountRate = 0.20;
            break;

        default:
            discountRate = 0.00;
    }

    return discountRate;
}


//FUNCTION 7: DISPLAY RECEIPT

void displayReceipt(
    string movie,
    string schedules,
    double ticketPrice,
    int quantity,
    int discountChoice,
    string foodname,
    int foodQty,
    double foodTotal,
    string bundleName,
    double bundlePrice,
    double subtotal,
    double discount,
    double total,
    double payment,
    double change,
    int seatNumbers[],
    int seatCount
) {

    cout << "\n\n============================================\n";
    cout << "               CINEMA RECEIPT\n";
    cout << "============================================\n";

    //Movie
    cout << left
         << setw(20)
         << "Movie:"
         << movie
         << endl;

    //Showtime
    cout << left
         << setw(20)
         << "Showtime:"
         << schedules
         << endl;

    //Ticket price
    cout << left
         << setw(20)
         << "Ticket Price:"
         << "PHP "
         << fixed
         << setprecision(2)
         << ticketPrice
         << endl;

    //Quantity
    cout << left
         << setw(20)
         << "Quantity:"
         << quantity
         << endl;

    //Discount type
    cout << left
         << setw(20)
         << "Discount:";

    switch (discountChoice) {

        case 1:
            cout << "No Discount";
            break;

        case 2:
            cout << "Student (10%)";
            break;

        case 3:
            cout << "Senior Citizen (20%)";
            break;

        case 4:
            cout << "PWD (20%)";
            break;
    }

    cout << endl;

    //Seats
    cout << left
         << setw(20)
         << "Seats:";

    for (int i = 0; i < seatCount; i++) {

        cout << seatNumbers[i];

        if (i < seatCount - 1) {
            cout << ", ";
        }
    }

    cout << endl;

    cout << "--------------------------------------------\n";

    //Single Food
    cout << left
         << setw(20)
         << "Food Item:"
         << foodname;
    if (foodQty > 0) {
        cout << " (x" << foodQty << ")";
    }
    cout << endl;

    cout << left
         << setw(20)
         << "Food Total:"
         << "PHP "
         << fixed
         << setprecision(2)
         << foodTotal
         << endl;

    //Bundle
    cout << left
         << setw(20)
         << "Snack Bundle:"
         << bundleName
         << endl;

    cout << left
         << setw(20)
         << "Bundle Price:"
         << "PHP "
         << fixed
         << setprecision(2)
         << bundlePrice
         << endl;

    cout << "--------------------------------------------\n";

    //Subtotal
    cout << left
         << setw(20)
         << "Subtotal:"
         << "PHP "
         << fixed
         << setprecision(2)
         << subtotal
         << endl;

    //Discount amount
    cout << left
         << setw(20)
         << "Discount Amount:"
         << "PHP "
         << fixed
         << setprecision(2)
         << discount
         << endl;

    //Total
    cout << left
         << setw(20)
         << "TOTAL:"
         << "PHP "
         << fixed
         << setprecision(2)
         << total
         << endl;

    cout << "--------------------------------------------\n";

    //Payment
    cout << left
         << setw(20)
         << "Payment:"
         << "PHP "
         << fixed
         << setprecision(2)
         << payment
         << endl;

    //Change
    cout << left
         << setw(20)
         << "Change:"
         << "PHP "
         << fixed
         << setprecision(2)
         << change
         << endl;

    cout << "============================================\n";
}
