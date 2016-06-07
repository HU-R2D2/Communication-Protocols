#include "../include/RESTCallBack.h"
#include "../include/RESTEngine.h"
#include "../include/RestApplicationProtocol.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iostream>

class ShoppingCart {

public:

  ShoppingCart(){
    std::cout << "new shopping cart initiliazed" << "\n";
  }

  void addToCart(RESTContext* context){
    RESTParameters *p = context->params;
    printf("c1: p1=[%s], p2=[%s], p3=[%s]\r\n",p->getParam("id").c_str(),p->getParam("sku").c_str(),
                p->getParam("qty").c_str());
    std::cout << "Adding new product to cart" << "\n";
  }

  void removeFromCart(RESTContext* context){
    RESTParameters *p = context->params;
    std::cout << "Adding removing product from cart" << "\n";
  }
};

int main(){
  std::cout << "This is an example for REST api.\n";

  ShoppingCart * p = new ShoppingCart();
  RestApplicationProtocol rap = RestApplicationProtocol();

  RESTCallBack * pc1 = new RESTCallBack(p, &ShoppingCart::addToCart, "This lets you add an item to a shopping cart");
  pc1->addParam("id","Shopping cart ID");
  pc1->addParam("sku","Item SKU");
  pc1->addParam("qty","Quantity of that item to add");

  RESTCallBack * pc2 = new RESTCallBack(p, &ShoppingCart::removeFromCart,"This lets you remove an item from a shopping cart");
  pc2->addParam("id","Shopping cart ID");
  pc2->addParam("sku","Item SKU");

  //intern
  rap.addCallbackFunction("/shoppingcart/item","POST",pc1);
  rap.addCallbackFunction("/shoppingcart/item","DELETE",pc2);

  rap.invokeApiCall("/shoppingcart/item?id=1&sku=242&qty=4","POST","blablablabla");

  rap.invokeApiCall("/shoppingcart/item?id=1&sku=242&qty=4","DELETE","blablablabla");


  delete p;
  delete pc1;
  delete pc2;

  getchar();


}
