#include <string>
#include <LinkedList.h>

class HashMap
{
private:
    static const int CAPACITY = 100009;
    LinkedList arr[CAPACITY];

    int getHash(std::string key);

public:
    HashMap();
    ~HashMap();
};

HashMap::HashMap()
{
}

HashMap::~HashMap()
{
}

int HashMap::getHash(std::string key)
{
    long long hash = 5381;
    for (auto &&c : key)
    {
        hash = hash * 33 + c;
    }
    return hash & CAPACITY;
}
