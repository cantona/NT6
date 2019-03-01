// Room: /binghuo/pingyuan1.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "平原");
        set("long", @LONG
這裡是十來裡方圓的平原，此處竟有大片土地可供奔馳，實是說
不出的快活。沿途所見，除了低丘高樹之外，盡是青草奇花。草叢之
中，偶爾驚起一些叫不出名目的大鳥小獸，看來也皆無害于人。向北
轉過一大片樹林，只見西北角上似乎是一座石山。
LONG );
        set("outdoors", "binghuo");
        set("no_clean_up", 0);
        set("exits", ([
                "south"  : __DIR__"haitan",
                "north"  : __DIR__"shulin3",
        ]));
        setup();
        replace_program(ROOM);
}
