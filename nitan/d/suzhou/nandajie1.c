// Room: /d/suzhou/nandajie1.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "南大街");
        set("long", @LONG
南大街乃是城裡的繁華地段，一到晚上，更是一派燈紅酒綠，尤為
熱鬧。笑聲、歌聲、琴聲、簫聲，匯成一片送入了你的耳朵，你不禁心
猿意馬，很想就此停步享受一番。蘇州的城裡秀麗景色此時已使你心曠
神怡，此時此刻只想與這大自然秀麗的景色融為一體。從這裡看去，蘇
州南城的街景是一片喧鬧。在街的東北面是一個茶館，正東望去是一座
蘇州園林。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"shizilin",
                "west"      : __DIR__"jubaozhai",
                "north"     : __DIR__"baodaiqiao",
                "south"     : __DIR__"nandajie2",
                "southwest" : __DIR__"shuyuan",
                "northeast" : __DIR__"chaguan",
        ]));
	set("coor/x", 1110);
	set("coor/y", -1070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}