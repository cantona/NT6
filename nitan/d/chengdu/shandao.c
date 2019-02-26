//Edited by fandog, 02/18/2000

inherit ROOM;
void create()
{
        set("short", "山道");
        set("long", @LONG
這是一條樵夫鄉農踐踏出來的山道，偶而可見一兩個江湖中人揹着
包袱，彆着刀劍走過。北面是一片蓊鬱的山林，南邊就是有名的白帝城
了。
LONG );
        set("exits", ([
                "south" : __DIR__"baidicheng",
                "north" : __DIR__"shennongjia",
        ]));
        set("outdoors", "jiangling");
        set("no_clean_up", 0);
        set("coor/x", -15070);
	set("coor/y", -1820);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}