#include <iostream>
#include <string>

enum AccountCountry
{
	Germany,
	USA
};

class Account
{
	public:
		Account(std::string Name, std::string Password, std::string Email, std::string Description);
		~Account();
	private:
		static int Accounts;
		
		int Id;
		
		std::string Name;
		std::string Password;
		std::string Email;
		std::string Description;
		AccountCountry Country;
		
		std::string CheckName(std::string Name);
		std::string CheckPassword(std::string Name);
		std::string CheckEmail(std::string Name);
		std::string CheckDescription(std::string Description);
};

Account::Account(std::string Name, std::string Password, std::string Email, std::string Description)
{
	this->Name = this.CheckName(Name);
	this->Password = this.CheckPassword(Password);
	this->Email = this.CheckEmail(Email);
	this->Description = this.CheckDescription(Description);
	return *this;
}
