//Room: /d/dali/shanlu3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","山路");
        set("long",@LONG
一條的山路蜿蜒穿行在茂密的森林中，向東不遠可達大理國的中
心--大理城，西去則進入深山。由於接近大理中心，這條路修整的相
當平整，儘管山勢崎嶇，行路並不困難。
LONG);
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "west"    : __DIR__"shanlu2",
            "east"    : __DIR__"northgate",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19170);
	set("coor/y", -6860);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}