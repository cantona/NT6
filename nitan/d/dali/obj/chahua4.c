//chahua4.c
#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(HIB"八仙過海"NOR, ({"cha hua", "hua"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", 
"一株茶花，八朵異色同株，枝上共開八朵花，"MAG"深紫"NOR"和"HIR"淡紅"NOR"的花各一
朵，那是鐵拐李和何仙姑，朵朵顏色不同，紅花最小。而且形狀朵
朵不同，各有其妙。\n");
                set("value", 85);
                set("material", "plant");
                set_weight(10);
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", "$N輕輕地把一朵$n戴在頭上。\n");
                set("unequip_msg", "$N輕輕地把$n從頭上摘了下來。\n");
        }
        setup();
}
