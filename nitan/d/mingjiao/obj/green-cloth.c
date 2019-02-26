// green-cloth.c 綠色聖衣
#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
        set_name(GRN"綠色聖衣"NOR, ({ "cloth" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","這是一件繡着紅色火焰的綠色聖衣。\n");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 10);
        }
        setup();
}