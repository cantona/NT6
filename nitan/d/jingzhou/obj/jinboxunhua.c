//Edited by fandog, 02/15/2000
#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(HIY"金波旬花"NOR, ({"jinbo xunhua", "hua"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", 
"這金色的花朵，便是奇毒無比的金波旬花。“波旬”兩字是
梵語，是“惡魔”的意思。這毒花是從天竺傳來的，原來天
竺人叫它為“惡魔花”，\n");
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
