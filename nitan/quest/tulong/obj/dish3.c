#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIY"鴛鴦五珍膾"NOR, ({"dish"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是傳說中的御膳，一雞一鴨經精心烤炙，再配以各種珍膳，不易吃到哦。\n");
                set("unit", "碟");
                set("value", 120);
                set("food_remaining", 30);
                set("food_supply", 30);
        }
}
