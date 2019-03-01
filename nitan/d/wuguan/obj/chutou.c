#include <ansi.h>
#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name(WHT "鋤頭" NOR, ({ "chu tou", "chu", "tou" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", WHT "這是一把鋤頭，普通百姓的日常務農用品。\n" NOR);
                set("value", 50);
                set("material", "steel");
                set("wield_msg", WHT "$N" WHT "拿出一把鋤頭握在手中。\n" NOR);
                set("unwield_msg", WHT "$N" WHT "將手中的鋤頭抗在肩上。\n" NOR);
        }
        init_hammer(4);
        setup();
}