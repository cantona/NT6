// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// alarm.c

#include <ansi.h>
inherit F_CLEAN_UP;

#define SHOUT_LIST      ({ })

int help(object me);
void create() {seteuid(getuid());}


int main(object me, string arg)
{
        object ob;
        string target, msg, mud,from;
        object obj;

        if (! SECURITY_D->valid_grant(me, "(immortal)"))
                return 0;
                        
        if (! arg || sscanf(arg, "%s %s", target, msg) != 2) 
                return help(me);
                
        obj = find_player(target);
        write(HIG "\n 你警告" + obj->name(1) + "，因其" + msg + "的行為。 \n" NOR);
        
        tell_object(obj, sprintf( HIR "\n 遊戲管理者警告你：\n \n \n \n" + "      你的" HIW "「%s」" HIR "行為違反了遊戲規則，請輸入"HIW" help rules "HIR"查詢遊戲規則，特此警告。\n \n"+"      如有任何問題，請立刻申訴。若有再犯，將按照規則處理。\n \n \n \n \n \n" NOR, msg));

        if (! wizardp(me) && member_array(query("id", me), SHOUT_LIST) == -1)
                return notify_fail("目前暫不開放玩家 shout。\n");
                
        if (! arg) return notify_fail("你想要大叫什麼？\n");

        shout( HIG "【系統信息】泥潭公告："+ obj->name(1) + "因為" + msg + "被系統警告。\n" NOR );
        write( HIG "【系統信息】泥潭公告："+ obj->name(1) + "因為" + msg + "被系統警告。\n" NOR );

        return 1;
}




int help(object me)
{
        write(@HELP
指令格式：alarm <某人> <訊息>
你可以用這個指令警告違反規則的玩家。
同時神仙保留不經警告就直接處理違規玩家的權利。
HELP
        );
        return 1;
}
