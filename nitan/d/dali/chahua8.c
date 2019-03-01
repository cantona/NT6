//Room: /d/dali/chahua8.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","茶花園後門");
        set("long", @LONG
大理茶花冠絕天下，鎮南王府的茶花自然更非凡品。你站在茶花
園後門口，對著滿園春色，不禁大喜過望。東邊就進園了，西面是一
條石舖甬道。
LONG );
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "east"   : "/d/dali/chahua7",
            "west"   : "/d/dali/yongdao2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19081);
	set("coor/y", -6821);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}