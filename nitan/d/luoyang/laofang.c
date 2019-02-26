inherit ROOM;

void create()
{
        set("short", "牢房");
        set("long", @LONG
這裏是牢房，四面都用鐵欄杆圍住，正面有一扇小鐵門鎖着，後面高
處有一扇窗，用於透氣，微弱的光線從窗外射了進來，整個牢房就是一個
大鐵籠，用來關一些罪大惡極的犯人。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"xunbu",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -7020);
	set("coor/y", 2200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}