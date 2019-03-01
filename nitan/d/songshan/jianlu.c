// Room: /d/songshan/jianlu.c
// Last Modified by Winder on Jul. 15 2001

#include <ansi.h>
inherit ROOM;
int do_zong(string arg);

void create()
{
        set("short", "劍廬");
        set("long", @LONG
這是一間凈室，室內一物不設。窗外偶爾光線斜入，映見正中樑頂
似乎存放著一些物事。
LONG );
        set("sword_count", 1);
        set("exits", ([ /* sizeof() == 2 */
                "west" : __DIR__"eastting",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 10);
        set("coor/y", 900);
        set("coor/z", 90);
        setup();
}
void init()
{
        add_action("do_zong", "zong");
        add_action("do_zong", "tiao");
        add_action("do_zong", "jump");
}
int do_zong(string arg)
{
        object ob, me= this_player();
        if (arg != "sword" && arg != "liang") return 0;
        if( (int)me->query_dex() < 38 )
                return notify_fail("你縱起身形，一掠而起，就差一點就可以夠到樑了，真是可惜。\n");
        if (query("sword_count") < 1)
                return notify_fail("你縱起身形，一掠而起，伸手往樑上一摸，卻不料摸了一個空。\n");
        addn("sword_count", -1);
        ob = new(WEAPON_DIR"treasure/zhanlu-jian");
        if ( ob->violate_unique() )
        {
                destruct( ob );
                return notify_fail("你縱起身形，一掠而起，伸手往樑上一摸，卻不料摸了一個空。\n");
        }
        ob->move(me);
        message_vision("$N縱起身形，一掠而起，伸手往樑上一摸，一個鷂子翻身輕輕落地，手上多了一把外形古樸的長劍。\n", me);
        return 1;
}