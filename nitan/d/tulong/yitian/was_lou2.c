#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "萬安寺第二層");
        set("long", @LONG
這裡是萬安寺的第二層，寺樓裡站著幾個身著火紅袈裟的和尚。一見你上樓，
立馬向你撲來。
LONG );
        set("exits", ([
            "down"  : "/d/tulong/yitian/was_houdian",
            "up"    : "/d/tulong/yitian/was_lou3",
        ]));

        set("objects", ([
            "/d/tulong/yitian/npc/18jingang-4zhang" :4,
        ]));
        setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "up" && objectp(present("zhang seng", environment(me))))
           return notify_fail(CYN "杖僧齊聲喝道：哪裡走？滾下來！\n" NOR);

        if (dir == "down" && objectp(present("zhang seng", environment(me))))
           return notify_fail(CYN "杖僧齊聲喝道：哪裡逃？納命來！\n" NOR);

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
