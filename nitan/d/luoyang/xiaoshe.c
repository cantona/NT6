inherit ROOM;

void create()
{
        set("short", "綠竹小院");
        set("long", @LONG
這是一個綠竹遮蔽下的清涼小院，院子裏有五間小舍，左二右三，
均以粗竹子架成。地上擺滿了竹條、竹篾和一個快做好的竹籃子。一個
老翁正在院中劈柴升火做飯。象是感覺到你走進來了，可他連頭也沒給
抬一抬。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"zhulin3",
                "northeast"  :  __DIR__"youshe1",
                "northwest"  :  __DIR__"zuoshe1",
        ]));
        set("objects", ([
                __DIR__"npc/lvzhu" : 1,
                __DIR__"obj/zhudao" : 1,
        ]));
	set("coor/x", -6950);
	set("coor/y", 2150);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}