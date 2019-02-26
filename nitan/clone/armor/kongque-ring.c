
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIG "孔雀環" NOR, ({ "kongque ring", "kongque", "ring" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", HIG "孔雀環乃神鳥孔雀之化身，象徵着「敏捷」！\n" NOR);
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/dex", 20);
                set("armor_prop/damage", 200);
        }
        setup();
}

int query_autoload()
{
        return 1;
}