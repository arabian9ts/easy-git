//
//  object.hpp
//  eat
//
//  Created by arabian9ts on 2017/03/17.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//


#ifndef object_hpp
#define object_hpp

#include "util.hpp"
#include "compress.hpp"



class Object{
    
    /** オブジェクトが何を表しているかを識別するパラメータ */
private:
    char type_strs[10][10] = {"commit", "tree", "blob", "unknown"};
public:
    enum Type{commit = 0, tree = 1, blob = 2, unknown = 3};
 
    
private:
    /*-------------------------fields-------------------------------*/
    Type type; // data type of this obj
    std::string name = "";
    std::string path = "";
    std::string hash = ""; // sha-1 hash of (path echo(file))
    /*---------------------------END--------------------------------*/
    
    
    /*-------------------------functions----------------------------*/
    /** コンストラクタオーバーライド用初期化関数 */
    void initialize(Type type, std::string name, std::string path, std::string hash);
    
    /** blobオブジェクトのファイルパスを再帰的に連結する */
    std::string cyclic_getPath(std::string buff);
    /*---------------------------END--------------------------------*/
    
    
    
public:
    /*-------------------------fields-------------------------------*/
    /** 木構造の子供と兄弟 */
    Object* child = NULL;
    Object* next = NULL;
    /*---------------------------END--------------------------------*/
    
    
    /*-------------------------functions----------------------------*/
    Object();
    Object(Type type, std::string name, std::string path);
    Object(Type type, std::string name, std::string path, std::string hash);
    ~Object();
    
    /** blob, treeなどのオブジェクトの属性をstringで返す */
    std::string getType();
    
    /** オブジェクトの名前を返す */
    std::string getName();
    
    /** オブジェクトのハッシュ値を返す */
    std::string getHash();
    
    /** オブジェクトのワークスペースからの相対パスで返す */
    std::string getPath();
    
    /** indexファイルに書き出すファイルパスの集合をstringで返す */
    std::vector<std::string> index_path_set();
    
    /** Objectファイルを元のプロジェクトに復元 */
    void restore();
    
    /** 指定したファイルを指定した場所にコピーする */
    void copy_obj(std::string from, std::string to);
    
    /** オブジェクトファイルを書き出す */
    void make_copy_objects();
    
    /** tree, blobオブジェクトの生成 */
    std::string make_tree_blob_obj();
    
    /** ファイルのハッシュ値を計算する */
    void calc_hash();
    
    /** ルートのコミットハッシュの訂正 */
    void rehash_root();
    
    /** ファイルの詳細を出力する */
    void dump();
    
    /** すでに求めてあるハッシュ値をセットする */
    void setHash(std::string hashcode);
    
    /*---------------------------END--------------------------------*/
};

#endif /* object_hpp */
