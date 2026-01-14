#include <iostream>

using namespace std;

struct Node
{
    char symbol; //znak dla lisci
    int freq; //czestotliwosc
    //wskaznik do lewego i prawego dziecka
    Node* left;
    Node* right;
};

int heap_size = 0;
Node** heap;

int LEFT(int i) { return 2*i+1; } //indeks lewego dziecka w kopcu
int RIGHT(int i) { return 2*i+2; } //indeks prawego dziecka w kopcu
int PARENT(int i) { return (i-1)/2; } //indeks rodzica

//ogarnia wlasnosc minimum kopca w dol od wezla i

void HEAPIFY(Node* t[], int i)
{
    int l = LEFT(i);
    int r = RIGHT(i);
    int smallest = i; //najmniejszy element

    // czy lewe dziecko ma mniejsza czestotliwosc
    if(l < heap_size && t[l]->freq < t[smallest]->freq)
    {
        smallest = l;
    }

    // czy prawe dziecko ma mniejsz¹ czêstotliwoœæ
    if(r < heap_size && t[r]->freq < t[smallest]->freq)
    {
        smallest = r;
    }

    // jeœli rodzic nie jest najmniejszy, zamieniamy z najmniejszym dzieckiem
    if(i != smallest)
    {
        swap(t[i], t[smallest]);
        HEAPIFY(t, smallest); // rekurencyjnie naprawia dalej w dol
    }
}

//buduje kopiec maksymalny z nieposortowanej tablicy
void BUILD_HEAP(Node* t[], int size) {
    heap_size = size;
    for(int i = heap_size/2-1; i>=0; i--) {
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
    while(i > 0 && t[PARENT(i)]->freq > t[i]->freq) {
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
    node->left = NULL;
    node->right = NULL;
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
    // dla lewego dziecka 0 dla prawego 1
    odzyskiwanie(node->left, code + "0", codes);
    odzyskiwanie(node->right, code + "1", codes);
}

//huffman
Node* HUFFMAN(Node* nodes[], int n)
{
    //inicjalizacja kolejki priorytetowej
    heap = new Node*[n];

    for(int i=0; i<n; i++)
    {
        heap[i] = nodes[i];
    }

    //buduje kopiec
    BUILD_HEAP(heap, n);

    //drzewo huffmana
    for(int i=1; i<=n-1; i++)
    {
        Node* x = EXTRACT_MIN(heap); //najmniejsza czestotliwosc
        Node* y = EXTRACT_MIN(heap); //kolejny z najmniejsza
        Node* z = createNode('\0', x->freq + y->freq); //suma czestotliwosci dzieci
        z->left = x;    // x lewe dziecko
        z->right = y;   // y prawe dziecko

        //wstawianie nowego wezla spowrotem do kopca
        HEAP_INSERT(heap, z);
    }
    //zwracanie korzenia drzewa
    Node* root = EXTRACT_MIN(heap);

    delete[] heap;  // zwolnienie pamiêci tablicy kopca
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
