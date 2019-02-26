inherit ROOM;

void create()
{
        set("short", "北城門");
        set("long", @LONG
這裏是汝州的北城門。這裏的行人不少。這裏有幾個官兵正在檢查
來往的百姓。旁邊還站着幾個軍官，耀武揚威地站在那裏，不停地指手
畫腳。
LONG
        );

        set("exits", ([
                "south" : __DIR__"beidajie",
                "north" : "/d/beijing/road10",
        ]));

        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 3,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6760);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
