#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIR "【 地 陰 】" NOR);
        set("long", HIR @LONG

                       地            陰

    這裡便是陰間的最深處「地陰」，你面前是一個無底深淵，深淵內
側懸浮著一塊血紅色的巨大晶體(jingti)，時明時暗，散發出暗淡的血
紅色光芒，投射著絲絲熱量。也許這就傳說中的「地陰血脈」吧。

LONG NOR );
        set("exits", ([
                "up" : __DIR__"diyin_road2",
        ]) );

        set("item_desc", ([
                "jingti" : RED "一塊血紅色的巨大晶體，發出血色光"
                           "芒，你忍不住想敲(qiao)一塊下來。\n" NOR,
        ]));

        set("no_sleep_room", 1);

        set("no_magic", 1);
        setup();
}

void init()
{
        add_action("do_qiao", "qiao");
}

int do_qiao(string arg)
{
        object me = this_player();
        object ob;

        if( (!arg) || !((arg == "jingti") || (arg == "晶體")))
                return notify_fail("你要敲什麼？\n");

        message_vision(HIW "\n$N" HIW "一躍而起，飛身一掌劈在血紅色晶體一側。\n" NOR, me);

        if( query("not_xuemai") || query("combat_exp", me)<1500000 )
        {
                message("vission", HIY "可是晶體只是輕微的晃動了一下，再沒其它反應。\n" NOR, me);
                return 1;
        }
        ob = new(__DIR__"obj/diyin");
        ob->move( environment(me) );
        message_vision(HIR "只見晶體受震，「喀嚓」一聲，一小塊晶體碎片落在了地上。\n" NOR, me);
        set("not_xuemai", 1);
        remove_call_out("regenerate");
        call_out("regenerate", 86400);
        return 1;
}

int regenerate()
{
        set("not_xuemai", 0);
        return 1;
}
