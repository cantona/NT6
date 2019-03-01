inherit ROOM;

void create()
{
        set("short", "西門");
        set("long", @LONG
開封府內西面的主要交通要道，街道兩邊店鋪林立，行人車馬如
梭。小商販們挑着擔子來回吆喝。此地向東就是相國寺的放生池，再
向北過去不遠，就能見到延慶觀的大門了。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"wroad",
                "west" : "/d/zhongzhou/eroad3",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5080);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}