#include <room.h>

inherit ROOM;

void create()
{
        set("short", "木屋");
        set("long", @LONG
這是凌霄城弟子在城外巡邏護山的哨所，每天都有雪山弟子
守衛，以保護凌霄城安全清凈。不過，憑凌霄城在武林中的名頭,
一般宵小之輩也不敢來此搗亂
LONG );
        set("exits", ([
                "west" : __DIR__"sroad6",
        ]));

        set("objects", ([
                CLASS_D("lingxiao") + "/wangwanren" : 1,
        ]));

        create_door("west", "木門", "east", DOOR_CLOSED);
        set("no_clean_up", 0);
        setup();
} 
