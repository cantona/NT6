
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIR "麒麟指環" NOR, ({ "qilin ring", "qilin", "ring" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", HIR "麒麟指環乃火麒麟之化身，象征著「力量」！\n" NOR);
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/str", 10);
                set("armor_prop/damage", 500);
        }
        setup();
}        

int query_autoload()
{
        return 1;
}