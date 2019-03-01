#include <ansi.h>
#include <weapon.h>
inherit ITEM;

void create()
{
        set_name(HIG "七子剛鏢" NOR, ({"qizi gangbiao"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "這是一枚四川唐門秘制的剛鏢，威力無比。\n");
                set("value", 21);
                set("unit", "枚");
        }
        setup();
}
