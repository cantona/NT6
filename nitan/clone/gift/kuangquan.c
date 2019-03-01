// kuangquan.c 礦泉水

#include <ansi.h>

inherit ITEM;

int filter_user(object ob);

void create()
{
        set_name(HIG "礦泉水" NOR, ({ "water" }));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一瓶礦泉水，可以治療口幹舌"
                            "燥，遭受飛彈襲擊以後感覺格外良好。\n");
                set("value", 8000);
                set("no_sell", 1);
                set("unit", "瓶");
        }
}

void init()
{
        add_action("do_drink", "drink");
}

int do_drink(string arg)
{
        object me;

        if (! arg || ! id(arg))
                return notify_fail("你要喝什麼？\n");

        me = this_player();
        message_vision(HIG "$N掏出一瓶" + name() + HIG
                       "，“咕咚咕咚”喝了個幹幹凈凈。\n" NOR, me);
        set("water", me->max_water_capacity(), me);
        me->permit_say(6000);
        destruct(this_object());
        return 1;
}