// Room: /d/gaibang/underdl.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "大和街邊");
        set("long", @LONG
這是大理城中大和街邊上的大樹洞。裏面破破爛爛的，丟滿了各種
雜物，還有丐幫弟子收集的破銅爛鐵等。從這裏通往丐幫的祕密通道。
LONG );
        set("exits", ([
                "out"       : "/d/dali/dahejieeast",
                "northeast" : __DIR__"dlandao2",
        ]));
        set("objects", ([
                "/clone/npc/mu-ren" : 4,
                "/clone/misc/bone"  : 2,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -39900);
        set("coor/y", -71030);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}