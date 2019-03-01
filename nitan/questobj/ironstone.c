// ironstone.c
inherit ITEM;
#include <ansi.h>
void create()
{
        set_name(HIB"鐵石"NOR, ({ "iron stone","stone"}));
        set_weight(30000);
        set("taskobj", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long","這是一塊隕星鐵石，表面燒得焦黑的，看上去堅硬之極。\n似乎是制造兵器的絕好材料。\n");
                set("value", 0);
                set("material", "wood");
        }
}