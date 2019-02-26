inherit ROOM;

void create()
{
 set("short", "西大街");
        set("long", @LONG
開封府內西面的主要交通要道，街道兩邊店鋪林立，行人車馬如
梭商販的吆喝，市民與小販的討價還價，喧鬧無比。南邊不遠就是延
慶觀。東面是龍亭園。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"wroad2",
                  "east" : __DIR__"tinyuan",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5070);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}