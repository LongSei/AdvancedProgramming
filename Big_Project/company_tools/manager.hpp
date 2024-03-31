#ifndef manager_hpp
#define manager_hpp
#include<bits/stdc++.h>
#include"./company_tools/chatbox.hpp"
#include"./entities/characters.hpp"
using namespace std;

class Manager {
    public:
        void addNewEmployment();
        void addNewChatBox();
        void removeEmployment(Characters* emploment);
        void removeChatBox(ChatBox* chatbox);

    private: 
        vector<Characters*> employment;
        vector<ChatBox*> chatbox;
};

#endif