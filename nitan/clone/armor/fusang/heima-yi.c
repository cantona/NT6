

#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(HIB "黑麻衣" NOR, ({ "heima yi", "heima", "yi" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", HIB "這是一件用扶桑黑麻制成的勁衣，多為扶桑武士穿戴。\n" NOR);
                set("material", "steel");
                set("value", 800000);
                set("armor_prop/armor", 300);
                set("armor_prop/dex", 2);

        }
        setup();
}

int query_autoload()
{
        return 1;
}
