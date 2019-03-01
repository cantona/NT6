#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        string *names=({HIW"百合"NOR,HIR"玫瑰"NOR,HIB"芙蓉"NOR,HIY"海棠"NOR,HIM"薔薇"NOR,HIG"玉蘭"NOR,HIC"丁香"NOR,
                       HIY"臘梅"NOR,HIR"月季"NOR,HIW"雪蓮"NOR});
        set_name(names[random(sizeof(names))], ({"flower", "hua"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long","一朵美麗的"+query("name", this_object())+NOR"。\n");
                set("value", 0);
                set("material", "plant");
                set_weight(10);
                set("armor_prop/armor", 0);
                set("armor_prop/per", random(2)+1);
                set("wear_msg", "$N輕輕地把一朵$n戴在頭上。\n");
                set("unequip_msg", "$N輕輕地把$n從頭上摘了下來。\n");
        }
        setup();
}
