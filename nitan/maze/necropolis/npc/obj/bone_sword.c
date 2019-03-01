 // sword_long.c
// Copyright (C) 1995 - 2001, by FengYun Workshop. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
// 
#include <weapon.h>
inherit SWORD; 
void create() {
        set_name("骨劍", ({ "bone sword" }) );
        set_weight(7000);
                set("maze_item",1); 
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把不知道什麼骨頭變成的劍。\n");
                set("value", 0);
                set("material", "steel");
                set("wield_msg", "$N拿出一把$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n收起來。\n");
        }
        ::init_sword(25);
}     