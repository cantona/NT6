//chahua2.c
#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(HIR"十八學士"NOR, ({"cha hua", "hua"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", 
"一株茶花，枝上共開十八朵花，朵朵顏色不同，"HIR"紅"NOR"的就是全紅，"MAG"紫"NOR"
的便是全紫，決無半分混雜。而且十八朵花形狀朵朵不同，各有各
的妙處，開時齊開，謝時齊謝，是天下茶花的極品。\n");
                set("value", 100);
                set("material", "plant");
                set_weight(10);
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", "$N輕輕地把一朵$n戴在頭上。\n");
                set("unequip_msg", "$N輕輕地把$n從頭上摘了下來。\n");
        }
        setup();
}