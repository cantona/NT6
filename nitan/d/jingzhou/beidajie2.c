inherit ROOM;

void create()
{
        set("short", "北大街");
        set("long", @LONG
這是一條寬闊的青石街道，向南北兩頭延伸。北邊是北城門通向
城外。南邊顯得很繁忙。東邊是一家小飯館，門額上寫着『唐氏飯莊
』幾個字，陣陣酒肉香酒香讓你垂涎欲滴。西邊是一間藥店。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                //"east" : __DIR__"libailou",
                "east" : __DIR__"shupu",
                "south" : __DIR__"beidajie1",
                "west" : __DIR__"yaopu",
                "north" : __DIR__"jzbeimen",
        ]));
        set("objects", ([
                "/d/beijing/npc/liumang" : 1,
        ]));
        set("coor/x", -7100);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}