inherit ROOM;

void create()
{
        set("short", "關帝廟");
        set("long", @LONG
關帝廟前一個老大的鐵香爐，因為關老爺忠義守信。所以商人們
訂了協議總要拜一下關帝爺。許多希望能在武舉中得勝的人，也都要
到這廟來燒香。畢竟關帝又被稱為武聖。
LONG );
        set("objects", ([
                  __DIR__"npc/obj/guanyu" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"paifang",
        ]));

	set("coor/x", -5000);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}