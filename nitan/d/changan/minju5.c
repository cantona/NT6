//Room: minju5.c

inherit ROOM;

void create ()
{
        set ("short", "民居");
        set("long", @LONG
房間裏甚是寬敞，裏面擺設樸素而自然，左側是一個古色古色的
精雅梳粧枱，前面擺有兩張紅木圓椅。右側牆壁上掛有一幅美女撫琴
圖，上面配有幾行筆跡清秀的隸體小字，內側則是一張紅色帳幔垂掛
的低矮木榻。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/huarui5",
        ]));

        set("coor/x", -10700);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}