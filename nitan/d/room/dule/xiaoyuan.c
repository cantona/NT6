// xiaoyuan.c 獨樂居小院

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "小院");             /* EXAMPLE */
//**    set("short", "ROOM_NAME小院");
        set("long", @LONG
這裏是一個不大的院子，角落裏栽了幾棵樹，地上零零散散有一些碎
落葉片。院門虛掩，穿過院子就是一個小屋，非常精緻。
LONG );

//**    set("room_key", "ROOM_KEY");
        setup();

        set("exits", ([
                "north"  : __DIR__"dulewu",     /* EXAMPLE */
                "out"    : "/d/room/xiaoyuan",
        ]));

        set("outdoors", "OUTDOORS");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

//**    set("KEY_DOOR", ([
//**            "exit" : "north",
//**            "room" : __DIR__"dulewu",
//**    ]));
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}