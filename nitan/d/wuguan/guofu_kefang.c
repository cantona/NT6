inherit ROOM;

void create()
{
	set("short", "客房");
	set("long", @LONG
這裡是郭府客人們的住處，整整齊齊的一排平房。門的左
右兩邊各是一張床，床上的被褥被疊得整整齊齊。床頭正對的
地方擺著一張桌子，旁邊還放著一張椅子。桌上整齊地放著文
房四寶，旁邊還放著幾本書。地上擺著一盆牡丹花，一絲清香
縈繞房中。因為郭靖是當今的大英雄，所以江湖上有不少豪傑
每年都來拜訪他。
LONG);
        set("no_fight", 1);
	set("no_clean_up", 0);
	set("sleep_room", 1);
	set("exits", ([
		"east" : __DIR__"guofu_huayuan",
	]));
	setup();
	replace_program(ROOM);
}
