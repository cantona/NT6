// Room: /d/songshan/danfang.c
// Last Modified by winder on Jul. 15 2001

#include <ansi.h>;
inherit ROOM;
void create()
{
        set("short", "丹房");
        set("long", @LONG
左冷禪既是一代武學宗師，刀圭之術亦甚是了得。他在對藥理也十
分精通。丹房內放置着數百隻白瓷瓶子裝着，貼上標籤，分門別類地放
在四周的藥架上。
LONG);
        set("exits", ([
                "east" : __DIR__"houting",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -30);
        set("coor/y", 930);
        set("coor/z", 90);
        setup(); 
        replace_program(ROOM);
}