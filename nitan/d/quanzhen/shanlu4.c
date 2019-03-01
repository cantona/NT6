// /d/quanzhen/shanlu4.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "道路");
        set("long", @LONG
此處位於終南山山腳。巍峨的終南山，自古以來就是歷代名人遊
覽的聖地。它西起甘肅的岐山，東至陝西的潼關，其間跨越十餘縣，
連綿八百餘裡。素有萬裡終南山之稱。往東可看見一座寺廟。往西是
一條通往密林的幽靜小路。往北可上終南山.
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "northup" : __DIR__"shanlu8",
                "east"    : __DIR__"puguangsi",
                "west"    : __DIR__"shanlu5",
                "south"   : __DIR__"shanjiao",
        ]));

        set("coor/x", -3130);
        set("coor/y", 0);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}