#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
using namespace std;
using json = nlohmann::json;

/*
cd "/Users/sachingupta/Desktop/CoCo/" && g++ -std=c++11 main.cpp -o main && "/Users/sachingupta/Desktop/Coco/"main
*/

void createanaccount(json &jsonData, const string &username, const string &password, const string &accounttype)
{

  // JSON Setup Object for the User's LOGIN data
  json setupObject;
  setupObject["username"] = username;
  setupObject["password"] = password;
  setupObject["account_type"] = accounttype;

  // JSON Information Object for the User's PROFILE data
  json informationObject;
  informationObject["Country"] = "BLANK";
  informationObject["Experience"] = "BLANK";
  informationObject["Fieldofinterest"] = "BLANK";
  informationObject["Level"] = "BLANK";
  informationObject["Oneword"] = "BLANK";

  // JSON Object for Overall Data
  json userObject;
  userObject["setup"] = setupObject;
  userObject["information"] = informationObject;

  // Add the user's data to the JSON file
  jsonData.push_back(userObject);

  std::ofstream output("data.json");
  output << jsonData.dump(4);
  output.close();
}

int signup(json &data)
{

  string username;
  string password;
  string account_type;

  // User Enters username, password, account type

  cout << "Enter your USERNAME: ";
  cin >> username;

  cout << "Enter your PASSWORD: ";
  cin >> password;

  while ((account_type != "User") && (account_type != "Recruiter"))
  {
    cout << "Enter your ACCOUNT TYPE (User or Recruiter): ";
    cin >> account_type;
  }

  // Uses createanaccount function to add the details to the main json file and save them

  createanaccount(data, username, password, account_type);

  return data.size();
}

int login()
{
  std::ifstream f("data.json");
  json data = json::parse(f);
  f.close();
  string tryusername;
  string trypassword;
  string tryaccount_type;

  // Ask for their account details

  cout << "Enter your account's USERNAME: ";
  cin >> tryusername;

  cout << "Enter your account's PASSWORD: ";
  cin >> trypassword;

  cout << "Enter your account's ACCOUNT TYPE: ";
  cin >> tryaccount_type;

  for (int i = 0; i < data.size(); i++)
  {
    if (((tryusername != "not found") && (tryusername == data.at(i)["setup"]["username"].get<string>())) && (trypassword == data.at(i)["setup"]["password"].get<string>()) && (tryaccount_type == data.at(i)["setup"]["account_type"].get<string>()))
    {
      return i;
      // If their account is found within the json file, it allows them to login and returns their index within the json file
    }
  }
  return -10;
  // Indicates their account is not found, meaning they won't be able to log in
}

void updatevalueinformation(json &data, int account_index, const std::string &newValue, const std::string &category)
{

  json &setupObject = data[account_index]["information"];

  // Update the value of the specified category within the JSON file
  setupObject[category] = newValue;

  std::ofstream output("data.json");
  output << data.dump(4);
  output.close();
}

void UserProfile(json &data, int account_index)
{
  int selection;
  while (true)
  // While loop allows them to keep on updating their profile until they finish
  {

    // Prints out their personal profile in a nice looking way
    cout << "\n\n\nPERSONAL PROFILE \n----------------\n\n";
    cout << "1. Enter your Country: " << data.at(account_index)["information"]["Country"].get<string>();
    cout << "\n2. Enter your Years of Work Experience: " << data.at(account_index)["information"]["Experience"].get<string>();
    cout << "\n3. Enter your Field of Interest: " << data.at(account_index)["information"]["Fieldofinterest"].get<string>();
    cout << "\n4. Enter your Management Level: " << data.at(account_index)["information"]["Level"].get<string>();
    cout << "\n5. Enter a word that best describes you: " << data.at(account_index)["information"]["Oneword"].get<string>() << "\n\n\n";

    cout << "Enter the Question Number to Edit (0 to exit): ";
    cin >> selection;
    cout << "\n";
    if (selection < 1 || selection > 5)
    {
      break;
    }

    string answer;

    // Allows them to edit their personal profile, and uses the updatevalueinformation function to update the value within the json file

    if (selection == 1)
    {
      cout << "1. Enter your Country: ";
      cin >> answer;
      updatevalueinformation(data, account_index, answer, "Country");
    }
    if (selection == 2)
    {
      cout << "2. Enter your Years of Work Experience: ";
      cin >> answer;
      updatevalueinformation(data, account_index, answer, "Experience");
    }
    if (selection == 3)
    {
      cout << "3. Enter your Field of Interest: ";
      cin >> answer;
      updatevalueinformation(data, account_index, answer, "Fieldofinterest");
    }
    if (selection == 4)
    {
      cout << "4. Enter your Management Level: ";
      cin >> answer;
      updatevalueinformation(data, account_index, answer, "Level");
    }
    if (selection == 5)
    {
      cout << "5. Enter a word that best describes you: ";
      cin >> answer;
      updatevalueinformation(data, account_index, answer, "Oneword");
    }
  }
}

void RecruiterProfile(json &data, int account_index)
{
  // Profile for a Recruiter/Employer
  int selection;
  while (true)
  {
    cout << "\n\n\nEmployer Profile (What are you looking for in a Candidate)\n----------------------------------------------------------\n\n";
    cout << "1. Enter Country of Office: " << data.at(account_index)["information"]["Country"].get<string>();
    cout << "\n2. Enter the Required Work Experience: " << data.at(account_index)["information"]["Experience"].get<string>();
    cout << "\n3. Enter the Job's Field: " << data.at(account_index)["information"]["Fieldofinterest"].get<string>();
    cout << "\n4. Enter the Management Level: " << data.at(account_index)["information"]["Level"].get<string>();
    cout << "\n5. Enter a word that best describes a potential employee: " << data.at(account_index)["information"]["Oneword"].get<string>() << "\n\n\n";

    cout << "Enter the Question Number to Edit (0 to exit): ";
    cin >> selection;
    cout << "\n";
    if (selection < 1 || selection > 5)
    {
      break;
    }

    string answer;

    if (selection == 1)
    {
      cout << "1. Enter Country of Office: ";
      cin >> answer;
      updatevalueinformation(data, account_index, answer, "Country");
    }
    if (selection == 2)
    {
      cout << "2. Enter the Required Work Experience: ";
      cin >> answer;
      updatevalueinformation(data, account_index, answer, "Experience");
    }
    if (selection == 3)
    {
      cout << "3. Enter the Job's Field: ";
      cin >> answer;
      updatevalueinformation(data, account_index, answer, "Fieldofinterest");
    }
    if (selection == 4)
    {
      cout << "4. Enter the Management Level: ";
      cin >> answer;
      updatevalueinformation(data, account_index, answer, "Level");
    }
    if (selection == 5)
    {
      cout << "5. Enter a word that best describes a potential employee: ";
      cin >> answer;
      updatevalueinformation(data, account_index, answer, "Oneword");
    }
  }
}

int calculatematches(json &data, int account_index, string account_type)
{
  int matches = 0;
  string othertype;

  if (account_type == "User")
  {
    othertype = "Recruiter";
  }
  else if (account_type == "Recruiter")
  {
    othertype = "User";
  }

  for (int i = 0; i < data.size(); i++)
  {
    int same = 0;
    if (data.at(i)["setup"]["account_type"].get<string>() == othertype) // makes sure it is matching with the opposite account type. As an applicant is looking for employers, and employers are looking for applicants to fill their jobs
    {
      // Compares the applicants answers with the employers answers to see if they match (and vice versa)
      if (data.at(account_index)["information"]["Country"].get<string>() == data.at(i)["information"]["Country"].get<string>())
      {
        same += 1;
      }
      if (data.at(account_index)["information"]["Experience"].get<string>() == data.at(i)["information"]["Experience"].get<string>())
      {
        same += 1;
      }
      if (data.at(account_index)["information"]["Fieldofinterest"].get<string>() == data.at(i)["information"]["Fieldofinterest"].get<string>())
      {
        same += 1;
      }
      if (data.at(account_index)["information"]["Level"].get<string>() == data.at(i)["information"]["Level"].get<string>())
      {
        same += 1;
      }
      if (data.at(account_index)["information"]["Oneword"].get<string>() == data.at(i)["information"]["Oneword"].get<string>())
      {
        same += 1;
      }
    }

    // If 3 out of 5 answers match, they will be considered a match

    if (same >= 3)
    {
      matches += 1;
    }
  }

  return matches;
}

void newmessaes(json &dat, string to, string from, string message)
{
  // Creates an email in the allocated json file meant for emails

  // JSON object to hold the user's overall data
  json userObject;
  userObject["message"] = message;
  userObject["to"] = to;
  userObject["from"] = from;

  // Adds the user's data to the JSON array
  dat.push_back(userObject);
  std::ofstream output("dat.json");
  output << dat.dump(4);
  output.close();

  cout << "\n\n\nThe message has successfully sent to " << to << "!\n";
}

void inboxview(json &dat, json &data, int account_index)
{
  // Shows the user's inbox, by going through the email json file, and outputting the messages that are "to" the user

  string person = data.at(account_index)["setup"]["username"].get<string>();

  cout << "\n\nINBOX\n-----\n\n";
  int qq = 0;

  for (int i = 0; i < dat.size(); i++)
  {

    if (((dat.at(i)["to"].get<string>()) == person))
    {
      string otherperson = dat.at(i)["from"].get<string>();

      cout << "\n\n"
           << otherperson << ":\n     " << dat.at(i)["message"].get<string>() << "\n\n";
      qq = 1;
    }
  }
  if (qq == 0)
  {
    cout << "You have no emails in your inbox.\n";
  }
  cout << "\n";
}

void sentview(json &dat, json &data, int account_index)
{
  // Shows the user's sent emails, by going through the email json file, and outputting the messages that are "from" the user

  string person = data.at(account_index)["setup"]["username"].get<string>();

  cout << "\n\nSENT\n-----\n\n";

  int qq = 0;

  for (int i = 0; i < dat.size(); i++)
  {

    if (((dat.at(i)["from"].get<string>()) == person))
    {
      string otherperson = dat.at(i)["to"].get<string>();

      cout << otherperson << ":\n     " << dat.at(i)["message"].get<string>() << "\n\n";

      qq = 1;
    }
  }

  if (qq == 0)
  {
    cout << "You have no sent mail.\n";
  }
  cout << "\n";
}

void messageoptions(json &dat, json &data, int account_index)
{
  // Puts the email options in an easier to use format

  int messagechoice;

  while (true)
  {
    cout << "\n\n\nPress '1' to Compose an Email, '2' for Inbox, and '3' for Sent: ";
    cin >> messagechoice;

    bool temp = true;
    string to;
    string message;
    string from = data.at(account_index)["setup"]["username"].get<string>();
    if (messagechoice == 1)
    {
      while (temp)
      {
        cout << "\n\nWho are you sending the message to (username): ";
        cin >> to;

        for (int i = 0; i < data.size(); i++)
        {
          if (data.at(i)["setup"]["username"].get<string>() == to)
          {
            temp = false;
            break;
          }
        }
      }

      cout << "Enter the message to send: ";
      cin >> message;

      newmessaes(dat, to, from, message);
    }
    if (messagechoice == 2)
    {
      inboxview(dat, data, account_index);
    }
    if (messagechoice == 3)
    {
      sentview(dat, data, account_index);
    }
    else
    {
      break;
    }
  }
}

bool ismatch(int i, json &data, int account_index, string account_type)
{
  // Given a bool value on if a specific user and the logged in user are a match
  int matches = 0;
  string othertype;

  if (account_type == "User")
  {
    othertype = "Recruiter";
  }
  else if (account_type == "Recruiter")
  {
    othertype = "User";
  }
  int same = 0;
  if (data.at(i)["setup"]["account_type"].get<string>() == othertype)
  {
    if (data.at(account_index)["information"]["Country"].get<string>() == data.at(i)["information"]["Country"].get<string>())
    {
      same += 1;
    }
    if (data.at(account_index)["information"]["Experience"].get<string>() == data.at(i)["information"]["Experience"].get<string>())
    {
      same += 1;
    }
    if (data.at(account_index)["information"]["Fieldofinterest"].get<string>() == data.at(i)["information"]["Fieldofinterest"].get<string>())
    {
      same += 1;
    }
    if (data.at(account_index)["information"]["Level"].get<string>() == data.at(i)["information"]["Level"].get<string>())
    {
      same += 1;
    }
    if (data.at(account_index)["information"]["Oneword"].get<string>() == data.at(i)["information"]["Oneword"].get<string>())
    {
      same += 1;
    }
  }

  if (same >= 3)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void autoemailmatches(json &data, json &dat, int account_index, string account_type)
{

  // emails the applicants of whom are a match

  for (int a = 0; a < data.size(); a++)
  {
    if (ismatch(a, data, account_index, account_type))
    {
      newmessaes(dat, data.at(a)["setup"]["username"].get<string>(), data.at(account_index)["setup"]["username"].get<string>(), "I am happy to request an interview with you! Please reply to confirm a date and time!");
    }
  }
}

int main()
{

  // Setting up and giving access to the main JSON file and the email JSON file

  std::ifstream f("data.json");
  json data = json::parse(f);
  f.close();

  std::ifstream frr("dat.json");
  json dat = json::parse(frr);
  frr.close();

  // The following just activates the functions/features, and organizes the program in an appealing way

  string initial_choice;
  int account_index;
  string account_type;

  cout << "\n\nCoCo: Connect with Companies\n----------------------------\n-------------\n----\n\nWould you like to LOGIN or SIGN-UP or QUIT: ";
  cin >> initial_choice;
  cout << "\n";

  if (initial_choice == "SIGN-UP")
  {
    account_index = signup(data) - 1;
    cout << "\nAccount is Successfully Created, and you are Logged In as well!";
  }
  else if (initial_choice == "LOGIN")
  {
    account_index = login();
    if (account_index == -10)
    {
      cout << "\nThat Account Does Not Exist. Please Try Again...";
      main();
    }
    else
    {
      cout << "\nLogin is Successful!";
    }
  }
  else
  {
    cout << "\n\nQuitting CoCo...\n\n\n";
    return 0;
  }
  std::ifstream f2("data.json");
  json updatedData = json::parse(f2);
  f2.close();

  if (data.at(account_index)["setup"]["account_type"].get<string>() == "User")
  {
    account_type = "User";
  }
  else if (data.at(account_index)["setup"]["account_type"].get<string>() == "Recruiter")
  {
    account_type = "Recruiter";
  }

  if (account_type == "Recruiter")
  {
    while (true)
    {
      string option_user;

      cout << "\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------";
      cout << "\nLogged in as a Recruiter. Please Enter 'A' to update your Job Posting, 'B' to view the number of matches your job posting has with users, or Enter 'C' to access your Email: ";
      cin >> option_user;
      cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------";

      if (option_user == "A")
      {
        RecruiterProfile(data, account_index);
      }
      else if (option_user == "B")
      {
        cout << "\n\nYou have " << calculatematches(data, account_index, account_type) << " job match! ";

        string autocad;
        cout << "Enter YES if you would like to email an interview request to all the candidate matches: ";
        cin >> autocad;

        if (autocad == "YES")
        {
          autoemailmatches(data, dat, account_index, account_type);
        }
      }
      else if (option_user == "C")
      {
        messageoptions(dat, data, account_index);
      }
      else
      {
        cout << "\n\nQuitting CoCo...\n\n\n";
        break;
      }
    }
  }
  else if (account_type == "User")
  {
    while (true)
    {
      string option_user;

      cout << "\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------";
      cout << "\nLogged in as a User. Please Enter 'A' to update your Personal Profile, 'B' to view the number of job matches you have, or Enter 'C' to access your Email: ";
      cin >> option_user;
      cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------";

      if (option_user == "A")
      {
        UserProfile(data, account_index);
      }
      else if (option_user == "B")
      {
        cout << "\n\n\nYou have " << calculatematches(data, account_index, account_type) << " job matches!";
      }
      else if (option_user == "C")
      {
        messageoptions(dat, data, account_index);
      }
      else
      {
        cout << "\n\nQuitting CoCo...\n\n\n";
        break;
      }
    }
  }
}