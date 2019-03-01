// Room: /d/huanggong/nanxundian.c

inherit ROOM;

void create()
{
        set("short", "南熏殿");
        set("long", @LONG
南熏殿裡的木構, 藻井和天花, 彩畫均極富麗. 凡立新帝, 都要在
這裡給其母後上尊號, 並舉行冊封大典, 閣臣在此寫金寶冊. 這裡存著
歷代帝後及先聖名賢的圖像.
LONG
        );
        set("exits", ([
                "north"     : __DIR__"wuying",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2810);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}