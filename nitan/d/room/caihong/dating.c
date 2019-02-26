// dating.c 彩虹居大廳

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "大廳");             /* EXAMPLE */
//**    set("short", "ROOM_NAME大廳");
        set("long", @LONG
這就是彩虹居主人迎送客人的地方，正中有一些桌椅，側面是屏風，
廳堂中掛着兩個條幅。不過上面居然什麼都沒有寫。東面是主人的房間。
LONG );

        set("default_long", "這就是ROOM_NAME主人ROOM_OWNER迎送客"  /* EXAMPLE */
                            "人的地方。正中有些桌椅，側面是兩扇"   /* EXAMPLE */
                            "屏風。東首是主人ROOM_OWNER的房間，"   /* EXAMPLE */
                            "有一扇木門虛掩着。南邊是大門，出去"   /* EXAMPLE */
                            "就是院子。");                         /* EXAMPLE */
                                                                   /* EXAMPLE */
        setup();

        set("exits", ([
                "east"   : __DIR__"woshi",
                "north"  : __DIR__"houyuan",
                "south"  : __DIR__"xiaoyuan",   /* EXAMPLE */
        ]));

        create_door("east", "木門", "west", DOOR_CLOSED);

        set("no_sleep_room", 1);

//**    set("KEY_DOOR", ([
//**            "exit" : "south",
//**            "room" : __DIR__"xiaoyuan",
//**    ]));
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}