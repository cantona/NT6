//HSQTING.C

inherit ROOM;

void create()
{
        set("short", "洪水旗大廳");
        set("long", @LONG
這裡是洪水旗的大廳，廳中四壁漆墨，連桌案台椅俱為黑色，槍
曳黑纓，劍垂玄穗，布置得冷漠森嚴。廳中央擺有茶幾，洪水旗掌旗
使唐洋正襟而坐，面帶殺氣。
LONG );
        set("exits", ([
                "south" : __DIR__"hsqchanglang",
        ]));
        set("objects", ([
                __DIR__"npc/tangyang": 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}