// This program is a part of NITAN MudLIB

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("異果", ({ "yiguo"}) );
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("prep", "on");
                set("unit", "個");
                set("long", "一種你從未見過的奇異果子。\n");
                set("value", 1);
                set("food_remaining", 1);
                set("food_supply", 16);
        }
        setup();
}        
