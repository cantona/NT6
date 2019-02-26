// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <room.h>

inherit ROOM;
// inherit HARBOR;

void create()
{
        set("short", "舟山");
        set("long", @LONG
這是舟山的一個漁港，邊上有艘大船(chuan)，船上坐着幾個漁夫打
扮的人，乘船可渡過大海到達傳説中的桃花島。西面是嘉興城，東面是一
望無際的大海。
LONG );
        set("outdoors", "taohua");
        set("exits", ([
                "west" : "/d/jiaxing/nanhu1",
        ]));

        set("item_desc", ([
                "chuan" : "這是一艘海船，可載人渡海，但是船家在平時也用它來打魚。\n",
        ]));

        set("navigate/locx", 0);
        set("navigate/locy", -200);

        set("cost", 2);

        setup();
}
