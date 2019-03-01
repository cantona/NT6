//Room: yongtai-nankou.c

inherit ROOM;

void create ()
{
        set ("short", "永泰南口");
        set("long", @LONG
華瑞街和永泰大道的交叉口，一根三丈多高的旗桿之上，挑起了
四盞鬥大的燈籠，每當暮色降臨，這裡燈火通明。南面是一家包子舖，
北方通向永泰大道。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "east" : "/d/changan/huarui1",
                "north" : "/d/changan/yongtai-dadao5",
                "south" : "/d/changan/baozipu"
        ]));

        set("outdoors", "changan");  
        set("coor/x", -10760);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}