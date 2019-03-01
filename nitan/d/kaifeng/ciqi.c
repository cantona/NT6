inherit ROOM;

void create()
{
        set("short", "雅琪軒");
        set("long", @LONG
雅琪軒是間出售官瓷的商店，其間也出售些書畫精品。你瞧了一
下，店舖中四面木架子上大小各類的瓷器，大多是富貴人家用的。象
粗瓷，粗碗之類東西，只能從地攤買了。
LONG );
        set("objects", ([
                  __DIR__"npc/liuzhanggui" : 1,
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"road3",
        ]));

	set("coor/x", -5050);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}