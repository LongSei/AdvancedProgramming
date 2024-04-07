#ifndef chatbox_hpp
#define chatbox_hpp

#include<bits/stdc++.h>
#include"../entities/characters.hpp"
using namespace std;

class ChatBox {
    public: 
        void init();
        void inviteMember(Characters* new_member);
        void removeMember(Characters* member);
        bool canMessage(Characters* emp);
        void appendMessage(Characters* emp, string message);

    private: 
        map<Characters*, bool> isMember;
        vector<pair<Characters*, string> > messageMemory;
};

#endif