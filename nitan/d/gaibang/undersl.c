// Room: /d/gaibang/undersl.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "屋角邊");
        set("long", @LONG
這是老喬家廚房大木柴堆下面。裡面破破爛爛的，丟滿了各種雜
物，還有丐幫弟子收集的破銅爛鐵等。從這裡通往丐幫的秘密通道。
LONG );
        set("exits", ([
                "up"        : "/d/shaolin/chufang2",
                "southwest" : __DIR__"slandao2",
        ]));
        set("objects",([
                CLASS_D("gaibang") + "/he-bj" : 1,
                "/clone/npc/mu-ren" : 4,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -20);
        set("coor/y", 720);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}