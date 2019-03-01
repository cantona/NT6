#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "庭院");
        set("long", @LONG
這裡是萬安寺的西院，打掃得非常幹凈。大院兩旁是幾間大屋，全以鬆木搭
成，極大的木柱，木料均不去皮，天然質樸，卻與大院正對的一座金碧輝煌的殿
堂截然不同，這裡到處都是蒙古兵，戒備很是深嚴。
LONG );
        set("exits", ([
                "west" : "/d/tulong/yitian/was_dayuan",
        ]));

        set("objects", ([
                "/d/tulong/yitian/npc/bing1" : 5,
        ]));

        set("outdoors", "beijing");
        setup();
}

