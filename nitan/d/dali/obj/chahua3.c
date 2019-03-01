//chahua3.c
#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(HIG"十三太保"NOR, ({"cha hua", "hua"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", 
"一株茶花，枝上共開十三朵花，朵朵顏色不同，決無半分混雜。而
且十三朵花形狀朵朵不同，各有各的妙處，開時齊開，謝時齊謝，
是僅次於十八學士的天下茶花極品。\n");
                set("value", 90);
                set("material", "plant");
                set_weight(10);
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", "$N輕輕地把一朵$n戴在頭上。\n");
                set("unequip_msg", "$N輕輕地把$n從頭上摘了下來。\n");
        }
        setup();
}
