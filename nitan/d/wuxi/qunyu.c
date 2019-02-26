// Room: /d/wuxi/qunyu.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "羣玉院");
        set("long", @LONG
你一走進來，一眼就看到大廳的牆上掛着一幅幅春宮圖(tu)，一下
子就明白了這是什麼地方。廳內到處張燈結綵，香氣撲鼻。幾名打扮得
妖里妖氣的女人分站兩旁對你發出媚笑。老鴇上上下下、前前後後招呼
着客人。
LONG );
        set("exits", ([
                "west" : __DIR__"southroad2",
        ]));
        set("item_desc", ([
                "tu" : "",
        ]));
        set("objects", ([
                __DIR__"npc/laobao" : 1,
        ]));
        set("coor/x", 1050);
	set("coor/y", -760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}