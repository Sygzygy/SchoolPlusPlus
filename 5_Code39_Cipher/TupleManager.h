/*
* TupleManager and HashTable by Jason Joseph
* Created on October 31, 2024
*
* TupleManager: Manages a tuple containing a binary key, string identifier, and ASCII character. This class encapsulates
* the data within, providing access and modification functions for each field. The tuple structure supports equality comparison
* and swapping, making it flexible for usage in data structures that require dynamic field handling.
*
* HashTable: A vector-based map-like structure that stores and manages TupleManager instances. This class allows for insertion,
* lookup, and deletion by both binary key and string identifier, while hiding the underlying vector implementation. Designed for
* efficient access and modular usage, it provides controlled exception handling for safe element retrieval and is optimized with
* capacity reservation when the number of entries is known in advance.
*
* Together, TupleManager and HashTable implement a modular structure for storing and managing tuples in a way that supports 
* map-like behavior.
*/

#pragma once
#include <tuple>
#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <optional>

using namespace std;

/* ============================== TupleManager ============================== */

template<typename BitsetType, typename StringType, typename CharType>
class TupleManager : public tuple<BitsetType, StringType, CharType> {
public:
    // Constructor initializing tuple fields: binary key, string, and ASCII
    TupleManager(BitsetType binaryKey, StringType str, CharType ascii) 
        : tuple<BitsetType, StringType, CharType>{ binaryKey, str, ascii } {}

    // Accessors for each field
    BitsetType getBinaryKey() const {
        return get<0>(*this);
    }
    StringType getString() const {
        return get<1>(*this);
    }
    CharType& getASCIIValue() {
        return get<2>(*this);
    }

    // Const version for read-only access
    const CharType& getASCIIValue() const {
        return get<2>(*this);
    }

    // Mutators for each field, encapsulating direct modification
    void setBinaryKey(BitsetType binaryKey) {
        get<0>(*this) = binaryKey;
    }
    void setString(StringType str) {
        get<1>(*this) = str;
    }
    void setASCIIValue(CharType ascii) {
        get<2>(*this) = ascii;
    }

    // Comparison operator to check if two TupleManager instances are identical
    bool operator==(const TupleManager& other) const {
        return getBinaryKey() == other.getBinaryKey() &&
            getString() == other.getString() &&
            getASCIIValue() == other.getASCIIValue();
    }

    // Swap function for efficiently exchanging two TupleManager instances
    void swap(TupleManager& other) {
        std::swap(get<0>(*this), get<0>(other));
        std::swap(get<1>(*this), get<1>(other));
        std::swap(get<2>(*this), get<2>(other));
    }

    // Default destructor
    ~TupleManager() = default;
};

/* =============================== HashTable ================================ */

template<typename BitsetType, typename StringType, typename CharType>
class HashTable : public vector<TupleManager<BitsetType, StringType, CharType>> {
private:
    using TupleType = TupleManager<BitsetType, StringType, CharType>;

public:
    // Default constructor and destructor
    HashTable() = default;
    ~HashTable() = default;

    // Inserts a TupleType instance directly into the HashTable
    void insert(const TupleType& manager) {
        this->push_back(manager);
    }

    // Access operator for elements by binary key; throws out_of_range if key is not found
    CharType& operator[](const BitsetType& key) {
        for (auto& manager : *this) {
            if (manager.getBinaryKey() == key) {
                return manager.getASCIIValue();
            }
        }
        throw out_of_range{ "Key not found" };
    }

    // Access operator for elements by string identifier; throws out_of_range if not found
    CharType& operator()(const StringType& str) {
        for (auto& manager : *this) {
            if (manager.getString() == str) {
                return manager.getASCIIValue();
            }
        }
        throw out_of_range{ "String not found" };
    }

    // Removes an element by binary key, if it exists in the table
    void eraseByKey(const BitsetType& key) {
        auto iteratorPosition = remove_if(this->begin(), this->end(),
            [&key](const TupleType& manager) {
                return manager.getBinaryKey() == key;
            });
        this->erase(iteratorPosition, this->end());
    }

    // Removes an element by string identifier, if it exists in the table
    void eraseByString(const StringType& str) {
        auto iteratorPosition = remove_if(this->begin(), this->end(),
            [&str](const TupleType& manager) {
                return manager.getString() == str;
            });
        this->erase(iteratorPosition, this->end());
    }

    // Finds and returns an iterator to the element by binary key, if present
    auto findByKey(const BitsetType& key) const {
        return find_if(this->begin(), this->end(),
            [&key](const TupleType& manager) {
                return manager.getBinaryKey() == key;
            });
    }

    // Finds and returns an iterator to the element by string identifier, if present
    auto findByString(const StringType& str) const {
        return find_if(this->begin(), this->end(),
            [&str](const TupleType& manager) {
                return manager.getString() == str;
            });
    }
};
