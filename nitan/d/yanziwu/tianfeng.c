// Room: /d/yanziwu/tianfeng.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "天風榭");
        set("long", @LONG
天風榭建在蔓陀山峯上，四面鏤刻的窗廊，四時風來，涼爽宜人，
號為天風。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "west"   : __DIR__"path24",
        ]));
        set("coor/x", 1220);
        set("coor/y", -1250);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}