#include <iostream>
#include <string>

using namespace std;

/* TODO
 *
 * BETTER MENU
 *  - entire screen between entries (page break insert)
 *  - switching if else to switch case break
 *
 * TESTING
 *  - random testing options
 *  - bigger testing sizes
 *  - long testing options (valgrind)
 *
 * BETTER DATING (DONE)
 *  - measuring by year (DONE)
 */
int globalCurrentYear = 2022;
int globalCurrentMonth = 10;
int globalCurrentDay = 23;

template <class aTemplate>

class LinkedList{
public:
        LinkedList* nextLinkedList;
        aTemplate* item;

        LinkedList(){
            this->item = nullptr;
            this->nextLinkedList = nullptr;
        }

        LinkedList(aTemplate* item){
            this->item = item;
            this->nextLinkedList = nullptr;
        }
        void printLinkedList(){
            if(item != nullptr){
                cout << *item;
            }
            else{
                cout << "nullptr";
            }
        }

};

template <class aTemplate>

class List{

    private:
        LinkedList<aTemplate> *firstLinkedList;
        LinkedList<aTemplate> *finalLinkedList;
        LinkedList<aTemplate> *CurLinkedList;
    public:

    List(){
        this->firstLinkedList = nullptr;
        this->finalLinkedList = nullptr;
        CurLinkedList = nullptr;
    }

    ~List(){
        LinkedList<aTemplate> *temp = firstLinkedList;
        while(firstLinkedList != nullptr){
            firstLinkedList = firstLinkedList->nextLinkedList;
            delete temp;
            temp = firstLinkedList;
        }
    }

    void AddItem(aTemplate* item){
        LinkedList<aTemplate> *NewLinkedList = new LinkedList<aTemplate>(item);

        if(firstLinkedList != nullptr){
            LinkedList<aTemplate> *linkedListIter = firstLinkedList;
            LinkedList<aTemplate> *linkedListIterLaggingBehind;
            // inserting at front
            if (NewLinkedList->item >= firstLinkedList->item)
            {
                NewLinkedList->nextLinkedList = firstLinkedList;
                firstLinkedList = NewLinkedList;
                return;
            }
            // inserting in list
            while (linkedListIter->item < NewLinkedList->item)
            {
                if (linkedListIter->nextLinkedList == nullptr)
                {
                    // inserting at finalLinkedList
                    finalLinkedList->nextLinkedList = NewLinkedList;
                    finalLinkedList = finalLinkedList->nextLinkedList;
                    return;
                }
                linkedListIterLaggingBehind = linkedListIter;
                linkedListIter = linkedListIter->nextLinkedList;
            }
            NewLinkedList->nextLinkedList = linkedListIter;
            linkedListIterLaggingBehind->nextLinkedList = NewLinkedList;

        }
        else{
            firstLinkedList = NewLinkedList;
            finalLinkedList = NewLinkedList;
        }

    }

    aTemplate* GetItem(aTemplate* item){
       LinkedList<aTemplate> *linkedListIterator = firstLinkedList;

        if(linkedListIterator->item == item){
            firstLinkedList = firstLinkedList->nextLinkedList;
            delete linkedListIterator;
            return item;
        }
        if(linkedListIterator != nullptr){

            while(linkedListIterator->nextLinkedList != nullptr && linkedListIterator->nextLinkedList->item != item){
                linkedListIterator = linkedListIterator->nextLinkedList;
            }
            if(linkedListIterator != nullptr){
                linkedListIterator->nextLinkedList = linkedListIterator->nextLinkedList->nextLinkedList;
                linkedListIterator = linkedListIterator->nextLinkedList;
                delete linkedListIterator;
                return item;
            }
            return nullptr;
            }
        else{
            return nullptr;
        }
   }

   bool IsInList(aTemplate* item){
       LinkedList<aTemplate>* temp = firstLinkedList;
       while(temp != nullptr){
           if(temp->item == item){
               return true;
           }
           temp = temp->nextLinkedList;
       }
       return false;
   }

   bool IsEmpty(){ // this assumes every linked list node has an item
       if(firstLinkedList == nullptr){
           return true;
       }
       return false;
   }

   int Size(){
       LinkedList<aTemplate> *linkedListIterator = firstLinkedList;
       int c = 0;
       while(linkedListIterator != nullptr){
           linkedListIterator = linkedListIterator->nextLinkedList;
           c++; // :)
       }
       return c;
   }

    aTemplate* SeeNext(){
        if(firstLinkedList == nullptr){
            cout << "Error: List is empty" << endl;
            return nullptr;
        }
        if(CurLinkedList == nullptr){
            CurLinkedList = firstLinkedList;
            return CurLinkedList->item;
        }
        if (CurLinkedList->nextLinkedList == nullptr){
            cout << "Error: End of List" << endl;
            return nullptr;
        }
        CurLinkedList = CurLinkedList->nextLinkedList;
        return CurLinkedList->item;

   }

   aTemplate* SeeAt(int i){
       LinkedList<aTemplate>* temp = firstLinkedList;
       int j = 1;
       while(temp != nullptr && j != i){
           j+=1;
           temp = temp->nextLinkedList;
       }
       if(temp != nullptr){
           CurLinkedList = temp;
           return temp->item;
       }
       cout << "Error: Index not in list" << endl;
       return nullptr;
   }

   // Sets location of SeeNext to the start of the list
    void Reset(){
       CurLinkedList = nullptr;
    }

    void printItem(aTemplate* item){
        if(item != nullptr){
            cout << *item;
        }
        else{
            cout << "No value";
        }
    }

    void display(){
        if(firstLinkedList != nullptr){
            LinkedList<aTemplate> *temp = firstLinkedList;
            while(temp->nextLinkedList != nullptr){
                temp->printLinkedList();
                cout << endl;
                temp = temp->nextLinkedList;
            }
            temp->printLinkedList();
            cout << endl;
        }
        else{
            cout << "List is empty.\n" << endl;
        }
   }

};

class Student{
    private:
        string FirstName;
        string LastName;
        string MNumber;
        float GPA;
        string BirthDate;
    public:
        Student(string FirstName, string LastName, string MNumber, string BirthDate, float GPA = 0.0){
            this->FirstName = FirstName;
            this->LastName = LastName;
            this->MNumber = MNumber;
            this->GPA = GPA;
            this->BirthDate = BirthDate;
        }
        string GetName(){
            return FirstName + " " + LastName;
        }
        string GetMNumber(){
            return MNumber;
        }
        int GetAge(){
            int Age = stoi(BirthDate.substr(BirthDate.length()-4,BirthDate.length()-1)); //Casting strings to integers
            if ((stoi(BirthDate.substr(3,5)) - globalCurrentMonth) > 0)
            {
                Age++;
                if ((stoi(BirthDate.substr(0,2)) - globalCurrentMonth) < 0)
                {
                    Age--;
                }
            }
            return globalCurrentYear - Age;
        }
        bool operator> (Student AStudent){
            int A;
            int B;
            A = stoi(this->GetMNumber().substr(1, this->GetMNumber().length()-1));
            B = stoi(AStudent.GetMNumber().substr(1, AStudent.GetMNumber().length()-1));
                if(A > B){
                    return true;
                }
                else{
                    return false;
                }
            }
         bool operator< (Student AStudent){
            int A;
            int B;
            A = stoi(this->GetMNumber().substr(1, this->GetMNumber().length()-1));
            B = stoi(AStudent.GetMNumber().substr(1, AStudent.GetMNumber().length()-1));
                if(A < B){
                    return true;
                }
                else{
                    return false;
                }
            }
         bool operator== (Student AStudent){
            int A;
            int B;
            A = stoi(this->GetMNumber().substr(1, this->GetMNumber().length()-1));
            B = stoi(AStudent.GetMNumber().substr(1, AStudent.GetMNumber().length()-1));
                if(A == B){
                    return true;
                }
                else{
                    return false;
                }
            }
         void print()
         {

             cout << "Name: " << this->GetName()
                  << '\t' << "MNumber: " << this->MNumber
                  << '\t' << "Birth Date: " << this->BirthDate
                  << '\t' << endl;
         }

         friend ostream &operator<<( ostream &output, const Student &student )
         {
             output  << "Name: " << student.FirstName << " " << student.LastName
                    << '\t' << "MNumber: " << student.MNumber
                    << '\t' << "Birth Date: " << student.BirthDate
                    << '\t' << endl;
             return output;
         }


         ostream& operator<<(ostream &output)
         {
             output  << "Name: " << this->GetName()
                     << '\t' << "MNumber: " << this->MNumber
                     << '\t' << "Birth Date: " << this->BirthDate
                     << '\t' << endl;
             return output;
         }


};





// User interface for LinkedList of Students
void UserMenu(){
    // UserMenu base provided by Nitin Nitin
    // Creates a list of students
    List<Student> sList = List<Student>();

    // Input String
    string input = "";
    string prompt = "Select an option: \n\nPrint List \t- \tp\nAdd Student \t- \ta\nDel Student \t- \td\nCheck List \t- \tc\nCheck empty \t- \te\nCheck Size \t- \ts\nNext Student \t- \tn\nStudent at \t- \tm\nReset index \t- \tr\n\nQuit - q\nHelp - h\n";
    string studentList = " _____ _             _            _     _     _     _   \n/  ___| |           | |          | |   | |   (_)   | |  \n\\ `--.| |_ _   _  __| | ___ _ __ | |_  | |    _ ___| |_ \n `--. \\ __| | | |/ _` |/ _ \\ '_ \\| __| | |   | / __| __|\n/\\__/ / |_| |_| | (_| |  __/ | | | |_  | |___| \\__ \\ |_ \n\\____/ \\__|\\__,_|\\__,_|\\___|_| |_|\\__| \\_____/_|___/\\__|";

    while(input != "q"){
        cout << prompt << endl;
        cin >> input;
        cout << '\f';
        if(input == "p"){
            cout << studentList << endl;
            cout << "Student Name\t\t\tM Number" << endl;
            cout << "__________________________________________________________________________" << endl;
            sList.display();
        }
        else if(input == "a"){
            // Input for optional GPA
            string i = "";

            // Required Student Variables
            string first;
            string last;
            // Birthday Inputed seperately
            string mNum;
            string dateHolderMonth, dateHolderDay, dateHolderYear;

            // Prompts user for Student information
            cout << "Creating new Student...\n\nEnter First Name: ";
            cin >> first;
            cout << "Enter Last Name: ";
            cin >> last;
            cout << "Enter M#: ";
            cin >> mNum;
            cout << "Enter Birthday:";
            string bDay = "lol";
            while (true)
            {
                cout << "\nBirth Month (2 digits, please include leading 0's): " << endl;
                cin >> dateHolderMonth;
                cout << "Birth Day (2 digits, please include leading 0's): ";
                cin >> dateHolderDay;
                cout << "Birth Year (4 digits, please include leading 0's): ";
                cin >> dateHolderYear;
                bDay = string(dateHolderMonth + "/" + dateHolderDay + "/" + dateHolderYear);
                if (bDay.length() == 10)
                {
                    break;
                }
                cout << "Malformed data! Please enter the birth day correctly. \n";
                cout << bDay.length() << "  " << bDay;
            }

            // Optional GPA
            cout << "Would you like to include GPA?(y/n)";
            cin >> i;
            if(i == "y"){
                double GPA;
                cout << "Enter GPA: ";
                cin >> GPA;
                // Creates a student with GPA
                Student *newStudent = new Student(first, last, mNum, bDay, GPA);
                sList.AddItem(newStudent);
            }
            else{
                // Creates Student without GPA
                Student *newStudent = new Student(first, last, mNum, bDay);
                sList.AddItem(newStudent);
            }
            cout << "Student Created." << endl;


        }
        else if(input == "d"){
            string mNum;
            if(sList.Size() == 0){
                cout << "List is empty, cannot delete Students.\n" << endl;
                continue;
            }
            cout << "Enter the M# of the student to be deleted: ";
            cin >> mNum;
            Student temp = Student("F", "L", mNum, "00000000");
            if(sList.GetItem(&temp) == nullptr){
                cout << "Student not found. Nothing modified.\n" << endl;
            }
            else{
                cout << "Student Deleted.\n" << endl;
            }
        }
        else if(input == "c"){
            string mNum;
            cout << "Enter the M# of the student to check: ";
            cin >> mNum;
            Student temp = Student("F", "L", mNum, "00000000");
            if(!(sList.IsInList(&temp))){
                cout << "Student not found in List.\n" << endl;
            }
            else{
                cout << "Student is in the List.\n" << endl;
            }
        }
        else if(input == "e"){
            if(sList.IsEmpty()){
                cout << "List is empty.\n" << endl;
            }
            else{
                cout << "List is not empty.\n" << endl;
            }
        }
        else if(input == "s"){
            cout << "List is " << sList.Size() << " Students.\n" << endl;
        }
        else if(input == "n"){
            Student *temp = sList.SeeNext();
            if(temp != nullptr){
                temp->print();
            }
            cout << endl;
        }
        else if(input == "m"){
            int i;
            cout << "What index would you like to check?: ";
            cin >> i;
            Student *temp = sList.SeeAt(i);
            if(temp != nullptr){
                temp->print();
            }
            cout << endl;
        }
        else if(input == "r"){
            sList.Reset();
            cout << "Resetting List Index...\n" << endl;

        }
        else if(input == "h"){
            cout << prompt << endl;
        }
        else if(input != "q"){
            cout << "Invalid Input, please try again." << endl;
        }

    }


}



void TestStudent(){
    // Test Student 1
    string first1 = "Takeshi";
    string last1 = "Tanaka";
    string bDay1 = "18/10/1998";
    string mNum1 = "#123456789";
    double GPA1 = 3.98;

    // Test Student 2
    string first2 = "John";
    string last2 = "Smith";
    string bDay2 = "18/10/1996";
    string mNum2 = "#987654321";
    double GPA2 = 3.72;

    Student Takeshi = Student(first1, last1, mNum1, bDay1, GPA1);
    Student John = Student(first2, last2, mNum2, bDay2, GPA2);
    cout << "Name: " << Takeshi.GetName() << "\nAge: " << Takeshi.GetAge() << "\nM#: " << Takeshi.GetMNumber() << endl << endl;
    cout << "Name: " << John.GetName() << "\nAge: " << John.GetAge() << "\nM#: " << John.GetMNumber() << endl << endl;

    cout << "M# Are equal: " << (Takeshi==John) << endl;
    cout << "John has larger M#: " << (Takeshi<John) << endl;
    cout << "Takeshi has larger M#: " << (Takeshi>John) << endl;
}


void TestList(){
    List<int> newList;
    int a = rand() % 100;
    int b = rand() % 100;
    int c = rand() % 100;
    cout << "a:" << a << "\t b:" << b << "\t c:" << c << endl;
    newList.AddItem(&a);
    cout << "Appending " << a << ": ";
    newList.display();
    newList.AddItem(&b);
    cout << "Appending " << b << ": ";
    newList.display();
    newList.AddItem(&c);
    cout << "Appending " << c << ": ";
    newList.display();
    cout << "List size: " << newList.Size() << endl;

    cout << "NextLinkedList: " << *newList.SeeNext() << endl; // First Item
    cout << "NextLinkedList: " <<  *newList.SeeNext() << endl; // Second Item
    cout << "NextLinkedList: " <<  *newList.SeeNext() << endl; // Third Item
    cout <<  "NextLinkedList: ";
    newList.SeeNext();

    cout << "Reseting NextLinkedList..." << endl;
    newList.Reset();    // Resets the CurLinkedList


    cout << "NextLinkedList: " <<  *newList.SeeNext() << endl; // Second Item
    cout << "NextLinkedList: " <<  *newList.SeeAt(1) << endl;
    cout << "NextLinkedList: " <<  *newList.SeeNext() << endl; // Second Item

    cout << endl;
    newList.display();
    cout << "Is " << c << " in List?: " << newList.IsInList(&c) << endl;
    newList.GetItem(&c);

    cout << endl;
    newList.display();
    cout << "Is " << c << " in List?: " << newList.IsInList(&c) << endl;

    cout << endl;
    newList.display();
    cout << "Is empty?: " << newList.IsEmpty() << endl;

    cout << endl;
    newList.GetItem(&a);
    newList.GetItem(&b);
    newList.display();
    cout << "Is empty?: " << newList.IsEmpty() << endl;

    cout << endl;
    newList.display();
    newList.~List();
    newList.display();
    cout << endl;

}


int main(){

    // Functions to test the Linked list class and Student Class
    TestList();
    TestStudent();

    // Opens the Menu interface
    UserMenu();




    return 0;
}
