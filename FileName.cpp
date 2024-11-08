#include <iostream>
using namespace std;

struct Product {
    int id;
    double price;
    char name[50];
    char manufacturer[50];
    char group[50];
    char arrivalDate[20];
    int shelfLifeDays;
};

void showProduct(const Product& product) {
    cout << "ID: " << product.id << endl;
    cout << "Name: " << product.name << endl;
    cout << "Manufacturer: " << product.manufacturer << endl;
    cout << "Group: " << product.group << endl;
    cout << "Price: " << product.price << endl;
    cout << "Arrival Date: " << product.arrivalDate << endl;
    cout << "Shelf Life: " << product.shelfLifeDays << endl;
}

void writeProductsToFile(const char* pathToFile, Product products[], int N) {
    FILE* file;
    if (fopen_s(&file, pathToFile, "w") == 0) {
        fwrite(products, sizeof(Product), N, file);
        fclose(file);
    }
}

void readProductsFromFile(const char* pathToFile, Product products[], int N) {
    FILE* file;
    if (fopen_s(&file, pathToFile, "r") == 0) {
        fread(products, sizeof(Product), N, file);
        fclose(file);
    }
}

void sortByGroup(Product products[], int N) {

    cout << "Products sorted by category:\n";
    char currentGroup[50] = "";

    for (int i = 0; i < N; ++i) {

        if (strcmp(currentGroup, products[i].group) != 0) {
            strcpy_s(currentGroup, products[i].group);
            cout << "----------------------------------------" << endl;
            cout << "Group: " << currentGroup << endl;
        }
        
        showProduct(products[i]);
    }
}

void sortByPrice(Product products[], int N) {
    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < N - i - 1; ++j) {
            if (products[j].price > products[j + 1].price) {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}

void addProduct(Product products[], int& N, const Product& newProduct) {
    products[N++] = newProduct;
}

void deleteProduct(Product products[], int& N, int id) {
    for (int i = 0; i < N; ++i) {
        if (products[i].id == id) {
            for (int j = i; j < N - 1; ++j) {
                products[j] = products[j + 1];
            }
            N--;
            return;
        }
    }
}

Product* findProductById(Product products[], int N, int id) {
    for (int i = 0; i < N; ++i) {
        if (products[i].id == id) {
            return &products[i];
        }
    }
    return 0;
}

Product* findProductByName(Product products[], int N, const char* name) {
    for (int i = 0; i < N; ++i) {
        if (strcmp(products[i].name, name) == 0) {
            return &products[i];
        }
    }
    return 0;
}
Product* findProductByArrivalDate(Product products[], int N, const char* arrivalDate) {
    for (int i = 0; i < N; ++i) {
        if (products[i].arrivalDate == arrivalDate) {
            return &products[i];
        }
    }
}
Product* findProductByShelfLife(Product products[], int N, int shelfLifeDays) {
    for (int i = 0; i < N; ++i) {
        if (products[i].shelfLifeDays == shelfLifeDays) {
            return &products[i];
        }
    }
}

int main() {
    const char* pathToFile = "products.bin";
    int N = 8;
    Product products[100] = {
        {1, 20.0, "Mineral Water", "Aqua", "Beverages", "2024-10-01", 365},
        {2, 15.0, "Canned Peas", "GreenCo", "Canned Goods", "2024-09-15", 730},
        {3, 7.5, "Chocolate Bar", "SweetFactory", "Sweets", "2024-11-01", 180},
        {4, 50.0, "Olive Oil", "HealthyOil", "Oils", "2024-08-20", 730},
        {5, 5.0, "Bread", "DailyBaker", "Bakery", "2024-11-05", 7},
        {6, 12.0, "Juice", "FreshFruit", "Beverages", "2024-10-10", 180},
        {7, 3.5, "Cookies", "BakerHouse", "Sweets", "2024-10-15", 60},
        {8, 18.0, "Sunflower Oil", "AgroOil", "Oils", "2024-09-10", 540}
    };

    writeProductsToFile(pathToFile, products, N);

    int choice;
    
         cout << "Menu:\n";
         cout << "1 - Show all products grouped by category\n";
         cout << "2 - Sort products by price\n";
         cout << "3 - Find product by ID\n";
         cout << "4 - Find product by name\n";
         cout << "5 - Find product by arrival date\n";
         cout << "6 - Find product by shelf life\n";
         cout << "7 - Add a product\n";
         cout << "8 - Delete a product\n";
         cout << "0 - Exit\n";
         cout << "Enter your choice: ";
         cin >> choice;

        switch (choice) {
        case 1: {
            sortByGroup(products, N);
            break;
        }
        case 2: {
            sortByPrice(products, N);
            cout << "Products sorted by price:\n";
            for (int i = 0; i < N; ++i) {
                showProduct(products[i]);
            }
            break;
        }
        case 3: {
            int searchId;
            cout << "Enter product ID: ";
            cin >> searchId;
            Product* foundProduct = findProductById(products, N, searchId);
            showProduct(*foundProduct);
            break;
        }
        case 4: {
            char searchName[50];
            cout << "Enter product name: ";
            cin.getline(searchName, 50);
            Product* foundProduct = findProductByName(products, N, searchName);
            showProduct(*foundProduct);
            break;
        }
        case 5: { 
            char searchDate[20];
            cout << "Enter arrival date (YYYY-MM-DD): ";
            cin.getline(searchDate, 20);
            Product* foundProduct = findProductByArrivalDate(products, N, searchDate);
            showProduct(*foundProduct);
            break;
        }
        case 6: {
            int searchShelfLife;
            cout << "Enter shelf life (in days): ";
            cin >> searchShelfLife;
            Product* foundProduct = findProductByShelfLife(products, N, searchShelfLife);
showProduct(*foundProduct);
            break;
        }
        case 7: {
            Product newProduct;
            cout << "Enter new product details:\n";
            cout << "ID: ";
            cin >> newProduct.id;
            cout << "Name: ";
            cin.getline(newProduct.name, 50);
            cout << "Manufacturer: ";
            cin.getline(newProduct.manufacturer, 50);
            cout << "Group: ";
            cin.getline(newProduct.group, 50);
            cout << "Price: ";
            cin >> newProduct.price;
            cout << "Arrival Date: ";
            cin.getline(newProduct.arrivalDate, 20);
            cout << "Shelf Life: ";
            cin >> newProduct.shelfLifeDays;
            addProduct(products, N, newProduct);
            cout << "Product added!\n";
            break;
        }
        case 8: {
            int deleteId;
            cout << "Enter product ID to delete: ";
            cin >> deleteId;
            deleteProduct(products, N, deleteId);
            cout << "Product deleted!\n";
            break;
        }
      }
    return 0;
}