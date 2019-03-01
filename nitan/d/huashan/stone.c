//Room: stone 領悟玄鐵劍法的地方

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short","巨石上");
        set("long", @LONG
這裡是華山瀑布下的一塊天然巨大石頭上，周圍盡是湍急的水流，
洶湧的高山洪水（hongshui）傾泄而下拍打在你身上。
LONG );
        set("outdoors", "huashan");
        set("can_practice_xiantie-jian", 1);
        set("item_desc", ([
                "hongshui" : HIW "洪水洶湧無比，你只覺隨時有可能被洪水沖到水中。\n" NOR,
        ]));
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump()
{
        object me = this_player();

        if (me->is_busy() || me->is_fighting())
              return notify_fail("你忙完了再說吧！\n");

        message_vision(HIG "$N" HIG "縱身跳上瀑布 ……\n", me);

        me->move(__DIR__"shanhongpb");

        return 1;
}
