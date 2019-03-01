// muwu2.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "小木屋");
        set("long", @LONG
這是一間不是很大的木頭屋子，這裡看起來象個藥室，室中擺放著
各種不同的配藥的用具和一些已經配好了的藥。
LONG );
        set("exits", ([
                "south" : __DIR__"xiaodao3",
        ]));
        set("objects", ([
                CLASS_D("xiaoyao")+"/xuemuh" : 1,
//                __DIR__"npc/yaotong": 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", 80);
        set("coor/y", -480);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
