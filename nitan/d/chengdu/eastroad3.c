// Room: eastroad3.c
// Date: Feb.14 1998 by Java

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "東大街");
        set("long", @LONG
你走在東大街上，踩著堅實的青石板地面。向北是一條寬直的大
道。北邊可以通往東城門，西南邊通向南大街，東南方就是有名的望
江樓了。東邊則是大名鼎鼎的俠義盟成都分部。不遠處有一幢破爛的
房屋，但是屋子的門樑 (liang)已經垮塌，把門封了個嚴實。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "southeast"  : __DIR__"wangjianglou",
            "southwest"  : __DIR__"southroad1",
            "north"      : __DIR__"eastroad2",
            "east"      : __DIR__"xym_cdfb",
        ]));

        set("item_desc", ([
                    "liang" : "房子的門樑垮塌，將門封了個嚴實。\n",
        ]) );

//        set("no_clean_up", 0);
        set("coor/x", -15200);
	set("coor/y", -1840);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_break", "break");
}

int do_break(string arg)
{
        int n;
        object weapon, me = this_player();

        if (arg != "liang")
                return 0;

        if (query("break"))
                return notify_fail("房樑已經被震飛，用不著再費力了。\n");

        message_vision(HIY "$N" HIY "走到房前，運氣雙掌，猛地擊"
                       "向垮塌的房樑！\n" NOR, me);

        if( query("max_neili", me)<1000 )
        {
               message_vision(HIR "結果只聽一聲悶哼，$N" HIR "內"
                              "力不濟，被房樑反震，眼前頓時一黑…"
                              "…\n" NOR, me);
               set("neili", 0, me);
               me->unconcious();
               return 1;
        }

        message_vision(HIY "只聽一聲轟響，房樑頓時被$N" HIY "震"
                       "得飛起，露出了大門！\n" NOR, me);

        set("exits/enter", __DIR__"minju");
        set("neili", 0, me);
        set("break", 1);
        return 1;
}