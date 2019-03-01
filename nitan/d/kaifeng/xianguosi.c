inherit ROOM;

void create()
{
        set("short", "相國寺");
        set("long", @LONG
大相國寺佔地五百余畝，轄六十四個禪，律院，養僧千余。是京
城最大的寺院和全國佛教活動中心。門前『大相國寺』的匾額乃是當
今御筆親書。大門敞開，多有行人來往。
LONG );
        set("objects", ([
                  __DIR__"npc/zhike" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"qianyuan",
                  "south" : __DIR__"jiedao",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5040);
	set("coor/y", 2170);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}