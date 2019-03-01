inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
開封府內西面的主要交通要道，街道兩邊店舖林立，行人車馬如
梭。小商販們挑著擔子來回吆喝。此地向東就是相國寺的放生池，再
向北過去不遠，就能見到延慶觀的大門了。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"wroad1",
                  "eastup" : __DIR__"fangsheng",
                "west" : __DIR__"ximen",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5070);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}