#include <ansi.h>
#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name(HIG "水瓢" NOR, ({ "shui piao", "shui", "piao" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", HIG "這是一個用老葫蘆劈開做成的瓢，普通百姓的日常務農用品。\n" NOR);
                set("value", 10);
                set("material", "steel");
                set("wield_msg", HIG "$N" HIG "拿出一個水瓢握在手中。\n" NOR);
                set("unwield_msg", HIG "$N" HIG "將手中的水瓢插在腰上。\n" NOR);
        }
        init_hammer(4);
        setup();
}