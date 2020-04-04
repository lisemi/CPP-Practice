#include <iostream>
using namespace std;

class Product{
public:
	virtual void Show() = 0;
};

class ProductA : public Product{
public:
	void Show(){
		cout << "I'm ProductA" << endl;
	}
};

class ProductB : public Product{
public:
	void Show(){
		cout << "I'm ProductB" << endl;
	}
};

class Factory{
public:
	virtual Product *CreateProduct() = 0;
};

class FactoryA : public Factory{
public:
	Product *CreateProduct(){
		return new ProductA();
	}
};

class FactoryB : public Factory{
public:
	Product *CreateProduct(){
		return new ProductB();
	}
};

int main(int argc, char *argv[]){
	Factory *factoryA = new FactoryA();
	Product *productA = factoryA->CreateProduct();
	productA->Show();

	Factory *factoryB = new FactoryB();
	Product *productB = factoryB->CreateProduct();
	productB->Show();

	if (factoryA != NULL){
		delete factoryA;
		factoryA = NULL;
	}

	if (productA != NULL){
		delete productA;
		productA = NULL;
	}

	if (factoryB != NULL){
		delete factoryB;
		factoryB = NULL;
	}

	if (productB != NULL){
		delete productB;
		productB = NULL;
	}
	return 0;
}