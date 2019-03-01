//chahua6.c
#include <ansi.h>
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(MAG"風"WHT"塵三"HIR"俠"NOR, ({"cha hua", "hua"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", 
"一株茶花，同株開著三朵花，三朵花中"MAG"紫色"NOR"者最大，那是虯髯客，"WHT"白
色"NOR"者次之，那是李靖，"HIR"紅色"NOR"者最嬌艷而最小，那是紅拂女。朵朵顏色
不同，而且形狀朵朵不同，各有其妙。\n");
                set("value", 80);
                set("material", "plant");
                set_weight(10);
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", "$N輕輕地把一朵$n戴在頭上。\n");
                set("unequip_msg", "$N輕輕地把$n從頭上摘了下來。\n");
        }
        setup();
}

