//chahua8.c
#include <ansi.h>
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(HIG"八寶妝"NOR, ({"cha hua", "hua"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", 
"一株茶花，八朵異色同株，枝上共開八朵花，朵朵顏色不同，而且形
狀朵朵不同，各有其妙。\n");
                set("value", 50);
                set("material", "plant");
                set_weight(10);
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", "$N輕輕地把一朵$n戴在頭上。\n");
                set("unequip_msg", "$N輕輕地把$n從頭上摘了下來。\n");
        }
        setup();
}

