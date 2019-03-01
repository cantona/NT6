// maoeryan.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(GRN"貓兒眼"NOR, ({ "maoer yan", "yan" }) );
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一粒暗綠而發放毫光的寶石。\n");
                set("unit", "粒");
                set("value", 100000 );
        }

}
