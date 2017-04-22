//
//  object.cpp
//  eat
//
//  Created by arabian9ts on 2017/03/17.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#include "object.hpp"



//using namespace boost::filesystem;

/*-----------------------------------------初期化処理------------------------------------------------*/

/**
 * ノードの初期化用関数
 * コンストラクタのオーバーロードを擬似的に再現
 */
void Object::initialize(Type type, std::string name, std::string path){
    this->type=type;
    this->name=name;
    this->path=path;
    this->child=NULL;
    this->next=NULL;
}

/**
 * デフォルトコンストラクタ
 */
Object::Object(){
    initialize(unknown, "", "");
}

/**
 * 初期化用コンストラクタ
 */
Object::Object(Type type, std::string name, std::string path){
    initialize(type, name, path);
}

/**
 * 再帰的にデストラクタを呼びだせる
 */
Object::~Object(){
    if(this->child!=NULL){
        delete this->child;
    }
    if(this->next!=NULL){
        delete this->next;
    }
}


/*-----------------------------------------初期化処理終了----------------------------------------------*/
/*-------------------------------------オブジェクト操作関数開始------------------------------------------*/

/**
 * ハッシュ値の計算
 */
void Object::calc_hash(){
    /* すでにハッシュが計算されているものはスキップ */
    if(getHash()==""){
        std::ifstream ifs(path.c_str());
        std::string line="";
        std::string buff=getType()+" ";
        
        if(ifs){
            buff+=getPath()+" ";
            while(getline(ifs,line))
            {
                buff+=line;
            }
        }
        else{
            buff+=read(".eat/index");
        }
        
        hash=sha1(buff);
        buff=std::string("");
    }

    if(child!=NULL)
        child->calc_hash();
    if(next!=NULL)
        next->calc_hash();
    
}

/**
 * ファイルの詳細を出力
 */
void Object::dump(){
    std::cout << std::endl;
    std::cout << "Object name = " << getName() << std::endl;
    std::cout << "Object type = " << getType() << std::endl;
    std::cout << "Object path = " << getPath() << std::endl;
    std::cout << "Object hash = " << getHash() << std::endl;
    
    if(child!=NULL)
        child->dump();
    if(next!=NULL)
        next->dump();
}

/**
 * すでに求めてあるハッシュ値をセットする
 */
void Object::setHash(std::string hashCode){
    hash=hashCode;
}

/**
 * 木構造をもとに.eat/Objects/にファイルを書き出す
 */
void Object::make_copy_objects(){
    if(type==blob)
        copy_obj();
    if(child!=NULL)
        child->make_copy_objects();
    if(next!=NULL)
        next->make_copy_objects();
}

/**
 * ファイルを.eat/objectsにコピー
 */
void Object::copy_obj(){
    std::string forward=".eat/objects/"+getHash();
    std::string src=getPath();
    
    struct stat st;
    if(stat(forward.c_str(), &st)){
        std::ifstream ifs(src);
        if(!ifs){
            std::cerr << src << "cannot open" << '\n';
            return;
        }
        std::ofstream ofs(forward, std::ios::trunc);
        if(!ofs){
            std::cerr << forward << "cannot open" << '\n';
            return;
        }
        ofs << ifs.rdbuf() << std::flush;
        if(!ifs){
            std::cerr << forward << "cannot write" << '\n';
            return;
        }
        if(!ofs){
            std::cerr << src << "cannot write" << '\n';
            return;
        }
    }
}

/**
 * コミットオブジェクトを生成する
 * logにコミットオブジェクトのハッシュとコメントをダンプする
 * 木構造のcommit, tree, blobオブジェクトを生成する
 */
void Object::make_commit_obj(std::string commit_msg){
    write(".eat/logs/"+getBranch(),
          getHash()+"\n"+getTime()+"\n\""+commit_msg+"\"", std::ofstream::app);
    make_tree_blob_obj();
}

/**
 * tree, blobオブジェクトの生成
 */
std::string Object::make_tree_blob_obj(){
    /* カレント以下のオブジェクトをすべて取得 */
    Object* current=this->child;
    std::string buff="";
    
    /* 同階層のすべてオブジェクトの情報を連結 */
    while(current!=NULL){
        buff+=current->getType()+" "+current->getName()+" "+current->getHash()+"\n";
        if(current->child!=NULL)
            write(".eat/objects/"+this->getHash(), current->make_tree_blob_obj(), std::ofstream::out);
        current=current->next;
    }
    
    /* 連結した情報を書き出し */
    write(".eat/objects/"+this->getHash(), buff, std::ofstream::out);

    return buff;
}

/*-----------------------------------オブジェクト操作関数終了------------------------------------------*/
/*-----------------------------------------ゲッター開始----------------------------------------------*/

/**
 * オブジェクトのタイプを返す
 */
std::string Object::getType(){
    return type_strs[type];
}

/**
 * オブジェクトのネイティブ名を返す
 */
std::string Object::getName(){
    return name;
}

/**
 * オブジェクトのハッシュ値を返す
 */
std::string Object::getHash(){
    return hash;
}

/**
 * オブジェクトの相対パスを返す
 */
std::string Object::getPath(){
    return path;
}

/**
 * 再帰的に相対パスを連結する
 */
std::string Object::cyclic_getPath(std::string buff){
    if(child!=NULL)
        buff+=child->cyclic_getPath(buff);
    if(next!=NULL)
        buff+=next->cyclic_getPath(buff);
    if(type==blob || type==tree)
        buff+=getPath()+" "+getHash()+";";

    return buff;
}

/**
 * indexファイルに記述するためのファイル相対パスの集まりを返す
 * 返る文字列は改行コードを含む単一のstring変数の参照
 */
std::vector<std::string> Object::index_path_set(){
    return split(cyclic_getPath(""),';');
}


/*-----------------------------------------ゲッター終了----------------------------------------------*/

