// Room: /d/gaibang/undertree.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "沙丘小洞");
        set("long", @LONG
這裏是沙丘石碑下的一個密洞。裏面破破爛爛的，丟滿了各種
雜物，還有丐幫弟子收集的破銅爛鐵等。從這裏通往丐幫的祕密通
道。
LONG );
        set("exits", ([
                "west" : "d/xingxiu/silk5",
                "east" : __DIR__"xxandao2",
        ]));
        set("objects",([
                CLASS_D("gaibang") + "/yu-hx" : 1,
        ]));
        set("coor/x", -21990);
        set("coor/y", 1000);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}