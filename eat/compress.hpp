//
//  compress.hpp
//  easy-git
//
//  Created by arabian9ts on 2017/06/05.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef compress_hpp
#define compress_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/copy.hpp>

namespace cmp {
    
    /** 渡した文字列を圧縮して返却 */
    std::string compress(std::string tar);
    
    /** 渡した文字列を解凍して返却する */
    std::string decompress(std::string named);
    
}

#endif /* compress_hpp */
