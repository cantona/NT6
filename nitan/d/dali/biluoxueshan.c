//Room: /d/dali/biluoxueshan.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","碧羅雪山");
        set("long",@LONG
你身處一片大雪山之中，此地只是半山腰，卻已經積雪皚皚，寒
風刺骨了。仰頭望去，銀白的峰尖似在雲中，天空也藍得特別深邃。
由此向上的山顛杳無生命的蹤跡，只向下百丈的山腰便是樹木蒼鬱、
飛禽走獸橫行的世界了。向東不遠有一條大河流過，在崇山峻嶺之間
沖擊出一片谷地。
LONG);
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "eastdown"   : __DIR__"shanlu2",
            "westdown"   : __DIR__"lushuieast",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19190);
	set("coor/y", -6870);
	set("coor/z", 40);
	setup();
        replace_program(ROOM);
}