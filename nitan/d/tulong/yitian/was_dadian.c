#include <ansi.h>

inherit ROOM;


void create()
{
        set("short", "大殿");
        set("long", @LONG
這裏是萬安寺的大殿，非常的寬敞明亮，這裏本是萬安寺眾僧早晚課之處，
佛像前擺着一個供桌，桌上的香爐中插着幾柱香。地上擺着一些蒲團。幾個和尚
盤膝做在上面。左右兩旁是兩個偏殿。
LONG );
        set("exits", ([
                "north" : "/d/tulong/yitian/was_zoulang3",
                "south" : "/d/tulong/yitian/was_zoulang2",
                "east" : "/d/tulong/yitian/was_piandiane",
                "west" : "/d/tulong/yitian/was_piandianw",
        ]));

        set("objects", ([
            "/d/tulong/yitian/npc/18jingang-4bo" :4,
        ]));

        setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "north" && objectp(present("bo seng", environment(me))))
           return notify_fail(CYN "鈸僧齊聲喝道：哪裏走？滾下來！\n" NOR);

        if (dir == "south" && objectp(present("bo seng", environment(me))))
           return notify_fail(CYN "鈸僧齊聲喝道：哪裏逃？納命來！\n" NOR);

        if (dir == "west" && objectp(present("bo seng", environment(me))))
           return notify_fail(CYN "鈸僧齊聲喝道：哪裏逃？納命來！\n" NOR);

        if (dir == "east" && objectp(present("bo seng", environment(me))))
           return notify_fail(CYN "鈸僧齊聲喝道：哪裏逃？納命來！\n" NOR);

        return ::valid_leave(me, dir);
}

void reset()
{
        object ob;

        ::reset();

        foreach (ob in all_inventory(this_object()))
        {
                if (ob->is_character() ||
                    ob->is_head() ||
                    ob->is_corpse() ||
                    query("no_get", ob) )
                        continue;
                destruct(ob);
        }
        
        return;
}
