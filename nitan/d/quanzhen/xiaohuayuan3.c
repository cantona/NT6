// xiaohuayuan3.c 小花園
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "小花園");
        set("long", @LONG
這裡是重陽觀裡的小花園，種植著一些叫不出名字來的花木，
園角砌著一座假山，假山下是一潭小小的金魚池，池水清澈見底，
你看見有數條紅色的金魚在裡面悠哉遊哉地遊來遊去。幾個道童正
在這裡嬉戲著。
LONG
        );
        set("outdoors", "chongyang");
        set("exits", ([
                "west" : __DIR__"xiaohuayuan2",
        ]));

        set("objects", ([
                __DIR__"npc/daotong" : random(2),
        ]));

        set("coor/x", -2710);
        set("coor/y", 130);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}