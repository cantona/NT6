inherit ROOM;

void create()
{
        set("short", "大驛道");
        set("long", @LONG
你走在一條塵土飛揚的大驛道上。北上就是北京城。挑擔子的、
行商的、趕着大車的馬伕、上京趕考的書生，熙熙攘攘，非常熱鬧。
不時還有兩三騎快馬從身邊飛馳而過，揚起一路塵埃。西邊有個小攤，
許多人在那裏歇息。
LONG );
        set("exits", ([
                "north" : "/d/beijing/road4",
                "south" : "/d/beijing/road9",
                "west" : "/d/beijing/xiaotan"                
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2770);
	set("coor/y", 7570);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}