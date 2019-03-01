// Last Modified by sir
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name( "熨好的布" , ({"bu"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "匹");
                set("long", 
"這是一匹熨好的布，它已經可以直接被送去加工了。\n");
                set("value", 1);
        }
        setup();
}