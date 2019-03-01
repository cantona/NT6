// Room: /d/gaibang/undertree.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "雪坑小洞");
        set("long", @LONG
這裡是大雪山雪坑下的一個密洞。裡面破破爛爛的，丟滿各種
雜物，還有丐幫弟子收集的破銅爛鐵等。從這裡通往丐幫的秘密通
道。
LONG );
        set("exits", ([
                "out"  : "d/xuedao/hollow",
                "northeast" : __DIR__"xsandao2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -30000);
        set("coor/y", -10000);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}