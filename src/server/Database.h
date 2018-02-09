#pragma once

#include <list>
#include <string>
#include "eErrorCode.h"
#include "UserData.h"

class Database
{

public:
	Database();
	~Database();

	// Users management
	void							clear();
	int								addUser(std::string const&, std::string const&);
	bool							removeUser(UserData&);
	bool							removeUser(std::string const&);

	int								checkCredentials(UserData const&, std::string const&) const;
	int								checkCredentials(std::string const&, std::string const&) const;


	// Friends
	eErrorCode						removeFriend(UserData&, std::string const&);
	eErrorCode						addFriendRequest(UserData&, std::string const&);
	eErrorCode						validateFriendRequest(UserData&, std::string const&);
	eErrorCode						refuseFriendRequest(UserData&, std::string const&);

	// Serialization
	std::string						serialize() const;
	void							deserialize(std::string const&);

	// Utils
	bool							hasUser(std::string const&) const;

	UserData*						getUser(std::string const&);
	UserData const*					getUser(std::string const&) const;
	std::list<UserData>::iterator	getIterator(std::string const&);

	// Getters
	std::list<UserData> const&		getUsers() const;

	// Setters
	void							setUsers(std::list<UserData>&);

private:


	std::list<UserData>	_users;

};

