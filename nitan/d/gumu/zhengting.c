// zhengting.c 正廳
// Java Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "正廳");
        set("long", @LONG
這裏是古墓的正廳，本來應該停放靈柩棺木之類的東西，卻不知道
被人般到哪裏去了。廳正中端擺着一張大石椅，廳角上擺放着一些石頭
做成的櫥櫃，中間是一張大石桌。
LONG        );
        set("exits", ([
                "west"  : __DIR__"mudao15",
                "east"  : __DIR__"mudao14",
                "north" : __DIR__"mudao11",
                "south" : __DIR__"mudao16",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3200);
        set("coor/y", -40);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}
