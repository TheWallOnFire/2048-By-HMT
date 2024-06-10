//#include "Defined.h"
//
//#include <iostream>
//#include <fstream> //Create and write to files
//#include <sstream> //templates and types that enables interoperation between string buffers and string objects
//#include <string>
//#include <cstdlib>
//
//using namespace std;
//
//int main()
//{
//    int a, i = 0;
//    string text, old, password1, password2, pass, name, password0, age, user, word, word1;
//    string creds[2], cp[2];
//
//    //Check if file exists and can be opened, else create file
//    ofstream of;
//
//    of.open("user_file.txt", ios::app);
//    if (!of)
//    {
//        cout << "System Error: Unable to create user_file.txt database.\nSystem execution halted." << endl;
//        exit(0);
//    }
//    of.close();
//
//    cout << "-----------------------" << endl;
//    cout << "   Securtiy System     " << endl;
//    cout << "-----------------------" << endl << endl;
//
//    do
//    {
//        cout << endl << endl;
//        cout << "   Select an option:   " << endl;
//        cout << "***********************" << endl;
//        cout << "   1. Register         " << endl;
//        cout << "   2. Login            " << endl;
//        cout << "   3. Change Password  " << endl;
//        cout << "   4. End Program      " << endl << endl;
//
//        cout << endl << endl;
//        cout << "Enter your choice: " << endl;
//        cin >> a;
//
//        switch (a)
//        {
//        case 1: //capture basic user creds and save them to a file
//        {
//            cout << "    Register New User    " << endl;
//            cout << "*************************" << endl << endl;
//            cout << "Please enter a username:-" << endl;
//            cin >> name;
//            cout << "Please enter a password:-" << endl;
//            cin >> password0;
//            cout << "Please enter your age:- " << endl;
//            cin >> age;
//
//            //Open file and write basic user data to the file
//            ofstream of1;
//            of1.open("user_file.txt", ios::app);
//            if (of1.is_open())
//            {
//                of1 << "\n\n";
//                of1 << name << "\n";
//                of1 << password0 << "\n";
//                of1 << age << "\n";
//                cout << "Registration successful" << endl;
//            }
//            of1.close();
//            break;
//        }
//        case 2: //Accept user credentials and compare them to file contents
//        {
//            i = 0;
//
//            cout << "          Login          " << endl;
//            cout << "*************************" << endl << endl;
//            cout << "Please enter a username:-" << endl;
//            cin >> user;
//            cout << "Please enter a password:-" << endl;
//            cin >> pass;
//
//            //Open file to compare credentials and validate user
//            ifstream of2;
//            of2.open("user_file.txt");
//
//            if (of2.is_open())
//            {
//                while (!of2.eof())
//                {
//                    while (getline(of2, text))
//                    {
//                        istringstream iss(text);
//                        iss >> word;
//                        creds[i] = word;
//                        i++;
//                    }
//
//                    if (user == creds[0] && pass == creds[1])
//                    {
//                        cout << endl << "Login successful!" << endl;
//                        cout << "Details: " << endl;
//                        cout << "Username: " + user << endl;
//                        cout << "Password: " + pass << endl;
//                    }
//                    else
//                    {
//                        cout << "Login unsuccessful. \n Invalid credentials submitted." << endl;
//                    }
//                }
//            }
//
//            break;
//        }
//        case 3: //Accept user password and update file
//        {
//            i = 0;
//            cout << "         Change Password         " << endl;
//            cout << "*********************************" << endl << endl;
//
//            ifstream of0;
//            of0.open("user_file.txt");
//
//            cout << "Please enter your current password:-" << endl;
//            cin >> old;
//
//            if (of0.is_open())
//            {
//                while (!of0.eof())
//                {
//                    while (getline(of0, text))
//                    {
//                        istringstream iss(text);
//                        iss >> word1;
//                        cp[i] = word1;
//                        i++;
//                    }
//
//                    if (old == cp[1])
//                    {
//                        of0.close();//close existing file & free up memory space. 
//
//                        ofstream of1;
//                        if (of1.is_open())
//                        {
//                            cout << "Enter your new password:-" << endl;
//                            cin >> password1;
//                            cout << "Reenter the new password to confirm:- " << endl;
//                            cin >> password2;
//
//                            if (password1 == password2)
//                            {
//                                of1 << cp[0] << "\n";
//                                of1 << password1;
//                                cout << "Password changed successfully." << endl;
//                            }
//                            else
//                            {
//                                of1 << cp[0] << "\n";
//                                of1 << old;
//                                cout << "Password do not match." << endl;
//                            }
//                        }
//                        else
//                        {
//                            cout << "Credential mismatch. Password not changed." << endl;
//                        }
//                    }
//                }
//            }
//            break;
//        }
//        case 4:
//        {
//            cout << "Program terminination in progress." << endl;
//            cout << "Program shutdown complete." << endl;
//            break;
//        }
//        default: //Assume no valid option selected
//        {
//            cout << "No valid option selected.\nPlease try again." << endl;
//            break;
//        }
//        }
//    } while (a != 4);
//    return 0;
//}