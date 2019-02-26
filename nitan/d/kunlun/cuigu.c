// Room: /d/kunlun/cuigu.c
// Last Modified by winder on Jun. 29 2001

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", HIG"翠谷"NOR);
        set("long", @LONG
出得洞來，面前竟是個花團錦簇的翠谷，紅花綠樹，交相掩映。腳
下踏著的是柔軟細草，鼻中聞到的是清幽花香，鳴禽間關，鮮果懸枝，
哪想得到在這黑黝黝的洞穴之後，竟會有這樣一個洞天福地？離地丈許
高處有一山洞(dong)。
LONG );
        set("outdoors", "hongmei");
        set("exits", ([
                "west"    : __DIR__"pubu",
                "south"   : __DIR__"xianjing",
                "eastup"  : __DIR__"shanbi",
        ]));
        set("item_desc", ([
                "dong": "一個不知深淺的山洞。\n",
        ]));
        set("objects", ([
                __DIR__"npc/sheep" : 2,
        ]));
        set("coor/x", -100000);
        set("coor/y", 20050);
        set("coor/z", 40);
        setup();
}
void init()
{
        add_action("do_enter","enter");
}
int do_enter(string arg)
{
        object me = this_player();
        int n=query("str", me);
        if( !arg || arg != "dong")
        {
                write("你想幹什麼呀?\n");
                return 1;
        }
        message_vision("$N深吸了一口氣，慢慢沿着洞壁往外爬。\n", me);
        me->move(__DIR__"pingtai");
        return 1;
}
