// Room: /d/wuxi/road1.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "東驛道");
        set("long", @LONG
這是一條連接蘇州和無錫的大驛道，富饒的魚米之鄉也使得官府
的所藏十分地殷實，築橋修路自然就舍得花錢了。這裡的路要比別的
地方寬闊得多，路邊的楊柳樹也顯得特別得精神，向西可以看見無錫
的熙春門。北面是一片茂盛的杏樹林，好象有一條小道穿進去。向東
就可以去蘇州了。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"road2",
                "west"  : __DIR__"eastgate",
        ]));
        set("coor/x", 1080);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}