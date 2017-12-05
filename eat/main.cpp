//
//  main.cpp
//  eat
//
//  Created by arabian9ts on 2017/03/16.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#include "generator.hpp"
#include "help/helper.hpp"
#include "color.hpp"

/*-------------------- test headers --------------------*/

#include "sha1Test.hpp"
#include "readerTest.hpp"
#include "compressTest.hpp"

/*------------------ end test headers ------------------*/

Object* root = NULL;

/*----------------------------------------ファイル操作関数--------------------------------------------*/

/**
 * headsファイルに書き出す
 * @param refer : 現在のブランチのパス
 */
void write_head(std::string refer){
    util::write(".eat/HEAD", refer, std::ofstream::trunc);
}

/**
 * refsファイルに書き出す
 * @param hashcode : ヘッドの参照コミットハッシュ
 */
void write_refs(std::string hashcode){
    util::write(".eat/refs/heads/"+util::getBranch(), hashcode, std::ofstream::trunc);
}

/**
 * blobオブジェクトのパスをindexに書き出す
 * @oaram file_name_list : indexに書き出すファイルのリスト
 */
void write_index(std::vector<std::string> file_names_list){

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
}

/**
 * コミットログを書き出す
 * @param commit_msg : コミットログに記録するコミットメッセージ
 */
void write_log(std::string commit_msg){
    util::write(".eat/logs/"+util::getBranch(),
                "\""+commit_msg+"\"\n"+util::getTime()+"\n"+root -> getHash(), std::ofstream::app);
}

/*---------------------------------------ファイル操作関数終了-------------------------------------------*/
/*--------------------ここから下はコマンドの関数,ここから上はコマンドで使用する関数-----------------------------*/

/**
 * initコマンドを実行
 * index, refsなどを生成
 */
void init(){
    struct stat st;
     if(stat(".eat", &st) == 0){
         std::cout << "directory is already administered by eat" <<
         std::endl;
         return;
     }
    
    /* create dirs such as objects, refs, ...*/
    const char* dir_name[] = {
        ".eat",
        ".eat/objects",
        ".eat/refs",
        ".eat/refs/heads",
        ".eat/logs",
    };
    
    for(int i = 0; i < sizeof(dir_name)/sizeof(dir_name[0]); i++)
            mkdir(dir_name[i], 0775);
    
    /* create files such as HEAD, master, ... */
    const char* file_names[] = {
        ".eat/index",
        ".eat/HEAD",
        ".eat/refs/heads/master",
        ".eat/config",
        ".eat/logs/master",
    };
    
    for(int i = 0; i < sizeof(file_names)/sizeof(file_names[0]); i++)
        util::touch(file_names[i]);
    
    write_head(".eat/refs/heads/master");
    
}


/**
 * addコマンドを実行する
 * @param argc : 指定されたファイル/ディレクトリの数
 * @param argv : 指定されたファイル/ディレクトリの名前
 */
void add(int argc, const char *argv[]){
    root = new Object(Object::Type::commit,"","");
    if(util::read(".eat/index") != "")
        gen::index2tree(root, 0);
    for(int i = 1; i <= argc; i++){
        /* ディレクトリなら、そのディレクトリをrootとしてコール */
        if (!util::isFile(argv[i])) {
            // ツリーオブジェクトをルートにして部分木を生成
            gen::read_native_tree(root, argv[i]);
        }
        else if(util::isFile(argv[i])){
            gen::graft(root, new Object(Object::Type::blob, argv[i], argv[i]));
        }
        std::cout << argv[i] << std::endl;
    }
    
    /* それぞれのsha1ハッシュを計算 */
    root -> calc_hash();
    
    /* indexにパスを書き込み*/
    write_index(root -> index_path_set());
    
    root -> make_copy_objects();
    
//    root -> dump();
    
}

/**
 * indexからコミットツリーを作成し、commitファイルを生成する
 * @param tree_generated : すでにコミットツリーが生成されているかどうか
 */
void commit(int tree_generated){
    if(!tree_generated){
        root = new Object(Object::Type::commit, "", "");
        gen::index2tree(root, 0);
        root -> calc_hash();
//        root->dump();
    }
    
    if(util::last_commit(util::getBranch()) == root -> getHash()){
        std::cout << "no changes to commit" << std::endl;
        return;
    }
    
    root -> make_tree_blob_obj();
    write_log(util::fetch_commit_msg());
    write_refs(root -> getHash());
    
}

/**
 * リポジトリ内のすべてのファイルをaddし、内部でcommitする
 */
void reflect(){
    const char* args[] = {"dammy", "./"};
//    add(1, args);
    root = new Object(Object::Type::commit, "", "");
    gen::read_native_tree(root, "./");
    
    /* それぞれのsha1ハッシュを計算 */
    root -> calc_hash();
    
    /* indexにパスを書き込み*/
    write_index(root -> index_path_set());
    
    root -> make_copy_objects();
    
    root -> dump();
    root -> rehash_root();
    commit(1);
}

/**
 * コミットログをダンプ
 * @param count : 何個前までのログを表示するか
 */
void log(int count = 5){
    std::vector<Log> logs=util::getLogs(util::getBranch());
    
    if(logs.size() < count)
        count = logs.size();
    
    std::cout << std::endl;
    for (int i = 0; i < count; i++) {
        logs[i].dump();
    }

}


/**
 * 引数に応じてresetを実行
 * commit id -> その時点のコミットまでリセット
 * HEAD　-> 直前までリセット
 * @param version : 何個前のバージョンの状態に戻すか
 */
void reset(int version = 0){
    std::vector<std::string> rmlist = util::split(util::read(".eat/index", "\n", 1),  '\n');
    
    if(rmlist.size() <= 0) {
        return;
    }
    
    for(int i = 0; i < rmlist.size(); i++){
        rmlist[i] = util::split(rmlist[i], ' ')[0];
//        std::cout << "delete " << rmlist[i] << std::endl;
    }
    util::rmfiles(rmlist);
    
    std::vector<std::string> commits = util::commitlist(util::getBranch());
    
    if(version > commits.size()-1)
        version = commits.size()-1;
    
    if(commits.size() <= version) {
        return;
    }
    
    std::string commithash = commits[version];
//    std::cout << commithash << std::endl;
    
    root = new Object(Object::Type::commit,"","");
    gen::commit2tree(root, commithash);
//    std::cout << "-------------------------" << std::endl;
//    root -> dump();
    root -> restore();
    write_index(root -> index_path_set());
}


/**
 * 引数あり : ブランチ作成, 引数なし : ブランチリストをダンプ
 * @param branch : 作成するブランチ名, 空文字の場合はブランチリストの要求と解釈
 */
void branch(std::string branch){
    if("" == branch){
        std::vector<std::string> branch_list = util::file_dir_list(".eat/refs/heads");
        for(auto v : branch_list)
            std::cout << v << std::endl;
        std::cout << "\nnow: @" << util::getBranch() << std::endl;
        return;
    }
    
    root = new Object(Object::Type::commit,"","");
    if(util::isExist(branch))
        std::cout << "branch: " << branch << "is already exist" << std::endl;
    else{
        util::touch(".eat/refs/heads/"+branch);
        root -> copy_obj(".eat/logs/"+util::getBranch(), ".eat/logs/"+branch);
        root -> copy_obj(".eat/refs/heads/"+util::getBranch(), ".eat/refs/heads/"+branch);
    }
}

/**
 * 作業ブランチを変更
 * @param branch : チェックアウトするブランチ名
 */
void checkout(std::string branch){
    if(util::isExist(".eat/refs/heads/"+branch)){
        write_head(".eat/refs/heads/"+branch);
        std::cout << "switch to " << branch << std::endl;
        reset(0);
    }
    else{
        std::cout << "branch: " << branch << "is not exist" << std::endl;
    }
}

/**
 * 現在のブランチに引数のブランチをマージ
 * logもコピーする
 * masterの最新コミットidがブランチに含まれているなら、fast-forward
 * そうでなければCONFLICTアラート
 * --force引数で強制的にマージし、masterのCONFLICTファイルをすべてマージ元のファイルで置き換える
 * @param branxh : 取り込むブランチ名
 */
void merge(std::string targ_branch){
    std::string base_branch = util::getBranch();
    
    std::vector<std::string> targ_commits = util::commitlist(targ_branch);
    std::vector<std::string>::iterator itr = find(targ_commits.begin(), targ_commits.end(), util::last_commit(base_branch));
    
    if(itr != targ_commits.end()){
        std::cout << "fast-forward : " << std::endl;
        root = new Object(Object::Type::commit,"","");
        gen::commit2tree(root, util::last_commit(targ_branch));
        write_index(root -> index_path_set());
        root -> rehash_root();
        commit(1);
        reset(0);
    }
    else{
        std::cout << "non fast-forward : " << std::endl;
    }
}


/*----------------------------------------コマンド関数終了--------------------------------------------*/
/*-------------------------------------------メイン関数----------------------------------------------*/

/**
 * メイン関数
 * コマンドライン引数からコマンドを識別し、実行する
 * @param argc : サブコマンド,引数の数(プログラム名含む)
 * @param argv : サブコマンド,引数(プログラム名含む)
 * @return : プログラム終了コード
 */

int main(int argc, const char *argv[]) {
    
    /* without argument */
    if(1 == argc){
        printf("Usage: eat help\n");
        return 0;
    }
    /* except for file_name */
    argc--;
    
    /* excute command */
    const char *subcom = argv[1];
    argc--;
    
    if(strcmp(subcom, "init") == 0){
        init();
        return 0;
    }
    
    if(!util::isExist(".eat")){
        std::cout << "this dir is not eat repository" << std::endl;
        return 0;
    }
    else if(strcmp(subcom, "add") == 0){
        add(argc, ++argv);
//        std::cout << "Warning : this formula is deprecated !" << std::endl;
    }
    else if(strcmp(subcom, "commit") == 0){
        commit(0);
    }
    else if(strcmp(subcom, "reflect") == 0){
        reflect();
    }
    else if(strcmp(subcom, "branch") == 0){
        if(argc == 0)
            branch("");
        else if(argc == 1)
            branch(argv[2]);
        else
            std::cout << "check for branch fomula by using: eat help branch" << std::endl;
    }
    else if(strcmp(subcom, "checkout") == 0){
        if(argc == 1)
            checkout(argv[2]);
        else
            std::cout << "check for checkout fomula by using: eat help checkout" << std::endl;
    }
    else if(strcmp(subcom, "merge") == 0){
        if(argc == 1)
            merge(argv[2]);
        else
            std::cout << "check for merge fomula by using: eat help merge" << std::endl;
    }
    else if(strcmp(subcom, "reset") == 0){
        if(argc == 0)
            reset(0);
        else if(argc == 1)
            reset(atoi(argv[2]));
    }
    else if(strcmp(subcom, "log") == 0){
        if(argc == 1)
            log(atoi(argv[2]));
        else
            log();
    }
    else if(strcmp(subcom, "help") == 0){
        Helper* helper = new Helper();

        if(argc == 1)
            helper -> describe(argv[2]);
        else
            helper -> describe("help");
        
        delete helper;
    }
    else{
        std::cout << "ERROR : not eat command !  check formulae by using: eat help" << std::endl;
    }
    
//    sha1Test();
//    readerTest();
//    compressTest();
    
//    Clout(Color::pallet::blue) << "color test" << std::endl;
    
    if(root != NULL)
        delete root;
    return 0;
    
/*----------------------------------------PROGRAM END-------------------------------------------*/
}
