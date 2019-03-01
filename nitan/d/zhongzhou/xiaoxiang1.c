inherit ROOM;

void create()
{
        set("short", "小巷");
        set("long", @LONG
前面看起來好象要到小巷底了，巷中行人越發稀少。西北
角上好象有一座破爛房子，遠遠望去煙霧彌漫，陳舊不堪，原
來是座破廟。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "northwest" : __DIR__"guandimiao",
                  "east" : __DIR__"xiaoxiang",
        ]));
        set("outdoors", "zhongzhou");

        set("coor/x", -9060);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}