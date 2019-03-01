// yishiting.c 盤龍居議事廳

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "議事廳");
        set("long", @LONG
這就是盤龍居主人和重要人物商量大事之處，正中有不少桌椅，側
面是屏風，廳堂中掛著兩個條幅，兩旁通往演武廳。
LONG );

        set("default_long", "這就是ROOM_NAME主人ROOM_OWNER和重要人物"  /* EXAMPLE */
                            "商量江湖大事之處，正中有不少桌椅，側面是" /* EXAMPLE */
                            "屏風，廳堂中掛著兩個條幅，兩旁通往演武廳" /* EXAMPLE */
                            "。");                                     /* EXAMPLE */
                                                                       /* EXAMPLE */

        set("exits", ([
                "east"   : __DIR__"yanwu1",
                "west"   : __DIR__"yanwu2",
                "north"  : __DIR__"zhongting",
                "south"  : __DIR__"yingke",
        ]));

        set("no_sleep_room", 1);
        setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}