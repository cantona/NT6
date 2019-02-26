// xiaohuayuan2.c 小花園
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "小花園");
        set("long", @LONG
這裏是重陽觀裏的小花園，種植着一些叫不出名字來的花木，
園角砌着一座假山，假山下是一潭小小的金魚池，池水清澈見底，
你看見有數條紅色的金魚在裏面悠哉遊哉地游來游去。幾個道童正
在這裏嬉戲着。
LONG
        );
        set("outdoors", "chongyang");
        set("exits", ([
                "east" : __DIR__"xiaohuayuan3",
                "west" : __DIR__"chanfang3",
                "southwest" : __DIR__"xiaohuayuan1",
        ]));
        set("objects", ([
                __DIR__"npc/daotong" : random(3),
        ]));

        set("coor/x", -2720);
        set("coor/y", 130);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}