#include <weapon.h>
#include <ansi.h>

inherit HAMMER;

void create()
{
        set_name(WHT "大石頭" NOR, ({ "stone" }) );
        set_weight(16000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", "一塊大大的圓滾滾的石頭。\n");
                set("value", 0);
                set("material", "iron");
        }
        init_hammer(10);
        setup();
}
