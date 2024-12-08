#include <iostream>
#include <vector>
#include <string>

using namespace std;

/////////////////// UTILITIES ////////////////////
bool isPrime(int n)
{
    if(n == 2 || n == 3)
        return true;

    if(n == 1 || n % 2 == 0)
        return false;

    for(int i = 3; i * i <= n; i += 2)
        if(n % i == 0)
            return false;

    return true;
}

int nextPrime(int n)
{
    if(n % 2 == 0)
        ++n;

    for(; !isPrime(n); n += 2)
        ;

    return n;
}
/////////////////// UTILITIES ////////////////////->end

class StringHashFamily
{
  public:
    StringHashFamily(int count) : MULTIPLIERS(count)
    {
        generateNewFunctions();
    }

    int getNumberOfFunctions() const
    {
        return MULTIPLIERS.size();
    }

    void generateNewFunctions()
    {
        int r = rand() % 50 + 1;
        for(auto& mult : MULTIPLIERS)
        {
            r = nextPrime(r + 1);
            mult = r;
        }
    }

    size_t hash(const string& x, int which) const
    {
        const int multiplier = MULTIPLIERS[which];
        size_t hashVal = 0;

        for(auto ch : x)
            hashVal = multiplier * hashVal + ch;

        return hashVal;
    }

    void printMultipliers() const
    {
        cout << "Multipliers: ";
        for(int mult : MULTIPLIERS)
        {
            cout << mult << " ";
        }
        cout << endl;
    }

  private:
    vector<int> MULTIPLIERS;
};

template<typename Datatype, typename FunctionFamily>
class HashTable
{
  public:
    HashTable(int Tablesize = 101, int numHashFunctions = 2) : TableSize(nextPrime(Tablesize)), currentSize(0), numHashFunctions(numHashFunctions), hashFunctions(numHashFunctions)
    {
        array.resize(TableSize);
        makeEmpty();
    }

    void makeEmpty()
    {
        currentSize = 0;
        for(auto & entry : array)
            entry.isActive = false;
    }

    bool contains(const Datatype& x) const
    {
        return find_element_pos(x) != -1;
    }

    bool insert(Datatype& x)
    {
        if(contains(x))
            return false;

        return insert_element(x);
    }

  private:
    struct HashEntry
    {
        Datatype element;
        bool isActive;

        HashEntry(const Datatype& e = Datatype(), bool a = false) : element(e), isActive(a) {}
        HashEntry(Datatype&& e, bool a = false) : element(std::move(e)), isActive(a) {}
    };

    vector<HashEntry> array;
    int TableSize;
    int currentSize;
    int numHashFunctions;
    FunctionFamily hashFunctions;

    int find_position(Datatype x, int i) const
    {
        return hashFunctions.hash(x, i) % TableSize + 1;
    }

    int find_element_pos(const Datatype& x) const
    {
        for(int i = 0; i < numHashFunctions; ++i)
        {
            int pos = find_position(x, i);
            if(array[pos].isActive && array[pos].element == x)
            {
                return pos;
            }
        }
        return -1;
    }

    bool insert_element(Datatype& x)
    {
        int KICK = 0;
        int MAX_KICK = 10;
        while(KICK < MAX_KICK)
        {
            for(int i = 0; i < numHashFunctions; ++i)
            {
                int current_pos = find_position(x, i);
                if(!array[current_pos].isActive)
                {
                    array[current_pos] = std::move(HashEntry(std::move(x), true));
                    ++currentSize;
                    return true;
                }
            }
            int kick_off = rand() % numHashFunctions;
            int final_pos = find_position(x, kick_off);
            std::swap(x, array[final_pos].element);
            KICK++;
            cout << "kick!!!" << endl;
        }
        return false;
    }
};
