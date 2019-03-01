// qishayan.c 漆沙硯

inherit ITEM;
#include <ansi.h>;
void create()
{
        set_name(HIM"漆沙硯"NOR, ({"qisha yan", "yan"}) );
        set("taskobj", 1);
        set_weight(100);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","漆沙硯，上有宋宣和內府制六字。其形質類澄沙而絕輕，入水不沉，甚異之。\n");
                set("value", 0);
                set("unit" , "方");
        }
        setup();
}

        

