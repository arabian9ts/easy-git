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
void Object::initialize(Type type, std::string name, std::string path, std::string hash){
    this->type=type;
    this->name=name;
    this->path=path;
    this->hash=hash;
    this->child=NULL;
    this->next=NULL;
}

/**
 * デフォルトコンストラクタ
 */
Object::Object(){
    initialize(unknown, "", "", "");
}

/**
 * 初期化用コンストラクタ
 */
Object::Object(Type type, std::string name, std::string path){
    initialize(type, name, path, "");
}

/**
 * 初期化用コンストラクタ(ハッシュが予め求まっている場合)
 */
Object::Object(Type type, std::string name, std::string path, std::string hash){
    initialize(type, name, path, hash);
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
    std::ifstream ifs(path.c_str());
    std::string line="";
    std::string buff;
    
    if(ifs){
        buff=getType()+" "+getPath()+" ";
        while(getline(ifs,line)){
            buff+=line;
        }
    }
    else{
        buff+=read(".eat/index");
    }
    
    hash=sha1(buff);
    buff=std::string("");
    
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

/* Objectファイルを元のプロジェクトに復元 */
void Object::restore(){
    
    if("blob"==getType())
        copy_obj(".eat/objects/"+getHash(), getPath());
    else if("tree"==getType())
        mkdir(getPath().c_str(), 0755);
    
    if(child!=NULL)
        child->restore();
    if(next!=NULL)
        next->restore();
}


/**
 * 木構造をもとに.eat/Objects/にファイルを書き出す
 */
void Object::make_copy_objects(){
    if(type==blob)
        copy_obj(getPath(), ".eat/objects/"+getHash());
    if(child!=NULL)
        child->make_copy_objects();
    if(next!=NULL)
        next->make_copy_objects();
}

/**
 * ファイルを.eat/objectsにコピー
 */
void Object::copy_obj(std::string from, std::string to){
    struct stat st;
    std::ifstream ifs(from);
    if(!ifs){
        std::cout << "cannot open " << from << std::endl;
        return;
    }
    std::ofstream ofs(to, std::ios::out);
    if(!ofs){
        std::cout << "cannot open " << to << std::endl;
        return;
    }
    std::cout << "copy " << from << " to " << to <<std::endl;
    ofs << ifs.rdbuf() << std::flush;
    
    ifs.close();
    ofs.close();
}

/**
 * コミットオブジェクトを生成する
 * logにコミットオブジェクトのハッシュとコメントをダンプする
 * 木構造のcommit, tree, blobオブジェクトを生成する
 */
void Object::make_commit_obj(std::string commit_msg){
    write(".eat/logs/"+getBranch(),
          "\""+commit_msg+"\"\n"+getTime()+"\n"+getHash(), std::ofstream::app);
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
            write(".eat/objects/"+getHash(), current->make_tree_blob_obj(), std::ofstream::trunc);
        current=current->next;
    }
    
    /* 連結した情報を書き出し */
    write(".eat/objects/"+this->getHash(), buff, std::ofstream::trunc);

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
 */
std::vector<std::string> Object::index_path_set(){
    return split(cyclic_getPath(""),';');
}

/* ルートのコミットハッシュの訂正 */
void Object::rehash_root(){
    hash=sha1Code(".eat/index");
}

/*-----------------------------------------ゲッター終了----------------------------------------------*/

