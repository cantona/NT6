inherit ROOM;

void create()
{
        set("short", "後院");
        set("long", @LONG
 這裡是雪山寺的後院，後院不大，栽了幾株參天雪鬆，在白晃晃
的雪山背景下，竟是飄然出世的心動。南邊便是的練武場了。
LONG );
        set("outdoors", "xueshan");
        set("exits", ([
                "northdown" : __DIR__"dilao",
                "south"     : __DIR__"chang3",
        ]));
        setup();
        replace_program(ROOM);
}