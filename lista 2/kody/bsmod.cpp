//mod
#include <iostream>


using namespace std;

int porownania=0, przypisania=0;

class Node
{
public:
    int data; // wartosc elementu
    Node* next; //wskanzik na nastepny elelment

    Node(int value)
    {
        data=value; //przypisanie wartosci do elementu
        next=nullptr; //ze nie ma nastpenego
    }

};

class Lista
{
public:
    Node* head; //wskaznik na poczatek listy
    int size; //rozmiar listy

    Lista()
    {
        head=nullptr;
        size=0;
    } //ze na poczatku pusta i rozmiar 0

    //dodawanie na koniec
    void append(int value)
    {
        Node* newNode = new Node(value); //tworzy nowy element

        if(head==nullptr) //ze jesli pusta to nowy jest poczatkiem
        {
            head=newNode;
        } else //inaczej przechodzi do ostatniego elementu
        {
            Node* temp=head;
            while(temp->next) //szuka gdzie next jest nullptr puste
            {
                temp=temp->next; //idzie do kolejnego
            }
            temp -> next = newNode; //i dopisuje nowy na koneic
        }
    }


        //wstawianie
    void insert(Node* node, int value)
    {
        Node* newNode = new Node(value); //tworzy nowy elment

        if(!node) //jesli pusty to na poczatek
        {
            newNode->next=head; //nowy elmenyt wkakuje na stary poczatek
            head=newNode; //nowy elment jest nowym poczatkiem
        } else //wstaiwanie za podanym elmeentem
        {
            newNode -> next = node -> next; //nowy na to co wskazywal stary
            node -> next = newNode; //stary elemnt wkazuje na nowy
        }
    }

    //wyswietlanie
    void display()
    {
        Node* temp =head;
        while(temp)
        {
            cout << temp->data << " ";
            temp=temp->next;
        }
        cout << endl;
    }

    //desturktor
    ~Lista()
        {
            while(head)
            {
                Node* temp=head;
                head=head->next;
                delete temp;
            }
        }




};


void insertion(Lista& lista)
{
    //jak ma 0 lub 1 to juz posortowana
    if (!lista.head || !lista.head->next)
    {
        return;
    }

    Lista posortowana; //nowa pusta lista na posortowane lemenety

    Node* current = lista.head; //ze zaczyna od pierwszego elmeentu nieposortowanej

    //przechodzi przez wszystkie
    while (current)
    {
        Node* posortowanacurrent=posortowana.head;
        Node* prev = nullptr;

        // szukanie miejsca do wstawienia
        while (posortowanacurrent && posortowanacurrent->data < current->data)
        {
            porownania++;
            prev=posortowanacurrent; //zapamietuje obecny element
            posortowanacurrent=posortowanacurrent->next;
        }

        //wstawianie
        posortowana.insert(prev, current->data);
        przypisania++;

        current=current->next;

    }

    //zamiana list oryginalna na posortowana
    przypisania++;
    lista.head=posortowana.head;
    posortowana.head=nullptr;


}

void bucketsort(int t[], int n)
{
    //maksymalna i minimalna
    int maks=t[0];
    int mins=t[0];
    przypisania+=2;
    for(int i=1; i<n; i++)
    {
        porownania++;
        if(t[i]>maks)
        {
            maks=t[i];
            przypisania++;
        }
        porownania++;
        if(t[i]<mins)
        {
            mins=t[i];
            przypisania++;
        }
    }

    //sprawdza czy wsyzstkie liczby sa takie same
    if(maks==mins) return;

    //kubki jako tablice list
   Lista* b = new Lista[n];

   //rozdziela elementy do kubka
   for(int i=0; i<n; i++)
   {
       double skala=(double)(t[i]-mins)/(maks-mins+1);
       int ktorykubelek = int(n*skala);

       b[ktorykubelek].append(t[i]);
       przypisania++; //dla push back

   }

   //sortowanie kazdego kubeczka
   for(int i=0; i<n; i++)
   {
       insertion(b[i]);
   }

   //laczy kubki
   int i=0;
   for(int j=0; j<n; j++)
   {
       Node* current = b[j].head;
       while(current)
       {
           t[i]=current->data;
           i++;
           przypisania++;
           current = current->next;
       }
   }

    delete[] b;
}

int main()
{

    int n=0;
    cin >> n;

    int* tablica = new int[n];

    for(int i=0; i<n; i++)
    {
        cin >> tablica[i];
    }

    bucketsort(tablica, n );

    for(int i=0; i<n; i++)
    {
        cout << tablica[i] << " ";
    }
    cout << endl;


    cout << porownania << endl;
    cout << przypisania << endl;

    return 0;
}
