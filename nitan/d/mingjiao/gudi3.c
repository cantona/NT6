// Room: /d/mingjiao/gudi3.c

inherit ROOM;

void create()
{
        set("short", "崑崙仙境");
        set("long", @LONG
出得洞來，面前竟是個花團錦簇的翠谷，紅花綠樹，交相掩映。
腳下踏著的是柔軟細草，鼻中聞到的是清幽花香，鳴禽間關，鮮果懸
枝，哪想得到在這黑黝黝的洞穴之後，竟會有這樣一個洞天福地？離
地丈許高處有一山洞(dong)。
LONG );
        set("outdoors", "mingjiao");
        set("exits", ([
                "west"  : __DIR__"gudi5",
                "south" : __DIR__"gudi4",
        ]));
        set("item_desc", ([
                "dong": "一個不知深淺的山洞。\n",
        ]));
        set("objects", ([
                __DIR__"npc/sheep" : 2,
        ]));
        setup();
}
void init()
{
        add_action("do_enter","enter");
}
int do_enter(string arg)
{
        object me = this_player();

        if( !arg || arg != "dong")
        {
                write("你想幹什麼呀?\n");
                return 1;
        }
        message_vision("$N深吸了一口氣，慢慢沿着洞壁往外爬。\n", me);
        me->move(__DIR__"gudi2");
        return 1;
}