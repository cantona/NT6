// /d/shenlong/wuchang.c
// Last Modified by winder on Aug. 18 2002
 
inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
這是一個寬大的練武場，有幾個手執短劍的少年少女在這裏練功。
旁邊站着幾人，有男有女，年紀輕的三十來歲，老的已有六七十歲，身上
卻不帶兵刃。南邊是一條走廊。
LONG );
        set("exits", ([
                "south" : __DIR__"zoulang",
        ]));
        set("objects", ([
                "/d/shaolin/npc/mu-ren": 5,
        ]));
        setup();
        replace_program(ROOM);
}
