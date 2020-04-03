#include "LoginUserMenu.h"
#include "MainMenu.h"

LoginUserMenu::LoginUserMenu(const std::string& title, Application* app) : Menu(title, app)
{
	Paint(); // required in constructor
}

void LoginUserMenu::OutputOptions()
{
	if (!app->IsUserLoggedIn())
	{
		for (int i = 0; i < app->GetCurrentAccount()->users.length(); i++)
		{
			Option(i + 1, app->GetCurrentAccount()->users[i]->GetUsername());
		}
	}
}

bool LoginUserMenu::HandleChoice(char choice)
{
	// since we are using numbers here we shift the char down by '1'
	// this puts '1' as 0, '2' as 1, '3' as 2, '4' as 3, etc.
	// this reverses the + 1 above and lets us do the range check below
	int index = choice - '1';
	std::string password;


	////OLD
	//while (index >= 0 && index < app->GetCurrentAccount()->users.length()) //greater than 0, less than the number of users in the list
	//{
	//		while ((password.empty())) //if cin is empty, try again
	//		{	
	//			std::cout << "Enter password for " + cUser->GetUsername() + ": ";
	//			getline(std::cin, password);
	//		}

	//		while (!(password == cUser->GetPass())) //if cin password doesnt match stored password, try again
	//		{
	//			std::cout << "Wrong password, try again: ";
	//			getline(std::cin, password);
	//		}

	//		if (app->LoginUser(cUser->GetUsername(), password))
	//		{
	//			//if password is correct go back to main menu
	//			return true;
	//		}
	//		else
	//			cout << "\n\tPassword incorrect.";
	//}

	//New
	if (index >= 0 && index < app->GetCurrentAccount()->users.length())
	{
		const User* cUser = app->GetCurrentAccount()->users[index];
		std::cout << "Enter password for " + cUser->GetUsername() + ": ";	
		getline(std::cin, password);										

		if (app->LoginUser(cUser->GetUsername(), password))
		{
			//if password is correct go back to main menu
			return true;
		}
		else
		{
			cout << "\n\tPassword incorrect. Please try again or select another user.";
			cout << "\n\tPress any key to continue.";
			_getwch();//Wait for user input before continuing. This functions return value is ignored on purpose.
		}
	}
return false;
}