inherit ROOM;

void create()
{
        set("short", "文廟");
        set("long", @LONG
這裡是文廟正殿，內有孔夫子像。歷代皇帝都懂得利用儒教思想來鞏
固自己的江山社稷，當朝皇帝自然也不例外。不論何人到此，都畢恭畢敬
地上香禮拜。
LONG );
        set("exits", ([
                "west" : __DIR__"nroad3",
        ]));

        set("objects", ([
                "/d/beijing/npc/shusheng1" : 1,
                "/clone/misc/mazedoor" : 1,
        ]));

	set("coor/x", -6980);
	set("coor/y", 2210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}