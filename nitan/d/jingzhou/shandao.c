//Edited by fandog, 02/18/2000

inherit ROOM;
void create()
{
        set("short", "山道");
        set("long", @LONG
這是一條黃泥山道，不時可見江湖中人揹着包袱，彆着刀劍往北走
去。地上有許多車馬碾過的痕跡。
LONG );
        set("exits", ([
                "northeast"  : __DIR__"qingshilu2",
                "west"  : __DIR__"shangang",
        ]));
        set("outdoors", "jiangling");
        set("no_clean_up", 0);
        set("coor/x", -7130);
	set("coor/y", -2100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}