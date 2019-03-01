inherit ROOM;

void create()
{
        set("short", "柴房");
        set("long", @LONG
這間小柴房堆滿了鬆柴，多是賣柴的漢子因為賣不出去而拿來換
上一餐的。也有些是窮苦人上山砍了奉獻給佛祖的，好在開封邊的野
豬林多的是鬆樹，所以倒也從沒缺過柴禾。
LONG );

        set("objects", ([
                  __DIR__"npc/obj/chaihe1" : 1,
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"zoulang2",
                  "east" : __DIR__"caidi3",
        ]));

	set("coor/x", -5010);
	set("coor/y", 2220);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}