// honghua-ling.c 紅花令
// Last Modified by winder on Sep. 12 2001

#include <ansi.h>;
inherit ITEM;

void create()
{
        set_name(HIR"紅花令"NOR, ({ "honghua ling","ling"}) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("long", HIG"這是一塊綠油油的竹牌，上書紅花令三個大字，是紅花會至高無上的令牌。\n"NOR);
                set("value", 100000);
                set("material", "iron");
        }
        setup();
}

void init()
{
        call_out("dest", 1800);
}

void dest()
{
        destruct(this_object());
}