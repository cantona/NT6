#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(MAG"波斯明教教服"NOR, ({ "bosi cloth","cloth"}) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", "這是一件波斯明教總舵的教服。\n");
                set("value", 300);
                set("material", "silk");
                set("armor_prop/armor", 2);
        }
        setup();
}
