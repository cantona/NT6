inherit ROOM;

void create()
{
        set("short", "石林");
        set("long", @LONG
這裡矗立著各種各樣形狀各異的石頭，有的象人，有的象
樹，有的又象動物，你這邊看著象這樣，也許換個角度又象其
他的，千姿百態。把你眼睛都看花了。北邊有一座高峰，卻甚
是象朵蓮花，名為蓮花峰。
LONG);
        set("outdoors", "kunming");

        set("exits", ([
                "northup" :__DIR__"lianhua",
                "east" : __DIR__"shilin1", 
                "west"  :__DIR__"qingshilu",
        ]));
	set("coor/x", -16780);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}