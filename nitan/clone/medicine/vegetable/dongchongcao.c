// dongchongcao.c 冬蟲草

#include <ansi.h>
inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_fu", "fu");
}

void create()
{
        set_name(HIB"冬蟲草"NOR, ({"dongchong cao", "cao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "株");
                set("long", HIB"這是一株夏季從冬季鑽入土中的死蟲身上長出的冬蟲夏草。受傷了敷上有奇效。\n"NOR);
                set("value", 2500);
        }
        set("pour_type", "1");
        setup();
}

int do_fu(string arg)
{
        string what = query("cure");
        int howmuch = query("amount");
        object me = this_player();

        if(!id(arg)) return notify_fail("你要敷什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要敷什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢敷，小心別敷歪了。\n");

        if( query("eff_qi", me) == query("max_qi", me) )
                return notify_fail("你現在身上沒有受到任何傷害！\n");
        else {
                me->receive_curing("qi", 150);
                message_vision("$N把一株冬蟲草放進口中嚼碎，小心敷在傷口上，氣色看起來好多了。\n", me);
                destruct(this_object());
                return 1;
        }
}
