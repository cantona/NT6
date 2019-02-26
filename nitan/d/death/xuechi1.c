#include <ansi.h>
inherit ROOM; 

void create() 
{ 
        set("short", HIR "血池地獄" NOR);
        set("long", HIR @LONG
血池地獄，你疑心怎麼從酆都走到這裏來了的。四處瀰漫着濃厚的
血霧，你什麼也看不清楚，空中浮動着若隱若現的鬼火，血池裏到處是
死人肉和沸騰的鮮血，十分恐怖。

LONG NOR);
        set("no_clean_up", 0);
        
        set("exits", ([ /* sizeof() == 2 */
                "south" : __DIR__"yanluodian",
                "down"  : "/d/death/xuechi2",
        ]));
       
        set("no_magic", 1);
        setup();
}

int valid_leave(object me, string dir)
{
        int i;
        object ob;
        me = this_player();
        if (dir == "down")
        {
                if (! present("qilin xue", me) || 
                    !objectp(ob=query_temp("armor/boots", me)) || 
       query("id", ob) != "qilin xue" )
                        return notify_fail(CYN "你沒有穿麒麟靴無法進入沸騰的血池中！\n" NOR);
        }
        return ::valid_leave(me, dir);
}
