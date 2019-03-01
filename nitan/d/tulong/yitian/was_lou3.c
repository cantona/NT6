#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "萬安寺第三層");
        set("long", @LONG
這裡是萬安寺的第三層，寺樓裡站著幾個身著火紅袈裟的和尚。一見你上樓，
立馬向你撲來。
LONG );
        set("exits", ([
            "down"  : "/d/tulong/yitian/was_lou2",
            "up"    : "/d/tulong/yitian/was_lou4",
        ]));

        set("objects", ([
            "/d/tulong/yitian/npc/18jingang-5jian" :5,
        ]));
        setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "up" && objectp(present("jian seng", environment(me))))
           return notify_fail(CYN "劍僧齊聲喝道：哪裡走？滾下來！\n" NOR);

        if (dir == "down" && objectp(present("jian seng", environment(me))))
           return notify_fail(CYN "劍僧齊聲喝道：哪裡逃？納命來！\n" NOR);

        return ::valid_leave(me, dir);
}
