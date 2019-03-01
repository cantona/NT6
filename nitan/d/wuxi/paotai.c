// Room: /d/wuxi/paotai.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "要塞炮台");
        set("long", @LONG
這已經來到了長江邊了，官府在此修築了江陰要塞炮台。四尊古銅
色的神威大炮巍然佇立，黑洞洞的炮口直對著江面。炮台上幾名官兵來
回巡視，看見你，不耐煩地沖你一揮手，叫你趕快離開這兒。炮台下方
立著一個巨大的木牌(pai)，老遠就能看見上面的字。
LONG );
        set("outdoors", "wuxi");
        set("item_desc", ([
                "pai" : "
※〈〉要塞方圓五十裡江面，禁止打漁渡船！〈〉※\n",
        ]));
        set("exits", ([
                "south"  : __DIR__"road6",
        ]));
        set("objects", ([
                __DIR__"npc/junshi" : 4,
        ]));
        set("coor/x", 1040);
	set("coor/y", -650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}