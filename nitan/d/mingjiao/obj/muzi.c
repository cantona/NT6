// Code of JHSH
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("火槍模子", ({ "huoqiang muzi", "muzi" }) );
        set_weight(40000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一副火槍模子，用紅土砌成。\n");
                set("unit", "副");
                set("no_get",1);
                set("value",1);
//                                set("no_drop",1);

        }

}
