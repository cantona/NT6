// yanwu2.c 盤龍居演武廳

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "演武廳");             /* EXAMPLE */
//**    set("short", "ROOM_NAME演武廳");
        set("long", @LONG
這是盤龍居的演武廳，有時有些江湖朋友來會，想一試身手，就
在這裡比武較量。
LONG );

        set("default_long", "這是ROOM_NAME的演武廳，有時有些江湖朋友來"/* EXAMPLE */
                            "會，想一試身手，就在這裡比武較量。" );    /* EXAMPLE */
                                                                       /* EXAMPLE */

        set("exits", ([
                "east" : __DIR__"yishiting",
        ]));

//**    set("objects", ([
//**            "/clone/weapon/zhubang" : 1,
//**            "/clone/weapon/zhujian" : 1,
//**            "/clone/weapon/mudao"   : 1,
//**    ]));

        set("no_sleep_room", 1);
        setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}