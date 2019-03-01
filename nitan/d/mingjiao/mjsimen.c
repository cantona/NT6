// Room: /d/mingjiao/mjsimen.c
// Date: Java 97/05/11

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "青石道");
        set("long", @LONG
穿過一片小鬆林，面前出現了一條寬廣的石板道，筆直通向前方。
沿道稀稀落落地種著幾棵柏樹，卻顯得高大挺拔，蝤龍般的枝幹向天
空高高伸展著。
LONG );
    set("exits", ([
        "north" : __DIR__"tomen2",
        "south" : __DIR__"mjsimen1",
    ]));
    set("no_clean_up", 0);
    set("outdoors", "mingjiao");
    setup();
    replace_program(ROOM);
}
