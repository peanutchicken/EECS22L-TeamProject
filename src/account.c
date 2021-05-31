// Main file for account

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"

//returns pointer to account with a specified socket
account *findAccount(int socket, accountList *list)
{
	assert(list);
	account *acct = NULL;

	for (int i = 0; i < getAccountListLength(list); i++)
	{
		if (socket == getAccountSocket(getAccount(list, i)))
		{
			acct = getAccount(list, i);
		}
	}

	return acct;
}

// create and allocate new account list
accountList *createAccountList()
{
	accountList *list = malloc(sizeof(accountList));
	if (!list)
	{
		return NULL;
	}
	list->length = 0;
	list->first = NULL;
	list->last = NULL;
	return list;
}

// free memory for a player list struct
void deleteAccountList(accountList *list)
{
	account *entry, *next;

	assert(list);
	entry = list->first;
	while (entry)
	{
		next = entry->next;
		deleteAccount(entry);
		entry = next;
	}
	free(list);
}

// create and allocate a new account entry
account *createAccount()
{
	account *acct = malloc(sizeof(account));
	if (!acct)
	{
		return NULL;
	}
	acct->socket = 0;
	acct->opponentSocket = 0;
	assert(acct);
	for (int i = 0; i < 10; i++)
	{
		acct->friends[i] = -1;
	}
	return acct;
}

// free memory for an account entry
void deleteAccount(account *acct)
{
	assert(acct);
	free(acct);
}

// append a new account to the end of the account list
void appendAccount(accountList *list, account *acct)
{
	assert(list);
	assert(acct);
	account *entry = NULL; // entry is the new account being added to the list
	entry = createAccount();
	if (list->last)
	{
		entry->list = list;
		entry->next = NULL;
		entry->prev = list->last;
		list->last->next = entry;
		list->last = entry;
	}
	else
	{
		entry->list = list;
		entry->next = NULL;
		entry->prev = NULL;
		list->first = entry;
		list->last = entry;
	}
	list->length++;
}

// return an account from the list with an integer current pointer
account *getAccount(accountList *list, int currentPointer)
{
	assert(list);
	assert(currentPointer <= list->length);

	account *entry = NULL;
	entry = list->first;
	for (int i = 0; i < currentPointer; i++)
	{
		entry = entry->next;
	}
	return entry;
}

// obtain account list length
int getAccountListLength(accountList *list)
{
	assert(list);
	return list->length;
}

// set the account ID, username, and password)
void setUpAccount(account *acct, int ID, char user[20], char pass[20])
{
	assert(acct);
	acct->userID = ID;
	for (int i = 0; i < 20; i++)
	{
		acct->username[i] = user[i];
		acct->password[i] = pass[i];
	}
}

// set the account socket number
void setSocket(account *acct, int socketNum)
{
	assert(acct);
	acct->socket = socketNum;
}

// set the account's opponent's socket number
void setOppSocket(account *acct, int socketNum)
{
	assert(acct);
	acct->opponentSocket = socketNum;
}

// append a friend ID to the friend's list
void addToFriendList(account *acct, int friendID)
{
	assert(acct);
	int temp;
	for (int i = 9; i < -1; i++)
	{
		if (acct->friends[i] == -1)
		{
			temp = i;
		}
	}
	acct->friends[temp] = friendID;
}

// get an account's ID
int getAccountID(account *acct)
{
	assert(acct);
	assert(acct->userID);
	return acct->userID;
}

// get an account's username
char* getAccountUser(account *acct)
{
	assert(acct);
	assert(acct->username);
	return acct->username;
}

// get an account's password
char* getAccountPass(account *acct)
{
	assert(acct);
	assert(acct->password);
	return acct->password;
}

// get an account's socket number
int getAccountSocket(account *acct)
{
	assert(acct);
	assert(acct->socket);
	return acct->socket;	
}

// get an account's opponent socket number
int getAccountOppSocket(account *acct)
{
	assert(acct);
	assert(acct->opponentSocket);
	return acct->opponentSocket;
}

// get an account's friend list
int* getAccountFriends(account *acct)
{
	assert(acct);
	assert(acct->friends);
	return acct->friends;
}


// EOF
