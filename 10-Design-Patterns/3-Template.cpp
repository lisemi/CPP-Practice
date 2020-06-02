#include <iostream>
// 网购
class OnlineShopping {
public:
	virtual void selectProduct() = 0;
	virtual void addToCart() = 0;
	virtual void order() = 0;
	void shopping() {
		selectProduct();
		addToCart();
		order();
	}
};
// 淘宝
class TaoBao : public OnlineShopping {
public:
	virtual void selectProduct() {
		std::cout << "在淘宝选商品" << std::endl;
	}
	virtual void addToCart() {
		std::cout << "将商品加入淘宝购物车" << std::endl;
	}
	virtual void order() {
		std::cout << "在淘宝下单" << std::endl;
	}
};
// 京东
class JingDong : public OnlineShopping {
public:
	virtual void selectProduct() {
		std::cout << "在京东选商品" << std::endl;
	}
	virtual void addToCart() {
		std::cout << "将商品加入京东购物车" << std::endl;
	}
	virtual void order() {
		std::cout << "在京东下单" << std::endl;
	}
};
int main() {
	OnlineShopping* shop = new TaoBao();
	shop->shopping();

	shop = new JingDong();
	shop->shopping();
	std::cin.get();
	return 0;
}
