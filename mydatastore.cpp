#include "product.h"
#include "user.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;
  
  MyDataStore::~MyDataStore()
  { 
    for(size_t i = 0; i < products_.size(); i++) {
      delete products_[i];
    }
    for(size_t i = 0; i < users_.size(); i++) {
      delete users_[i];
    }
  }

    /**
     * Adds a product to the data store
     */
    void MyDataStore::addProduct(Product* p)
    { 
      products_.push_back(p);

      std::set<std::string> tempSet = p->keywords();
      for(std::set<string>::iterator it = tempSet.begin(); it != tempSet.end(); ++it) {
        if(keyWords.find(*it) != keyWords.end()) {
          keyWords[*it].insert(p);
        }
        else {
          std::set<Product*> tempProd;
          tempProd.insert(p);
          keyWords.insert(std::make_pair(*it, tempProd));
        }
      }
    }

    /**
     * Adds a user to the data store
     */
    void MyDataStore::addUser(User* u)
    {
      users_.push_back(u); //implement cart
      std::vector<Product*> cart;
      cart_.insert(std::make_pair(u->getName(), cart));
      userMap.insert(std::make_pair(u->getName(), u));

    }

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) 
    {
      std::vector<Product*> items;
      std::set<Product*> tempKeys;
      std::set<Product*> final_;

      for(size_t i = 0; i < terms.size(); i++) {
        if(keyWords.find(terms[i]) != keyWords.end()) {
          tempKeys = keyWords[terms[i]];
          if(type == 0) {
            if(i == 0) {
              final_ = tempKeys;
            }
            else {
              final_ = setIntersection(final_, tempKeys);
            }
          }
          else if(type == 1) {
            final_ = setUnion(final_, tempKeys);
          }
        }
      }
        
      for(std::set<Product*>::iterator it = final_.begin(); it != final_.end(); it++) {
        items.push_back(*it);
      }
      return items;
    }
    
    void MyDataStore::addCart(std::string username, std::vector<Product*> hits, size_t hit)
    {
      if(userMap.find(username) == userMap.end()) {
        cout << "Invalid request" << endl;
        return;
      }
      else {
        if(hit <= hits.size() && hit > 0) {
          Product* temp = hits[hit - 1];
          cart_[username].push_back(temp);
        }
      }
    }

    void MyDataStore::buyCart(std::string username)
    {
      if(userMap.find(username) == userMap.end()) {
        cout << "Invalid username" << endl;
        return;
      }
      else {
        std::vector<Product*> newCart;
        std::vector<Product*> tempCart = cart_[username];
        User* tempU = userMap[username]; 
        for(size_t i = 0; i < tempCart.size(); i++) {
          if(tempU->getBalance() >= tempCart[i]->getPrice() && tempCart[i]->getQty() > 0) {
              tempU->deductAmount(tempCart[i]->getPrice());
              tempCart[i]->subtractQty(1);
          }
          else {
              newCart.push_back(tempCart[i]);
          }
        }
        cart_[username] = newCart;
      }
    }

    void MyDataStore::viewCart(std::string username)
    {
      if(userMap.find(username) == userMap.end()) {
        cout << "Invalid username" << endl;
        return;
      }
      else {
        std::vector<Product*> tempV = cart_[username];
        for(size_t i = 0; i < tempV.size(); i++) {
          cout << "Item " << i + 1 << endl;
          cout << tempV[i]->displayString() << endl;
        }
      }
    }

    /**
     * Reproduce the database file from the current Products and User values
     */
    void MyDataStore::dump(std::ostream& ofile) //quit ASK 
    { 
      ofile << "<products>" << endl;
      for(size_t i = 0; i < products_.size(); i++) {
        products_[i]->dump(ofile);
      }
      ofile << "</products>" << endl;
      ofile << "<users>" << endl;
      for(size_t i = 0; i < users_.size(); i++) {
        users_[i]->dump(ofile);
      }
      ofile << "</users>" << endl;
    }