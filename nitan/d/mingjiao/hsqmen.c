//HSQMEN.C

inherit ROOM;

void create()
{
        set("short", "洪水旗大門");
        set("long", @LONG
這裡是明教洪水旗的大門， 莊嚴古樸， 門前對插四面鑲藍蟠龍
旗門前水聲潺潺， 卻是一條水流從門下流出， 正是瀑布的上源，原
來， 整個洪水旗就建築在這條小河之上。
LONG );
        set("exits", ([
                "enter" : __DIR__"hsqchanglang",
                "south" : __DIR__"tohsq7",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}