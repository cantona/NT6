#include <ansi.h>
inherit ROOM;

int do_ci(string arg);
int do_zhan(string arg);

void create()
{
        set("short", "密室");
        set("long", @LONG
這裡是古墓中的密室，四周密不透風，你只能借著牆上昏暗的燈
光來勉強分辨方向。牆是用整塊的青石砌合起來的，接合的甚是完美，
你難以從中找出一絲縫隙。你正在欣賞，突然間發覺牆上似乎有幾塊
磚 (brick)高高凸起，與周圍的磚很不和諧。
LONG );

        set("exits", ([
                "up" : __DIR__"hanshuitan",
        ]));

        set("item_desc", ([
        "brick": HIC "\n幾塊普通的青磚，看不出有什麼特別的。\n" NOR,
        ]) );

        setup();
}

void init()
{
        add_action("do_ci", "ci");
        add_action("do_zhan", "zhan");
}


int do_ci(string arg)
{
        object me=this_player();
        object weapon;

        if( !arg || arg != "brick" ) {
                return notify_fail("你要刺什麼？\n");
        }

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("要刺牆不用家伙恐怕不行吧！\n");

        message_vision(HIG "\n$N" HIG "拔出兵刃，向青磚輕輕刺去，只聽得空空作聲，青磚"
                       "的另一頭仿佛是空的。\n", this_player());

        set_temp("tmarks/磚", 1, me);
        return 1;
}

int do_zhan(string arg)
{
        object me=this_player();

        if( !arg || arg != "brick" || query_temp("tmarks/磚", me)<1 ) {
                return notify_fail("你要粘住什麼？\n");
        }

        message_sort(HIC "\n$N" HIC "雙手緊貼青磚，使個‘粘’字訣，輕輕巧巧"
                     "地將這塊青磚粘了出來。如此沒粘到幾塊磚，牆壁上就現出了"
                     "一個大洞。\n" NOR,this_player());

        set("exits/down",__DIR__"houting");

        remove_call_out("close");
        call_out("close", 5, this_object());

        set_temp("tmarks/磚", 0, me);
        return 1;

}

void close(object room)
{
        message("vision", NOR + WHT"\n過不多一會兒，樑上落下幾塊青磚，又"
                "將牆上的洞遮住了。\n" NOR, room);

        delete("exits/down", room);
}
