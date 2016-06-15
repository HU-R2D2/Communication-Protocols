#include "gtest/gtest.h"
#include "../source/include/RESTCallBack.hpp"
#include "../source/include/RESTEngine.hpp"
#include "../source/include/RestApplicationProtocol.hpp"
#include "../source/include/UART.hpp"
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
    printf("c1: p1=[%s], p2=[%s], p3=[%s]\r\n",p->getParam("id").c_str(),p->getParam("sku").c_str(),p->getParam("qty").c_str());


    ASSERT_EQ("1000",p->getParam("id"));
    ASSERT_EQ("1234",p->getParam("sku"));
    ASSERT_EQ("4",p->getParam("qty"));
    std::cout << "Adding new product to cart" << "\n";
  }

  void removeFromCart(RESTContext* context){
    RESTParameters *p = context->params;

    printf("c1: p1=[%s], p2=[%s]\r\n",p->getParam("id").c_str(),p->getParam("sku").c_str());

    ASSERT_EQ("1000",p->getParam("id"));
    ASSERT_EQ("1234",p->getParam("sku"));
    std::cout << "Removing product from cart" << "\n";
  }
};

TEST(RestApplicationProtocol, AddingProductShoppingCart){
  ShoppingCart * p = new ShoppingCart();
  UART sendPort{ttyUSB0, 9600, "8N1"};
//  TransportProtocol tp = TransportProtocol();
  RestApplicationProtocol * rap = new RestApplicationProtocol(sendPort);

  RESTCallBack * pc1 = new RESTCallBack(p, &ShoppingCart::addToCart, "This lets you add an item to a shopping cart");
  pc1->addParam("id","Shopping cart ID");
  pc1->addParam("sku","Item SKU");
  pc1->addParam("qty","Quantity of that item to add");
  rap->addCallbackFunction("/shoppingcart/item","POST",pc1);
  rap->invokeApiCall("/shoppingcart/item?id=1000&sku=1234&qty=4","POST","blablablabla");


  delete pc1;
  delete p;
//  delete rap;
}

TEST(RestApplicationProtocol, RemovingProductShoppingCart){
  ShoppingCart * p = new ShoppingCart();
//  TransportProtocol tp = TransportProtocol();
  UART sendPort{ttyUSB0, 9600, "8N1"};
  RestApplicationProtocol * rap = new RestApplicationProtocol(sendPort);

  RESTCallBack * pc2 = new RESTCallBack(p, &ShoppingCart::removeFromCart,"This lets you remove an item from a shopping cart");
  pc2->addParam("id","Shopping cart ID");
  pc2->addParam("sku","Item SKU");
  rap->addCallbackFunction("/shoppingcart/item","DELETE",pc2);

  rap->invokeApiCall("/shoppingcart/item?id=1000&sku=1234","DELETE","blablablabla");


  delete pc2;
  delete p;
//  delete rap;
}
