#include "RESTCallBack.h"
#include "RESTEngine.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

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

#define CHECK(X) if (!(X)) { \
    std::cerr << "Failed to check " << #X << " at line " << __LINE__ << std::endl; \
    return EXIT_FAILURE; }

int main(){
  std::cout << "This is an example for REST api.\n";

  ShoppingCart * p = new ShoppingCart();
  RESTEngine engine;

  RESTCallBack *pc1 = new RESTCallBack(p, &ShoppingCart::addToCart, "This lets you add an item to a shopping cart");
  pc1->addParam("id","Shopping cart ID");
  pc1->addParam("sku","Item SKU");
  pc1->addParam("qty","Quantity of that item to add");

  RESTCallBack *pc2 = new RESTCallBack(p,&ShoppingCart::removeFromCart,"This lets you remove an item from a shopping cart");
  pc2->addParam("id","Shopping cart ID");
  pc2->addParam("sku","Item SKU");

  engine.addCallBack("/shoppingcart/item","POST",pc1);
  engine.addCallBack("/shoppingcart/item","DELETE",pc2);

   Dumais::JSON::JSON j1;
  engine.invoke(j1,"/shoppingcart/item?id=1&sku=242&qty=4","POST","blablablabla");


  Dumais::JSON::JSON json;
  engine.documentInterface(json);
  CHECK(!json.stringify(true).empty());

  Dumais::JSON::JSON swaggerSchema;
  engine.documentSwaggerInterface(swaggerSchema, "1", "title", "description", "http", "localhost", "/api");
  if (!swaggerSchema.isValid()) {
      std::cerr << "invalid JSON swagger schema" << std::endl;
  } else {
      std::ofstream swaggerSchemaFile("swagger.json");
      swaggerSchemaFile << swaggerSchema.stringify(true);
      swaggerSchemaFile.close();
  }


  delete p;
  delete pc1;
  delete pc2;


}
