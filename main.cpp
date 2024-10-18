
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
    private:
        struct Node 
        {
            //int data;
            string name;
            Node* prev;
            Node* next;
            Node(string nm, Node* p = nullptr, Node* n = nullptr) {
            //data  = val; 
            name = nm;
            prev = p;
            next = n;
        }
    };
    Node* head;
    Node* tail;
   
    public:
        DoublyLinkedList() { head = nullptr; tail = nullptr; }



        void insert_after(string n, int position) {
        if (position < 0) {
        cout << "Position must be >= 0." << endl;
        return;
        }
        Node* newNode = new Node(n);
        if (!head) {
        head = tail = newNode;
        return;
        }
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
        temp = temp->next;
        if (!temp) {
        cout << "Position exceeds list size. Node not inserted.\n";
        delete newNode;
        return;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
        temp->next->prev = newNode;
        else
        tail = newNode;
        temp->next = newNode;
        }

        void delete_val(string n) {
        if (!head) return;
        Node* temp = head;
        while (temp && temp->name != n)
        temp = temp->next;
        if (!temp) return;
        if (temp->prev)
        temp->prev->next = temp->next;
        else
        head = temp->next;
        if (temp->next)
        temp->next->prev = temp->prev;
        else
        tail = temp->prev;
        delete temp;
        }

        void delete_pos(int pos) {
        if (!head) {
        cout << "List is empty." << endl;
        return;
        }
        if (pos == 1) {
        pop_front();
        return;
        }
        Node* temp = head;
        for (int i = 1; i < pos; i++){
        if (!temp) {
        cout << "Position doesn't exist." << endl;
        return;
        }
        else
        temp = temp->next;
        }
        if (!temp) {
        cout << "Position doesn't exist." << endl;
        return;
        }
        if (!temp->next) {
        pop_back();
        return;
        }
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
        }

        void push_back( string n) {
        Node* newNode = new Node(n);
        if (!tail)
        head = tail = newNode;
        else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        }
        }

        void push_front(string n) {
        Node* newNode = new Node(n);
        if (!head)
        head = tail = newNode;
        else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        }
        }

        void pop_front() {
        if (!head) {
        cout << "List is empty." << endl;
        return;
        }
        Node * temp = head;
        if (head->next) {
        head = head->next;
        head->prev = nullptr;
        }
        else
        head = tail = nullptr;
        delete temp;
        }

        void pop_back() {
        if (!tail) {
        cout << "List is empty." << endl;
        return;
        }
        Node * temp = tail;
        if (tail->prev) {
        tail = tail->prev;
        tail->next = nullptr;
        }
        else
        head = tail = nullptr;
        delete temp;
        }

        ~DoublyLinkedList() {
        while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
        }
        }

        void print() {
        Node* current = head;
        if (!current) {
        cout << "List is empty." << endl;
        return;
        }
        while (current) {
        cout << current->name << " ";
       current = current->next;
        }
        cout << endl;
        }

        void print_reverse() {
        Node* current = tail;
        if (!current) {
        cout << "List is empty." << endl;
        return;
        }
        while (current) {
        cout << current->name << " ";
        current = current->prev;
        }
        cout << endl;
    }
};
int main() {
    
     vector<string> names;

     ifstream input;
     string n;
     input.open("name.txt");
     
       
            while(input>>n)
            {
                names.push_back(n); 
            }
           /* for(int i = 0; i < names.size(); i++)
            {
                cout<<names[i]<<" ";
            }*/
        
    input.close();

    vector<string> n2;
    DoublyLinkedList list;
    srand(time(0));
     int random = rand() % names.size(); 

    for (int i = 0; i < 5; i++)
    {
        list.push_back(names[random]);
        n2.push_back(names[random]);
        random = rand() % names.size(); 
    }
    cout<<"Store opens: "<<endl;
    list.print();
    cout<<"resulting line: "<<endl;
    list.print(); 

    srand(time(0));
    int prob = rand() % 100 + 1; 

    for (int j = 0; j < 20; j++)
    {
        cout<<"Time step #"<<j + 1<<endl; 
       
        if(prob <= 40)
        {
           cout<<n2[0]<<" left the line."<<endl;
           list.pop_front();
           list.print();
        }
        if(prob <= 60)
        {
            random = rand() % names.size();
            list.push_back(names[random]);
            n2.push_back(names[random]);
            cout<<n2.back()<<" joined the line"<<endl; 
           

        } 
        if(prob <= 20)
        {
            cout<<n2.back()<<" left the line."; 
            list.pop_back();
            list.print();
        }

         if(prob <= 10)
        {
            int ran = rand() % names.size();
            cout<<n2[ran]<<" left the line."; 
            list.delete_pos(ran);
            list.print();
        }

         if(prob <= 10)
        {
            cout<<" A vip joined the line."; 
            list.pop_back();
            list.print();
        }


    }
   

    return 0;
    }