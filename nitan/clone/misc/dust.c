// dust.c

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + WHT "化屍粉" NOR, ({ "dust" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", NOR + WHT "這是一包用毀屍滅跡的化屍粉，只"
                            "要一丁點就可以化去(" HIW "dissolve" NOR +
                            WHT ")一具屍體。\n" NOR);
                set("value", 50000);
        }
        setup();
}

void init()
{
        if (this_player() == environment())
                add_action("do_dissolve", "dissolve");
}

int do_dissolve(string arg)
{
        object ob;

        if (! arg)
                return notify_fail("你要用化屍粉溶解什麼東西？\n");

        if (! objectp(ob = present(arg, environment(this_player()))))
                return notify_fail("這裡沒有這樣東西。\n");

        if (! ob->is_corpse() && ! ob->is_body_part() && ! ob->is_head())
                return notify_fail("化屍粉只能用來溶解屍體。\n");

        if( query("defeated_by", ob) && query("defeated_by", ob) != this_player() )
                return notify_fail("這具屍體已被別人盯上了，還是別動為妙。\n");

        message_vision(WHT "$N" WHT "用指甲挑了一點化屍粉在$n"
                       WHT "上，頓時只聽「嗤嗤」幾聲，散發出一"
                       "股惡臭。\n" RED "待臭味漸漸散盡，卻見"
                       "$n" RED "僅剩下了一灘黃水。\n" NOR,
                       this_player(), ob);
        destruct(ob);
        return 1;
}