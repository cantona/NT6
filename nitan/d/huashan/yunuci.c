#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "玉女祠");
        set("long", @LONG
玉女祠裏供奉的到底是哪位玉女，有許多不同的説法，現在所能
看到的只一尊呆板的石像。祠中大石上有一處深陷，凹處積水清碧，
這是玉女的洗臉盆，碧水終年不幹。玉女祠左邊是一處山崖(cliff)，
很是陡峭。
LONG );
        set("outdoors", "huashan");
        set("exits", ([
                "east" : __DIR__"yunu",
        ]));
        set("item_desc", ([
                "cliff" : "玉女祠下的山崖很是陡峭，似乎連接了一條小路。\n",
        ]));

        set("resource/water", 1);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me = this_player();
        int n=query("dex", me);

        if (! arg || arg != "cliff")
        {
                write("你打算往哪裏跳？\n");
                return 1;
        }

        message_vision( HIY "$N" HIY "深吸了一口氣，飛身向山崖跳去。\n" NOR, me);

        if (n < 30)
        {
                message_vision( HIR "結果$N" HIR "慘叫了一聲，跌下了山崖"
                                "。\n" NOR, this_player());

                me->move(__DIR__"kuihua_2");
                me->unconcious();

                message("vision", HIR "只聽" + me->name() + HIR "一聲慘叫"
                                  "，從上面的山峯上重重的摔了下來。\n" NOR,
                                  environment(me), ({me}) );
        } else
        {
                message_vision( HIC "只見$N" HIC "身法矯健，輕輕一縱，飄然落"
                                "至崖底。\n" NOR, this_player());

                me->move(__DIR__"kuihua_2");

                message("vision", HIC "只見" + me->name() + HIC "從上面的山峯輕輕"
                                  "的落了下來。\n", environment(me), ({me}) );
        }
        return 1;
}
