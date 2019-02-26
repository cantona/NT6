inherit ROOM;

void create()
{
        set("short", "城北橋");
        set("long", @LONG
此橋高跨洛陽護城河之上，氣勢非凡。站在橋上向兩側望去，一條人
工開掘的護城河將洛陽城圍在當中，橋身以漢白玉造就，既美觀又很堅固。
橋上車水馬龍，川流不息。橋下的護城河水清澈見底，時有游魚躍起。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"beidoor",
                //"north" : __DIR__"guandaon1",
                "north" : __DIR__"road5",
        ]));

	set("coor/x", -6990);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}