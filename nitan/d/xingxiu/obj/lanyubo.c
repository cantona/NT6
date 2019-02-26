// lanyubo.c
#include <ansi.h>;
inherit ITEM;

void create()
{
        set_name(HIB"藍玉缽"NOR,({ "lanyu bo", "bo" }) );
        set_weight(30000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", "一隻藍田美玉精製而成的藥缽，雖然使用日久, 但絲毫沒有破痕。藥缽裏殘留了微量劇毒, 然已足夠毒死偷寶之人。\n");
                set("value", 20000);
        }
        setup();
}