/*Consider a scenario for Hospital to cater services to different kinds of patients as Serious
(top priority), b) non-serious (medium priority), c) General Checkup (Least priority).
Implement the priority queue to cater services to the patients.*/

#include <iostream>
#include <string.h>
using namespace std;

struct node
{
    int data, prior;
    char pnm[10], name[10];
    struct node *next;
} *front, *rear;
class Queue
{
public:
    int isempty();
    void pq_insert(int prior, char name[10]);
    void display();
    void p_delete();
};
int Queue::isempty()
{
    if ((rear = front) == NULL)
    {
        return 1;
    }
    return 0;
}
struct node *createnode(int prior, char name[10])
{
    struct node *temp;
    temp = new node;
    strcpy(temp->pnm, name);
    temp->prior = prior;
    temp->next = NULL;
    return temp;
}
void Queue::pq_insert(int prior, char name[10])
{
    int i;
    struct node *temp;
    temp = createnode(prior, name);
    if (isempty())
    {
        front = rear = temp;
    }
    else if (front->prior > temp->prior)
    {
        temp->next = front;
        front = temp;
    }
    else
    {
        rear = front;
        while (rear->next != NULL && temp->prior >= rear->next->prior)
        {
            rear = rear->next;
        }
        temp->next = rear->next;
        rear->next = temp;
    }
}
void Queue::display()
{
    struct node *temp;
    cout << "\n";
    cout << "PRIORITY \t SEVERITY \t\tPATIENT NAME" << endl;
    for (temp = front; temp != NULL; temp = temp->next)
    {
        if (temp->prior == 1)
            cout << temp->prior << "\t \t serious \t\t" << temp->pnm << endl;
        if (temp->prior == 2)
            cout << temp->prior << "\t \t non-serious \t \t" << temp->pnm << endl;
        if (temp->prior == 3)
            cout << temp->prior << "\t \t general checkup  \t" << temp->pnm << endl;
    }
}
void Queue::p_delete()
{
    struct node *temp;
    temp = front;
    front = front->next;
    temp->next = NULL;
    cout << "\n"
         << temp->pnm << " Patient checked successfully \n " << endl;
    delete temp;
    display();
}
int main()
{
    int priority, i, ch, n;
    int ans, patient_no;
    char name[10];
    Queue q;
    do
    {
        cout << "\n *****HOSPITAL HISTORY*****";
        cout << "\n 1.Enter the record you want";
        cout << "\n 2.Display";
        cout << "\n 3.Delete";
        cout << "\n Enter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "\n 1.Serious (top priority)";
            cout << "\n 2.Non-serious (medium priority)";
            cout << "\n 3.General Checkup (least priority)";
            cout << "\n Enter no. of patients: ";
            cin >> n;
            for (i = 0; i < n; i++)
            {
                cout << "\n Enter severity: ";
                cin >> priority;
                cout << "\n Enter patient name: ";
                cin >> name;
                q.pq_insert(priority, name);
            }
            break;
        case 2:
            q.display();
            break;
        case 3:
            q.p_delete();
            break;
        case 4:
            cout << "\n Wrong Choice!!";
            cin >> ch;
            break;
        }
        cout << "\n Do you want to continue (1/0)?";
        cin >> ans;
    } while (ans == 1);
    return 0;
}
