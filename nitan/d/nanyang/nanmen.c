// Room: /d/nanyang/nanmen.c
// Last Modified by winder on Nov. 20 2001

inherit ROOM;
void create()
{
        set("short","南城門");
        set("long",@LONG
這裡是南陽南門。南陽處南陽盆地內，水土肥沃，物產豐饒。再往
南就是漢水了，偶爾有漁夫在河上張網捕魚。
LONG);
        set("exits",([
                "north"   : __DIR__"dajie1",
                "south"   : __DIR__"hanshui2",
        ]));
        set("objects",([
                "/d/city/npc/bing" : 1,
        ]));
        set("outdoors","nanyang");
	set("coor/x", -6940);
	set("coor/y", 750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}