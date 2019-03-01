inherit ROOM;

void create()
{
        set("short", "浴室");
        set("long", @LONG
每年的五月初五日，寺中都會用清水清洗那些佛像。稱為洗佛。
用洗佛的殘水從人的頭頂澆灌而下，稱沐佛恩。雖然水很臟，但大家
都搶了來淋水。當然達官貴人是不會當眾狼狽的所以裡面辟有專門的
小浴室供他們使用。
LONG );
        set("objects", ([
                __DIR__"npc/zhangzao" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"zhongyuan",
                "west" : __DIR__"yushi2",
        ]));

	set("coor/x", -5050);
	set("coor/y", 2200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}