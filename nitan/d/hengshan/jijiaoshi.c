// Room: /d/hengshan/jijiaoshi.c
// Date: Oct. 2 1997 by That

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "雞叫石");
        set("long", @LONG
北嶽廟的西側，有一尺許見方的石頭，稱雞叫石。擊之，“咯咯”
作雞鳴聲，故名。清晨敲擊，引起山谷回聲，如羣雞爭鳴，就稱“金雞
報曉”。
LONG);
        set("exits", ([ /* sizeof() == 4 */
                "east"  : __DIR__"beiyuemiao",
        ]));
        set("outdoors", "hengshan");
        set("no_clean_up", 0);
        set("coor/x", 20);
        set("coor/y", 3170);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}
