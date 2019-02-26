inherit ROOM;

void create()
{
        set("short", "宣德門");
        set("long", @LONG
宣德門是開封的北城門，由於這裏歷來是皇城所在。城牆建築得
格外牢固。兩邊的藏兵洞主可容千人，其作用是當敵人攻破城門之時，
由伏兵殺出，截殺敵人。
LONG );
        set("objects", ([
                  __DIR__"npc/guanbing" : 2,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "kaifeng");
        set("exits", ([
                  "south" : __DIR__"road6",
                  "north" : __DIR__"jiaowai",
        ]));

	set("coor/x", -5060);
	set("coor/y", 2260);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}