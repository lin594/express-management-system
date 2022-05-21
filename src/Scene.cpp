#include "Scene.h"

#include <iostream>
Scene::Scene(
    std::vector<std::pair<std::string, std::function<void(void)> > > menus) {
    this->menus = menus;
}

void Scene::show() {
    int index = 0;
    std::cout << "请选择想要的操作：" << std::endl;
    for (auto& menu : menus) {
        std::cout << ALPHABET[index] << ": " << menu.first << std::endl;
        index++;
    }
    std::cout << "你的选择是: ";
    std::string choice;
    std::cin >> choice;
    auto it = ALPHABET_MAP.find(choice);
    if (it != ALPHABET_MAP.end() && it->second < menus.size()) {
        menus[it->second].second();
    } else {
        std::cout << "输入错误，请重新输入" << std::endl;
    }
}