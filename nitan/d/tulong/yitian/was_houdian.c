#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "後殿");
        set("long", @LONG
這裡是萬安寺的後殿，非常的寬敞明亮，佛像前擺著一個供桌，桌上的香爐
中插著幾柱香，地上擺著一些蒲團。右首處一個木制階梯，可以通向萬安寺的寺
樓。
LONG );
        set("exits", ([
            "south"  : "/d/tulong/yitian/was_zoulang3",
            "up"    : "/d/tulong/yitian/was_lou2",
        ]));

        set("objects", ([
            "/d/tulong/yitian/npc/18jingang-5dao" :5,
        ]));
        setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "up" && objectp(present("dao seng", environment(me))))
           return notify_fail(CYN "刀僧齊聲喝道：哪裡走？滾下來！\n" NOR);

        if (dir == "south" && objectp(present("dao seng", environment(me))))
           return notify_fail(CYN "刀僧齊聲喝道：哪裡逃？納命來！\n" NOR);

        return ::valid_leave(me, dir);
}
