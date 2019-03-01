// Room: /yixing/yixing.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
        set("short", "宜興");
        set("long", @LONG
這兒便是天下聞名的陶都，青山綠水之間掩映着一堆堆紫砂陶坯，
另有一番景色。向東行，不遠處就是太湖邊。南方便是湖州府了。
LONG );
        set("outdoors", "yixing");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"tiandi",
                "south"     : __DIR__"nanxun",
                "northwest" : "/d/wudang/wdroad2",
        ]));
        set("coor/x", 230);
	set("coor/y", -1020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}