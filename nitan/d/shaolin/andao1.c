#include <room.h>
inherit ROOM;

void create()
{
        set("short", "暗道");
        set("long", @LONG
這裏是一個陰暗潮濕的地道，四壁用粗糙的片巖壘垛而成，只見
一顆顆水珠沿着牆壁滾下來，濺在地上。也許是因為長時間無人通行
的緣故，整個地道瀰漫着一股腐屍般的惡臭。
LONG );
        set("exits", ([
                "south" : __DIR__"rukou",
                "north" : __DIR__"jianyu1",
        ]));
        create_door("north","木門","south",DOOR_CLOSED);
        set("no_clean_up", 0);
        set("objects",([
                "/d/shaolin/npc/ad-laoshu" : 4,
        ]));
        setup();
}
