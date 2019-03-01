inherit ROOM;

void create()
{
        set("short", "破廟");
        set("long", @LONG
這是小巷中的一座破廟，許多殘破的青磚散落在地下，從
牆洞中露出的一根大柱子已看不出本來的顏色，幾個叫花子懶
散的躺在門口。
LONG);

        set("exits", ([  
                "southeast" : __DIR__"xiaoxiang1",          
                "enter":__DIR__"inpomiao",
        ]));
        set("objects",([
                "/d/kaifeng/npc/qigai" : 2,
        ]));

        set("coor/x", -9070);
	set("coor/y", -980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}