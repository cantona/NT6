// Room: /lingzhou/qingtongxia.c
// Java Sep.23 1998

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "青銅峽");
        set("long", @LONG
這裏是黃河河西走廊段中最湍急的青銅峽，黃河一路流淌到這裏，
寬闊的河面一下子變窄，兩岸的峭壁象一對生死戀人緊緊不願分開，
黃河卻象不懂事的孩子從中硬擠而過，結果水流一下子變得咆哮起來，
波浪滔天，水聲隆隆。
LONG        );
        set("exits", ([
                "northeast" : __DIR__"xiaoba",
                "southwest" : __DIR__"mingshazhou",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6305);
        set("coor/y", 2885);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}