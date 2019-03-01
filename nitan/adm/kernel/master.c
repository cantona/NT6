// This program is a part of NT MudLIB
// Master.c
//
// For ES II mudlib
// Original from Lil
// Rewritten by Annihilator (11/07/94)
// Modified by Xiang for XKX (12/15/95)
// Rewritten by Lonely@nitan.org

#pragma optimize
#pragma save_binary


#define BIG5_PORT                       6000
#define UTF8_PORT                       6666
#define TOMUD_PORT                      7000

//-----------------------------------------------------------------------------

#include "/adm/kernel/master/compile_object.c";        /* 用來載入 MudOS 虛擬物件 */
#include "/adm/kernel/master/crash.c";                 /* 用來處理 Crash 時的緊急情況 */
#include "/adm/kernel/master/preload.c";               /* 預先載入初始化動作 */
#include "/adm/kernel/master/error.c";                 /* 處理錯誤訊息的函式 */
#include "/adm/kernel/master/file.c";                  /* 關於 domain_file , author_file , privs_file */
#include "/adm/kernel/master/ed.c";                    /* 有關 Edit 的一些設定 */
#include "/adm/kernel/master/parse.c";                 /* 文法(對中文Mud而言似乎沒有用處?) */
#include "/adm/kernel/master/object.c";                /* 環境遭到毀滅時, 所有內在物件都會呼叫此函式 */

//-----------------------------------------------------------------------------

#include "/adm/kernel/master/valid_asm.c";
#include "/adm/kernel/master/valid_author.c";
#include "/adm/kernel/master/valid_bind.c";            /* 檢查函式指標與物件的結合 */
#include "/adm/kernel/master/valid_compile.c"          /* 判斷一個文件是否可被編譯 */
#include "/adm/kernel/master/valid_compile_to_c.c";    /* 判斷是否可以用 LPC->C 編譯 */
#include "/adm/kernel/master/valid_domain.c";
#include "/adm/kernel/master/valid_hide.c";            /* 檢查匿蹤能力 */
#include "/adm/kernel/master/valid_link.c";            /* 控制 link 外部函式的用途 */
#include "/adm/kernel/master/valid_object.c";          /* 讓你能控制是否要載入某個物件 */
#include "/adm/kernel/master/valid_override.c";        /* 控制 efun:: 的用途 */
#include "/adm/kernel/master/valid_seteuid.c";
#include "/adm/kernel/master/valid_readwrite.c";       /* 檢查是否有權讀取寫入檔案 */
#include "/adm/kernel/master/valid_save_binary.c";     /* 控制一個物件是否可以儲存它已載入的程式 */
#include "/adm/kernel/master/valid_shadow.c";          /* 控制哪些物件可以被投影 */
#include "/adm/kernel/master/valid_socket.c";          /* 保護 socket 外部函式 */
#include "/adm/kernel/master/valid_database.c";        /* 控制mysql數據庫的連接 */

//-----------------------------------------------------------------------------

//        connect() 傳回的物件，會當作初始使用者物件 (initial user object)。
//        請注意，之後你可以使用 exec() 外部函式將改變使用者物件。

object connect(int port)
{
        object login_ob;
        mixed err;

        err = catch(login_ob = new(LOGIN_OB));

        if( err )
        {
                write("現在有人正在修改使用者連線部份的程式，請待會再來。\n");
                write(err);
                destruct(this_object());
        }

#ifdef CONFIG_NON_UTF8
        if( port == BIG5_PORT )
                set_temp("big5", 1, login_ob);

        else
#endif
        if( port == TOMUD_PORT )
                set_temp("tomud", 1, login_ob);

        //else
        //if( port == UTF8_PORT )
        //      set_encoding("utf-8", login_ob);

        return login_ob;
}

string get_root_uid()
{
        return ROOT_UID;
}

string get_bb_uid()
{
        return BACKBONE_UID;
}


string object_name(object ob)
{
        if( ob ) return ob->name();
}

// 是否直接運行BINARY，不調用文件。
int direct_run_binary(string file)
{
        object ob;
        object vob;

#ifndef BINARY_SUPPORT
        return 0;
#else
        if( sscanf(file, DATA_DIR "%*s") )
                // 如果是DATA下面的文件，不能直接運行BIN代碼，
                // 需要進行常規的版本有效檢查。
                return 0;

        if( objectp(ob = find_object(CONFIG_D)) &&
            objectp(vob = find_object(VERSION_D)) ) {
                // 找到了CONFIG_D，查看本地是否是版本發佈站
                // 點，如果是，則查看是否是發佈的源程序，是
                // 則返回否，表示需要檢查BIN。
                return query("release server", ob) != "local" &&
                       !VERSION_D->is_need_release_source(file);
        }

        // 沒有找到CONFIG_D && VERSION_D，不編譯，直接運行
        // BIN代碼。
        return 1;
#endif
}

void create()
{
        if( clonep() )   return;

        write("master: loaded successfully.\n");
}

void check_daemons()
{
        string *sp;
        int i;

        sp = epilog(0);
        if( !sp ) return;

        for (i = 0; i < sizeof(sp); i++)
                if( stringp(sp[i])) preload(sp[i]);
}

