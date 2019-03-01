// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void reset();

void create()
{
    set("short", "小木屋");
        set("long", @LONG
一所擺設簡單的小木屋。室內有一個香爐，牆上掛著一炳長劍。
當中坐著一位老者，穿著雖然樸素，卻令人不由得心生敬仰。
LONG );

    set("exits", ([
                "out" : __DIR__"xiaojing2",
    ]));

    set("objects", ([
                CLASS_D("huashan") + "/feng" : 1,
    ]));

    set("no_clean_up", 0);
    setup();
    //replace_program(ROOM);
}