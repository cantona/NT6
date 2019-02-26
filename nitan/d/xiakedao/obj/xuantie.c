// xuantie.c 玄鐵令

#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIC "玄鐵令" NOR, ({ "xuantie ling", "ling" }));
        set("long", "\n這是一塊碧綠色的玉牌，瑩潔光綠，真是一塊好玉。\n"+
         "正面雕龍刻鳳，正中寫着玄鐵兩個大字。這便是江湖上傳説的玄鐵令。\n");
        set("weight", 300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("value", 50000);
                set("material", "玉");
                set("armor_prop/armor", 2);
                set("female_only", 1);
        }
        setup();
}
