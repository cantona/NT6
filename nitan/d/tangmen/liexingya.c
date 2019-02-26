//liexingya.c                四川唐門—裂星崖

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "裂星崖");
        set("long",
"這裏是蓮藕小築後山的裂星崖。據説唐門的開山祖師？？？就是在這\n"
"裏靜坐五年，夜觀星變，終於悟出了威鎮江湖的唐門暗器絕技？？？？，\n"
"一株萬年古鬆自山崖外長了上來，高聳入雲。\n"
);
//？？，一株萬年古鬆(shu)自山崖外長了上來，高聳入雲。
        set("exits", ([
                        "southdown" : __DIR__"shandao5",
        ]));
        set("item_desc", ([
                "shu" : "這株古鬆據説是萬年前盤古開天時生長而成的。\n",
        ]));
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
        object ob;
        ob = this_player();

        if ( arg && arg == "shu" )
        {
                if ( (int)ob->query_skill("dodge", 1) < 21 && (int)ob->query_skill("finger", 1) < 21 )
                {
                        tell_object(ob, HIR "你的功夫還不夠高，爬上去恐怕會摔死的。\n" NOR, ob);
                        return 1;
                }

                message_vision(HIC "$N攀着繁茂的樹枝一步步爬了上去。\n" NOR, ob);
                ob->move(__DIR__"shugan1");
                return 1;
        }
        else
                return notify_fail("你要向哪裏爬？\n");
}