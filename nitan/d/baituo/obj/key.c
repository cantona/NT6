#include <ansi.h> 
inherit ITEM;

void create()
{
        set_name("鑰匙", ({ "key" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", YEL "這是一把普通的銅鑰匙。\n" NOR);
                set("value", 0);
                set("material", "iron");
        }
}