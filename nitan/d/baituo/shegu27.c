//Cracked by Roath
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        int i;

        set("short", "山溝");
        set("long", @LONG
這是一個馬蹄形的溝谷，三邊崖壁上長滿了筆直的白楊和雲杉，
古木間瀑布直落，宛如銀龍下竄，水花飛散，把你的衣服都打濕了。
這裏旁臨深淵，前面是陡峭的崖壁，已是蛇谷的盡頭，沒有道路可走
了。
LONG );

        set("exits", ([
            "south" : __DIR__"shegu26",
        ]));

        i = random (50);

        if( i < 20 )
        set("objects", ([
           // "/clone/drug/lingzhi" : 1,
           "/clone/drug/danggui" : 1,

        ]));

        else if( i < 30 ) set("objects", ([
            __DIR__"obj/branch4" : 1,
            __DIR__"npc/maque" : 1,
        ]));

        else if( i < 40 ) set("objects", ([
            __DIR__"npc/bt_snake" : 2,
        ]));

        else set("objects", ([
            __DIR__"obj/branch1" : 1,
            __DIR__"npc/pu_snake" : 1,
        ]));

        set("cost", 1);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49980);
        set("coor/y", 20230);
        set("coor/z", 20);
        setup();
}

void init()
{
        set("enter_shegu", 1, this_player());
}