// /d/beihai/huafang.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "畫舫齋");
        set("long", @LONG
濠濮澗北之畫舫齋，又稱水殿。為一環繞方形遊泳池對稱布置之庭
院，四面迥廊相通。建築坐北朝南，以池水為中心，南為春雨林塘殿，
東西分別是鏡香，觀妙室，四面廳廊回抱，構成一處幽勝的庭院。古柯
庭前有一粗壯繁茂的古槐，相傳已有千年，庭因名古柯。
LONG
        );

        set("exits", ([
                "north"     : __DIR__"houmen",
                "southwest" : __DIR__"dongmen",
                "southeast" : __DIR__"haopu",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -160);
        set("coor/y", 4090);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}