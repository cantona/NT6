#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
        set_name(CYN "黑衣"NOR, ({ "cloth" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","這是一件繡著紅色火燄的黑色聖衣。\n");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 1);
        }
        setup();
}