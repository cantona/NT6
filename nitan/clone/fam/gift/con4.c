#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(NOR + YEL "洗髓再造仙丹Ⅱ型" NOR, ({ "xisui xiandan2" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "此丹乃是天宮中的神品，凡人吃了可以平增根骨。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 200000);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("gift_type", "con");
                set("gift_name", "先天根骨");
                set("gift_point", 100);
                set("gift_msg", HIM "突然你渾身骨骼響個不停，但隨即又平和了下來。\n" NOR);
        }
        setup();
}