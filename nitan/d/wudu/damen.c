#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "五毒教大門");
        set("long", @LONG
這裏是一座隱沒于山林中的大宅院，高高的圍牆，硃紅色的大門，
好像是一座有錢人家的避暑別院。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "east" : __DIR__"lianwu",
                "west" : __DIR__"wdsl7",
        ]));
        set("objects", ([
                __DIR__"npc/jiaotu": 4,
                CLASS_D("wudu") + "/jiaotou" : 1,
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        object sha;

        if (dir != "east" ||
            ! objectp(sha = present("sha qianli", this_object())))
                return ::valid_leave(me, dir);

        return sha->permit_pass(me, dir);
}