inherit ROOM;

void create()
{
        set("short", "三老峯");
        set("long", @LONG
此處乃武當山三老峯，只見三座奇峯突兀，驚險無比，行人多不
敢放膽在此玩賞風景。
LONG );
        set("exits", ([
                "northdown": __DIR__"wuyaling",
                "southup"  : __DIR__"wulaofeng",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -350);
        set("coor/y", -340);
        set("coor/z", 120);
        setup();
        replace_program(ROOM);
}