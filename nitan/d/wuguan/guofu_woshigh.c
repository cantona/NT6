inherit ROOM;

void create()
{
	set("short", "卧室");
	set("long", @LONG
這裏就是郭靖和黃蓉的卧室。屋子裏的陳設很簡單。門的
左邊有一張軟牀。牀上的被褥被疊得整整齊齊。牀頭正對的地
方擺着一張梳粧枱。桌上擺着一個光亮的銅鏡，銅鏡旁邊的花
瓶裏，有一束百合花，正在散發出淡淡的幽香。裏邊放着兩張
木椅，中間是一茶几，上面擺着一盆山茶花。
LONG );
        set("no_fight", 1);
	set("no_clean_up", 0);
	set("exits", ([
		"west" : __DIR__"guofu_huayuan",
	]));
	setup();
	replace_program(ROOM);
}
