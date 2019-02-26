// cypress_bole.c 青柏樹幹 
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG"青柏樹幹"NOR,({ "bole", "cypress bole" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一根青柏樹幹，是製造香火的好材料。\n");
                set("unit", "根");
                set("value", 100);
                set("material", "wood");
                set("self_destruct", 1);
            }
        setup();
}
int value()
{
        return 1;
}
