#include <iostream>
using namespace std;

const int SIZE = 10;

struct Node {
    int nim;
    float ipk;
    Node* next;
};

void initTable(Node* table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i] = nullptr;
    }
}

int hashFunction(int nim) {
    return (nim % SIZE + SIZE) % SIZE;
}

void insert(Node* table[], int nim, float ipk) {
    int index = hashFunction(nim);
    Node* cur = table[index];
    while (cur != nullptr) {
        if (cur->nim == nim) {
            cur->ipk = ipk;  // update IPK jika NIM sudah ada
            return;
        }
        cur = cur->next;
    }
    Node* baru = new Node;
    baru->nim = nim;
    baru->ipk = ipk;
    baru->next = table[index];
    table[index] = baru;
}

Node* search(Node* table[], int nim) {
    int index = hashFunction(nim);
    Node* cur = table[index];
    while (cur != nullptr) {
        if (cur->nim == nim) {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

void removeKey(Node* table[], int nim) {
    int index = hashFunction(nim);
    Node* cur = table[index];
    Node* prev = nullptr;
    while (cur != nullptr) {
        if (cur->nim == nim) {
            if (prev == nullptr) {
                table[index] = cur->next;
            } else {
                prev->next = cur->next;
            }
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void display(Node* table[]) {
    cout << "\nDaftar Data Mahasiswa (Hash Table):\n";
    for (int i = 0; i < SIZE; i++) {
        cout << i << ": ";
        Node* tmp = table[i];
        while (tmp != nullptr) {
            cout << "(NIM: " << tmp->nim << ", IPK: " << tmp->ipk << ") -> ";
            tmp = tmp->next;
        }
        cout << "NULL\n";
    }
}

int main() {
    Node* table[SIZE];
    initTable(table);

    insert(table, 251001, 3.75);
    insert(table, 251011, 3.40);
    insert(table, 251021, 3.90);
    insert(table, 251002, 3.60);

    display(table);

    Node* hasil = search(table, 251011);
    if (hasil != nullptr) {
        cout << "\nMahasiswa dengan NIM 251011 ditemukan, IPK = " << hasil->ipk << endl;
    } else {
        cout << "\nMahasiswa dengan NIM 251011 tidak ditemukan\n";
    }

    removeKey(table, 251011);
    cout << "\nSetelah menghapus mahasiswa dengan NIM 251011:\n";
    display(table);

    return 0;
}
