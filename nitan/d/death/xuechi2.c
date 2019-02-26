#include <ansi.h>
inherit ROOM; 

void create() 
{ 
        set("short", HIR "血池地獄" NOR);
        set("long", HIR @LONG
血池地獄，你疑心怎麼從酆都走到這裏來了的。四處瀰漫着濃厚的
血霧，你什麼也看不清楚，空中浮動着若隱若現的鬼火，血池裏到處是
死人肉和沸騰的鮮血，十分恐怖，只見神獸玄武正在吃着死人肉。

LONG NOR);
        set("no_clean_up", 0);
        set("objects", ([
                __DIR__"npc/xuanwu" : 1,
        ]));

        set("exits", ([ /* sizeof() == 2 */
                "up"  : "/d/death/xuechi1",
        ]));
       
        set("no_magic", 1);
        setup();
}