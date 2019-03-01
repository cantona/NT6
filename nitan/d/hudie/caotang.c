// 草堂 caotang.c
 
#include <ansi.h>
#include <room.h>

inherit ROOM;

void create() 
{ 
        set("short", "草堂");
        set("long", @LONG
這是一個草堂，由于光線充足，顯得很明亮，草堂正中有一個檀
木桌，桌下面整齊地擺放著四個凳子。正門正對的牆上掛著一幅畫，
畫中是一個神清骨秀的中年人，左右有一副對聯，畫的正下方有個香
案，上面的香爐中插著幾根檀香，正冉冉地燃著。正對側面有一扇竹
門(door)虛掩著。
LONG );

        set("no_clean_up", 0);

        set("exits", ([ 
            "enter" : __DIR__"xfang4",
            "west" : __DIR__"chufang",
            "south" : __DIR__"maowu",
            "east" : __DIR__"xfang3",
        ]));

        set("objects",([
            __DIR__"npc/xtong1" : 1,
        ]));

        create_door("enter", "竹門", "out", DOOR_CLOSED);
        setup();
}