
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIY "天降﹒冷月冠" NOR, ({ "lengyue guan", "lengyue", "guan" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "頂");
                set("long", HIY "傳說乃月宮寶物，蘊涵著非凡之神力。\n" NOR);
                set("value", 1500000);
                set("armor_prop/dex", 30);
                set("armor_prop/str", 30);
                set("armor_prop/con", 30);
                set("armor_prop/damage", 3000);
                set("armor_prop/blade", 150);
                set("special/desc", "有效刀法等級提高150級。");
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