// juyan.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "老嫗巖");
        set("long", @LONG
一路過來，山路是越來越險。只見一塊大巖石擋在路中，自空憑
臨，宛似一個老婦彎腰俯視，但形狀陰森可怖，令人望而生畏。不少
遊客在此駐足觀看，往南是一片茂密的鬆林。往北上是一條陡峭的山
路。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "northup"    : __DIR__"shanlu12",
                "southdown"  : __DIR__"shulin3",
        ]));
        set("objects", ([
                CLASS_D("quanzhen")+"/ji": 1,
        ]));

        set("coor/x", -3170);
        set("coor/y", 90);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}