inherit ROOM;

void create()
{
	set("short", "臥室");
	set("long", @LONG
這裡就是郭靖和黃蓉的臥室。屋子裡的陳設很簡單。門的
左邊有一張軟床。床上的被褥被疊得整整齊齊。床頭正對的地
方擺著一張梳妝台。桌上擺著一個光亮的銅鏡，銅鏡旁邊的花
瓶裡，有一束百合花，正在散發出淡淡的幽香。裡邊放著兩張
木椅，中間是一茶幾，上面擺著一盆山茶花。
LONG );
        set("no_fight", 1);
	set("no_clean_up", 0);
	set("exits", ([
		"west" : __DIR__"guofu_huayuan",
	]));
	setup();
	replace_program(ROOM);
}
