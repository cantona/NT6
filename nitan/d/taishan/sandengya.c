// Room: /d/taishan/sandengya.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "三蹬崖");
        set("long", @LONG
沿階而上，來到三蹬崖，上有巨石如屋，明萬歷年間，盛夏遇暴風
雨，石自山巔墜此，柯紹皋題“飛來石”。御帳坪東有望駕石，如老翁
拱立。
LONG );
        set("exits", ([
                "eastdown"   : __DIR__"yunbu",
                "westup"     : __DIR__"wudafu",
        ]));
        set("outdoors", "taishan");
        set("no_clean_up", 0);
        set("coor/x", 50);
	set("coor/y", 210);
	set("coor/z", 110);
	setup();
        replace_program(ROOM);
}