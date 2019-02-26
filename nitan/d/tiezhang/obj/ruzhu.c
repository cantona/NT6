// ruzhu.c 片皮乳豬

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIY "片皮乳豬" NOR, ({"ruzhu"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "雞豆花色白細嫩，湯清味鮮，源於豆花，高於豆花，
被譽名為“豆花不用豆，吃雞不見雞”的佳餚美饌。\n");
                set("unit", "只");
                set("value", 300);
                set("food_remaining", 5);
                set("food_supply", 100);
        }
}