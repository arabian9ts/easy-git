//
//  sha1.hpp
//  eat
//
//  Created by arabian9ts on 2017/04/08.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef sha1_hpp
#define sha1_hpp

#include <sstream>
#include <boost/uuid/sha1.hpp>
#include <boost/cstdint.hpp>
#include <boost/array.hpp>

/* ファイルのハッシュ値を計算し、その結果を返す */
std::string sha1(std::string targ);

#endif /* sha1_hpp */
