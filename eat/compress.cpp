//
//  compress.cpp
//  easy-git
//
//  Created by arabian9ts on 2017/06/05.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#include "compress.hpp"


/**
 * 渡した文字列をzlib圧縮して返却
 * @param decomped : 圧縮する文字列
 * @return : 圧縮した文字列
 */
std::string cmp::compress(std::string decomped){
    std::stringstream compressed;
    std::stringstream original;
    original << decomped;
    boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
    out.push(boost::iostreams::zlib_compressor());
    out.push(original);
    boost::iostreams::copy(out, compressed);
    
    return compressed.str();
}


/**
 * zlib圧縮された文字列を解凍し、元の文字列を返却する
 * @param comped : 解凍する文字列
 * @return : 解答した文字列
 */
std::string cmp::decompress(std::string comped){
    std::stringstream compressed;
    std::stringstream decompressed;
    compressed << comped;
    boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
    out.push(boost::iostreams::zlib_decompressor());
    out.push(compressed);
    boost::iostreams::copy(out, decompressed);
    
    return decompressed.str();
}
