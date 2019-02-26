inherit ROOM;

void create()
{
        set("short", "金馬枋");
        set("long", @LONG
昆明名勝之一，金馬枋，傳説在每年的一天，其影子和碧
雞枋的影子交相輝印，稱為金碧交輝，巍巍奇觀。
LONG);
        set("outdoors", "kunming");

        set("exits", ([
                "west" : __DIR__"xiaoximen",
                "east"  :__DIR__"jinrilou",
        ]));

        set("objects", ([
                "/d/beijing/npc/old1" : 1,
                "/d/beijing/npc/boy1" : 1,
        ]));
	set("coor/x", -16850);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}