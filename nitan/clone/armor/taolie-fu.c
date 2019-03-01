
#include <armor.h>
#include <ansi.h>

inherit MYHEART;

void create()
{
        set_name(HIY "饕餮符" NOR, ({ "taolie fu", "taolie", "fu" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "張");
                set("long", HIY "這是一張道符，上面畫著一個古怪的巨獸。\n" NOR);
                set("value", 10000);
                set("armor_prop/greedy", 1);
                set("special/desc", "5%幾率打中對手降低對方食物及飲水量。");
        }
        setup();
}

int query_autoload()
{
        return 1;
}