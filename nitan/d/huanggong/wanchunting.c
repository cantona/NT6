// wanchunting.c

inherit ROOM;

void create()
{
        set("short", "萬春亭");
        set("long", @LONG
萬春亭, 始建於嘉靖十二年. 亭上圓下方, 抱廈四出, 上層傘狀圓
頂與下層眾多進出的檐角, 組織得極其巧妙. 
LONG
);
        set("outdoors", "huanggong");
        set("exits", ([
                "northwest" : __DIR__"yuhuayuan",
        ]) );
        set("objects", ([
                __DIR__"npc/gongnv" : 1,
        ]) );
	set("coor/x", -2810);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}