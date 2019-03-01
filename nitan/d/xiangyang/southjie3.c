// Room: /d/xiangyang/southjie3.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "南大街");
        set("long", @LONG
這裡是襄陽城南大街的南頭。南面就是朱雀內門，北邊非常熱鬧。
東邊是為襄陽城守軍打制鎧甲武器的兵器舖。十余年來，由于蒙古軍
的侵犯，叮叮當當的打鐵聲音就一直響個不停。西面是襄陽城的南兵
營，隱隱能聽見裡面傳來的兵士們的操練聲。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "east"  : __DIR__"tiejiangpu",
                "west"  : __DIR__"bingying3",
                "south" : __DIR__"southgate1",
                "north" : __DIR__"southjie2",
        ]));
        set("coor/x", -7820);
	set("coor/y", -800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}