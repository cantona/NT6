
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIG "劍魔之羽" NOR, ({ "jianmo zhiyu4", "zhiyu4", "jianmo" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", HIG "這是由獨孤求敗取神雕羽毛精心制作而成的頭飾，其中似乎蘊涵了高深的武學真諦。\n" NOR);
                set("value", 1500000);
                set("armor_prop/dex", 38);
                set("armor_prop/str", 38);
                set("armor_prop/con", 38);
                set("armor_prop/damage", 5200);
                set("armor_prop/sword", 180);
                set("special/desc", "有效劍法等級提高180級。");
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