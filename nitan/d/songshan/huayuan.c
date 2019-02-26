// Room: /d/songshan/huayuan.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "花園");
        set("long", @LONG
這是一個小園子，三面池塘，北面通向後庭。園中栽着不少奇花異
卉，山石古拙，顯是花了不菲的精力和財力。幾條碎石小路在茵茵草地
和葱蘢灌木中交疊，山風吹過，撒下一地花瓣。
LONG );
        set("exits", ([
                "north" : __DIR__"houting",
                "south" : __DIR__"chitang",
                "east"  : __DIR__"eastpath3",
                "west"  : __DIR__"westpath3",
        ]));
        set("outdoors", "songshan");
        set("no_clean_up", 0);
        set("coor/x", -20);
        set("coor/y", 920);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}