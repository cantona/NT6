// Room: /d/yueyang/taijiting.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "太極亭");
        set("long", @LONG
太極亭為重檐錐頂小亭，亭內地面繪有陰陽合抱的太極圖。在這裏
可以飽覽洞庭湖山景色。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"dongtingmiao1",
        ]));
        set("coor/x", -1670);
        set("coor/y", 2350);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}