// Room: /d/suzhou/road5.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "湖畔大道");
        set("long", @LONG
你走在一條青石大道上，人來人往非常繁忙，不時地有人騎着馬匆
匆而過。北面就是蘇州城了。西南邊岸邊，波光粼閃，白帆點綴，便是
周遭五百里的太湖了。湖面綠波上漂着一葉葉的小舟, 一陣陣悦耳的小
曲兒隨着湖上的輕風不時飄入你的耳中。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "north"     : __DIR__"road6",
                "southwest" : "/d/yanziwu/hupan",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
	set("coor/x", 1110);
	set("coor/y", -1170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}