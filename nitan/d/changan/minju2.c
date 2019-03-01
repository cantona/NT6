//Room: minju2.c

inherit ROOM;

void create ()
{
        set ("short", "民居");
        set("long", @LONG
房間裡甚是寬敞，裡面擺設樸素而自然，左側是一個古色古色的
精雅梳妝台，前面擺有兩張紅木圓椅。右側牆壁上掛有一幅美女撫琴
圖，上面配有幾行筆跡清秀的隸體小字，內側則是一張紅色帳幔垂掛
的低矮木榻。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/huarui2",
        ]));

        set("coor/x", -10740);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}