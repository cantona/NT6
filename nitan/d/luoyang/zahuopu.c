inherit ROOM;

void create()
{
        set("short", "雜貨鋪");
        set("long", @LONG
不知為什麼洛陽雖大，卻只有這一間雜貨鋪。所以每天人來人往，也
挺熱鬧。這裏無論是油鹽醬醋，還是大米白麪，各種日常用品也是樣樣齊
全。中間一張櫃枱，店主人正坐在櫃枱後面算帳。據説私底下他也賣一些
貴重的東西。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"sroad4",
        ]));
        set("objects", ([
                __DIR__"npc/xiao" : 1,
        ]));
	set("coor/x", -7000);
	set("coor/y", 2140);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}