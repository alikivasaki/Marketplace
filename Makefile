all:
	@clear
	@g++ -c oop24.cpp
	@g++ -c classes/admin.cpp
	@g++ -c classes/cart.cpp
	@g++ -c classes/category_manager.cpp
	@g++ -c classes/category.cpp
	@g++ -c classes/customer.cpp
	@g++ -c classes/order_history.cpp
	@g++ -c classes/product_manager.cpp
	@g++ -c classes/product.cpp
	@g++ -c classes/user_manager.cpp
	@g++ -c classes/user.cpp
	@g++ -c classes/product_history.cpp
	@g++ -o oop24 oop24.o admin.o cart.o category_manager.o category.o customer.o order_history.o product_manager.o product.o user_manager.o user.o product_history.o
	@rm oop24.o
	@rm admin.o
	@rm cart.o
	@rm category_manager.o
	@rm category.o
	@rm product_manager.o
	@rm customer.o
	@rm order_history.o
	@rm product.o
	@rm user_manager.o
	@rm user.o
	@rm product_history.o
	@./oop24 files/categories.txt files/products.txt files/users.txt
	