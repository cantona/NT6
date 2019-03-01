// Room: /d/quanzhou/wuliqiao.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "安平橋");
        set("long", @LONG
這就是當代最長的海港大石橋“安平橋”，全橋長五裡，寬丈五，
橋面上舖的都是大石板。石板有的長近十丈，重達五萬斤，橋上有亭子
五座。中亭有歷代重修碑記十三方，石雕武士兩尊，亭柱上還有一幅對
聯(duilian)。
LONG
        );
        set("objects", ([ /* sizeof() == 1 */
        ]));
        set("item_desc", ([ /* sizeof() == 1 */
                "duilian" : "
           世間有佛尊斯佛
           天下無橋長此橋\n",
        ]));
        set("outdoors", "quanzhou");
        set("exits", ([ /* sizeof() == 2 */
                "southup" : __DIR__"shanlu1",
                "north"   : "/d/fuzhou/puxian",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -910);
	set("coor/y", -7500);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}