#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(NOR"鮮花種籽"NOR, ({ "hua zhong"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "普通的鮮花種籽，不知道會開出什麼樣的花來。\n");
                set("unit", "粒"); 
                set("no_get",1);
                set("no_put",1);
                set("no_give",1);   
                set("value",50000);
        }
    setup();
}