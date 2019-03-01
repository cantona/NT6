// Room: /d/wuyi/2qu.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "二曲");
        set("long", @LONG
九曲溪盤流于群山之中，沿溪三十六峰，碧水丹山，風光旖麗。奇
峰雲海，山清水秀，號稱“三三水，六六峰”。二曲溪岸西邊就是亭亭
玉立的玉女峰了。東岸是黑乎乎的鐵板嶂。水流到此，倒影著亭亭玉女，
顯得格外嫵媚動人。朱熹《九曲棹歌》曰：“……二曲亭亭玉女峰，插
花臨水為誰容？道人不作陽台夢，興入前山翠幾重。……”
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "west"      : __DIR__"yunvfeng",
                "east"      : __DIR__"1qu",
                "northwest" : __DIR__"3qu",
                "northeast" : __DIR__"tiebanzhan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1390);
        set("coor/y", -5010);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
