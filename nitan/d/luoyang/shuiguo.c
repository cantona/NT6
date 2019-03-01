inherit ROOM;

void create()
{
        set("short", "水果店");
        set("long", @LONG
這間水果店地方不大，但卻有著豐富的水果品種：如香蕉，蘋果，橘
子，生梨，西瓜，荔枝等等，尤其是那荔枝，古語有詩雲：“日啖荔枝三
百顆，不辭長做嶺南人”。可見無論是當地居民還是來往遊客都很喜歡光
顧這裡。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"sroad6",
        ]));
        set("objects", ([
                __DIR__"npc/xiaofan" : 1,
        ]));
	set("coor/x", -7000);
	set("coor/y", 2120);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}