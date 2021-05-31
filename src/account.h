// header file for server

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct account account;
typedef struct accountList accountList;

// account list struct
struct accountList {
    account* first;
    account* last;
    int length;
};

// account entry struct
struct account {
    int userID;
    char username[20];
    char password[20];
    int socket; // 0 if not playing against an opponent
    int opponentSocket; // 0 if not playing against and opponent
    int friends[10]; // storing another user's userID. (-1 in array for no friend in that position)
    accountList *list;
    account *next; 
    account *prev;
};

//returns pointer to account with a specified socket
account *findAccount(int socket, accountList *list);

// create and allocate new account list
accountList *createAccountList();

// free memory for a player list struct
void deleteAccountList(accountList *list);

// create and allocate a new account entry
account *createAccount();

// free memory for an account entry
void deleteAccount(account *acct);

// append a new account to the end of the account list
void appendAccount(accountList *list, account *acct);

// return an account from the list with an integer current pointer
account *getAccount(accountList *list, int currentPointer);

// obtain account list length
int getAccountListLength(accountList *list);

// set the account ID, username, and password)
void setUpAccount(account *acct, int ID, char user[20], char pass[20]);

// set the account socket number
void setSocket(account *acct, int socketNum);

// set the account's opponent's socket number
void setOppSocket(account *acct, int socketNum);

// append a friend ID to the friend's list
void addToFriendList(account *acct, int friendID);

// get an account's ID
int getAccountID(account *acct);

// get an account's username
char* getAccountUser(account *acct);

// get an account's password
char* getAccountPass(account *acct);

// get an account's socket number
int getAccountSocket(account *acct);

// get an account's opponent socket number
int getAccountOppSocket(account *acct);

// get an account's friend list
int* getAccountFriends(account *acct);

#endif

// EOF
