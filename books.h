///////////////////////////////////////////////////////////////////
// NAME:               books.h
//
// PURPOSE:            This class is used to manage all books related.
//                     The class stock management will be used in
//                     main function
///////////////////////////////////////////////////////////////////

#ifndef BOOKS_H
#define BOOKS_H

//global var
#define MAX_BOOKS 20
#define MAX_CART 5
#define MAX_QUEUE 5

//book attributes
class Book{
    private:
        int id, quantity, discount;
        long long int isbn;
        float price;
        std::string title, author;

    public:
        //default constructor
        Book();

        //constructor with book's attribute
        Book(int, long long int, int, float, int, std::string, std::string);

        //constructor for suggest book attributes
        Book(std::string, std::string);

        //for single line book data
        void bookDetails();

        //for multi line book data
        void bookInfo();

        //mutator
        void setQuantity(int);

        //copy book attribute from book reference
        void copyData(Book*);

        friend class StockManagement;
};

//circular queue using array for suggested books
class QueueBook{
    private:
        int frontBook, rearBook;
        Book suggestedBook[MAX_QUEUE];

    public:
        //default constructor
        QueueBook();

        // Check if the queue is full
        bool isFull();

        // Check if the queue is empty
        bool isEmpty();

        // Adding an book to queue
        void enQueue(Book);

        // Removing a book
        Book deQueue();

        //return the front of queue without dequeue
        Book peek();
};

//payment system attributes
class PaymentSystem{
    private:
        float userPay = 0;
        float price = 0;

    public:
        //return true if payment enough
        bool verifyPayment();

        //set payment and price to 0
        void reset();

        //return updated payment made from user
        float updatePayment(float);

        //return updated price to calculate total price
        float updatePrice(float);

        //return additional payment because payment not enough
        float calcAddPayment();

        //return balance
        float calcBalance();

        //Accessors
        float getUserPay();
        float getPrice();
};

//This class cart implement the concept of stack
class Cart{
    private:
        int top = -1;
        Book cartBook[MAX_CART];

    public:
        //initialized cart with 0 book
        void emptyCart();

        //insert Book in cart to top of stack
        void push(Book);

        //delete book from top of stack
        void pop();

        //return the Book data at top position
        Book bookAtTop();

        //return the Book data at "i" position
        Book bookAt(int);

        //check if cart is full
        bool isFull();

        //check if cart is empty
        bool isEmpty();

        //return size of cart
        int size();
};

//book stock attributes
class StockManagement{
    private:
        Book* listBook[MAX_BOOKS];
        Book suggestedBook[MAX_BOOKS];
        Cart cart;
        PaymentSystem ps;
        QueueBook q;
        int bookIndex, quantity = 0;
        float totalSales = 0;
    
    public:
        //remove whitespace at front of std::string when getline
        std::string formatTitle(std::string);

        //read from books.txt file
        void importBooks();

        //write to books.txt file
        void exportBooks();

        //single line display
        void displayBooks();

        //multi line display
        void displayBookInfo(int);
        
        //Accessors
        int getBookIndex();
        std::string getBookTitle(int);
        int getBookQuantity(int);
        int getBookDiscount(int);

        //return true if cart is empty
        bool isCartEmpty();

        //display cart
        void displayCart();

        //add book to cart by push into cart stack
        void addToCart(int);

        //clear book in cart and clear payment
        void resetCart();

        //purchase books that is in cart
        void checkout();

        //remove recently added book
        void removeBook();

        //read from report.txt if exist, else create report.txt
        void importReport();

        //write to report.txt
        void exportReport();

        //read from report.txt to display output of report
        void displayReport();

        //using insertion sort to sort by book price (if true = ascending, else descending)
        void sortByPrice(bool);

        //using insertion sort to sort by book title (ascending)
        void sortByTitle();

        //using insertion sort to sort by book id (ascending)
        void sortByID();

        //using insertion sort to sort by book isbn (ascending)
        void sortByISBN();

        //using sequential search to search matching book id
        int findPosByID(int);

        //using binary search to search matching book isbn
        int findPosByISBN(long long int, int, int);  

        //update quantity of selected book
        void updateQuantity(int, int);

        //update discount of selected book
        void updateDiscount(int, int);

        //add book suggestion to the queue
        void addSuggestedBook();

        //remove the first book suggested in the queue
        void reviewSuggestedBook();
};

#endif