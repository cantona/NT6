// /d/yixing/clshishi.c
// Last Modified by winder on Jul. 12 2002

inherit ROOM;

void create()
{
        set("short", "石室");
        set("long", @LONG
昏暗的石屋沒有窗户，乃是長樂幫私設的刑堂及囚室。周圍擺放
着幾件刑具，牆上有些新舊不一的血痕，令人不寒而慄。室內甚是潮
濕，頭頂不時滴下水珠。
LONG );
        set("exits", ([
                "west" : __DIR__"clyongdao",
        ]));
        set("objects",([
                __DIR__"npc/cl_zhan" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", 309);
	set("coor/y", -991);
	set("coor/z", -1);
	setup();

        replace_program(ROOM);
}