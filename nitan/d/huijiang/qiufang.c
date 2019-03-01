// Room: /d/huijiang/qiufang.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "囚房");
        set("long",@LONG
這裡是紅花會關押叛徒和清狗的地方。門口大開著，也不怕要犯逃
跑掉。房間倒是打掃的很幹凈。鐵窗上一絲蛛蛛網也見不著。
LONG );
        set("exits", ([
                "north" : __DIR__"zoulang3" ,
        ]));
        set("objects", ([
                CLASS_D("honghua")+"/jiang-sigen" : 1,
        ]));        
        set("coor/x", -50050);
        set("coor/y", 9130);
        set("coor/z", 10);
        setup();
}

int valid_leave(object me, string dir)
{
        if ( (dir == "north") &&
                (query("family/family_name", me) != "紅花會") && 
                objectp(present("jiang sigen", environment(me))) &&
                (!present("honghua ling", me)))
        {
                me->receive_damage("qi", 15);
                me->receive_damage("jing", 5);
                return notify_fail("蔣四根攔住你說：非本會弟兄，私闖囚房，一定是清狗！\n"HIR"蔣四根不分青紅皂白，先海扁了你一頓。\n"NOR);
        }
        return ::valid_leave(me, dir);
}