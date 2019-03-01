#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name( HIG "神行靴" NOR, ({ "shenxing xue", "shenxing", "xue" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "雙");
                set("long", HIG "產自扶桑國的寶靴，多為頂級殺手所穿戴，可以增加身法。\n");
                set("value", 2000000);
                set("armor_prop/dex", 10); //後天身法+1
                set("material", "boots");
                set("limit", ([
                        "exp"  :  9000000,
                        "dex"  :  40,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
