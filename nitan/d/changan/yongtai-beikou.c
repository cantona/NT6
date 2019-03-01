//Room: yongtai-beikou.c

inherit ROOM;

void create ()
{
        set ("short", "永泰北口");
        set("long", @LONG
麒祥街的西盡頭，一根三丈多高的旗桿之上，挑起了四盞鬥大的
燈籠，每當暮色降臨，這裡燈火通明。北面是一家珠寶行，裡面隱隱
散出誘人的珠光寶氣，很多婦人路過這裡都不免要往裡瞧一瞧。南方
通向永泰大道。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "east" : "/d/changan/qixiang1",
                "north" : "/d/changan/zhubaohang",
                "south" : "/d/changan/yongtai-dadao1"
        ]));

        set("outdoors", "changan");  
        set("coor/x", -10760);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}