inherit ROOM;

void create()
{
        set("short", "師爺處");
        set("long", @LONG
一走進師爺的屋子，就見師爺的桌子上零星的散落着一些
糖和瓜果。北面的大牆上貼着一張大的告示，師爺悠閒的坐在
太師椅上。
LONG);
        set("exits", ([
                "south" : __DIR__"zoulang1",                 
        ]));

        set("coor/x", -9060);
	set("coor/y", -950);
	set("coor/z", 0);
	setup();
}