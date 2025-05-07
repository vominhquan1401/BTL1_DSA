
#include "main.hpp"

template <typename T>
class List
{
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;

    virtual List<T>* subList(int start, int end) = 0;
    virtual void printStartToEnd(int start, int end) const = 0;
    virtual void getArr(T* Arr) const = 0;
};

//
template <typename T>
class ListCopy : public List<T>
{
private:
    class Node
    {
    public:
        T pointer;
        Node* next;

    public:
        Node(T pointer, Node* next = nullptr) : pointer(pointer), next(next) {}
    };

private:
    Node* head;
    Node* tail;
    int size;

public:
    ListCopy()
    {
        head = tail = nullptr;
        size = 0;
    }
    ~ListCopy()
    {
        this->clear();
    }
    void push_back(T value)
    {
        Node* newNode = new Node(value, nullptr);
        if (this->size == 0)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        this->size++;
    }
    void push_front(T value)
    {
        Node* newNode = new Node(value, nullptr);
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }
        this->size++;
    }
    void insert(int index, T value)
    {
        if (index < 0 || index > size)
            return;
        Node* newNode = new Node(value, nullptr);

        if (index == 0)
        {
            newNode->next = head;
            head = newNode;
            if (tail == nullptr)
            {
                tail = newNode;
            }
        }
        else if (index >= this->size)
        {
            tail->next = newNode;
            tail = newNode;
        }
        else
        {
            Node* curr = head;
            for (int i = 0; i < index - 1; i++)
            {
                /* code */
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }
        this->size++;
    }
    void remove(int index)
    {
        if (index < 0 || index >= size)
            return;

        if (index == 0)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
            if (head == nullptr)
            {
                tail = nullptr;
            }
        }
        else
        {
            Node* curr = head;
            for (int i = 0; i < index - 1; i++)
            {
                curr = curr->next;
            }
            Node* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
            if (index == this->size - 1)
            {
                tail = curr;
            }
        }
        this->size--;
    }

    T& get(int index) const
    {
        if (index < 0 || index >= this->size)
            throw std::out_of_range("get(): Out of range");

        Node* curr = head;
        for (int i = 0; i < index; i++)
        {
            curr = curr->next;
        }
        return curr->pointer;
    }

    int length() const
    {
        return size;
    }

    void clear()
    {
        while (head != nullptr)
        {
            /* code */
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        this->size = 0;
    }
    void print() const
    {
        if (size == 0)
            cout << "nullptr" ;
        Node* temp = head;
        for (int i = 0; i < this->size; i++)
        {
            if (i == this->size - 1)
                cout << temp->pointer ;
            else
                cout << temp->pointer << " ";
            temp = temp->next;
        }
    }
    void reverse()
    {
        Node* prev = nullptr;
        Node* current = head;
        Node* next_node = nullptr;

        if (head == nullptr)
        {
            return;
        }
        else if (size == 1)
        {
        }
        else
        {

            while (current)
            {
                next_node = current->next;
                current->next = prev;
                prev = current;
                current = next_node;
            }

            head = prev;
            tail = head;
            while (tail->next)
            {
                tail = tail->next;
            }
        }
    }
    void printStartToEnd(int start, int end) const
    {
        Node* temp = head;
        for (int i = 0; i < start; i++)
            temp = temp->next;
        for (int i = start; i < end && i < this->length(); i++)
        {
            if (i == end - 1 || i == this->length() - 1)
                cout << temp->pointer;
            else
            {
                cout << temp->pointer << " ";
            }
            temp = temp->next;
        }
    }
    List<T>* subList(int start, int end)
    {
        // cout << "subbbbbbbbbbbbbb" << endl;
        if (this->size <= start || end <= 0 || start < 0)
        {
            return nullptr;
        }
        List<T>* result = new ListCopy<T>();

        Node* temp = head;
        end = min(end, this->length());
        // cout << endl
        //        << end << endl;
        for (int i = 0; i < start; i++)
        {
            temp = temp->next;
        }
        for (int i = start; i < end; i++)
        {
            result->push_back(temp->pointer);
            temp = temp->next;
        }
        // result->print();
        return result;
    }
    void getArr(T* Arr) const
    {
        for (int i = 0; i < this->length(); i++)
        {
            Arr[i] = this->get(i);
        }
    }
};

class Dataset
{
private:
    List<List<int>*>* data;
    List<string>* nameCol;
    // You may need to define more
public:
    Dataset()
    {
        this->nameCol = new ListCopy<string>();
        this->data = new ListCopy<List<int>*>();
    }
    ~Dataset()
    {
        delete data;
        delete nameCol;
    }
    Dataset(const Dataset& other)
    {
        if (this == &other)
            return;
        if (other.data == nullptr || other.data->length() == 0)
        {
            this->nameCol = new ListCopy<string>();
            this->data = new ListCopy<List<int>*>();
            return;
        }
        this->nameCol = new ListCopy<string>();
        this->data = new ListCopy<List<int>*>();
        for (int i = 0; i < other.data->length(); i++)
        {
            List<int>* temp = new ListCopy<int>();
            temp = other.data->get(i);
            this->data->push_back(temp);
        }
        this->nameCol = other.nameCol->subList(0, other.nameCol->length());
    }

    Dataset& operator=(const Dataset& other)
    {

        if (this == &other)
        {
            return *this;
        }
        if (other.data == nullptr || other.nameCol == nullptr)
        {
            this->nameCol = new ListCopy<string>();
            this->data = new ListCopy<List<int>*>();
            return *this;
        }
        this->nameCol = new ListCopy<string>();
        this->data = new ListCopy<List<int>*>();
        this->nameCol = other.nameCol->subList(0, other.nameCol->length());
        for (int i = 0; i < other.data->length(); i++)
        {
            List<int>* temp = new ListCopy<int>();
            temp = other.data->get(i);
            this->data->push_back(temp);
        }
        return *this;
    }
    bool loadFromCSV(const char* fileName)
    {
        ifstream file(fileName);
        if (file.is_open())
        {
            string str;
            int nums;

            file >> str;
            for (int i = 0; i < str.length(); i++)
            {
                if (str[i] == ',')
                    str[i] = ' ';
            }
            stringstream ss(str);
            while (ss >> str)
            {
                nameCol->push_back(str);
            }

            //* xử lý các hàng còn lại , thành ' ' dùng thư viện stringstream
            while (file >> str)
            {
                for (int i = 0; i < str.length(); i++)
                {
                    if (str[i] == ',')
                        str[i] = ' ';
                }
                stringstream ss(str);
                List<int>* temp1 = new ListCopy<int>();
                while (ss >> nums)
                {
                    temp1->push_back(nums);
                }
                data->push_back(temp1);
            }
            return true;
        }
        return false;
    }
    void getShape(int& nRows, int& nCols) const
    {
        nRows = this->data->length();
        if (nRows == 0)
        {
            nCols = 0;
            return;
        }
        nCols = this->data->get(0)->length();
    }
    void columns() const
    {
        this->nameCol->printStartToEnd(0, this->nameCol->length());
    }

    void printHead(int nRows = 5, int nCols = 5) const
    {
        if (nRows <= 0 || nCols <= 0 || (this->nameCol == nullptr && this->data == nullptr) || this->nameCol == nullptr)
        {
            return;
        }
        int lenNameCol = 0;
        if (nCols < this->nameCol->length())
        {
            lenNameCol = nCols;
        }
        else
        {
            lenNameCol = this->nameCol->length();
        }
        if (this->data->length() <= 0)
        {
            this->nameCol->printStartToEnd(0, lenNameCol);
            return;
        }
        int lenRow = 0;
        if (nRows < this->data->length())
        {
            lenRow = nRows;
        }
        else
        {
            lenRow = this->data->length();
        }
        this->nameCol->printStartToEnd(0, lenNameCol);
        for (int i = 0; i < lenRow; i++)
        {
            cout << endl;
            this->data->get(i)->printStartToEnd(0, lenNameCol);
        }
    }
    void printTail(int nRows = 5, int nCols = 5) const
    {
        if (nRows <= 0 || nCols <= 0)
            return;
        int lenCol = this->nameCol->length();

        if (nCols >= lenCol)
        {
            lenCol = nCols;
        }
        int lenRow = this->data->length();
        if (nRows >= lenRow)
        {
            lenRow = nRows;
        }
        this->nameCol->printStartToEnd(lenCol - nCols, this->nameCol->length());

        for (int i = lenRow - nRows; i < this->data->length() && nRows != 0; i++)
        {
            cout << endl;
            this->data->get(i)->printStartToEnd(lenCol - nCols, this->nameCol->length());
            nRows--;
        }
    }
    bool drop(int axis = 0, int index = 0, std::string columns = "")
    {
        int nCols = this->nameCol->length();
        int nRows = this->data->length();
        if (nRows == 0)
        {
            return false;
        }
        if (axis == 0) // xóa 1 hàng ở index
        {
            if (index < nRows && index >= 0)
            {
                this->data->remove(index);
                return true;
            }
        }
        else if (axis == 1)
        { // xóa 1 cột trùng có tên trùng với colums
            for (int i = 0; i < nCols; i++)
            {
                if (this->nameCol->get(i) == columns)
                {
                    this->nameCol->remove(i);
                    for (int j = 0; j < nRows; j++)
                    {
                        this->data->get(j)->remove(i);
                    }
                    return true;
                }
            }
        }
        return false;
    }
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const
    {
        Dataset dataset;
        if (this->nameCol == nullptr || this->data == nullptr)
            throw out_of_range("get(): Out of range");
        if (startRow < 0 || startCol < 0 || endCol < -1 || endRow < -1)
            throw out_of_range("get(): Out of range");
        if (endRow > this->data->length() - 1)
        {
            endRow = -1;
        }
        if (endCol > this->nameCol->length())
        {
            endCol = -1;
        }

        if (endRow == -1 && endCol == -1)
        {
            endRow = this->data->length() - 1;
            endCol = this->nameCol->length();
        }
        else if (endRow == -1)
        {
            endRow = this->data->length() - 1;
        }
        else if (endCol == -1)
        {
            endCol = this->nameCol->length();
        }

        if (startRow > endRow || startCol > endCol)
            throw out_of_range("get(): Out of range");
        if (startRow >= this->data->length() || startCol >= this->nameCol->length())
            throw out_of_range("get(): Out of range");
        dataset.nameCol = this->nameCol->subList(startCol, endCol + 1);
        for (int i = startRow; i <= endRow; i++)
        {
            dataset.data->push_back(this->data->get(i)->subList(startCol, endCol + 1));
        }
        return dataset;
    }

    double distanceEuclidean(const List<int>* x, const List<int>* y) const
    {
        double distance=0;
        int sizeX = x->length();
        int sizeY = y->length();
        int minSize = min(sizeX, sizeY);
        int* arrX = new int[sizeX];
        x->getArr(arrX);
        int* arrY = new int[sizeY];
        y->getArr(arrY);

        for (int i = 0; i < minSize; i++)
        {
            double diff = arrX[i] - arrY[i];
            distance += diff * diff;
        }

        for (int i = minSize; i < sizeX; i++)
        {
            distance += arrX[i] * arrX[i];
        }
        for (int i = minSize; i < sizeY; i++)
        {
            distance += arrY[i] * arrY[i];
        }

        delete[] arrX;
        delete[] arrY;

        return sqrt(distance);
    }
    int TanSoXuatHien(const int label[], int len, int k) const
    {
        int count[1000] = { 0 };
        // insert sort

        // Kiểm tra tần suất xuất hiện của từng phần tử trong mảng
        if (len > k)
        {
            len = k;
        }
        for (int i = 0; i < len; i++)
        {
            count[label[i]]++;
        }

        int max = count[0];
        int Maxlabel = 0;
        for (int i = 1; i < 1000; i++)
        {
            if (max < count[i])
            {
                max = count[i];
                Maxlabel = i;
            }
        }
        return Maxlabel;
    }

    Dataset predict(const Dataset& X_train, const Dataset& Y_train, const int k) const
    {
         if(k>X_train.data->length() || k <= 0)
             throw out_of_range("get(): Out of range");
        Dataset rs;
        if (X_train.data->length() <= 0 || this->data->length() <= 0 || Y_train.data->length() <= 0 || Y_train.nameCol->length() <= 0 || X_train.data == nullptr || Y_train.data == nullptr || this->data == nullptr)
        {
            return rs;
        }
        rs.nameCol->push_back(Y_train.nameCol->get(0));
        int len = min(Y_train.data->length(), X_train.data->length());

        int* label = new int[len];
        double* distance = new double[len];

        for (int i = 0; i < this->data->length(); i++)
        {
            for (int j = 0; j < len; j++)
            {
                distance[j] = distanceEuclidean(this->data->get(i), X_train.data->get(j));
            }

            for (int j = 0; j < len; j++)
            {
                label[j] = Y_train.data->get(j)->get(0);
            }

            bool swapped = false;
            for (int h = 0; h < len - 1; h++)
            {
                swapped = false;
                for (int j = 0; j < len - h - 1; j++)
                {
                    if (distance[j] > distance[j + 1])
                    {
                        swap(distance[j], distance[j + 1]);
                        swap(label[j], label[j + 1]);
                        swapped = true;
                    }
                }
                if (swapped == false)
                    break;
            }

            List<int>* temp = new ListCopy<int>();
            temp->push_back(this->TanSoXuatHien(label, len, k));
            rs.data->push_back(temp);
        }

        delete[] label;
        delete[] distance;
        return rs;
    }
    double score(const Dataset& y_test) const
    {
        if (y_test.data->length() != this->data->length() || y_test.data->length() <= 0 || this->data->length() <= 0 || this->data == nullptr || y_test.data == nullptr)
        {
            return -1;
        }
        double count = 0;
        double size = min(this->data->length(), y_test.data->length());
        for (int i = 0; i < size; i++)
        {
            if (y_test.data->get(i)->get(0) == this->data->get(i)->get(0))
            {
                count++;
            }
        }
        return count / size;
    }
    List<List<int>*>* getData() const
    {
        return data;
    }
};

class kNN
{
private:
    int k;
    Dataset X_train;
    Dataset Y_train;

public:
    kNN(int k = 5) : k(k) {};
    void fit(const Dataset& X_train, const Dataset& y_train)
    {
        this->X_train = X_train;
        this->Y_train = y_train;
    }
    Dataset predict(const Dataset& X_test)
    {
        return X_test.predict(this->X_train, this->Y_train, this->k);
    }
    double score(const Dataset& y_test, const Dataset& y_pred)
    {
        return y_test.score(y_pred);
    }
};

void train_test_split(Dataset& X, Dataset& Y, double test_size,
    Dataset& X_train, Dataset& X_test, Dataset& Y_train, Dataset& Y_test);

