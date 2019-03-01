// lianwu.c 盤龍居練武場

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "練武場");
        set("long", @LONG
此處便是盤龍居的練武場，人在江湖，武功萬萬不可荒廢。
LONG );

        set("default_long", "此處便是ROOM_NAME的練武場，人在江湖，武功"/* EXAMPLE */
                            "萬萬不可荒廢。");                         /* EXAMPLE */
                                                                       /* EXAMPLE */

        set("exits", ([
                "west" : __DIR__"houyuan",
        ]));

//**    set("objects", ([
//**            "/clone/npc/mu-ren" : 4,
//**    ]));

        set("outdoors", "OUTDOORS");
        set("no_sleep_room", 1);

        setup();
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}