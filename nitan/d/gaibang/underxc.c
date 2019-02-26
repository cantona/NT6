// Room: /d/gaibang/undertree.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "穀場槐樹邊");
        set("long", @LONG
這是穀場槐樹邊的谷堆，四周都是大谷堆。四周丟滿了各種
雜物，還有丐幫弟子收集的破銅爛鐵等。從這裏通往丐幫的祕密
通道。
LONG );
        set("exits", ([
                "up"    : "/d/village/square",
                "south" : __DIR__"xcandao2",
        ]));
        set("objects",([
                CLASS_D("gaibang") + "/ma-jw" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -970);
        set("coor/y", 270);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}