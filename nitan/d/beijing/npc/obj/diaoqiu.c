#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name( MAG "貂裘" NOR, ({ "diao qiu", "cloth" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", "一件用貂皮製作，做工細緻的皮外套，很是名貴。\n");
                set("value", 1000);
                set("material", "cloth");
                set("armor_prop/armor", 20);
        }
        setup();
}
