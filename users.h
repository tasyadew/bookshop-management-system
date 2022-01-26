///////////////////////////////////////////////////////////////////
// NAME:               users.h
//
// PURPOSE:            This class is used to manage all users related.
//                     The class Registration will be used in
//                     main function
///////////////////////////////////////////////////////////////////

#ifndef USERS_H
#define USERS_H

//user attributes (Node User)
class User{
    protected:
        int type, age;
        std::string username, password, email, phone, name;
        User* next; //linked list concept. So the amount of user will be flexible

    public:
        //default constructor
        User();

        //constructor with user's attributes
        User(int, std::string, std::string, int, std::string, std::string, std::string);

        //return true if username, password and type are all same
        bool verify(std::string, std::string, int);

        //display user detail
        void userDetails();
        
        friend class Registration;
        friend class ListUser;
};

//linked list user
class ListUser{
    private:
        User* headUser = NULL;

    public:
        //initialized the first user node
        void insertUser_head(int, std::string, std::string, int, std::string, std::string, std::string);

        //linked list insert at the end
        void insertUser_end(int, std::string, std::string, int, std::string, std::string, std::string);

        //Return the total user in the linked list
        int getLength();

        //return user data at the choosen position
        User* getUser(int position);

        //searching user to be deleted by their username
        void deleteUser(std::string username);
};

//registration attributes
class Registration{
    private:
        ListUser listUser;
    
    public:
        ///remove whitespace at front of std::string when getline
        std::string formatTitle(std::string);

        //read from users.txt file
        void importUsers();

        //write to users.txt file
        void exportUsers();

        //user cannot have the same username & length must be between 3-15
        bool validUsername(std::string&);

        //add new user and put at the end of linked list
        void newUser(int);

        //delete the selected user from the linked list
        void removeUser();

        //return true if type, username and password of user are all same
        //by using sequential search
        bool foundUserAcc(int, std::string, std::string);
        //verify user login
        void verifyUser(int &, int);

        //display linked list user
        void displayUserInfo();
};

#endif