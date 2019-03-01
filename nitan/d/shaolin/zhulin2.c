// Room: /d/shaolin/zhulin2.c
// Date: YZC 96/01/19

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "竹林小道");
        set("long", @LONG
這是一條卵石舖成的小道，曲曲折折地通向前方。兩邊是密密的
竹林。這裡人跡罕至，惟聞足底叩擊路面，有僧敲木魚聲；微風吹拂
竹葉，又如簌簌禪唱。令人塵心為之一滌，真是絕佳的禪修所在。
LONG );
        set("exits", ([
                "east" : __DIR__"wuqiku",
                "west" : __DIR__"hsyuan2",
                "south" : __DIR__"zhulin1",
                "north" : __DIR__"zhulin3",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "shaolin");
        create_door("east","木門","west",DOOR_CLOSED);
        setup();
}
