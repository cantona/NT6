#include <ansi.h>
inherit ROOM;

int do_open(string arg);

void create()
{
        set("short", "山崖");
        set("long",
"映照在陽光白雲之間的，是一座巍峨之極的大城。只見城牆
高逾三丈，牆頭牆垣雪白一片，盡是冰雪。城牆上隱隱有人頭晃
動，城頭樹著一面在罡風中招展的大旗，城樓上面寫著三個大字

            " WHT "※※※※※※※※※※※※※※※※
            ※                            ※
            ※" NOR + HIW "     凌      霄      城" NOR + WHT "     ※
            ※                            ※
            ※※※※※※※※※※※※※※※※" NOR "

城門前有一張厚厚的吊橋(bridge)正緊緊關閉著。如果想要進入
的話，必須要請人開(open)才行。\n");

        set("outdoors", "lingxiao");
        set("exits", ([
                    "east"  : __DIR__"cityout",
                    "west"  : __DIR__"cityout1",
                    "down"  : __DIR__"bingti",
        ]));

        set("item_desc", ([
                "bridge" : WHT "\n這是一張極大的吊橋，乃是凌霄城的一道防線。\n" NOR,
        ]) );
        setup();
}

void init()
{
        add_action("do_open","open");
}

int do_open(string arg)
{
        object me=this_player();

        if (! arg || arg != "bridge" )
                return notify_fail("你要幹嘛？\n");

        message_vision(HIY "\n$N" HIY "運足力氣，大叫一聲：“開門"
                       "呀！”\n" NOR, this_player());

        message_vision(HIY "只聽得城上有人說道：“有人來了，放吊橋"
                       "吧。”\n\n" NOR + HIC "只聽得“軋軋軋”響"
                       "了片刻，吊橋緩緩放下，露出一個方方正正的城"
                       "門來。\n" NOR, this_player());

        set("exits/north", __DIR__"gate");
        remove_call_out("close");
        call_out("close", 10, this_object());

        return 1;
}

void close(object room)
{
        message("vision", HIY "只聽“嘎嘎嘎嘎”幾聲，吊橋又被關了"
                          "起來。\n" NOR, room);
        delete("exits/north", room);
}
