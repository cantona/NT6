// Room: /d/mingjiao/tomen2.c
// Date: Java 97/05/11

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "青石階");
        set("long", @LONG
松林漸漸開闊，面前出現了一條寬廣的石板道，筆直通向前方。
沿道稀稀落落地種着幾棵柏樹，卻顯得高大挺拔，蝤龍般的枝幹向天
空高高伸展着。由此向南遠遠望去，是一座紅磚碧瓦的恢宏大宅。
LONG );
    set("exits", ([
        "west"  : __DIR__"tomen1",
        "east"  : __DIR__"shanjiao",
        "south" : __DIR__"mjsimen",
    ]));
    set("objects", ([
        __DIR__"npc/gaoshanwang": 1,
    ]));
    set("no_clean_up", 0);
    set("outdoors", "mingjiao");
    setup();
    replace_program(ROOM);
}
