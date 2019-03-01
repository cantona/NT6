// Last Modified by Winder on May. 21 2001
// Room: /d/fuzhou/puxian.c

inherit ROOM;

void create()
{
        set("short", "莆仙平原");
        set("long", @LONG
你走在莆仙平原上。這裡物產豐饒，人煙稠密，望北就是福州府城
了。往南就進入閩南。往西望去，是一帶丘陵。閩中丘陵苦不在高，連
綿起伏不斷。密密層層的樹叢中，一條山路蜿蜒前伸。
LONG );
        set("exits", ([
                "north" : __DIR__"zhongzhou",
                "south" : "/d/quanzhou/anpingqiao",
                //"west"  : "/d/nanshaolin/shanlu1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "fuzhou");
	set("coor/x", -80);
	set("coor/y", -6230);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}