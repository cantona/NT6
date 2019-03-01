inherit ROOM;

void create()
{
        set("short", "東門");
        set("long", @LONG
開封府內東面的主要交通要道，街道兩邊店舖林立，行人車馬如
梭。小商販們挑著擔子來回吆喝。出門向東北就是華北了，向東南是
揚州城。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "west" : __DIR__"eroad",
                "east" : __DIR__"guandao1",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5020);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}