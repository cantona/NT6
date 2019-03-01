//yayifu.c

#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("衙役服", ({"yayi fu", "cloth"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("long",
                "一件黑色短裝，嵌以紅邊，是長安府的衙役穿的．\n");
                set("material", "cloth");
                set("unit", "件");
                set("value", 500);
                set("armor_prop/armor", 10);
        }

        setup();
}