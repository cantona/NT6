inherit ROOM;

void create()
{
        set("short",  "碧雞枋" );
        set("long", @LONG
昆明名勝之一，碧雞枋，傳説在每年的一天，其影子和金
馬枋的影子交相輝印，稱為金碧交輝，巍巍奇觀。
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "west" : __DIR__"jinrilou", 
                "east"  :__DIR__"dongmen",
        ]));
        set("objects", ([
                "/d/beijing/npc/jumin1" : 1,
        ]));
	set("coor/x", -16830);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}