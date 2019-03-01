// restore.c

#include <ansi.h>
#include <localtime.h>
#include <command.h>

inherit F_CLEAN_UP;

protected string get_backup_data_dir(string what, int day);

int main(object me, string arg)
{
        int day;
        string what;
        string file;
        string dir;
        object ob, obn;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (BACKUP_D->is_backuping())
        {
                write("注意：自動備份馬上就要開始工作，現在不能執行恢復操作。\n");
                return 1;
        }

        if (! arg)
                return notify_fail("你想要幹什麼？\n");

        if (sscanf(arg, "%s from %d", what, day) != 2)
        {
                        what = arg;
                        day = 1;
        }
        
        if (! (ob = present(what, me)))
                ob = present(what, environment(me));

        if (! ob)
                ob = get_object(what);

        if (! ob || ! ob->is_ob_saved())
                return notify_fail("你想要恢復什麼？\n");
        
        if (day < 1 || day > 7)
        {
                write("沒有這個備份數據區。\n");
                return 1;
        }

        seteuid(getuid());
 
        dir = get_backup_data_dir(what, day);

        file = @TEXT
#include <ansi.h>

inherit F_SAVE;
inherit F_DBASE;

// 保存數據的映射變量
mapping save_dbase;

// 提供給外部的函數
mixed   query_data();
mixed   query_object_data(object ob);

void create()
{
        seteuid(ROOT_UID);
        if (! restore() && ! mapp(save_dbase))
                save_dbase = ([]);
}

// 某個物件讀取自己的記錄
mixed query_data()
{
        return query_object_data(previous_object());
}


// 讀取某個對象的記錄
mixed query_object_data(mixed ob)
{
        string index;
        mixed  data;
        object xob;
        
        if (! ob) return 0;

        if (stringp(ob))
        {
                index = ob;
                sscanf(index, "%s.c", index);
        } else
        if (objectp(ob))
                index = base_name(ob);
        else
                return 0;

        return save_dbase[index];
}

TEXT;        
        file += sprintf("string query_save_file() { return \"%sdbased\"; }\n", dir);
        
        write_file("/cmds/arch/ob_dbase.c", file, 1);    
        
        obn = get_object("/cmds/arch/ob_dbase.c");
        ob->receive_dbase_data(obn->query_object_data(ob));
        DATABASE_D->db_remove_item(base_name(ob));
        DATABASE_D->db_create_item(ob, ob->query_entire_dbase()); 

        destruct(obn);
        rm("/cmds/arch/ob_dbase.c");
        
        write(sprintf("從(%s)中復制%s的數據完畢。\n", dir, ob->name()));

        return 1;
}

// return the directory of the what
protected string get_backup_data_dir(string what, int day)
{
        mixed lt;
        int now;

        lt = localtime(time());
        lt[LT_MON]++;   // the month is from 0..31 so I will adjust it
        now = lt[LT_HOUR] * 100 + lt[LT_MIN];
        if (now > BACKUP_D->query_backup_time())
        {
                // because the o'clock has pass through the backuping
                // time, so the most recently backup data is of today
                day--;
        }

        lt[LT_MDAY] -= day;
        if (lt[LT_MDAY] > 0)
                return sprintf("%s%d-%d-%d/", BACKUP_DIR,
                               lt[LT_YEAR], lt[LT_MON], lt[LT_MDAY]);

        lt[LT_MON]--;
        switch (lt[LT_MON])
        {
        case 2:
                if ((lt[LT_YEAR] % 4) == 0 && (lt[LT_YEAR] % 100) != 0)
                        lt[LT_MDAY] += 29;
                else
                        lt[LT_MDAY] += 28;
                break;

        case 1: case 3: case 5: case 7: case 8: case 10:
                lt[LT_MDAY] += 31;
                break;

        case 4: case 6: case 9: case 11:
                lt[LT_MDAY] += 30;
                break;

        case 0: // last year
                lt[LT_MDAY] += 31;
                lt[LT_MON] = 12;
                lt[LT_YEAR] --;
        }

        return sprintf("%s%d-%d-%d/", BACKUP_DIR,
                       lt[LT_YEAR], lt[LT_MON], lt[LT_MDAY]);
}
