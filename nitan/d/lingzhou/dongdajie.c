// Room: /lingzhou/dongdajie.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "東大街");
        set("long", @LONG
這是靈州東大街，同樣的寬闊與幹凈，相比西大街的冷清要熱鬧多
了，街上人來人往，熙熙攘攘，幾個小孩正在胡同口玩耍，南面有不少
人圍在一起，北面是衙門，路邊有條狗正在追一只貓。
LONG );
        set("exits", ([
                "south" : __DIR__"jiangjungate",
                "north" : __DIR__"yamen",
                "west"  : __DIR__"center",
                "east"  : __DIR__"dongmen",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6265);
        set("coor/y", 2925);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
