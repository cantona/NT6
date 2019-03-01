//Room: /d/dali/shanlu7.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","山路");
        set("long",@LONG
行進在南詔崎嶇的山林中。高山聳立，雨林茂密繁盛，樹木大都
枝杈橫生，給行路帶來額外困難。附近山民經常行走才開出這樣的道
路來，儘管如此，行旅仍然需要挾帶砍刀，隨時準備砍除路邊樹木橫
出的障礙。
LONG);
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "northwest" : __DIR__"nongtian3",
            "eastup"    : __DIR__"shanlu8",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19040);
	set("coor/y", -6880);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}