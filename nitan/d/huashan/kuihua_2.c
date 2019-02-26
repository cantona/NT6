#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "山崖");
        set("long", @LONG
這裏是玉女祠山下的陡峭山崖，離前邊的山崖比較遠，看來想要
爬過去並不容易。
LONG );
        set("outdoors", "huashan");
        setup();
}

void init()
{
        add_action("do_climb", "climb");
}

int do_climb()
{
        object me = this_player();
        int n = me->query_skill("dodge", 1);

        message_vision( HIY "$N" HIY "深吸了一口氣，慢慢沿着山壁向上"
                        "爬。\n" NOR, this_player());
        if (n > 100)
        {
                message_vision(HIC "$N" HIC "爬了半天，手肘膝蓋都已"
                               "被堅石割得鮮血淋漓，終於爬上了上面的"
                               "山崖。\n" NOR, this_player());

                me->move(__DIR__"kuihua_1");

                message_vision(HIC "$N" HIC "從下面的山崖爬了上來"
                        "。\n" NOR, this_player());
        } else
        {
                message_vision(HIR "$N" HIR "爬了一會，一個不留神，"
                               "跌了下去。\n" NOR, this_player());
                me->unconcious();
        }
        return 1;
}