

#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(HIR "蚩尤戰袍" NOR, ({ "chiyou zhanpao2", "chiyou", "zhanpao2" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", HIR "一件外型奇異的長袍，上面繪製着魔神蚩尤的標誌。\n" NOR);
                set("material", "steel");
                set("value", 800000);
                set("armor_prop/armor", 600);
                set("armor_prop/str", 6);
                set("armor_prop/con", 6);
                set("limit", ([
                        "exp"  :  10000000,
                        "int"  :  40,
                        "dex"  :  60,
                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}
