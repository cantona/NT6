inherit ROOM;

void create()
{
        set("short","五老峰");
        set("long", @LONG
這裡便是武當山五老峰。只見那五座奇峰突兀，驚險無比，行人
多不敢放膽在此玩賞風景。
LONG );
        set("exits", ([
                "northdown": __DIR__"sanlaofeng",
                "southup"  : __DIR__"hutouyan",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -350);
        set("coor/y", -350);
        set("coor/z", 130);
        setup();
        replace_program(ROOM);
}