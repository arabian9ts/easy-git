//
//  main.cpp
//  eat
//
//  Created by arabian9ts on 2017/03/16.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#include "generator.hpp"

Object* root=NULL;

/*----------------------------------------ファイル操作関数--------------------------------------------*/

/**
 * headsファイルに書き出す
 * @param refer : 現在のブランチのパス
 */
int write_head(std::string refer){
    write(".eat/HEAD", refer, std::ofstream::trunc);
    return 0;
}

/**
 * refsファイルに書き出す
 */
int write_refs(std::string hashcode){
    write(".eat/refs/heads/"+getBranch(), hashcode, std::ofstream::trunc);
    return 0;
}

/**
 * blobオブジェクトのパスをindexに書き出す
 */
int write_index(std::vector<std::string> file_names_list){

    std::sort(file_names_list.begin(), file_names_list.end());
    file_names_list.erase(std::unique(file_names_list.begin(),
                                      file_names_list.end()),
                          file_names_list.end());
    
    std::ofstream writing_file;
    writing_file.open(".eat/index", std::ios::out);
    
    for (auto v : file_names_list){
        writing_file << v << std::endl;
    }
    
    writing_file.close();
    
    return 0;
}

/*---------------------------------------ファイル操作関数終了-------------------------------------------*/
/*--------------------ここから下はコマンドの関数,ここから上はコマンドで使用する関数-----------------------------*/

/**
 * initコマンドを実行
 * index, refsなどを生成
 */
int init(){
    struct stat st;
     if(stat(".eat", &st) == 0){
         std::cout << "directory is already administered by eat" <<
         std::endl;
         return 0;
     }
    
    /* create dirs such as objects, refs, ...*/
    const char  *dir_name[]={
        ".eat",
        ".eat/objects",
        ".eat/refs",
        ".eat/refs/heads",
        ".eat/logs"};
    
    for(int i=0;i<sizeof(dir_name)/sizeof(dir_name[0]);i++)
            mkdir(dir_name[i], 0775);
    
    /* create files such as HEAD, master, ... */
    const char *file_names[]={
        ".eat/index",
        ".eat/HEAD",
        ".eat/refs/heads/master",
        ".eat/config",
        ".eat/logs/master"};
    
    for(int i=0;i<sizeof(file_names)/sizeof(file_names[0]);i++)
        touch(file_names[i]);
    
    write_head("./refs/heads/master");
    
    return 0;
}


/**
 * addコマンドを実行する
 */
int add(int argc, const char *argv[]){
    struct stat st;
    root=new Object(Object::Type::commit,"","");
    if(read(".eat/index")!="")
        index2tree(root, 1);
    for(int i=1;i<=argc;i++){
        stat(argv[i], &st);
        /* ディレクトリなら、そのディレクトリをrootとしてコール */
        if ((st.st_mode & S_IFMT) == S_IFDIR) {
            // ツリーオブジェクトをルートにして部分木を生成
            read_native_tree(root,argv[i]);
        }
        else{
            graft(root, new Object(Object::Type::blob,argv[i],argv[i]));
        }
    }
    
    /* それぞれのsha1ハッシュを計算 */
    root->calc_hash();
    
    /* indexにパスを書き込み*/
    write_index(root->index_path_set());
    
    root->make_copy_objects();
    
//    root->dump();
    return 0;
}

/**
 * indexからコミットツリーを作成し、commitファイルを生成する
 */
int commit(int tree_generated){
    if(!tree_generated){
        root=new Object(Object::Type::commit,"","");
        index2tree(root, 0);
        root->calc_hash();
//        root->dump();
    }
    
    if(last_commit(getBranch())==root->getHash()){
        std::cout << "no changes to commit" << std::endl;
        return 0;
    }
    std::string msg="";
    std::cout << "commit message : ";
    while(msg=="")
        std::getline(std::cin, msg);
    
    root->make_commit_obj(msg);
    write_refs(root->getHash());
    
    return 0;
}

/**
 * リポジトリ内のすべてのファイルをaddし、内部でcommitする
 */
int reflect(){
    const char* args[]={"dammy","./"};
    add(1, args)==0;
    root->rehash_root();
    commit(1);
    return 0;
}

/**
 * コミットログをダンプ
 */
int log(int count=0){
    std::vector<std::string> logs=getLogs(getBranch());
    count=(logs.size()/3-count)*3;
    if(count<0 || count==logs.size())
        count=0;
    
    for(int i=logs.size()-1;i>=count;i--){
        if(i%3==0)
            std::cout << "message: " << logs[i]+"\n" << std::endl;
        else if(i%3==1)
            std::cout << "date: " << logs[i] << std::endl;
        if(i%3==2)
            std::cout << "\ncommit: " << logs[i] << std::endl;
    }
    return 0;
}

/**
 * 引数あり : ブランチ作成, 引数なし : ブランチリストをダンプ
 */
int branch(std::string branch){
    if(""==branch){
        std::vector<std::string> branch_list=file_dir_list(".eat/refs/heads");
        for(auto v : branch_list)
            std::cout << v << std::endl;
        return 0;
    }
    
    if(isExist(branch))
        std::cout << "branch: " << branch << "is already exist" << std::endl;
    else
        touch(".eat/refs/heads/"+branch);
    
    return 0;
}

/**
 * 作業ブランチを変更
 */
int checkout(std::string branch){
    if(isExist(".eat/refs/heads/"+branch)){
        write_head(".eat/refs/heads/"+branch);
        std::cout << "checkout to " << branch << std::endl;
    }
    else
        std::cout << "branch: " << branch << "is not exist" << std::endl;
    return 0;
}

/**
 * 現在のブランチに引数のブランチをマージ
 * logもコピーする
 * masterの最新コミットidがブランチに含まれているなら、fast-forward
 * そうでなければCONFLICTアラート
 * --force引数で強制的にマージし、masterのCONFLICTファイルをすべてマージ元のファイルで置き換える
 */
int merge(){
    return 0;
}

/**
 * 引数に応じてresetを実行
 * commit id -> その時点のコミットまでリセット
 * HEAD　-> 直前までリセット
 */
int reset(){
    root=new Object(Object::Type::commit,"","");
    std::string commithash=read(".eat/refs/heads/"+getBranch());
    commit2tree(root, commithash);
    root->restore();
    return 0;
}


/*----------------------------------------コマンド関数終了--------------------------------------------*/
/*-------------------------------------------メイン関数----------------------------------------------*/

/**
 * メイン関数
 * コマンドライン引数からコマンドを識別し、実行する
 */

int main(int argc, const char *argv[]) {
    /* without argument */
    if(1==argc){
        printf("Usage: hogehoge\n");
        return 0;
    }
    /* except for file_name */
    argc--;
    
    /* excute command */
    const char *subcom=argv[1];
    argc--;
    
    if(strcmp(subcom, "init")==0){
        init();
    }
    else if(strcmp(subcom, "add")==0){
        add(argc, ++argv);
    }
    else if(strcmp(subcom, "commit")==0){
        commit(0);
    }
    else if(strcmp(subcom, "reflect")==0){
        reflect();
    }
    else if(strcmp(subcom, "branch")==0){
        if(argc==0)
            branch("");
        else if(argc==1)
            branch(argv[2]);
        else
            std::cout << "assert branch usage" << std::endl;
    }
    else if(strcmp(subcom, "checkout")==0){
        if(argc==1)
            checkout(argv[2]);
        else
            std::cout << "assert checkout usage" << std::endl;
    }
    else if(strcmp(subcom, "merge")==0){
        merge();
    }
    else if(strcmp(subcom, "reset")==0){
        reset();
    }
    else if(strcmp(subcom, "log")==0){
        if(argc>0)
            log(atoi(argv[2]));
        else
            log();
    }
    else{
        std::cout << "not eat command !  execute \"eat\" and check usage !\n" << std::endl;
    }
    
//    sha1Test();
    
    if(root!=NULL)
        delete root;
    return 0;
}
