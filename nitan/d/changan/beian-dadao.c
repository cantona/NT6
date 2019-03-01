//Room: beian-dadao.c

inherit ROOM;

void create ()
{
        set ("short", "北安大道");
        set("long", @LONG
長安城的主街北安大道寬敞筆直，繁華熱鬧，許多外來的旅客和
商人都不斷來往經過這裡。北安大道再向北就是長安城的北城門，往
南則是故皇宮的白虎街。
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "north" : "/d/changan/beian-daokou",
                "south" : "/d/changan/baihu2",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}