// jusuo.c 盤龍居居所

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "居所");
        set("long", @LONG
這就是盤龍居主人休息，讀書的地方。樓上就是主人的卧室，西面則
是書房。
LONG );

        set("default_long", "這就是ROOM_NAME主人ROOM_OWNER休息、讀書的" /* EXAMPLE */
                            "地方。樓上就是主人的卧室，西面則是書房。");/* EXAMPLE */
                                                                        /* EXAMPLE */

        set("exits", ([
                "up"   : __DIR__"woshi",
                "west" : __DIR__"shufang",
                "east" : __DIR__"huayuan",  /* EXAMPLE */
        ]));

        set("no_sleep_room", 1);
        setup();

//**    set("KEY_DOOR", ([
//**            "exit" : "east",
//**            "room" : __DIR__"huayuan",
//**    ]));
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}