//
//  generator.cpp
//  eat
//
//  Created by arabian9ts on 2017/04/19.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#include "generator.hpp"

/**
 * ノードジェネレータ
 * make_tree 内で利用
 */
Object* graft(Object *parent, Object *targ){
    /* rootノードが存在しないなら終了 */
    if(parent==NULL)
        return NULL;
    
    /* parentが最下層なら次の階層をつくる */
    if(parent->child==NULL)
        parent->child=targ;
    
    /* 下の階層の末尾に追加 */
    else{
        Object *search_point=parent->child;
        while(search_point->next!=NULL){
            search_point=search_point->next;
        }
        search_point->next=targ;
    }
    return targ;
}

/**
 * blob と tree の木構造を再帰的に生成
 */
std::string relative_path="";
void read_native_tree(Object *subtree, std::string subroot){
    struct stat st;
    std::vector<std::string> files_dirs=file_dir_list(subroot);
    
    /* すべてのディレクトリを読み込み */
    for(auto v : files_dirs){
        if(subroot!="./")
            relative_path=subroot+"/"+v;
        else
            relative_path=v;
        stat(relative_path.c_str(), &st);
        
        /* ディレクトリなら、そのディレクトリをrootとしてコール */
        if ((st.st_mode & S_IFMT) == S_IFDIR) {
            // ツリーオブジェクトをルートにして部分木を生成
            read_native_tree(graft(subtree,new Object(Object::Type::tree,v,relative_path)),relative_path);
        }
        
        /* ファイルなら、ジェネレータをコールしてノードを追加 */
        else {
            graft(subtree, new Object(Object::Type::blob,v,relative_path));
        }
    }
}


/**
 * indexからコミットツリーを生成
 * rehash : add, reflectでは最新のファイル状態を取得するため再ハッシュ
 * commitでは再ハッシュは行わない
 */
void index2tree(Object* root, int rehash){
    Object::Type type;
    std::vector<std::string> index_lines;
    index_lines=split(read(".eat/index","\n",1), '\n');
    
    /* Object*のアドレスを格納するmap */
    std::map<std::string, Object*> mp;
    
    /* index各行のファイルパスとハッシュを分断したベクトル */
    std::vector<std::string> filepath_hash;
    
    /* indexのパスを分割した、ディレクトリ名のベクトル */
    std::vector<std::string> dirs;
    
    /* Objectツリーの親を探すために、徐々に連結するパス */
    std::string stored_path;
    
    /* デフォルトの親をrootにセット */
    Object* parent=root;
    
    /* 一行ずつindexを読み込む */
    for(auto line : index_lines){
        
        /*-------------------各行でリセットする値---------------------*/
        parent=root;
        stored_path="";
        filepath_hash=split(line, ' ');
        line=filepath_hash[0];
        dirs=split(line, '/');
        std::vector<std::string>::iterator dir = dirs.begin();
        /*---------------------------------------------------------*/
        
        /* 分断したファイルパスで、各ディレクトリ名ごとにループ */
        while(dir!=dirs.end()){
            
            /* 確認済みのパス(初期はrootと同地)に連結 */
            stored_path+=*dir;
            
            /* まだ登録されていないディレクトリなら新規登録 */
            if(mp.count(stored_path)==0){
                
                /* ファイル化かディレクトリでtypeを決定しておく */
                if(isFile(stored_path))
                    type=Object::Type::blob;
                else
                    type=Object::Type::tree;
                
                /* 接ぎ木して、追加したオブジェクトを親にセット */
                if(!rehash)
                    parent=graft(parent,new Object(type,*dir,stored_path,filepath_hash[1]));
                else
                    parent=graft(parent,new Object(type,*dir,stored_path));
                
                /* 新たに登録したファイルパス/ディレクトリパスを記憶 */
                mp.insert(std::pair<std::string,Object*>(stored_path,parent));
            }
            /* 既に登録されているなら親を取得して接ぎ木 */
            else{
                /* 登録されているならそのディレクトリの親を取得 */
                parent=mp[stored_path];
            }
            
            /* 最後のディレクトリ名/ファイル名でなければ'/'を付加 */
            if((++dir)!=dirs.end())
                stored_path+="/";
        }
    }
}

/**
 * commitオブジェクトからツリーを生成
 */
void commit2tree(Object* root, std::string comhash){
    std::vector<std::string> lines=split(read(".eat/objects/"+comhash,"\n",1), '\n');
    
    /* index各行のファイルパスとハッシュを分断したベクトル */
    std::vector<std::string> type_name_hash;
    
    std::string type;
    std::string name;
    std::string hash;
    
    /* 一行ずつindexを読み込む */
    for(auto line : lines){
        type_name_hash=split(line, ' ');
        type=type_name_hash[0];
        name=type_name_hash[1];
        hash=type_name_hash[2];
        
        std::string relative_path;
        if(""!=(relative_path=root->getPath()))
            relative_path+="/";
        
        if("tree"==type){
            commit2tree(
                        graft(root, new Object(Object::Type::tree,name,relative_path+name,hash)),
                        hash);
        }
        else if("blob"==type){
            graft(root, new Object(Object::Type::blob,name,relative_path+name,hash));
        }
    }
}




