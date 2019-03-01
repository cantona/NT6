#include <ansi.h>
inherit ITEM;
void create()
{
        set_name("樹幹", ({ "shu gan", "tree", "shu", "gan" }));
        set("weight", 130000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "巨大的樹幹，比一個人還要粗。\n" NOR);
                set("value", 10);                
        }
        setup();
}