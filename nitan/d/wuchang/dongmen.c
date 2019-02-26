inherit ROOM;

void create ()
{
        set ("short","東門");
        set ("long", @LONG
這裏是東門了。有很多行人都在往城內走。在戰亂的年代，武漢竟
然出奇地熱鬧。有幾個官兵正耀武揚威地站在這裏，檢查着來往的行人。
LONG);

        set("exits", ([
                "west":__DIR__"zhongxin",
        ]));
        set("objects",([
                "/d/city/npc/bing":2,
        ]));
        set("outdoors", "wuchang");

	set("coor/x", -5080);
	set("coor/y", -1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}