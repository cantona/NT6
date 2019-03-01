// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "寒玉蕭" NOR, ({"hanyu xiao", "xiao"}));
        set_weight(4500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "這根寒玉蕭是鬼三的傳家寶。\n" NOR);
                set("unit", "把");
                set("value", 5000);
                set("item_origin", 1);
                set("material_attrib", "hanyu");
                set("material_name", HIG "寒玉" NOR);
        }
}
