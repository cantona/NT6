inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
北面就是汝州城的知府衙門，雖然未經什麼修繕，但是略略掉漆的
紅木白牆卻顯現出一番更加威嚴肅穆的感覺。東去是汝州城中心，這裡
也沒有什麼店舖。
LONG
        );

        set("exits", ([
                "north" : __DIR__"yamen-damen",
                "south" : __DIR__"yingbin-lou1",
                "west" : __DIR__"ximen",
                "east" : __DIR__"ruzhou",
        ]));


        set("outdoors", "ruzhou");
	set("coor/x", -6770);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
