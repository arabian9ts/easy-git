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

namespace cmp {
    
    /** 圧縮する文字列を指定したファイル名に圧縮 */
    void compress(std::string tar, std::string named);
    
    /** 指定したファイル名のファイルを解答して、元の文字列を返却する */
    std::string decompress(std::string named);
    
}

#endif /* compress_hpp */
