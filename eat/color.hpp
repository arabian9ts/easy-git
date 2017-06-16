//
//  color.hpp
//  easy-git
//
//  Created by arabian9ts on 2017/06/12.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef color_hpp
#define color_hpp

#include "util.hpp"

#include <string>
#include <streambuf>
#include <sstream>


class Color : public std::streambuf {
    
public:
    
    enum pallet{red, green, yellow, blue, magenta, cyan, white, def};
    const char* color;
    
private:
    
    std::map<pallet, std::string> paint;
    
    
public:
    
    Color(pallet p) {
        paint.insert(std::pair<pallet, std::string>(pallet::red, "\x1b[31m"));
        paint.insert(std::pair<pallet, std::string>(pallet::green, "\x1b[32m"));
        paint.insert(std::pair<pallet, std::string>(pallet::yellow, "\x1b[33m"));
        paint.insert(std::pair<pallet, std::string>(pallet::blue, "\x1b[34m"));
        paint.insert(std::pair<pallet, std::string>(pallet::magenta, "\x1b[35m"));
        paint.insert(std::pair<pallet, std::string>(pallet::cyan, "\x1b[36m"));
        paint.insert(std::pair<pallet, std::string>(pallet::white, "\x1b[37m"));
        paint.insert(std::pair<pallet, std::string>(pallet::def, "\x1b[39m"));
        
        color = paint[p].c_str();
        
    }
    
    virtual int_type overflow(int_type ich) {
        char ch[1];
        ch[0] = (char)ich;
//        ch[1] = '\0';
        
        printf(color);
        printf("%s", ch);
        printf(paint[def].c_str());
        
        return ich;
    }

    
};



class Clout : public std::ostream {

private:
    
    Color* cl;
    
public:
    Clout(Color::pallet p) : std::ostream(cl = new Color(p)) {}
    
    ~Clout() {
        delete cl;
    }
    
};


#endif /* color_hpp */
