#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

class MenuItem {
public:
    MenuItem(const std::string& name, double price, std::string type) : name(name), price(price), type(type){}
    ~MenuItem() {}

    void displayInfo() const {
        std::cout << "Name: " << name << ", Price: " << price << ", Type: " << type << std::endl;
    }
    void saveToFile(std::ofstream& outFile) const {
        outFile << name << " " << price << " " << type << " ";
    }

    double getPrice() const {
        return price;
    }

    const std::string& getName() const {
        return name;
    }
    const std::string& getType() const {
        return type;
    }


protected:
    std::string name;
    double price;
    std::string& type;
};

template <typename T1, typename T2>
class Pair {
public:
    Pair(const T1& first, const T2& second) : first(first), second(second) {}

private:
    T1 first;
    T2 second;
};

void sortMenuItemsByPrice(std::vector<MenuItem>& menuitems) {
    std::sort(menuitems.begin(), menuitems.end(), [](const MenuItem& a, const MenuItem& b) {
        return a.getPrice() < b.getPrice();
        });
}
class Appetizer : public MenuItem {
public:
    using MenuItem::MenuItem;  

    void displayInfo() const {
        MenuItem::displayInfo();
        
    }
};

class MainCourse : public MenuItem {
public:
    using MenuItem::MenuItem;

    void displayInfo() const {
        MenuItem::displayInfo();
    }
};
class Dessert : public MenuItem {
public:
    using MenuItem::MenuItem;

    void displayInfo() const {
        MenuItem::displayInfo();
    }
};


void addMenuItem(std::vector<MenuItem>& menuitems, const MenuItem& item) {
    menuitems.push_back(item);
}

class StockInfo {
public:
    StockInfo(int totalQuantity) : totalQuantity(totalQuantity) {}

private:
    int totalQuantity;
};
void saveMenuItemsToFile(const std::vector<MenuItem*>& menuitems, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия файла для записи." << std::endl;
        return;
    }

    for (const auto* menuitem : menuitems) {
        menuitem->saveToFile(outFile);
    }

    outFile.close();
}


int main() {
    setlocale(LC_ALL, "Russian");

    std::vector<MenuItem*> menuitems;

    int choice;
    std::string filename;

    do {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавить позицию в меню" << std::endl;
        std::cout << "2. Найти позицию в меню" << std::endl;
        std::cout << "3. Вывести список позиций в меню" << std::endl;
        std::cout << "4. Сохранить в файл" << std::endl;
        std::cout << "5. Сортировать по цене" << std::endl;
        std::cout << "6. Выход" << std::endl;

        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string name;
            double price;
            std::string type;
            std::cout << "Введите данные позиции в меню:" << std::endl;
            std::cout << "Название: ";
            std::cin >> name;
            std::cout << "Стоимость: ";
            std::cin >> price;
            int a;
            std::cout << "Тип: " << std::endl << "1.Апитайзер" << std::endl << "2.Главное блюдо" << std::endl << "3.Десерт" << std::endl;
            std::cin >> a;
            switch (a)
            {
            case 1: {
                type = "Appetizer";
                Appetizer ap(name, price, type);
            }
            case 2: {
                type = "MainCourse";
                MainCourse mc(name, price, type);
            }
            case 3: {
                type = "Dessert";
                Dessert de(name, price, type);
            }
            default:
                  {
                std::cout << "Неверный выбор." << std::endl;
            }
           } 
            menuitems.push_back(new MenuItem(name, price, type));
        }
        case 2: {
            std::string name;
            std::cout << "Введите позиции для поиска:" << std::endl;
            std::cout << "название: ";
            std::cin >> name;


            auto it = std::find_if(menuitems.begin(), menuitems.end(), [&](const MenuItem* menuitem) {
                return menuitem->getName() == name;
                });

            if (it != menuitems.end()) {
                (*it)->displayInfo();
            }
            else {
                std::cout << "Позиция не найдена." << std::endl;
            }

            break;
        }
        case 3: {
            std::cout << "Список позиций в меню:" << std::endl;
            for (const auto* menuitem : menuitems) {
                menuitem->displayInfo();
            }
            break;
        }
        case 4: {
            std::cout << "Введите имя файла для сохранения данных: ";
            std::cin >> filename;
            saveMenuItemsToFile(menuitems, filename);
            break;
        }
        case 5: {
            std::sort(menuitems.begin(), menuitems.end());
            std::cout << "Список позиций отсортирован по цене." << std::endl;
            break;
        }
        case 6:
            std::cout << "Выход." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор." << std::endl;
        }
    } while (choice != 6);

    for (const auto* menuitems : menuitems) {
        delete menuitems;
    }

    return 0;
}
