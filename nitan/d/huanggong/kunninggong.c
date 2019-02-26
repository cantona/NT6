// Room: /d/huanggong/kunninggong.c

inherit ROOM;

void create()
{
        set("short", "坤寧宮");
        set("long", @LONG
這是皇后的寢宮. 這裏與前面皇上的乾清宮, 象徵天地乾坤, 紫徵
正中. 坤寧意為大地安寧. 後宮的東西六院則象徵十二星宿. 這裏是皇
帝大婚的洞房, 也是祭祀薩滿教諸神的地方.
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
                 "west"  : __DIR__"gong4",
                 "east"  : __DIR__"gong9",
                 "south" : __DIR__"jiaotaidian",
                 "north" : __DIR__"kunningmen",
        ]));
        set("objects", ([ /* sizeof() == 4 */
                __DIR__"npc/getong" : 1,
        ]));

	set("coor/x", -2810);
	set("coor/y", 7771);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}