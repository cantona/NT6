#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在一條青石大道上，四周靜悄悄的。四周是濃密的樹
林，陰森森的十分怕人。西北方不遠就是陝鄂的邊界了。北邊
卻是一片草地。你抬頭向遠方眺望，隱隱約約能夠看到武當山
的影子，只令人想飛奔而上。
LONG);
        set("outdoors", "sanbuguan");
        set("exits", ([
            "northwest" : __DIR__"wdroad6",
            "north"     : "/d/xiangyang/caodi6",
            "east"      : __DIR__"wdroad4",
            "southdown" : "/d/jingzhou/jzbeimen",
        ]));
        setup();
}

void init()
{
        add_action("do_float", "float");
        add_action("do_float", "piao");
}

int do_float()
{
        object me;

        me = this_player();

        if (me->query_skill("tiyunzong", 1) < 160 ||
            me->query_skill("dodge", 1) < 160)
        {
                message_vision("$N跳了跳，原地蹦噠了一會兒。\n", me);
                return 1;
        }

        if( query("neili", me)<150 )
        {
                tell_object(me, "你的內力不夠，還是休息一下再説吧。\n");
                return 1;
        }

        addn("neili", -120, me);

        message_sort(HIC "\n$N" HIC"深吸一口氣，邁開大步，雙足"
                     "如飛，踩着山間雜草，飄然而起，直奔那武當"
                     "山去了！轉瞬不見，只留下遠遠一個影子。\n"
                     "\n" NOR, me);
        me->move("/d/wudang/guangchang");
        tell_object(me, "片刻，你已經飛身上了武當山上。\n");
        message("vision", "只見一陣清風掠過，" + me->name() +
                "已經飄然而至。\n", environment(me), ({ me }));
        return 1;
}
