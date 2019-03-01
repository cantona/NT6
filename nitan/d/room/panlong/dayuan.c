// xiaoyuan.c 盤龍居大院

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "大院");             /* EXAMPLE */
//**    set("short", "ROOM_NAME大院");
        set("long", @LONG
這是一個寬闊的院落，種著各種樹木，陽光照下來透過樹蔭投下層層
影子。有一條大路通向裡面。
LONG );

        set("default_long", "這是一個寬闊的院落，種著各種樹木，陽光照"   /* EXAMPLE */
                            "下來透過樹蔭投下層層影子。一條大路通向裡"   /* EXAMPLE */
                            "面，踩得非常平滑的，看來是經常有人來往。"); /* EXAMPLE */
                                                                         /* EXAMPLE */

        set("exits", ([
                "north"  : __DIR__"qianting",
                "out"    : "/d/room/xiaoyuan",
        ]));

        set("outdoors", "OUTDOORS");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);
        setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}