// Room: /d/gumu/zhongting.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "中廳");
        set("long", @LONG
這處是古墓派弟子參見掌門之處，此刻古墓傳人小龍女及神鵰大俠
楊過早已名頌江湖，這對璧人不但武功已成一派宗師，兩人矢志不渝之
深情更令世人傾慕不已。廳內只一張長桌，兩把石椅。
    廳上方有一塊匾額(bian).
LONG        );
        set("exits", ([
                "east"  : __DIR__"mudao06",
                "west"  : __DIR__"mudao05",
                "south" : __DIR__"mudao08",
                "north" : __DIR__"mudao17",
        ])); 
        set("item_desc", ([
                "bian" :  HIR"
             ※※※※※※※※※※※※※※※※※※※※
             ※※※※　                      ※※※※
             ※※※※    此情不悔 天荒地老   ※※※※
             ※※※※                        ※※※※
             ※※※※※※※※※※※※※※※※※※※※\n"NOR,
        ]));
        set("objects", ([
                CLASS_D("gumu")+"/longnv" : 1,
        ]));
        set("valid_startroom",1);
        set("coor/x", -3200);
        set("coor/y", 10);
        set("coor/z", 90);
        setup();
        "/clone/board/gumu_b"->foo();
}

void init()
{ 
        add_action("do_jump","zong");
        add_action("do_jump","tiao");
        add_action("do_jump","jump");
}

int do_jump(string arg)
{
        object me = this_player();

        if (arg!="bian")
                return notify_fail("要往哪裏跳？\n");
        if(me->query_skill("yunv-shenfa", 1) < 10)
                return notify_fail("你玉女身法功力不夠，跳不上匾額。\n");
        message_vision(HIY"$N凝氣守中，平空拔起數丈，輕輕落在匾額之後。\n"NOR,me);
        me->move(__DIR__"bianhou"); 
        return 1; 
}
