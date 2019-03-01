// Room: /d/quanzhou/jishi.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "集市");
        set("long", @LONG
這裡是居民購買日常生活用品和商販的場所，各種商品應有盡有，
琳琅滿目。同時這裡也進行著與外國商人的買賣交易。香料、石等是本
地商家最搶手的需求品，因為他們都知道一旦將其運到中原，將會獲得
極豐厚的利潤。不難想象為何這裡長年累月人來人往，川流不息，吵吵
嚷嚷盡是討價還價的聲音。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"huajiaoting",
                "east"  : __DIR__"tumenji",
                "west"  : __DIR__"xinmenji",
        ]));
        set("objects", ([
                __DIR__"npc/xiaofan" : 1,
        ]));
	set("coor/x", -900);
	set("coor/y", -7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}