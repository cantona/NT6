// Room: /lingzhou/mingshazhou.c
// Java Sep.23 1998

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "鳴沙洲");
        set("long", @LONG
鳴沙洲就在青銅峽的上遊，附近就是連天的沙丘，這裡正好處在
風口，強勁的西北風吹的黃沙漫天橫飛、嗡嗡作響，鳴沙洲由此得名，
一走到這裡你就覺得透體冰涼，飛沙打在你臉上生疼生疼，讓你睜不
開眼睛。
LONG        );
        set("exits", ([
                "northeast" : __DIR__"qingtongxia",
                "southwest" : __DIR__"xuanhebao",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6315);
        set("coor/y", 2875);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}