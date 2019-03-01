//lhqmen.c

inherit ROOM;

void create()
{
        set("short", "烈火旗大門");
        set("long", @LONG
這裡是明教烈火旗的大門，莊嚴古樸，門前對插四面鑲紅飛龍旗。
金色門釘扣在火漆紅門上，分外精神。也是通往明教總舵的必經之地。
所以來往的人也特別多。
LONG );
        set("exits", ([
                "enter"     : __DIR__"lhqyuan",
                "southdown" : __DIR__"lhqpaifang",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}