inherit ROOM;

void create()
{
        set("short", "正北門");
        set("long", @LONG
南嶽大廟正北門是大廟的後門，正在衡山山麓。回望大廟，紅牆
黃瓦，金碧輝煌。北面是上山的六小路。
LONG );
        set("exits", ([ 
                "south"  : __DIR__"houdian",
                "northup": __DIR__"shanlu1",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6890);
	set("coor/y", -5610);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}