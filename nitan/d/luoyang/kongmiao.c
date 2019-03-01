inherit ROOM;

void create()
{
        set("short", "孔廟");
        set("long", @LONG
這裡是孔廟正殿，內有孔夫子像。歷代皇帝都懂得利用儒教思想來鞏
固自己的江山社稷，當朝皇帝自然也不例外。不論何人到此，都畢恭畢敬
地上香禮拜。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"wroad2",
        ]));
        set("objects", ([
                "/d/beijing/npc/shusheng2" : 1,
        ]));
	set("coor/x", -7010);
	set("coor/y", 2190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}