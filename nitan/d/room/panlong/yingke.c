// yingke.c 盤龍居迎客廳

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "迎客廳");             /* EXAMPLE */
//**    set("short", "ROOM_NAME迎客廳");
        set("long", @LONG
這裏是盤龍居的主人迎接八方來客的地方。大凡客人來拜見主人，少
不得在這裏寒暄敍話，了盡仰慕之情。東面通往一個茶室，是主人陪同客
人品嚐天下名茶之處。
LONG );

        set("default_long", "這裏是ROOM_NAME的主人ROOM_OWNER迎接八方來" /* EXAMPLE */
                            "客的地方。大凡客人來拜見ROOM_OWNER，少不"  /* EXAMPLE */
                            "得在這裏寒暄敍話，了盡仰慕之情。東面通往"  /* EXAMPLE */
                            "一個茶室，是主人陪同客人品嚐天下名茶之處"  /* EXAMPLE */
                            "。" );                                     /* EXAMPLE */
                                                                        /* EXAMPLE */

        set("exits", ([
                "north"  : __DIR__"yishiting",
                "south"  : __DIR__"zoudao",
                "east"   : __DIR__"chashi",
        ]));

        create_door("east", "木門", "west", DOOR_CLOSED);

//**    set("objects", ([
//**            "/d/room/roomnpc/yahuan" : 2,
//**    ]));

        set("no_sleep_room", 1);
        setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}