inherit ROOM;

void create()
{
        set("short", "平心石");
        set("long", @LONG
百尺峽盡頭，兩邊巖崖勢欲相合，中夾兩塊巨石，前邊一塊刻有
『驚心石』三字。過此回望，石上刻有『平心石』三字，示人們以險
境已經過去，已進入平安之途了。頓時心情至此一舒。
LONG );
        set("exits", ([
            "westdown" : __DIR__"baichi",
            "eastup"   : __DIR__"laojun",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "huashan" );

        setup();
        replace_program(ROOM);
}