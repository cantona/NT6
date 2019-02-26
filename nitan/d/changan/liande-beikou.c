//Room: liande-beikou.c

inherit ROOM;

void create ()
{
        set ("short", "連德北口");
        set("long", @LONG
麒祥街的東盡頭，一根三丈多高的旗杆之上，挑起了四盞斗大的
燈籠，每當暮色降臨，這裏燈火通明。北面有一座竹棚，裏面隱隱傳
來唱戲的聲音。南方通向連德大道。
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "west" : "/d/changan/qixiang6",
                "north" : "/d/changan/xiyuan",
                "south" : "/d/changan/liande-dadao1"
        ]));

        set("outdoors", "changan");  
        set("coor/x", -10680);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}