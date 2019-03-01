// Room: /d/huangshan/kuzhu.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "苦竹溪");
        set("long", @LONG
沿途盛產苦竹，所以溪水也有淡淡的澀味，但是良藥苦口，苦竹更
是入藥的上品，所以來往之人依然愛飲此泉，對于解乏提神極有幫助。
更有人特地來此取竹根入藥。于是便有山民在此伐竹販賣。
LONG
        );
        set("exits", ([ 
                "westup" : __DIR__"jiulong",
        ]));
        set("objects", ([
                __DIR__"npc/snake" : 2,
        ]) );
        set("item_desc", ([
                "苦竹溪": "你可以試著從溪（xi）中喝（drink）一口。\n",
                "kuzhuxi": "你可以試著從溪（xi）中喝（drink）一口。\n"
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -575);
        set("coor/y", -1080);
        set("coor/z", -20);
        setup();
}
init()
{
        add_action("do_drink","drink");
        add_action("do_climb","climb");
}
int do_drink(string arg)
{
        object me = this_player();

        if(!arg || arg != "xi") return 0;
        if( query("water", me) >= me->max_water_capacity() )
                return notify_fail("你似乎並不渴。\n");
        message_vision("$N彎下腰，在苦竹溪中喝了一大口苦水！\n",me);
        addn("water", 50, me);
        return 1;
}

int do_climb(string arg)
{
        object         me;
        int mlvl;

        if(!arg || arg != "up")
        {
                write("你要往哪裡爬？\n");
                return 1;
        }
        me = this_player();
        message_vision("\n$N慢慢地向上爬去。\n",me);
        me->start_busy(4);
        call_out("fliping",4,me);
        me->stop_busy();
        return 1;
}

int fliping(object me)
{
        if( !me->is_ghost())
        {
                me->move(__DIR__"huangshan");
                message_vision("$N順著崖壁爬了上來。\n", me);
        }
        return 1;
}