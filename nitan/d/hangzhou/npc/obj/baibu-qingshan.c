// mancloth 
// by ruri
#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIW"白布輕衫"NOR, ({ "baibu qingshan", "cloth","shan" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", "一件白色長衫，洗得十分幹凈。\n");
                set("material", "cloth");
                set("value", 0);
                set("armor_prop/armor", 1);
        }
        setup();
}