// huyao.c

#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name( BLU "骷髏冠" NOR, ({ "kulou guan", "guan" }) );
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "頂");
                set("long", "這是一頂骷髏做的寶冠。\n");
                set("value", 500);
                set("material", "head");
                set("armor_prop/armor", 10);
        }
        setup();
}

