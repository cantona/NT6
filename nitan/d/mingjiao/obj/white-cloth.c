// white-cloth.c 白色聖衣
#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
        set_name(WHT"白色聖衣"NOR, ({ "cloth" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","這是一件繡着紅色火焰的白色聖衣。\n");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 40);
        }
        setup();
}