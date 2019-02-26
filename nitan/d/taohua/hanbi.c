// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "涵碧峯");
        set("long", @LONG
涵碧峯實際上是一塊碩大無朋的太湖石峯，高四丈有餘，因為特別適
合青苔生長，通體碧綠，故而得名“涵碧”。據傳説，這是花石綱遺物中
的上品，比起蘇州名聞天下的瑞雲峯和獅子峯來有過之而無不及，原址本
在蘇州，因黃藥師夫人馮氏原籍蘇州，黃藥師才費偌大心力，將之移往桃
花島，使夫人不致有僻處海外之感。
LONG );
        set("exits", ([
                "south" : __DIR__"songlin3",
                "northeast" : __DIR__"bibochi",
        ]));

        /*
        set("objects", ([
                "/d/taohua/npc/shagu" : 1,
        ]));
        */

        set("outdoors", "taohua");

        set("coor/x", 8980);
        set("coor/y", -2970);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

/*
int valid_leave(object me, string dir)
{

        if( (query("family/master_name", me) != "程英" )
         && (query("family/master_name", me) != "黃藥師" )
         && (!query_temp("shagu_pass", me) )
        && present("sha gu", this_object()) )
        return notify_fail("\n傻姑傻笑了幾聲，伸開雙手一攔，説到：要進去先陪我玩一會兒吧，這裏人都不理我，悶死了！\n");

        return ::valid_leave(me, dir);
}
*/