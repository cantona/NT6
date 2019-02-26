// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("鐵箱", ({"tie xiang", "box"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long",
                              "這是隻鐵箱，好像能打開(open)\n");
                set("unit", "只");
                set("open_count", 1);
                set("weight", 1000);
        }
}

void init()
{
        add_action("do_open","open");
}

int do_open()
{
        object ob, me = this_player();
        
        if (query("open_count") > 0)
        {
                message_vision(
                        HIY "$N伸手打開鐵箱，箱子裏有一本書，上寫《天魔訣》三字。\n" NOR, 
                        this_player());
                addn("open_count", -1);
                ob = new("/clone/book/tianmo-jue");
                ob -> move(me);
                return 1;
        }
        else 
                return notify_fail("鐵盒已經被別人打開過了。\n");
}