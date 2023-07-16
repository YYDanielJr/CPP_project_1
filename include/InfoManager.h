#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <ctime>   // 获取当前时间
#include <sstream>
#include <memory>
#include <fstream>

using std::string;
using uint = unsigned int;

class UserExistException : public std::exception
{
public:
    const char* what()
    {
        return "User Exist, so adding operation failed.\n";
    }
};

class User
{
private:
    uint UID;
    string userName;
    string sexual;
    union BirthdayStruct
    {
        struct
        {
            uint day : 5;
            uint month : 4;
            uint year : 11;
        } dividedBirthday;
        uint birthdayNumber;
    } birthday;
    string mailbox;
    uint coins;
public:
    User(const string& userName, int uid, const string& sexual, uint year, uint month, uint day, const string& mailbox);
    User(const string& userName, int uid, const string& sexual, uint birthday, const string& mailbox);
    User(const string& userName, int uid, const string& sexual, uint birthday, const string& mailbox, uint coins);
    uint getUid() const;
    const string &getUserName() const;
    const string &getSexual() const;
    const string &getMailbox() const;
    uint getCoins() const;
    uint getBirthdayNumber() const;
    const BirthdayStruct& getBirthdayStruct() const;
    int getAge() const;
    void setCoins(uint coins);
    bool equalsTo(User& user) ;
};
class InfoManager
{
private:
    std::vector<User> userList;
    std::unique_ptr<std::ofstream> savefile;

public:
    InfoManager();
    unsigned long long getUserNumber();
    void addUser(const User& user);
    void deleteUser(User& user);
    void deleteUser(uint uid);
    void deleteUser(string& username);
    void show();
    void changeCoinNumber(string& username, uint coin);
    // 下方四个排序全部是升序排序。
    void sortByUID();
    void sortByName();
    void sortByCoinsUp();
    void sortByCoinsDown();
    void sortByAge();
    /** 下方的函数作用是进行文件写入。
     * 但是我的做法可以说是效率极低的。我的做法是只要有改动就全盘重新写入。
     * 一定有效率更高的办法，但是写起来确实是相对复杂。
     */
    void save();
};