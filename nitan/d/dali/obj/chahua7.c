//chahua7.c
#include <ansi.h>
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(HIR"二"WHT"喬"NOR, ({"cha hua", "hua"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", 
"一株茶花，同株開著兩朵花，一朵花色"HIR"純紅"NOR"，一朵"WHT"純白"NOR"，各有其妙。\n");
                set("value", 75);
                set("material", "plant");
                set_weight(10);
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", "$N輕輕地把一朵$n戴在頭上。\n");
                set("unequip_msg", "$N輕輕地把$n從頭上摘了下來。\n");
        }
        setup();
}

