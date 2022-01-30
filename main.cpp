#include <iostream>
#include <iomanip>

using namespace std;


template<typename charT, typename traits = std::char_traits<charT> >
class center_helper {
    std::basic_string<charT, traits> str_;
public:
    center_helper(std::basic_string<charT, traits> str) : str_(str) {}

    template<typename a, typename b>
    friend std::basic_ostream<a, b> &operator<<(std::basic_ostream<a, b> &s, const center_helper<a, b> &c);
};

template<typename charT, typename traits = std::char_traits<charT> >
center_helper<charT, traits> centered(std::basic_string<charT, traits> str) {
    return center_helper<charT, traits>(str);
}

// redeclare for std::string directly, so we can support anything that implicitly converts to std::string
center_helper<std::string::value_type, std::string::traits_type> centered(const std::string &str) {
    return center_helper<std::string::value_type, std::string::traits_type>(str);
}

template<typename charT, typename traits>
std::basic_ostream<charT, traits> &
operator<<(std::basic_ostream<charT, traits> &s, const center_helper<charT, traits> &c) {
    std::streamsize w = s.width();
    if (w > c.str_.length()) {
        std::streamsize left = (w + c.str_.length()) / 2;
        s.width(left);
        s << c.str_;
        s.width(w - left);
        s << "";
    } else {
        s << c.str_;
    }
    return s;
}


struct Node {
    int data;
    Node *prev, *next;

    Node() {
        this->data = -1;
        this->next = this->prev = nullptr;
    }

    Node(int data) {
        this->data = data;
        this->next = this->prev = nullptr;
    }

    Node(int data, Node *prev, Node *next) : data(data), prev(prev), next(next) {}


};


class DLL {
public:
    Node *start, *trv;

    DLL() {
        trv = start = nullptr;
    }

    void putTRVatStart() {
        trv = start;
    }

    void putTRVatLast() {
        putTRVatStart();
        while (trv->next != nullptr) {
            trv = trv->next;
        }
    }

    void insertAtBeg(int data) {
        if (isEmpty()) {
            Node *tmp = new Node(data, nullptr, start);
            start = tmp;
        } else {
            Node *tmp = new Node(data, nullptr, start);
            start->prev = tmp;
            start = tmp;
        }
    }

    void insertAtEnd(int data) {
        if (isEmpty()) {
            insertAtBeg(data);
            return;
        }

        putTRVatStart();
        while (trv->next != nullptr) {
            trv = trv->next;
        }
        Node *tmp = new Node(data, trv, nullptr);
        trv->next = tmp;
    }

    bool isEmpty() {
        if (start == nullptr)
            return true;
        return false;
    }

    int getLastPos() {
        int count = 0;
        putTRVatStart();
        if (isEmpty()) {
            return 0;
        } else {

            while (trv != nullptr) {
                trv = trv->next;
                count++;
            }
            return count;
        }
    }

    void printDLL() {
        if (isEmpty()) {
            cout << "Underflow";
        } else {
            putTRVatStart();
            cout << "null <- ";
            while (trv != nullptr) {
                cout << setw(4) << centered(std::to_string(trv->data));
                trv = trv->next;
                if (trv == nullptr) {
                    cout << "-> null";
                } else {
                    cout << "<->";
                }
            }

        }
        cout << endl;
    }

    void printDLLReverse() {
        if (isEmpty()) {
            cout << "Underflow";
        } else {
            putTRVatLast();
            cout << "null <-";
            while (trv != nullptr) {
                cout << setw(4) << centered(std::to_string(trv->data));
                trv = trv->prev;
                if (trv == nullptr) {
                    cout << " -> null";
                } else {
                    cout << "<->";
                }
            }

        }
        cout << endl;
    }

    void insertAtNth(int data, int pos) {
        if (pos == 1) {
            insertAtBeg(data);
        } else if (pos < 1) {
            cout << "Invalid Position" << endl;
            return;
        } else if (pos > getLastPos()) {
            if (pos == getLastPos() + 1) {
                insertAtEnd(data);
            } else {
                cout << "Position is too big" << endl;
            }
        } else {
            putTRVatStart();
            int currentPos = 1;
            while (currentPos != pos - 1) {
                trv = trv->next;
                currentPos++;
            }
            Node *tmp = new Node(data, trv, trv->next);
            trv->next = tmp;
            tmp->next->prev = tmp;
        }
    }

    void deleteAtBeg() {
        if (isEmpty()) {
            cout << "Underflow" << endl;
            return;
        }

        Node *tmp = start;
        start = tmp->next;
        free(tmp);
        return;

    }

    void deleteAtEnd() {
        if (isEmpty()) {
            cout << "Underflow" << endl;
            return;
        }
        putTRVatLast();
        trv->prev->next = nullptr;
        free(trv);
    }

    void deleteAtNth(int pos) {
        if (pos < 1 || pos > getLastPos()) {
            cout << "Invalid Position" << endl;
            return;
        }
        if (pos == 1) {
            deleteAtBeg();
            return;
        }
        if (pos == getLastPos()) {
            deleteAtEnd();
            return;
        }
        putTRVatStart();
        int currentPOS = 1;
        while (currentPOS != pos) {
            trv = trv->next;
            currentPOS++;
        }
        trv->prev->next = trv->next;
        trv->next->prev = trv->prev;
        free(trv);
    }
};


int main() {
    DLL d1;
    d1.insertAtBeg(5);
    d1.insertAtBeg(8);
    d1.insertAtBeg(54);
    d1.insertAtBeg(98);
    d1.printDLL();
    d1.deleteAtNth(3);
    d1.printDLL();
    return 0;
}
