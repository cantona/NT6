inherit ROOM;

void create()
{
        set("short", "二樓雅座");
        set("long", @LONG
這裏相對樓下比較安靜，環境更加幽雅，擺設更精緻，服務也更是周
到。但收費也會稍微的高那麼一點，但更重要的是坐在這裏你能欣賞到説
書先生所説的一段段生動有趣，引人入勝的故事，所以一些上了年紀的老
人總是整天捧了個茶壺座在這裏。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "down" : __DIR__"chalou",
                  "west" : __DIR__"shuoshu",
        ]));
        set("objects", ([
                "/d/beijing/npc/chake" : 1,
        ]));
	set("coor/x", -7000);
	set("coor/y", 2160);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}