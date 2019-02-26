inherit ROOM;

void create()
{
        set("short", "丐幫中州分舵");
        set("long", @LONG
這裏是丐幫設在中州府的分舵。破廟角落中散放着一些稻
草和破棉被，正中的神像早已被人搬走，如今被一幫叫化子佔
了地方，幾隻破瓦罐散落在廟中各處，原來是盛滴水的。
LONG);
        set("no_clean_up", 0);
        set("outdoors", "zhongzhou");
        set("exits", ([
                  "out" : __DIR__"guandimiao",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("coor/x", -9071);
	set("coor/y", -981);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}