#include <iostream>

using namespace std;

struct Node
{
    char symbol; //znak dla lisci
    int freq; //czestotliwosc
    //wskaznik do lewego i prawego dziecka
    Node* child0;
    Node* child1;
    Node* child2;
};

int heap_size = 0;
Node** heap;

int CHILD0(int i) { return 3*i + 1; }  // ZMIANA: 3 dzieci zamiast 2
int CHILD1(int i) { return 3*i + 2; }
int CHILD2(int i) { return 3*i + 3; }
int PARENT(int i) { return (i-1)/3; }  // ZMIANA: /3 zamiast /2

//ogarnia wlasnosc minimum kopca w dol od wezla i

void HEAPIFY(Node* t[], int i)
{
    int c0 = CHILD0(i);
    int c1 = CHILD1(i);
    int c2 = CHILD2(i);
    int smallest = i;


    // sprawdzamy wszystkie 3 dzieci
    if(c0 < heap_size && t[c0]->freq < t[smallest]->freq)
    {
        smallest = c0;
    }
    if(c1 < heap_size && t[c1]->freq < t[smallest]->freq)
    {
        smallest = c1;
    }
    if(c2 < heap_size && t[c2]->freq < t[smallest]->freq)
    {
        smallest = c2;
    }

    if(i != smallest)
    {
        swap(t[i], t[smallest]);
        HEAPIFY(t, smallest);
    }
}

//buduje kopiec maksymalny z nieposortowanej tablicy
void BUILD_HEAP(Node* t[], int size)
{
    heap_size = size;
    for(int i = (heap_size-2)/3; i >= 0; i--)
    {
        HEAPIFY(t, i);
    }
}

//usuwa i zwraca wezel z najmniejsza czestotliwoscia
Node* EXTRACT_MIN(Node* t[])
{
    if(heap_size <= 0) return NULL;

    Node* min_node = t[0];      // minimalny element to korzeñ kopca
    t[0] = t[heap_size-1];      // ostatni element na miejsce korzenia
    heap_size--;                // zmniejszamy rozmiar kopca

    if(heap_size > 0)
    {
        HEAPIFY(t, 0);          // przywracamy w³asnoœæ kopca
    }

    return min_node;
}

//wstawianie nowego wezla do kopca
void HEAP_INSERT(Node* t[], Node* node)
{
    heap_size++;
    int i = heap_size-1;
    t[i] = node;

    // przywracamy w³asnoœæ kopca w górê (od liœcia do korzenia)
    while(i > 0 && t[PARENT(i)]->freq > t[i]->freq)
    {
        swap(t[i], t[PARENT(i)]);
        i = PARENT(i);
    }
}

//tworzenie nowego wezla
Node* createNode(char symbol, int freq)
{
    Node* node = new Node;
    node->symbol = symbol;
    node->freq = freq;
    node->child0 = NULL;
    node->child1 = NULL;
    node->child2 = NULL;
    return node;
}

//odzyskiwanie kodow
void odzyskiwanie(Node* node, string code, string codes[])
{
    if(!node) return;

    // jeœli to liœæ (ma symbol), zapisujemy kod
    if(node->symbol != '\0')
    {
        codes[(int)node->symbol] = code;  // zapisujemy kod dla tego symbolu
        return;
    }

    // rekurencyjnie przechodzimy przez drzewo:
    odzyskiwanie(node->child0, code + "0", codes);
    odzyskiwanie(node->child1, code + "1", codes);
    odzyskiwanie(node->child2, code + "2", codes);
}

//huffman
Node* HUFFMAN(Node* nodes[], int n)
{
    if(n == 1) return nodes[0];

    //inicjalizacja kolejki priorytetowej
    heap = new Node*[n];

    for(int i=0; i<n; i++)
    {
        heap[i] = nodes[i];
    }

    //buduje kopiec
    BUILD_HEAP(heap, n);


    while(heap_size > 1)
    {
        // pobieramy 3 najmniejsze elementy
        Node* x = EXTRACT_MIN(heap);
        Node* y = EXTRACT_MIN(heap);

        // jeœli po pobraniu y kopiec jest pusty, tworzymy wêze³ z 2 dzieci
        if(heap_size == 0)
        {
            Node* z = createNode('\0', x->freq + y->freq);
            z->child0 = x;
            z->child1 = y;
            // child2 zostaje NULL
            HEAP_INSERT(heap, z);
        }
        else
        {
            // pobieramy trzeci element
            Node* w = EXTRACT_MIN(heap);
            Node* z = createNode('\0', x->freq + y->freq + w->freq);
            z->child0 = x;
            z->child1 = y;
            z->child2 = w;
            HEAP_INSERT(heap, z);
        }
    }

    Node* root = EXTRACT_MIN(heap);
    delete[] heap;
    return root;
}


int main()
{
    int n;
    cin >> n;

    char symbols[n];
    int freqs[n];

        for(int i=0; i<n; i++)
    {
        cin >> symbols[i] >> freqs[i];
    }

    //wezly liscie
    Node* nodes[n];

    for(int i=0; i<n; i++)
    {
        nodes[i] = createNode(symbols[i], freqs[i]);
    }

    //budowanie drzewa
    Node* root = HUFFMAN(nodes, n);

    //odzyskiwanie kodow
    string codes[256]; //tablica na kody dla wszystkich ascii

    if(root)
    {
        if(root->symbol != '\0')
        {
            codes[(int)root->symbol] = "0";
        }
        else
        {
            odzyskiwanie(root, "", codes);  // Wywo³anie funkcji
        }
    }

    for(int i=0; i<n; i++)
    {
        cout << symbols[i] << " " << codes[(int)symbols[i]] << endl;
    }


    return 0;
}
