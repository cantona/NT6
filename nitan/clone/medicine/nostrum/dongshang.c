// dongshang.c 祛瘡粉

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_mo", "mo");
}

void create()
{
        set_name(HIC"祛瘡粉"NOR, ({"quchuang fen", "quchuangfen","fen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("long", "這是一治療凍瘡的藥粉，塗抹(mo)在患處立刻見效。\n");
                set("value", 2000);
        }
        setup();
}

int do_mo(string arg)
{
        object me = this_player();
        if (!id(arg))
                return 0;
        if (me->is_busy() )
                return notify_fail("別急，慢慢來。\n");
        if (!me->query_condition("ill_dongshang"))
        {
                write("你現在又沒有被凍傷，往哪兒抹藥？\n");
                return 1;
        } else {
                me->clear_condition("ill_dongshang");
                message_vision("$N把祛瘡粉抹在凍傷的地方，凍瘡消去了不少。\n", me);
                me->start_busy(2);
                destruct(this_object());
                return 1;
        }
}