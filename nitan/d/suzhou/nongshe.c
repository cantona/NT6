// nongshe.c
// By Jpei

inherit ROOM;

void create()
{
        set("short", "農舍");
        set("long",@long
這是一間普通的農舍，裏面陳設相當簡陋，頂上的茅草也不整齊，
露出好幾個天牀。一位農夫正坐在門邊抽旱煙。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "west" : __DIR__"caoebei",
        ]));
        set("objects", ([
                __DIR__"npc/axiang" : 1,
        ]));
	set("coor/x", 1040);
	set("coor/y", -1100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}