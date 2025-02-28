/*
Name: Dev KishorKumar Shah
UIN: 658560014
Professor: Ethan Ordentlich
Project 1 – Library Management System
Class - CS251
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

// Function Declarations
void printMenu();
void addBookToFile(vector<string> &titles, vector<string> &isbns, vector<int> &statuses, const string &fileName);
void loadFromFile(vector<string> &titles, vector<string> &isbns, vector<int> &statuses, const string &fileName);
string getStatusString(int status);
void clearLibrary(vector<string> &titles, vector<string> &isbns, vector<int> &statuses);
void exportDataToFile(const string &outputFile, const vector<string> &titles, const vector<string> &isbns, const vector<int> &statuses);
void printCheckoutStats(const vector<int> &statuses);
void searchLibrary(const vector<string> &titles, const vector<string> &isbns, const vector<int> &statuses, int searchOption, const string &searchTerm);
void removeLibraryEntry(vector<string> &titles, vector<string> &isbns, vector<int> &statuses, int removeOption, const string &removeTerm);
void printInvalidEntries(const vector<string> &titles, const vector<string> &isbns, const vector<int> &statuses);
void displayLibrary(const vector<string> &titles, const vector<string> &isbns, const vector<int> &statuses);

int main()
{
    string command;

    // Using vectors to store the library data
    vector<string> titles;
    vector<string> isbns;
    vector<int> statuses;

    cout << "Welcome to the Library Management System" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    do
    {
        printMenu();
        cout << endl
             << "Enter a command (case does not matter): ";
        getline(cin, command);
        cout << endl;
        if (command == "a" || command == "A")
        {
            /*string fileName;
            cout << "Enter the filename you want to add the book: ";
            getline(cin, fileName);
            cout << "\n";
            */
            addBookToFile(titles, isbns, statuses, "database.csv"); // The argument database.csv can be changed to fileName and this function can be used according to input based
        }
        else if (command == "l" || command == "L")
        {
            string fileName;
            cout << "What database to read from? ";
            getline(cin, fileName);
            cout << "\n";

            loadFromFile(titles, isbns, statuses, fileName);
        }

        else if (command == "c" || command == "C")
        {
            clearLibrary(titles, isbns, statuses);
        }

        else if (command == "o" || command == "O")
        {
            string outputFile;
            cout << "Enter the name of the output file: ";
            getline(cin, outputFile);
            cout << "\n";

            exportDataToFile(outputFile, titles, isbns, statuses);
        }

        else if (command == "d" || command == "D")
        {
            displayLibrary(titles, isbns, statuses);
        }
        else if (command == "p" || command == "P")
        {
            printCheckoutStats(statuses);
        }
        else if (command == "s" || command == "S")
        {
            int searchOption;
            cout << "Would you like to search by (1) name or (2) ISBN." << endl;
            cout << "Enter the numeric choice: ";
            cin >> searchOption;
            cin.ignore(); // Consume newline character
            if (searchOption == 1 || searchOption == 2)
            {
                cout << "Enter the " << (searchOption == 1 ? "book name" : "book 13-digit ISBN (with dashes)") << ": ";
                string searchTerm;
                getline(cin, searchTerm);
                cout << "\n";

                searchLibrary(titles, isbns, statuses, searchOption, searchTerm);
            }
            else // if the numeric choice is not 1 or 2 then this error message is printed
            {
                cout << "Invalid search by choice option." << endl;
            }
        }
        else if (command == "r" || command == "R")
        {
            int removeOption;
            cout << "Would you like remove by (1) name or (2) ISBN." << endl;
            cout << "Enter the numeric choice: ";
            cin >> removeOption;
            cin.ignore(); // Consume newline character

            if (removeOption == 1 || removeOption == 2)
            {
                cout << "Enter the " << (removeOption == 1 ? "book name" : "book 13-digit ISBN (with dashes)") << ": ";
                string removeTerm;
                getline(cin, removeTerm);
                cout << "\n";

                removeLibraryEntry(titles, isbns, statuses, removeOption, removeTerm);
            }
            else // if the numeric choice is not 1 or 2 then this error message is printed
            {
                cout << "Invalid remove by choice option." << endl;
            }
        }
        else if (command == "i" || command == "I")
        {
            printInvalidEntries(titles, isbns, statuses);
        }

        cout << endl;
    } while (!(command == "x" || command == "X"));

    return 0;
}

void printMenu()
{
    cout << "Library Management Menu" << endl;
    cout << "-----------------------" << endl;
    cout << "A - Add Item To Library" << endl;
    cout << "C - Clear The Library Of All Entries" << endl;
    cout << "D - Display Library Entries" << endl;
    cout << "I - List Invalid Library Entries" << endl;
    cout << "L - Load Library From File" << endl;
    cout << "O - Output Library To File" << endl;
    cout << "P - Print Out Checkout Stats" << endl;
    cout << "R - Remove A Library Entry" << endl;
    cout << "S - Search For A Library Entry" << endl;
    cout << "X - Exit Program" << endl;
}

void addBookToFile(vector<string> &titles, vector<string> &isbns, vector<int> &statuses, const string &fileName)
{
    string title, isbn;
    cout << "What is the book title? ";
    getline(cin, title); // Getting user input for Book
    cout << "\n";
    size_t index = title.find(',');
    if (!(index == string::npos)) // Checking if the title contains any commas if it does then the error message is printed
    {
        cout << "The book title cannot contain commas." << endl;
        return;
    }

    cout << "What is the 13-digit ISBN (with hyphens)? "; // Getting user input for ISBN
    getline(cin, isbn);
    cout << "\n";

    // Add the data to vectors
    titles.push_back(title);
    isbns.push_back(isbn);
    statuses.push_back(0); // Default status for the book

    // Open the CSV file in append mode
    ofstream dataFile;
    dataFile.open(fileName, ios::app);

    if (dataFile.is_open())
    {
        // Write the new book information to the file
        size_t lastIndex = titles.size() - 1;
        dataFile << titles[lastIndex] << "," << isbns[lastIndex] << "," << statuses[lastIndex] << "\n";
        dataFile.close();
        // Printing out the  library on the console
        cout << "The Following Entry Was Added\n";
        cout << "-----------------------------\n";
        cout << titles[lastIndex] << " --- " << isbns[lastIndex] << " --- " << getStatusString(statuses[lastIndex]) << endl;
    }
    else // Error message if the file was not opened properly
    {
        cout << "Unable to open the database file." << endl;
    }
}

void loadFromFile(vector<string> &titles, vector<string> &isbns, vector<int> &statuses, const string &fileName)
{
    ifstream dataFile;
    dataFile.open(fileName);

    if (dataFile.is_open())
    {
        string line;
        int count = 0; // Counting the number of lines read from the file
        while (getline(dataFile, line))
        {
            // Skip empty lines
            if (line.empty())
            {
                continue;
            }
            count++; // incrementing count

            size_t firstComma = line.find(",");                  // Finding the first comma after the title
            size_t secondComma = line.find(",", firstComma + 1); // Finding the second comma after isbn and the starting position is the first character of isbn

            if (firstComma != string::npos) // This condition checks if after the first comma it is not equal to npos which means there is no isbn
            {
                string title = line.substr(0, firstComma);
                string isbn;
                isbn = line.substr(firstComma + 1, secondComma - firstComma - 1);
                if (isbn.size() == 0)
                {
                    isbn = "000-0-00-000000-0"; // Default ISBN if not provided
                }

                // if (secondComma != string::npos)
                // {
                //     isbn = line.substr(firstComma + 1, secondComma - firstComma - 1);
                // }
                // else
                // {
                //     isbn = "000-0-00-000000-0"; // Default ISBN if not provided
                // }

                int status = 0;                  // Default status is "In Library"
                if (secondComma != string::npos) // Checking if the status is provided in the datafile
                {
                    // Check if status is provided in the line
                    status = stoi(line.substr(secondComma + 1)); // Convert status to integer
                }
                else
                {
                    // Status not provided, set it to "In Library"
                    status = 0;
                }

                titles.push_back(title);
                isbns.push_back(isbn);
                statuses.push_back(status);
            }
            else
            {
                // This is for edge cases if the line does not contain any comma
                string title = line;
                string isbn = " 000-0-00-000000-0"; // Default ISBN
                int status = 0;                     // Default status is "In Library"

                titles.push_back(title);
                isbns.push_back(isbn);
                statuses.push_back(status);
            }
        }

        dataFile.close();

        if (!titles.empty())
        {
            cout << "Read in " << count << " lines from the file.\n"; // printing out the number of lines read
        }
        else
        {
            cout << "No entries to display." << endl;
        }
    }
    else
    {
        cout << "Could not find the database file." << endl;
    }
}

void displayLibrary(const vector<string> &titles, const vector<string> &isbns, const vector<int> &statuses)
{
    if (titles.empty()) // if library is empty then this error message is displayed
    {
        cout << "Your Current Library\n"
             << "--------------------\n";
        cout << "The library has no books.\n";
    }
    else
    {
        cout << "Your Current Library\n"
             << "--------------------\n";

        for (size_t i = 0; i < titles.size(); ++i)
        {
            cout << titles[i] << " ---" << isbns[i] << " --- ";

            // Check if the status index is valid
            if (i < statuses.size())
            {
                cout << getStatusString(statuses[i]) << endl; // getStatusString changes the status from int to its appropriate string values
            }
            else
            {
                cout << "In Library" << endl; // Default to "In Library" if status is not provided
            }
        }
    }
}

string getStatusString(int status) // sets status to its string representation
{
    if (status == 0)
    {
        return "In Library";
    }
    else if (status == 1)
    {
        return "Checked Out";
    }
    else if (status == 2)
    {
        return "On Loan";
    }
    else if (status == 3)
    {
        return "Unknown State";
    }
    else
    {
        return "Invalid State";
    }
}

void clearLibrary(vector<string> &titles, vector<string> &isbns, vector<int> &statuses) // Clearing the library by empyting all the data from the vectors
{
    titles.clear();
    isbns.clear();
    statuses.clear();
    cout << "Your Library is now empty." << endl;
}

void exportDataToFile(const string &outputFile, const vector<string> &titles, const vector<string> &isbns, const vector<int> &statuses) // This function exports all the data from the vector to the target file which is given by the user.
{
    ofstream output;
    output.open(outputFile);

    if (!output.is_open())
    {
        cout << "Unable to open the output file." << endl;
    }
    else
    {
        // Export data from vectors to the output file
        for (size_t i = 0; i < titles.size(); ++i)
        {
            output << titles[i] << "," << isbns[i] << "," << statuses[i] << "\n"; // writing the data to the file.
        }

        cout << "\n";
        cout << "Data exported to " << outputFile << ".\n";
        output.close();
    }
}
void printCheckoutStats(const vector<int> &statuses) // printing out the statuses in an organised way by categorizing them into these sections
{
    int totalBooks = statuses.size();
    int inLibraryCount = 0;
    int checkedOutCount = 0;
    int onLoanCount = 0;
    int unknownCount = 0;
    int otherCount = 0;

    // Calculate the counts for each status
    for (int status : statuses)
    {
        switch (status)
        {
        case 0:
            inLibraryCount++;
            break;
        case 1:
            checkedOutCount++;
            break;
        case 2:
            onLoanCount++;
            break;
        case 3:
            unknownCount++;
            break;
        default:
            otherCount++;
            break;
        }
    }

    // Print the checkout stats
    cout << "Your Current Library's Stats" << endl;
    cout << "----------------------------" << endl;
    cout << "Total Books: " << totalBooks << endl;
    cout << "   In Library: " << inLibraryCount << endl;
    cout << "   Checked Out: " << checkedOutCount << endl;
    cout << "   On Loan: " << onLoanCount << endl;
    cout << "   Unknown: " << unknownCount << endl;
    cout << "   Other: " << otherCount << endl;
}
void searchLibrary(const vector<string> &titles, const vector<string> &isbns, const vector<int> &statuses, int searchOption, const string &searchTerm) // searching for a particular book in the library database.
{
    int lastIndex = -1; // Initialize to an invalid index

    for (int i = titles.size() - 1; i >= 0; --i)
    {
        bool isMatch = false;

        if (searchOption == 1) // Search by name
        {
            // Perform case-insensitive search on titles
            if (titles[i].compare(searchTerm) == 0)
            {
                lastIndex = i;
                break; // Stop searching once an exact match is found
            }
        }
        else if (searchOption == 2) // Search by ISBN
        {
            // Perform case-insensitive search on ISBNs
            if (isbns[i].compare(searchTerm) == 0)
            {
                lastIndex = i;
                break; // Stop searching once an exact match is found
            }
        }
    }

    if (lastIndex != -1)
    {
        cout << "The Following Are Your Search Results\n"
             << "-------------------------------------\n";
        cout << titles[lastIndex] << "---" << isbns[lastIndex] << "---" << getStatusString(statuses[lastIndex]) << endl; // by setting the lastIndex to the i we get to particular book from the database and we can print out all data which goes together with that book.
    }
    else
    {
        cout << "The Following Are Your Search Results\n"
             << "-------------------------------------\n";
        cout << "No matching entry found in the library." << endl;
    }
}
void removeLibraryEntry(vector<string> &titles, vector<string> &isbns, vector<int> &statuses, int removeOption, const string &removeTerm) // removing a particular book from the library database, using the same logic used in previous function searchLibrary.
{
    int lastIndex = -1; // Initialize to an invalid index

    for (int i = titles.size() - 1; i >= 0; --i)
    {
        bool isMatch = false;

        if (removeOption == 1) // Remove by name
        {
            // Perform case-insensitive search on titles
            if (titles[i].compare(removeTerm) == 0)
            {
                lastIndex = i;
                break; // Stop searching once an exact match is found
            }
        }
        else if (removeOption == 2) // Remove by ISBN
        {
            // Perform case-insensitive search on ISBNs
            if (isbns[i].compare(removeTerm) == 0)
            {
                lastIndex = i;
                break; // Stop searching once an exact match is found
            }
        }
    }

    if (lastIndex != -1)
    {
        cout << "The Following Entry Was Removed From The Library\n"
             << "------------------------------------------------\n";
        cout << titles[lastIndex] << " --- " << isbns[lastIndex] << " --- " << getStatusString(statuses[lastIndex]) << endl;

        // Remove the entry from the vectors
        titles.erase(titles.begin() + lastIndex);
        isbns.erase(isbns.begin() + lastIndex);
        statuses.erase(statuses.begin() + lastIndex);
    }
    else
    {
        cout << "The Following Entry Was Removed From The Library\n"
             << "------------------------------------------------\n";
        cout << "No matching entry found in the library." << endl;
    }
}

void printInvalidEntries(const vector<string> &titles, const vector<string> &isbns, const vector<int> &statuses)
{
    cout << "The Following Library Entries Have Invalid Data\n"
         << "-----------------------------------------------\n";

    if (titles.empty() || isbns.empty() || statuses.empty())
    {
        cout << "The library has no books." << endl;
        return;
    }

    bool hasInvalidEntries = false;
    int status = 0;

    for (size_t i = 0; i < titles.size(); i++)
    {
        bool invalidISBN = false;
        bool invalidStatus = false;

        // Remove hyphens from ISBN and whitespaces and then check its length
        string isbnWithoutHyphens;
        for (char c : isbns[i])
        {
            if (c != '-' && c != ' ')
            {
                isbnWithoutHyphens += c;
            }
        }
        // cout << "/" << isbnWithoutHyphens << "/" << endl;

        // cout << isbnWithoutHyphens.size() << endl;

        if (isbnWithoutHyphens.size() != 13)
        {
            invalidISBN = true;
        }
        else
        {
            // Calculate the ISBN-13 check digit
            int sum = 0;
            for (int j = 0; j < 12; ++j)
            {
                if (j < 12 && isdigit(isbnWithoutHyphens[j]))
                {
                    int digit = isbnWithoutHyphens[j] - '0';
                    // cout << digit << endl;
                    sum += (j % 2 == 0) ? digit : (3 * digit);
                }
                else
                {
                    invalidISBN = true; // Non-digit character found
                    break;
                }
            }
            // cout << sum << "sum" << endl;

            int checkDigit = (10 - (sum % 10));
            // cout << checkDigit << endl;

            if (checkDigit != (isbnWithoutHyphens[12] - '0'))
            {
                invalidISBN = true; // Invalid check digit
            }
        }

        // Check checkout status validity if it's provided
        if (i < statuses.size())
        {
            status = statuses[i];
            if (status > 3)
            {
                // cout << status << "\n";
                invalidStatus = true; // Invalid status
            }
        }

        // Output invalid entries
        if (invalidISBN || invalidStatus)
        {
            cout << titles[i] << " --- " << isbns[i] << " --- " << getStatusString(statuses[i]) << endl;
            hasInvalidEntries = true;
        }
    }

    if (!hasInvalidEntries)
    {
        cout << "The library has no invalid entries." << endl;
    }
}
