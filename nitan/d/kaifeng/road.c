inherit ROOM;

void create()
{
        set("short", "御街");
        set("long", @LONG
這條道橫貫南北，北到宣德門，南至南盈門，是以前皇上出巡時
常走的道所以修得也是格外平整。道兩邊店鋪不斷。向南再過去不遠。
經過石拱門就是相國寺，北面是朱雀門。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"yaopu",
                  "southup" : __DIR__"gongmen",
                  "north" : __DIR__"zhuque",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5050);
	set("coor/y", 2230);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}