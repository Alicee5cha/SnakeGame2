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
		for (int i = 0; i < app->GetCurrentAccount()->GetUsers()->length(); i++)
		{
			Option(i + 1, (*app->GetCurrentAccount()->GetUsers())[i]->GetUsername());
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

	if (index >= 0 && index < app->GetCurrentAccount()->GetUsers()->length())
	{
		const User* cUser = (*app->GetCurrentAccount()->GetUsers())[index];
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
	else
	{
		cout << "\n\tChoose a valid user";
		cout << "\n\tPress any key to continue";
		_getwch();//Wait for user input before continuing. This functions return value is ignored on purpose.
	}

return false;
}