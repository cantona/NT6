inherit ROOM;

void create()
{
        set("short", "龍亭園");
        set("long", @LONG
這裏是一片花木葱鬱的園林。園林的南北兩邊分別是揚家湖和潘
家湖，湖中碧波盪漾，湖邊垂柳依依，芳草如茵。從此向東是龍亭大
殿，西面是西大街道。
LONG );
        set("objects", ([
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"longting",
                "west" : __DIR__"wroad3",
        ]));
        set("objects", ([
                CLASS_D("lingxiao") + "/shiqing" : 1,
        ]));

        set("outdoors", "kaifeng");

	set("coor/x", -5060);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}