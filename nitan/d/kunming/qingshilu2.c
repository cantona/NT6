inherit ROOM;

void create()
{
        set("short",  "青石路" );
        set("long", @LONG
一條青石大道，青石舖成，平坦寬闊，抬頭一看，前面的
城門清晰可見。
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "west" : __DIR__"dongmen", 
                "east"  :__DIR__"qingshilu1",
        ]));
	set("coor/x", -16810);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}