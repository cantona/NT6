// Room: /heizhao/hzyuanzi.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "黑沼院子");
        set("long", @LONG
牆裡是個院子，分為兩半，左一半是實土，右一半卻是水塘。
跨過院子，往北通向內堂，堂前是個月洞，仍無門扉。
LONG );
        set("outdoors", "heizhao");
        set("no_clean_up", 0);

        set("exits", ([
                "out"   : __DIR__"shanlu5",
                "north" : __DIR__"hzneitang",
        ]));
        set("coor/x", -5100);
        set("coor/y", -1490);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}