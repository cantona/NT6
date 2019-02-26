
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIR "劍魔" HIC "之羽" NOR, ({ "jianmo zhiyu6", "zhiyu6", "jianmo" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", HIW "這是由獨孤求敗取神鵰羽毛精心製作而成的頭飾，其中似乎藴涵了高深的武學真諦。\n" NOR);
                set("value", 1500000);
                set("armor_prop/dex", 50);
                set("armor_prop/str", 50);
                set("armor_prop/con", 50);
                set("armor_prop/damage", 7000);
                set("armor_prop/sword", 300);
                set("special/desc", "有效劍法等級提高300級。");
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