// shiweishi.c 事為室
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "事為室");
        set("long", @LONG
這裡是全真七子之首馬鈺的居室。房間很小，只擺放了一張床、
一張書桌和一把椅子。書桌上放著一本‘老子’，只看了一半，床上
被褥折疊得整整齊齊。
LONG
        );
        set("exits", ([
                "south" : __DIR__"cetang",
        ]));

        set("objects", ([
                CLASS_D("quanzhen")+"/ma" : 1,
        ]));
        set("coor/x", -2790);
        set("coor/y", 130);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}