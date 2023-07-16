#include "../include/InfoManager.h"
User::User(const string& userName, int uid, const string& sexual, uint year, uint month, uint day, const string& mailbox)
{
    this->userName = userName;
    UID = uid;
    this->sexual = sexual;
    this->birthday.dividedBirthday.year = year;
    this->birthday.dividedBirthday.month = month;
    this->birthday.dividedBirthday.day = day;
    this->mailbox = mailbox;
    coins = 100;
}

User::User(const string &userName, int uid, const string &sexual, uint birthday, const string &mailbox) {
    this->userName = userName;
    UID = uid;
    this->sexual = sexual;
    this->birthday.birthdayNumber = birthday;
    this->mailbox = mailbox;
    coins = 100;
}

User::User(const string &userName, int uid, const string &sexual, uint birthday, const string &mailbox, uint coins) {
    this->userName = userName;
    UID = uid;
    this->sexual = sexual;
    this->birthday.birthdayNumber = birthday;
    this->mailbox = mailbox;
    this->coins = coins;
}

uint User::getUid() const {
    return UID;
}

const string& User::getUserName() const {
    return userName;
}

const string& User::getSexual() const {
    return sexual;
}

const string& User::getMailbox() const {
    return mailbox;
}

uint User::getCoins() const {
    return coins;
}

uint User::getBirthdayNumber() const {
    return birthday.birthdayNumber;
}

const User::BirthdayStruct& User::getBirthdayStruct() const {
    return birthday;
}

int User::getAge() const {
    // 获取年份的方法来自Stackoverflow
    std::time_t t = std::time(nullptr);
    std::tm *const pTInfo = std::localtime(&t);
    int curYear = 1900 + pTInfo->tm_year;
    int curMonth = 1 + pTInfo->tm_mon;
    int curDay = pTInfo->tm_mday;
    int gapYear = curYear - (int)birthday.dividedBirthday.year;
    if (curMonth - (int)birthday.dividedBirthday.month > 0
        || curMonth - (int)birthday.dividedBirthday.month == 0 && curDay - (int)birthday.dividedBirthday.day <= 0)
    {
        gapYear--;
    }
    return gapYear;
}

void User::setCoins(uint coins) {
    this->coins = coins;
}

//--------------------------------------------------------------------------------

bool User::equalsTo(User &user) {
    if(this->userName == user.getUserName() && this->UID == user.getUid()
        && this->mailbox == user.getMailbox() && this->coins == user.getCoins()
        && this->sexual == user.getSexual() && this->birthday.birthdayNumber == user.getBirthdayNumber())
    {
        return true;
    }
    else
    {
        return false;
    }
}





//---------------------------------------------------------------------

InfoManager::InfoManager() {
    /** 数据文件的格式是：
     * 每一行为一条信息
     * UID、用户名、性别、出生日期（大数字形式）、邮箱、硬币
     */
    std::ifstream savefileReader("savefile", std::ios::in);
    if(savefileReader.good())
    {
        while(!savefileReader.eof())
        {
            uint uid;
            string userName;
            string sexual;
            uint birthday;
            string mailbox;
            uint coin;
            savefileReader >> uid >> userName >> sexual >> birthday >> mailbox >> coin;
            if(userName.size() > 0 && uid > 0)
            {
                User temp(userName, uid, sexual, birthday, mailbox, coin);
                userList.push_back(temp);
            }
        }
    }
    savefileReader.close();
    savefile = std::make_unique<std::ofstream>("savefile", std::ios::out);
}

unsigned long long InfoManager::getUserNumber() {
    return userList.size() + 1;
}

void InfoManager::addUser(const User& user)
{
    try
    {
        for(int i = 0; i < userList.size(); i++)
        {
            if(user.getUserName() == userList.at(i).getUserName())
            {
                throw UserExistException();
            }
        }
        userList.push_back(user);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    save();
}

void InfoManager::deleteUser(User& user)
{
    for(auto i = userList.begin(); i < userList.end(); i++)
    {
        if(user.equalsTo(*i))
        {
            userList.erase(i);
            save();
            return;
        }
    }
    std::cout << "User not found. Nothing was changed." << std::endl;
}

void InfoManager::deleteUser(uint uid)
{
    for(auto i = userList.begin(); i < userList.end(); i++)
    {
        if(i->getUid() == uid)
        {
            userList.erase(i);
            save();
            return;
        }
    }
    std::cout << "User not found. Nothing was changed." << std::endl;
}

void InfoManager::deleteUser(string& username)
{
    for(auto i = userList.begin(); i < userList.end(); i++)
    {
        if(i->getUserName() == username)
        {
            userList.erase(i);
            save();
            return;
        }
    }
    std::cout << "User not found. Nothing was changed." << std::endl;
}

void InfoManager::changeCoinNumber(std::string &username, uint coin) {
    for(auto i = userList.begin(); i < userList.end(); i++)
    {
        if(username == i->getUserName())
        {
            i->setCoins(coin);
            save();
            break;
        }
    }
}

// ------排序算法的实现--------------------------------------------------

void InfoManager::sortByUID()
{
    for(int i = 0; i < userList.size(); i++)
    {
        for(int j = 0; j < userList.size() - i - 1; j++)
        {
            if(userList.at(j).getUid() > userList.at(j+1).getUid())
            {
                std::swap(userList.at(j), userList.at(j+1));
            }
        }
    }
}

void InfoManager::sortByName()
{
    for(int i = 0; i < userList.size(); i++)
    {
        for(int j = 0; j < userList.size() - i - 1; j++)
        {
            if(userList.at(j).getUserName().compare(userList.at(j+1).getUserName()) == 1)
            {
                std::swap(userList.at(j), userList.at(j+1));
            }
        }
    }
}

void InfoManager::sortByCoinsUp()
{
    for(int i = 0; i < userList.size(); i++)
    {
        for(int j = 0; j < userList.size() - i - 1; j++)
        {
            if(userList.at(j).getCoins() > userList.at(j+1).getCoins())
            {
                std::swap(userList.at(j), userList.at(j+1));
            }
        }
    }
}

void InfoManager::sortByCoinsDown()
{
    for(int i = 0; i < userList.size(); i++)
    {
        for(int j = 0; j < userList.size() - i - 1; j++)
        {
            if(userList.at(j).getCoins() < userList.at(j+1).getCoins())
            {
                std::swap(userList.at(j), userList.at(j+1));
            }
        }
    }
}

void InfoManager::sortByAge()
{
    for(int i = 0; i < userList.size(); i++)
    {
        for(int j = 0; j < userList.size() - i - 1; j++)
        {
            if(userList.at(j).getBirthdayNumber() < userList.at(j+1).getBirthdayNumber())
            {
                std::swap(userList.at(j), userList.at(j+1));
            }
        }
    }
}

//------------------------------------------------------------------------

void InfoManager::show() {
    /** 输出格式：
     * $用户名: test2
     * 性别: 男
     * 出生日期: 1998-02-01
     * 邮箱:10001@test.com
     * UID: 2
     * 硬币: 100
     * 年龄: 25
     */
    for(auto i = userList.begin(); i < userList.end(); i++)
    {
        std::cout << "$用户名: " << i->getUserName() << std::endl;
        std::cout << "性别: " << i->getSexual() << std::endl;
        std::cout << "出生日期: " << i->getBirthdayStruct().dividedBirthday.year << "-"
                                << i->getBirthdayStruct().dividedBirthday.month << "-"
                                << i->getBirthdayStruct().dividedBirthday.day << std::endl;
        std::cout << "邮箱: " << i->getMailbox() << std::endl;
        std::cout << "UID: " << i->getUid() << std::endl;
        std::cout << "硬币: " << i->getCoins() << std::endl;
        std::cout << "年龄: " << i->getAge() << std::endl;
    }
}

void InfoManager::save()
{
    savefile->close();
    savefile = std::make_unique<std::ofstream>("savefile", std::ios::out);
    for(auto i = userList.begin(); i < userList.end(); i++)
    {
        savefile->operator<<(i->getUid()) << " " << i->getUserName() << " " << i->getSexual()
                 << " " << i->getBirthdayNumber() << " " << i->getMailbox() << " "
                 << i->getCoins() << "\n";
    }
    savefile->flush();  // 同步
}