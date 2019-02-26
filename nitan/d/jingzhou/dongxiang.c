// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "閨房");
        set("long", @LONG
這是淩小姐的閨房，一股幽香撲面而來。一張繡榻放在牆角，垂
着細紗。淩小姐正對着一盆菊花在沉思。北面是座花園。
LONG );

        set("exits", ([
                "west" : __DIR__"houyuan",
        ]));

        set("objects", ([
                __DIR__"npc/shuanghua" : 1,
        ]));
        
        setup();
        replace_program(ROOM);
}
