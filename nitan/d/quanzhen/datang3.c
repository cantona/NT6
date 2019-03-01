// datang3.c 大堂三進
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "大堂三進");
        set("long", @LONG
這裡是大堂的第三進，是全真教弟子議事的地方。全真教祖師王
重陽王真人最近閉關修煉，教內的俗事一般都交給大弟子馬鈺來處理。
遇有事時，馬真人便會召集六位師弟師妹，包括三代弟子中的部分大
弟子來到此地議事。
LONG
        );
        set("exits", ([
                "east" : __DIR__"laojundian",
                "south" : __DIR__"nairongdian",
                "west" : __DIR__"datang2",
                "north" : __DIR__"guozhendian",
        ]));
        set("objects", ([
                CLASS_D("quanzhen")+"/fang" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -2780);
        set("coor/y", 110);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}