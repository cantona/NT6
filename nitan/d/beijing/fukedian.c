inherit ROOM;

void create()
{
        set("short", "虎坊客棧");
        set("long", @LONG
這是京城虎坊路街頭鄰街的一家客棧。客棧不大，前廳掛著一幅
猛虎下山的巨畫。當門掛著對鴛鴦球。球上系著幾個小小的黃銅風鈴。
微風掠過，風鈴發出清脆悅耳的叮咚聲。上有橫批『虎坊客棧』。
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("objects", ([
                "/d/beijing/npc/xiaoer3" : 1,
        ]));
        set("exits", ([
                "north" : "/d/beijing/kediandayuan",
                "south" : "/d/beijing/fu_2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2810);
	set("coor/y", 7660);
	set("coor/z", 0);
	setup();
//        "/clone/board/kedian2_b"->foo();
        replace_program(ROOM);
}