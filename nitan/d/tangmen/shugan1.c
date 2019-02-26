//shugan1.c                四川唐門—裂星崖古樹

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "參天古樹");
        set("long",
      "這是萬年古鬆的樹頂。當年祖師爺？？？曾在這裏日觀雲動，夜觀星\n" 
      "變，最終悟出了？？？？的唐門絕學，因此很多弟子常常在這裏日夜靜坐。\n" 
);
        set("area", "tangmen");
        setup();
}

void init()
{
        add_action("do_climb","climb");
        add_action("do_climb","pa");
}

int do_climb(string arg)
{
        object ob, room;

        ob = this_player();

        if ( arg && arg=="up" )
        {
                message_vision(HIC "$N攀着繁茂的樹枝一步步爬了上去。\n" NOR, ob);

                if ( (int)ob->query_skill("dodge", 1) < 31 && (int)ob->query_skill("finger", 1) < 31 )
                {
                        message_vision(HIR "$N腳下一滑，手上沒抓緊，仰天摔了下來。\n" NOR, ob);
                        addn("qi", -10, ob);
                        return 1;
                }

                ob->move(__DIR__"shugan2");
                return 1;
        }
        else
                if ( arg && arg=="down" )
                {
                        message_vision(HIC "$N攀着繁茂的樹枝小心翼翼的爬了下去。\n" NOR, ob);
                        ob->move(__DIR__"liexingya");
                        return 1;
                }
                else
                        return notify_fail("你要向哪裏爬？\n");
}