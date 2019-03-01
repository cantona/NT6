// caoyao.c

#include <ansi.h>

inherit ITEM;

void create() 
{
        set_name(HIG "不知名草藥" NOR, ({"cao yao", "yao", "cao"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "株");
                set("long", "這是一株生長在密林中的不知名的草藥，一般人都會誤認成雜草。\n");
        }
        setup();
}