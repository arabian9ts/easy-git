//
//  compress.cpp
//  easy-git
//
//  Created by arabian9ts on 2017/06/05.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#include "compress.hpp"


/**
 * 渡した文字列を圧縮して返却
 * @param tar : 圧縮する文字列
 * @return : 圧縮した文字列
 */
std::string cmp::compress(std::string tar){
    std::stringstream compressed;
    std::stringstream original;
    original << tar;
    boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
    out.push(boost::iostreams::zlib_compressor());
    out.push(original);
    boost::iostreams::copy(out, compressed);
    
    return compressed.str();
}


/**
 * 指定したファイル名のファイルを解答して、元の文字列を返却する
 * @param named : 解答するファイル名
 * @return : 解答した文字列
 */
std::string cmp::decompress(std::string named){
    return "";
}
