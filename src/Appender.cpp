/*
 * Appender.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Appender.hh"

namespace log4cpp {
    Log4cppCleanup& Appender::_fuckinDummy(Log4cppCleanup::_cleanup);

    Appender::AppenderMap* Appender::_allAppenders;

    Appender::AppenderMap& Appender::_getAllAppenders() {
        if (!_allAppenders) 
            _allAppenders = new Appender::AppenderMap();

        return *_allAppenders;
    }

    Appender* Appender::getAppender(const std::string& name) {
        AppenderMap& allAppenders(_getAllAppenders());
        AppenderMap::iterator i = allAppenders.find(name);
        return (allAppenders.end() == i) ? NULL : ((*i).second);
    }
    
    void Appender::_addAppender(Appender* appender) {
        //REQUIRE(_allAppenders.find(appender->getName()) == _getAllAppenders().end())
        _getAllAppenders()[appender->getName()] = appender;
    }

    void Appender::_removeAppender(Appender* appender) {
        _getAllAppenders().erase(appender->getName());
    }
    
    bool Appender::reopenAll() {
        bool result = true;
        AppenderMap& allAppenders(_getAllAppenders());
        for(AppenderMap::iterator i = allAppenders.begin(); i != allAppenders.end(); i++) {
            result = result && ((*i).second)->reopen();
        }
        
        return result;
    }
    
    void Appender::closeAll() {
        AppenderMap& allAppenders(_getAllAppenders());
        for(AppenderMap::iterator i = allAppenders.begin(); i != allAppenders.end(); i++) {
            ((*i).second)->close();
        }
    }
    
    void Appender::_deleteAllAppenders() {
        AppenderMap& allAppenders(_getAllAppenders());
        for(AppenderMap::iterator i = allAppenders.begin(); i != allAppenders.end(); i++) {
            delete ((*i).second);
        }
    }
    

    Appender::Appender(const std::string& name) :
        _name(name) {
        _addAppender(this);
    }
    
    Appender::~Appender() {
        _removeAppender(this);
    }
    
    bool Appender::reopen() {
        return true;
    }

    /*
    const std::string& Appender::getName() const {
        return _name;
    }
    */
}
