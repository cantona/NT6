// zuoxiang.c 盤龍居左廂房

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "左廂房");
        set("long", @LONG
這是盤龍居的左廂房，是客人居住的地方。
LONG );

        set("default_long", "這是ROOM_NAME的左廂房，是客人居住的地方。雖" /* EXAMPLE */
                            "然不算奢華，卻也布置得非常舒適。一張床整" /* EXAMPLE */
                            "齊幹凈，沒有多少折紋，而窗簾厚大結實，使" /* EXAMPLE */
                            "屋內光線恰到好處。" );                    /* EXAMPLE */
                                                                       /* EXAMPLE */

        set("exits", ([
                "west" : __DIR__"zhongting",
        ]));

        set("sleep_room", 1);
        set("no_fight", 1);

        create_door("west", "木門", "east", DOOR_CLOSED);

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}