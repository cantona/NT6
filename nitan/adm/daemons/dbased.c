// dbased.c 永久記憶的數據庫(可以記錄所有的場景和物品)
// 數據庫中的路徑以dbase為根、文件路徑為途徑。
// 比如/d/city/kedian這個對象保存在數據庫中的將是：
// /dbase/d/city/kedian，保存的內容是一個mixed類型，當對象的
// restore函數被調用的時候，對象必須保證有receive_dbase_data
// 函數用來接收保存在數據庫中的數據。 當對象保存的時候，則必
// 須有save_dbase_data函數返回需要保存的數據。
// Write by Doing
// Add MySQL by Lonely

#include <ansi.h>

#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

#include "/adm/etc/database.h"

// 保存數據的映射變量
mapping save_dbase;

// 調用函數announec_all_save_object時候的標誌
#define ONLY_SAVE               0
#define DESTRUCT_OBJECT         1
nosave  int save_flag = ONLY_SAVE;

public int announce_all_save_object(int destruct_flag);

// 提供給外部的函數
mixed   query_data();
int     set_data(mixed data);
mixed   query_object_data(object ob);
int     set_object_data(object ob, mixed data);
mapping query_save_dbase();
string *query_saved_object();
int     clear_object(mixed ob);
int     remove(string euid);
void    mud_shutdown();

void create()
{
        seteuid(ROOT_UID);
        if( !restore() && !mapp(save_dbase) )
                save_dbase = ([]);

        // auto save per 15 minute (900s)
        //set_heart_beat(450 + random(30));
        SCHEDULE_D->set_event(300, 1, this_object(), "announce_all_save_object", ONLY_SAVE);
}

// 數據庫對象析構函數
int remove(string euid)
{
        if( previous_object() != find_object(SIMUL_EFUN_OB) || !is_root(euid) )
                // Must be called from simul_efun object
                return 0;

        announce_all_save_object(save_flag);
        return 1;
}

// MUD將要停止運行
void mud_shutdown()
{
        save_flag = DESTRUCT_OBJECT;
        destruct(this_object());
}

// 通知所有的需要保存數據的對象
public int announce_all_save_object(int destruct_flag)
{
        object ob;
        string *e;
        int i;

        if( mapp(save_dbase) )
                e = keys(save_dbase);
        else
                e = ({ });
        // 通知所有的存盤對象保存數據
        for( i = 0; i < sizeof(e); i++ )
        {
                if( !stringp(e[i]) )
                        // 不應該不是字符串
                        map_delete(save_dbase, e[i]);
                else if( objectp(ob = find_object(e[i])) )
                {
                        // 找到了存盤的對象，通知它們
                        if( destruct_flag == DESTRUCT_OBJECT )
                                catch(destruct(ob));
                        else
                                catch(ob->save());
                }
        }

        save();
        return 1;
}

// 清理所有對象
int cleanup_all_save_object(int raw)
{
        object ob;
        string *e;
        int i;

        if( mapp(save_dbase) )
                e = keys(save_dbase);
        else
                return 1;

        // 通知所有的存盤對象保存數據
        for( i = 0; i < sizeof(e); i++ )
        {
                if( !stringp(e[i]) )
                        // 不應該不是字符串
                        map_delete(save_dbase, e[i]);
                else if( file_size(e[i] + ".c") < 0 )
                {
                        log_file("dbase", sprintf("data of (%s) cleaned because no found object.\n",
                                                  e[i]));
                        if( raw )
                        {
#ifdef DB_SAVE
                                DATABASE_D->db_remove_item(e[i]);
#endif
                                map_delete(save_dbase, e[i]);
                        }
                }
        }

        save();
        return 1;
}

// 心跳函數，自動保存所有的數據
protected int heart_beat()
{
        set_heart_beat(450 + random(30));
        announce_all_save_object(ONLY_SAVE);
}

string query_save_file() { return DATA_DIR + "dbased"; }

// 某個物件讀取自己的記錄
mixed query_data()
{
        return query_object_data(previous_object());
}

// 某個物件保存自己的記錄
int set_data(mixed data)
{
        return set_object_data(previous_object(), data);
}

// 讀取某個對象的記錄
mixed query_object_data(mixed ob)
{
        string index;
        mixed  data;

        if( !ob ) return 0;

        // 只有ROOT或對象自己才可以保存或讀取數據
        if( !is_root(previous_object()) &&
            previous_object() != ob ) return 0;

        if( stringp(ob) )
        {
                index = ob;
                sscanf(index, "%s.c", index);
        }
        else if( objectp(ob) )
                index = base_name(ob);
        else
                return 0;

#ifdef DB_SAVE
        // 從內存中讀取應該更快
        if( undefinedp(save_dbase[index]) )
        {
                data = DATABASE_D->db_restore_item(index);
                // 為了shutdown保存時候做標記
                save_dbase[index] = data;
                return data;
        }
#endif
        return save_dbase[index];
}

// 保存某個對象的記錄
int set_object_data(mixed ob, mixed data)
{
        string index;

        if( !ob ) return 0;

        // 只有ROOT或對象自己才可以保存或讀取數據
        if( !is_root(previous_object()) &&
            previous_object() != ob ) return 0;

        if( stringp(ob) )
        {
                index = ob;
                sscanf(index, "%s.c", index);
        }
        else if( objectp(ob) )
                index = base_name(ob);
        else
                return 0;

        if( !data )
        {
                map_delete(save_dbase, index);
                return 1;
        }

#ifdef DB_SAVE
        DATABASE_D->db_save_item(index, data);
#endif
        save_dbase[index] = data;
        return 1;
}

// 讀取所有對象的記錄
mapping query_save_dbase()
{
        return save_dbase;
}

// 查閲保存了數據的所有對象
string *query_saved_object()
{
        return keys(save_dbase);
}

// 清除一個對象
int clear_object(mixed ob)
{
        string index;
        object xob;

        // 由於一個對象在清除前一般會保存自己的數據，所以一旦數據受到
        // 損傷需要恢復對象為原始狀態的時候就必須先清除對象本身，然後
        // 清空它的數據。

        if( !ob ) return 0;

        if( stringp(ob) )
        {
                index = ob;
                sscanf(index, "%s.c", index);
                xob = find_object(index);
        }
        else if( objectp(ob) )
        {
                xob = ob;
                index = base_name(xob);
        }
        else return 0;

        if( !is_root(previous_object()) &&
            previous_object() != xob ) return 0;

        if( xob ) destruct(xob);

#ifdef DB_SAVE
        DATABASE_D->db_remove_item(index);
#endif
        map_delete(save_dbase, index);
        return 1;
}
