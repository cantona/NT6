// hulannaao.c 湖藍衲襖

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIB"湖藍衲襖"NOR, ({"hulan naao", "cloth"}));
        set_weight(1500);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一套湖藍色的布襖，江湖人多穿此類衣服御寒。\n");
                set("unit", "套");
                set("value", 500);
                set("material", "cloth");
                set("armor_prop/armor", 3);
        }
        setup();
}