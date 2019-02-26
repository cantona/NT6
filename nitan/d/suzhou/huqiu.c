// Room: /d/suzhou/huqiu.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "虎丘山");
        set("long", @LONG
虎丘山因其山形似蹲虎而得名。又相傳吳王葬後，有白虎出現其墓
上，故名虎丘。山前絕巖幽谷，花木繁茂，景色綺麗，後山空濛寬廣，
石壁樹立，氣勢雄渾。有“山藏寺裏”的特色，遂被譽為“吳中第一名
勝”。
LONG );
        set("outdoors", "suzhou");
//        set("no_clean_up", 0);
        set("exits", ([
                "northeast" : __DIR__"road1",
                "south"      : __DIR__"toumenshan",
        ]));
        set("objects", ([
                "/d/hangzhou/obj/shuzhi" : 1,
                "/d/hangzhou/obj/eluanshi" : 1,
        ]));
	set("coor/x", 1100);
	set("coor/y", -1020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}