//chahua13.c
#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(HIW"倚"HIG"欄"HIR"嬌"NOR, ({"cha hua", "hua"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", 
"一株茶花，白色花瓣上有一抹綠暈、一長列紅條。\n");
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