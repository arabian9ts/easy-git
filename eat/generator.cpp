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
 * blob と tree の木構造を再帰的に作成する
 */
std::string relative_path="";
void read_native_tree(Object *subtree, std::string subroot){
    DIR *dir;
    struct dirent *dp;
    struct stat st;
    
    /* subtreeが存在しないなら終了 */
    if(NULL==(dir=opendir(subroot.c_str()))){
        printf("cannot open %s\n", subroot.c_str());
        return;
    }
    
    /* すべてのディレクトリを読み込み */
    for(dp=readdir(dir);dp!=NULL;dp=readdir(dir)){
        /* .で始まるものとeatはスキップ */
        int start_with_dot=boost::algorithm::starts_with(dp->d_name, ".");
        if(!start_with_dot && dp->d_name!=std::string("eat")){
            if(subroot!="./")
                relative_path=subroot+"/"+dp->d_name;
            else
                relative_path=dp->d_name;
            stat(relative_path.c_str(), &st);
            
            /* ディレクトリなら、そのディレクトリをrootとしてコール */
            if ((st.st_mode & S_IFMT) == S_IFDIR) {
                // ツリーオブジェクトをルートにして部分木を生成
                read_native_tree(graft(subtree,new Object(Object::Type::tree,dp->d_name,relative_path)),relative_path);
            }
            
            /* ファイルなら、ジェネレータをコールしてノードを追加 */
            else {
                graft(subtree, new Object(Object::Type::blob, dp->d_name,relative_path));
            }
        }
    }
}


/**
 * indexからコミットツリーを作成
 * rehash : add, reflectでは最新のファイル状態を取得するため再ハッシュ
 * commitでは再ハッシュは行わない
 */
int index2tree(Object* root, int rehash){
    Object::Type type;
    std::ifstream ifs(".eat/index");
    
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
    std::string line;
    while(getline(ifs, line)){
        
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
                parent=graft(parent,new Object(type,*dir,stored_path));
                
                /* 再度sha1の計算をすることを避けるため、indexで読んだsha1をセット */
                if(rehash)
                    parent->setHash(filepath_hash[1]);
                
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
    ifs.close();
    return 0;
}
