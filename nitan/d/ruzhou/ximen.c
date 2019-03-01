inherit ROOM;

void create()
{
        set("short", "西城門");
        set("long", @LONG
這裡是汝州的西城門。這裡的行人不少。這裡有幾個官兵正在檢查
來往的百姓。旁邊還站著幾個軍官，耀武揚威地站在那裡，不停地指手
畫腳。
LONG
        );

        set("exits", ([
                "east" : __DIR__"xidajie",
                "west" : "/d/songshan/taishique",
        ]));

        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 3,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6780);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
