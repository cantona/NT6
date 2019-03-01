
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIM "劍魔之羽" NOR, ({ "jianmo zhiyu", "zhiyu", "jianmo" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", HIM "這是由獨孤求敗取神雕羽毛精心制作而成的頭飾，其中似乎蘊涵了高深的武學真諦。\n" NOR);
                set("value", 1500000);
                set("armor_prop/dex", 30);
                set("armor_prop/str", 30);
                set("armor_prop/con", 30);
                set("armor_prop/damage", 3000);
                set("armor_prop/sword", 50);
                set("special/desc", "有效劍法等級提高50級。");
                set("limit", ([ 
                         "exp" : 100000000,
                         "scborn" : 1,
                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}