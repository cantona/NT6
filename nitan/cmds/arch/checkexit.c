// checkexit.c
// Created by jjgod
// Updated by Lonely (06/17/2002)
// 用於檢查一個目錄下的所有房間文件的出口連接是否正確
// 不包括該目錄的子目錄

#include <ansi.h>

inherit F_CLEAN_UP;

int help();

int main(object me, string arg)
{
        string info;
        int i;
        string *flist;
        string file;
        object rob;
        mapping exits;
        string *all_exit, *key;
        string exit;
        mapping errors;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg)
                return help();

        arg=resolve_path(query("cwd", me),arg);
        seteuid(getuid(me));
        
        if (file_size(arg) != -2)
                return notify_fail("沒有這個目錄。\n");

        info = HIR "正在檢查 " + arg + " 目錄下的房間文件：\n\n" NOR;
        
        message_system("整理批量檔案中，請稍候...");  
        if (! arrayp(flist = get_dir(arg + "/")) || ! sizeof(flist))
        {
                info += HIR "沒有任何可檢查的文件。\n" NOR;
                me->start_more(info);
                message_system("系統整理批量檔案處理完畢，請繼續遊戲。\n" ESC + "[K"); 
                return 1;
        }
        
        errors = ([ ]);
        for (i = 0; i < sizeof(flist); i++)
        {
                if (flist[i][strlen(flist[i])-2..strlen(flist[i])] != ".c")
                        continue;

                file = arg + "/" + flist[i];
                
                if (file_size(file) <= 0)
                        continue;
                // if (! objectp(rob = get_object(file)))
                if (! objectp(rob = find_object(file)))
                        rob = load_object(file);
                if (! objectp(rob))
                        continue;
                if (! rob->is_room())
                        continue;
                /*
                if (! inherits(ROOM, rob))
                        continue;
                */
                if( !mapp(exits=query("exits", rob)) || 
                    ! sizeof(exits))
                        continue;

                if (! i % 100)
                        reset_eval_cost();
                
                all_exit = keys(exits);
                foreach (exit in all_exit)
                {
                        if (file_size(exits[exit]) <= 0 &&
                            file_size(exits[exit] + ".c") <= 0)
                                errors[file] = exit;
                }
        }
        
        if (! sizeof(errors))
        {
                info += HIR "檢查完畢，沒有任何錯誤。" NOR;
                me->start_more(info);
                message_system("系統整理批量檔案處理完畢，請繼續遊戲。\n" ESC + "[K"); 
                return 1;
        }
        
        key = keys(errors);
        for (i = 0; i < sizeof(key); i++)
        {
                info += sprintf(CYN "文件 " WHT "%-30s" CYN " 的出口 " WHT "%-8s" CYN " 錯誤。\n" NOR,
                                key[i], errors[key[i]]);
        }
        
        info += HIR "\n檢查完畢。" NOR;
        me->start_more(info);
        message_system("系統整理批量檔案處理完畢，請繼續遊戲。\n" ESC + "[K"); 
        return 1;
}

int help()
{
        write(@HELP
指令格式：checkexit <目錄名>

檢查指定目錄下的房間文件的出口連接是否正確。
HELP
        );
        return 1;
}