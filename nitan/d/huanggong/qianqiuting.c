// qianqiuting.c

inherit ROOM;

void create()
{
        set("short", "千秋亭");
        set("long", @LONG
前明嘉靖十二年構建修建的千秋亭上圓下方, 抱廈四出, 上層傘狀
圓頂與下層眾多進出的檐角, 組織得極其巧妙.
LONG
);
        set("outdoors", "huanggong");
        set("exits", ([
                "northeast" : __DIR__"yuhuayuan",
        ]) );
        set("objects", ([
                __DIR__"npc/gongnv" : 1,
        ]) );
	set("coor/x", -2830);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}