//Room: minju3.c

inherit ROOM;

void create ()
{
        set ("short", "民居");
        set("long", @LONG
這所房子看起來好像已經很久沒人住了。雕花漆彩的門窗已是破
敗不堪，滿目蛛絲鼠糞，牆上地下到處都是灰塵，一隻老鼠跑來跑去。
院子裏雜草叢生，宅外牆滿是青苔蜘網，顯得既荒涼又陰森。四周死
一般的沉寂。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/huarui3",
        ]));

        set("coor/x", -10730);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}