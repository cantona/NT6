// Room: /d/yueyang/yinyangting.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "陰陽亭");
        set("long", @LONG
陰陽亭一大一小、一高一低、一陰一陽，象征柳毅和龍女。在這裡
可以飽覽洞庭湖山景色。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "west" : __DIR__"dongtingmiao1",
        ]));
        set("coor/x", -1650);
        set("coor/y", 2350);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}