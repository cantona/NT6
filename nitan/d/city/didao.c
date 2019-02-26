// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;
#include <ansi.h>

void create()
{ 
       set("short","地道");
        set("long", @LONG
這裏是在一條地道中。兩旁的牆壁上掛着些油燈，有的已經熄滅
了。壁上和腳下的潮氣讓人很不舒服。東面的牆似乎可以(pull)。
LONG );
        set("exits", ([
                 "out" : "/d/city/xiaofang",
        ]));       

        set("no_clean_up", 0);
        set("open_count", 1);
        setup();

}

void init() 
{
        add_action("do_pull","pull"); 
}

int do_pull() 
{ 
        object ob, me = this_player(); 
        if (query("open_count") > 0) 
        { 
                message_vision(HIY  
                        "$N伸手在牆上拍了幾下，不一會兒，東面的牆慢慢陷了下去，一隻鐵箱露了出來。\n" NOR, 
                        this_player()); 
                addn("open_count", -1); 
                ob = new("/d/city/obj/tiexiang"); 
                ob -> move(me); 
                return 1; 
        } 
        else 
                return notify_fail("這裏已經被別人打開過了。\n"); 
} 