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
    Appender::AppenderMap Appender::_allAppenders;

    Appender* Appender::getAppender(const string& name) {
        AppenderMap::iterator i = _allAppenders.find(name);
        return (_allAppenders.end() == i) ? NULL : ((*i).second);
    }
    
    void Appender::_addAppender(Appender* appender) {
        //REQUIRE(_allAppenders.find(appender->getName()) == _allAppenders.end())
        _allAppenders[appender->getName()] = appender;
    }

    void Appender::_removeAppender(Appender* appender) {
        _allAppenders.erase(appender->getName());
    }
    
    bool Appender::reopenAll() {
        bool result = true;
        for(AppenderMap::iterator i = _allAppenders.begin(); i != _allAppenders.end(); i++) {
            result = result && ((*i).second)->reopen();
        }
        
        return result;
    }
    
    Appender::Appender(const string& name) :
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
    const string& Appender::getName() const {
        return _name;
    }
    */
}
