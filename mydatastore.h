#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"

class MyDataStore : public DataStore {
public:
    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);
    
    void addCart(std::string username, std::vector<Product*> hits, size_t hit);

    void buyCart(std::string username);

    void viewCart(std::string username);

private:
    std::vector<Product*> products_;
    std::vector<User*> users_;
    std::map<std::string, std::vector<Product*>> cart_;
    std::map<std::string, std::set<Product*>> keyWords;
    std::map<std::string, User*> userMap;
};

#endif