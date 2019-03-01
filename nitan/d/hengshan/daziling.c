// Room: /d/hengshan/daziling.c
// Date: Oct. 2 1997 by That

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "大字嶺");
        set("long", @LONG
大字嶺是入恆山必由之路。石壁上鐫有 "恆宗" 二字，高可兩丈，
筆力遒勁，氣勢雄渾。
LONG);
        set("exits", ([ /* sizeof() == 4 */
                "west"      : __DIR__"yunge",
                "northeast" : __DIR__"hufengkou",
        ]));
        set("outdoors", "hengshan");
        set("no_clean_up", 0);
        set("coor/x", 10);
        set("coor/y", 3140);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}
