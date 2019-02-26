// tiexiao.c 鐵簫
#include <ansi.h>
#include <music.h> 

inherit ITEM;
inherit "/inherit/misc/_xiao";

void create()
{
        set_name(YEL "鐵簫" NOR,({ "tie xiao", "xiao" }) );
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("value", 300);
                set("material", "steel");
                set("long", "一柄普通鐵製洞簫，沉甸甸的有些墜手。\n");
        }
        setup();

}

void init() 
{
        add_action("play_xiao", "play"); 
}