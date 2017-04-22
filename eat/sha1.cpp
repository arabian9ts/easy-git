//
//  sha1.cpp
//  eat
//
//  Created by arabian9ts on 2017/04/08.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#include "sha1.hpp"
#include "eat.hpp"

typedef boost::array<boost::uint8_t,20> HashArray;

/**
 * ファイル名とファイル内容からハッシュ値を計算し、その結果を返す
 */
std::string sha1(std::string targ){
    
    boost::uuids::detail::sha1 sha1;
    unsigned int inthash[5];
    
    sha1.process_bytes(targ.c_str(),targ.length());
    sha1.get_digest(inthash);
    const boost::uint8_t *digest = reinterpret_cast<const boost::uint8_t *>(inthash);
    
    HashArray hash;
    for(int i=0;i<5;++i){
        hash[i*4]   = digest[i*4+3];
        hash[i*4+1] = digest[i*4+2];
        hash[i*4+2] = digest[i*4+1];
        hash[i*4+3] = digest[i*4];
    }


    std::stringstream hex;
    hex.str("");
    hex.clear(std::stringstream::goodbit);
    
    HashArray::const_iterator itr = hash.begin();
    const HashArray::const_iterator end_itr = hash.end();
    for(;itr!=end_itr;++itr){
        hex << std::hex << ( (*itr  & 0xf0 ) >> 4 )
        << (*itr  & 0x0f );
    }
    
    return hex.str();
}
