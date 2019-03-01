// xiaoyuan.c 彩虹居小院

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "小院");             /* EXAMPLE */
//**    set("short", "ROOM_NAME小院");
        set("long", @LONG
這裡是一個四四方方的院子，院牆都是用紅磚砌成，不算高，但是非
常清爽利落。院中幾棵古木成蔭，隱然有一種世外桃源的感覺。穿過院子
有一扇木門。
LONG );

        set("default_long", "這裡是一個四四方方的院子，院牆都是用" /* EXAMPLE */
                            "紅磚砌成，不算高，但是非常清爽利落。" /* EXAMPLE */
                            "院中幾棵古木成蔭，隱然有一種世外桃源" /* EXAMPLE */
                            "的感覺。院子外面隱約是ROOM_POSITION"  /* EXAMPLE */
                            "，院子的北面有一扇木門。");           /* EXAMPLE */
                                                                   /* EXAMPLE */
//**    set("room_key", "ROOM_KEY");
        setup();

        set("exits", ([
                "north"  : __DIR__"dating",     /* EXAMPLE */
                "out"    : "/d/room/xiaoyuan",
        ]));

        set("outdoors", "OUTDOORS");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

//**    set("KEY_DOOR", ([
//**            "exit" : "north",
//**            "room" : __DIR__"dating",
//**    ]));
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}