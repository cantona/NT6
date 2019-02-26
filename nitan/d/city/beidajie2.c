// Room: /city/beidajie2.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
        set("short", "北大街");
        set("long", @LONG
這是一條寬闊的青石街道，向南北兩頭延伸。北邊是北城門通向
城外。南邊顯得很繁忙。東邊是一座兩層的樓閣，掛着『太白遺風』
的招簾，門額上懸掛一方橫匾，『醉仙樓』三字擦得閃閃發亮，乃是
蘇學士的手筆。陣陣酒肉香酒香讓你垂涎欲滴。西邊是一座古樸的廟
宇，香火繚繞，那就是天下學武之人所共同敬仰的武廟了。
LONG );
        set("outdoors", "city");
        set("objects", ([
            "/d/city/npc/meipo" : 1,
        ]));
        set("exits", ([
                "east"  : "/d/city/zuixianlou",
                "south" : "/d/city/beidajie1",
                "west"  : "/d/city/wumiao",
                "north" : "/d/city/beimen",
        ]));
	set("coor/x", 0);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}