// Async C++方向暑期招新第一次测试程序
#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include "../include/InfoManager.h"

using std::string;

int main()
{
    std::shared_ptr<InfoManager> infoManager = std::make_shared<InfoManager>();
    while(true)
    {
        int n;
        std::cin >> n;
        switch(n)
        {
            case 1: // 功能1：添加用户账户
            {
                string userName;
                string sexual;
                uint day;
                uint month;
                uint year;
                string mailbox;
                std::cin >> userName;
                std::cin >> sexual;
                scanf("%u-%u-%u", &year, &month, &day);
                std::cin >> mailbox;
                User newUser(userName, infoManager->getUserNumber(), sexual, year, month, day, mailbox);
                infoManager->addUser(newUser);
                std::cout << "Add user complete." << std::endl;
                infoManager->show();
                break;
            }
            case 2: // 功能2：输出所有用户信息
            {
                infoManager->show();
                break;
            }
            case 3: // 功能3：删除用户信息
            {
                string nameToBeDeleted;
                std::cin >> nameToBeDeleted;
                infoManager->deleteUser(nameToBeDeleted);
                infoManager->show();
                break;
            }
            case 4: // 功能4：修改用户硬币数
            {
                string nameToChange;
                uint newCoin;
                std::cin >> nameToChange >> newCoin;
                infoManager->changeCoinNumber(nameToChange, newCoin);
                infoManager->show();
                break;
            }
            case 5: // 功能5：硬币排序
            {
                infoManager->sortByAge();
                infoManager->sortByCoinsDown();
                infoManager->show();
                infoManager->sortByUID();
                break;
            }
            
            case 6:
            {
                return 0;
            }
            default:
                break;
        }
    }

}