inherit ROOM;

void create()
{
        set("short", "兵器庫");
        set("long", @LONG
這裡是兵器庫，到處銀光閃閃，讓人眼花繚亂。寶刀、寶劍、金箍棒，
大刀、長劍、哨棒，短刀、短劍、短棍，各色各樣的兵器應有盡有，你一
時不知道挑什麼好。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"bingyin",
        ]));
        set("objects", ([
                "/clone/weapon/changjian" : 2,
                "/clone/weapon/gangdao" : 2,
                "/clone/weapon/dagger" : 2,
        ]));

	set("coor/x", -7030);
	set("coor/y", 2210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}