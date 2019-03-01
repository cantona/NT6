//chahua1.c
#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(HIY"落第秀才"NOR, ({"cha hua", "hua"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", 
"一株盛開的茶花，論顏色，一共是十七種。比十八學士少了一色，
偏又是駁而不純，開起來或遲或早，花朵又有大有小。它處處東施
效顰，學那十八學士，卻總是不像，好似個半瓶醋的酸丁。\n");
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