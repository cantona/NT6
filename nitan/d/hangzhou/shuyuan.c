// shuyuan.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "鳳池書院");
        set("long", @LONG
書院正中有一匾“鳳池書院”。書院裡坐著兩位老者，他們正在
吟詩作對。他們身旁的桌上舖著宣紙和筆墨。
LONG);
        set("exits", ([
            "west"      : __DIR__"road12",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 840);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}