// Room: /d/huijiang/yixiangting.c
// Last Modified by winder on Sep. 12 2001

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short","憶香亭");
        set("long",@LONG
這是一個精巧別致的小亭，上書“憶香亭”三個字，清秀挺拔宛然
便是陳家洛的手筆。旁邊幾行小字寫的是：“碧亦有時滅，血亦有時滅，
一縷香魂無斷絕！是耶非耶？化為蝴蝶。”陳家洛心中想念香香公主的
時候，常一個人來此獨坐。
LONG );
        set("outdoors", "huijiang");
        set("exits", ([
                "east" : __DIR__"zoulang2",
        ]));
        set("objects", ([
                CLASS_D("honghua")+"/chen-jialuo" : 1,
                __DIR__"obj/xiangcha" : 2,
                __DIR__"obj/dianxin" : 1,
        ]));
        set("coor/x", -50080);
        set("coor/y", 9140);
        set("coor/z", 10);
        setup();
}

void init()
{
        object me = this_player();
        tell_object(me,        "                         ");
        tell_object(me,        YEL"┌───┐\n"NOR);
        tell_object(me,        "                         ");
        tell_object(me, YEL"│"NOR);
        tell_object(me, HIG"憶香亭"NOR);  
        tell_object(me, YEL"│\n"NOR);
        tell_object(me,        "                         ");
        tell_object(me,        YEL"└───┘\n"NOR);
}