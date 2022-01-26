#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include "books.h"
#include "users.h"

using namespace std;

//global var
#define MAX_BOOKS 20
#define MAX_CART 5
#define MAX_QUEUE 5


/**********GLOBAL FUNCTION**********/

int showMenu(int x){
    int choice;
    switch (x){
        case 1: //Main Menu
            cout<< endl
                << "================================" << endl
                << "          BOOKSHOP APP          " << endl
                << "================================" << endl
                << "Welcome to Online Bookshop App!" << endl
                << "[1] Log In  - I have already registered" << endl
                << "[2] Sign Up - I am a new user" << endl
                << "[3] I am a Staff!" << endl
                << "[4] Exit" << endl
                << endl
                << "Enter your choice : ";
            cin >> choice;
            cout<< endl;
            break;
        case 2: //Customer Menu
            cout<< endl
                << "=============================" << endl
                << "        CUSTOMER MENU        " << endl
                << "=============================" << endl
                << "What would you like to do?" << endl
                << "[1] Purchase Books" << endl
                << "[2] View Cart" << endl
                << "[3] Suggest A Book" << endl
                << "[4] Log Out" << endl
                << endl
                << "Enter your choice : ";
            cin >> choice;
            cout<< endl;
            break;
        case 3: //Customer Menu > [1] Purchase Book
            cout<< endl
                << "Available action:"<< endl
                << "[1] Purchase a book!" << endl
                << "[2] Sort by price : Lowest to Highest" << endl
                << "[3] Sort by price : Highest to Lowest" << endl
                << "[4] Sort by title : A-Z" << endl
                << "[5] Search book ISBN" << endl
                << "[6] Back" << endl
                << endl
                << "Enter your action : ";
            cin >> choice;
            break;  
        case 4: //Customer Menu > [1] Purchase Book > [1] Purchase a book!
            cout<< endl
                << "Available action:"<< endl
                << "[1] Add to cart" << endl
                << "[2] Show the book details" << endl
                << "[3] Back" << endl
                << endl
                << "Enter your action : ";
            cin >> choice;
            break;
        case 5: //Customer Menu > [2] View Cart
            cout<< endl
                << "Available action:"<< endl
                << "[1] Checkout" << endl
                << "[2] Remove most recently added book" << endl
                << "[3] Back" << endl
                << endl
                << "Enter your action : ";
            cin >> choice;
            break;  
        case 10: //Staff Menu
            cout<< endl
                << "==========================" << endl
                << "        STAFF MENU        " << endl
                << "==========================" << endl
                << "What would you like to do?" << endl
                << "[1] View Book Stocks" << endl
                << "[2] Manage Book Stocks" << endl
                << "[3] Add Discount" << endl
                << "[4] Print Report" << endl
                << "[5] Register New Staff" << endl
                << "[6] Display User Info" << endl
                << "[7] Delete User" << endl
                << "[8] Review Suggested Book" << endl
                << "[9] Log Out" << endl
                << endl
                << "Enter your choice : ";
            cin >> choice;
            cout<< endl;
        default:
            break;
    }
    return choice;
}

//similar to system("pause"), but I add this so linux/mac user can run this program
void sysPause(){
    cout << endl << "Press any key to continue...";
    cin.ignore();
    cin.get();
}

//go to menu 4 if a book is chosen
void chosenBookFunc(int& subAction, StockManagement& sm, int& chosenBook){
    cout << "The chosen book is " << sm.getBookTitle(chosenBook) << endl;
    subAction = 0;

    while(subAction != 3){
        subAction = showMenu(4);
        switch(subAction){
            case 1:
                sm.addToCart(chosenBook);
                sysPause();
                subAction = 3;
                break;
            case 2:
                sm.displayBookInfo(chosenBook);
                sysPause();
                subAction = 3;
                break;
            
            case 3:
                /*leave loop*/
                break;

            default:
                cout<< "Invalid option! Please choose 1, 2 or 3." << endl;
                sysPause();
                break;
        }
    }
}

/**********MAIN FUNCTION**********/
int main(){
    StockManagement sm;
    Registration regUser;
    sm.importBooks();
    sm.importReport();
    regUser.importUsers();

    int choice = 0, subchoice = 0;
    choice = showMenu(1);
    
    //loop until user choose exit
    while(choice != 4){
        //MAIN MENU 
        //[1] To enter Customer Menu
        if (choice == 1){
            //verify user (maximum 3 attempts)
            subchoice = 4; //will not go into cust menu if acc not verified
            regUser.verifyUser(subchoice, 0);
            
            //CUSTOMER MENU
            while (subchoice != 4){
                subchoice = showMenu(2);
                
                //[1] Purchase Book Menu
                if (subchoice == 1){
                    cout<< "==========ALL BOOKS==========" << endl;
                    sm.sortByID();
                    sm.displayBooks();
                    
                    int chosenBook, bookID, action, subAction;
                    long long int bookISBN;
                    action = showMenu(3);
                    
                    //loop while user not choose to exit
                    while(action != 6){
                        //Available action:
                        switch (action){
                            //[1] Purchase a book!
                            case 1:
                                cout << "Enter your chosen book (book ID): ";
                                cin >> bookID;
                                
                                chosenBook = sm.findPosByID(bookID);
                                if (chosenBook == -1){
                                    cout << "There is no book with that ID!" << endl;
                                    sysPause();
                                    subAction = 3;
                                } else {
                                    chosenBookFunc(subAction, sm, chosenBook);
                                }
                                action = 6;
                                break;

                            //[2] Sort by price : Lowest to Highest
                            case 2:
                                sm.sortByPrice(true);
                                sm.displayBooks();
                                action = showMenu(3);
                                break;

                            //[3] Sort by price : Highest to Lowest
                            case 3:
                                sm.sortByPrice(false);
                                sm.displayBooks();
                                action = showMenu(3);
                                break;

                            //[4] Sort by title : A-Z
                            case 4:
                                sm.sortByTitle();
                                sm.displayBooks();
                                action = showMenu(3);
                                break;

                            //[5] Search Book ISBN
                            case 5:
                                cout<< "Enter the book's ISBN : ";
                                cin >> bookISBN;
                                
                                sm.sortByISBN();
                                chosenBook = sm.findPosByISBN(bookISBN, 0, sm.getBookIndex()-1);
                                if (chosenBook == -1){
                                    cout << "There is no book with that ISBN!" << endl;
                                    sysPause();
                                    subAction = 3;
                                } else {
                                    chosenBookFunc(subAction, sm, chosenBook);
                                }
                                action = 6;
                                break;

                            //[6] Back
                            case 6:
                                /*leave loop*/
                                break;

                            //Invalid input
                            default:
                                cout << "ERROR: Invalid input. Please enter option 1, 2, 3, 4 or 5" << endl;
                                sysPause();
                                action = showMenu(3);
                                break;
                        }
                    }
                }

                //[2] View Cart  
                else if (subchoice == 2) {
                    if(sm.isCartEmpty()){
                        cout << "The cart is empty! Please go to \"[1] Purchase Books\" to add some books" << endl;
                        sysPause();
                    }else{
                        sm.displayCart();
                        int action;
                        action = showMenu(5);
                        while(action != 3){
                            //Checkout
                            if(action == 1){
                                sm.checkout();
                                sysPause();
                                action = 3;
                            }

                            //Remove most recently added book
                            else if(action == 2){
                                sm.removeBook();
                                sysPause();
                                action = 3;
                            }

                            //Invalid input
                            else if(action != 3){
                                cout << "ERROR: Invalid input. Please enter option 1, 2 or 3" << endl;
                                sysPause();
                                action = showMenu(3);
                            }
                        }
                    }
                }
                
                //[3] Suggest a Book
                else if (subchoice == 3) {
                    sm.addSuggestedBook();
                    sysPause();
                }

                //Wrong input
                else if (subchoice != 4){
                    cout << "ERROR: Invalid input. Please enter option 1, 2, 3 or 4" << endl;
                    sysPause();
                    subchoice = showMenu(2);
                }
            }
        }
        //MAIN MENU
        //[2] To register new customer
        else if (choice == 2){
            regUser.newUser(0);
            sysPause();
        }

        //MAIN MENU
        //[3] To enter Staff Menu
        else if (choice == 3){
            //verify user (maximum 3 attempts)
            subchoice = 9; // subchoice 9 = logout
            regUser.verifyUser(subchoice, 1);
            
            while (subchoice != 9){
                subchoice = showMenu(10);
                int chosenBook, newQuantity, newDiscount;

                switch (subchoice){
                    //[1] View Book Stocks
                    case 1:
                        sm.sortByID();
                        sm.displayBooks();
                        cout<< endl;
                        sysPause();
                        break;

                    //[2] Manage Book Stocks
                    case 2:
                        cout<< "Manage Book Stock System" << endl;
                        sm.sortByID();
                        sm.displayBooks();
                        cout<< endl 
                            << "Choose a book to update stock quantity : ";
                        cin >> chosenBook;
                        cout<< "Enter the updated quantity             : ";
                        cin >> newQuantity;
                        sm.updateQuantity(chosenBook-1, newQuantity);
                        
                        cout<< endl
                            << "Book stock updated! Current stock for " << sm.getBookTitle(chosenBook-1)
                            << " is " << sm.getBookQuantity(chosenBook-1) << endl
                            << endl;
                        sysPause();
                        break;

                    //[3] Add Discount
                    case 3:
                        cout << "Manage Book Discount System" << endl;
                        sm.sortByID();
                        sm.displayBooks();
                        cout<< endl << "Choose a book to update the discount  : ";
                        cin >> chosenBook;
                        cout<< "Enter the updated discount            : ";
                        cin >> newDiscount;
                        sm.updateDiscount(chosenBook-1, newDiscount);

                        cout<< endl
                            << "Book discount updated! Current discount for " << sm.getBookTitle(chosenBook-1)
                            << " is " << sm.getBookDiscount(chosenBook-1) << "%" << endl
                            << endl;
                        sysPause();
                        break;

                    //[4] Print Report
                    case 4:
                        sm.displayReport();
                        sysPause();
                        break;

                    //[5] Register New Staff
                    case 5:
                        regUser.newUser(1);
                        sysPause();
                        break;

                    //[6] Display User Info
                    case 6:
                        regUser.displayUserInfo();
                        sysPause();
                        break;

                    //[7] Delete User
                    case 7:
                        regUser.displayUserInfo();
                        cout << endl;
                        regUser.removeUser();
                        sysPause();
                        break;

                    //[8] Review Suggested Book
                    case 8:
                        sm.reviewSuggestedBook();
                        sysPause();
                        break;

                    //[9] Log Out
                    case 9:
                        /*leave loop*/
                        break;

                    //invalid input
                    default:
                        cout<< "ERROR: Invalid input. Please enter option 1 - 9 only" << endl
                            << endl;
                        sysPause();
                        break;
                }
            }
        }
        //MAIN MENU
        //invalid input (other than 4)
        else{
            cout << "ERROR: Invalid input. Please enter option 1, 2, 3 or 4" << endl;
            sysPause();
        }
        sm.resetCart();
        choice = showMenu(1);
    }

    cout << "Thank you for using this App!" << endl;
    sm.sortByID();
    sm.exportBooks();
    regUser.exportUsers();

    return 0;
}