//
//  generator.hpp
//  eat
//
//  Created by arabian9ts on 2017/04/19.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef generator_hpp
#define generator_hpp

#include "object.hpp"


/**
 * ノードジェネレータ
 * make_tree 内で利用
 */
Object* graft(Object *parent, Object *targ);

/**
 * blob と tree の木構造を再帰的に作成する
 */
void read_native_tree(Object *subtree, std::string subroot);

/**
 * indexからコミットツリーを作成
 * rehash : add, reflectでは最新のファイル状態を取得するため再ハッシュ
 * commitでは再ハッシュは行わない
 */
int index2tree(Object* root, int rehash);


#endif /* generator_hpp */
