inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
這是一條由碎石鋪成的路，雖然有些顛簸，卻很寬闊，南去就是
長江了。不過前面一片亂石，攔住了去路，據説是當年諸葛亮為了阻
止吳兵追趕而設的。
LONG );
        set("objects", ([
                __DIR__"npc/boy" : 1,
                __DIR__"npc/girl" : 1,
        ]));
        set("exits", ([
                "north" : __DIR__"nanshilu",
                "south" : __DIR__"jiangbei",
        ]));

        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -7100);
	set("coor/y", -2100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}