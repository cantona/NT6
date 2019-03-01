//Room: /d/dali/feilihueast.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","妃麗湖東");
        set("long",@LONG
你站在妃麗湖的東岸，腳下的土路繞湖東連接南北的村鎮。眺望
湖中只見輕舟點點，正是捕魚的台夷竹筏。路邊盡是青青竹林，台夷
的竹樓間或出現。向西南去的岔路通往湖西的休獵部，正路向南直達
龍口城。
LONG);
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "south"      : __DIR__"longkou",
            "northwest"  : __DIR__"feilihu",
            "southwest"  : __DIR__"hexi",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19120);
	set("coor/y", -6970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}