#pragma once
#ifndef IMENU_H
#define IMENU_H

//This is an abstract class for Interface
//AdminMenu and UserMenu will inherit from this

class InterfaceMenu {
public:
    virtual void showMenu() = 0;
    virtual void handleInput() = 0;
    virtual ~InterfaceMenu() {}
};

#endif