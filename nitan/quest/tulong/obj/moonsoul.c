//zhenzhu.c
inherit ITEM;
#include <ansi.h>
void create()
{
        set_name( HIC"月魄"NOR, ({ "moonsoul"}));
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long","這是一顆夜明珠，放著幽藍的柔和的光，它出自月宮，價值連城。\n");
                set("value", 70000);
                set("material", "iron");
              }
}
