//Room: liande-nankou.c

inherit ROOM;

void create ()
{
        set ("short", "連德南口");
        set("long", @LONG
華瑞街的東盡頭，一根三丈多高的旗杆之上，挑起了四盞斗大的
燈籠，每當暮色降臨，這裏燈火通明。南面有一家小酒館，裏面隱隱
傳來划拳行令的聲音。北方通向連德大道。
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "west" : "/d/changan/huarui6",
                "north" : "/d/changan/liande-dadao5",
                "south" : "/d/changan/xiaojiuguan"
        ]));

        set("outdoors", "changan");  
        set("coor/x", -10680);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}