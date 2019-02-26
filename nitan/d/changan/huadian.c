//Room: huadian.c

inherit ROOM;

void create ()
{
        set ("short", "花店");
        set("long", @LONG
還沒進門，你就已經聞到一股清新的花香。店中各種名花，琳琅
滿目，不乏珍奇異種。來客不分高低貴賤，這裏的主人總是笑臉相迎。
許多城中的小夥子都喜歡在這兒逗留，想挑選一些美麗的鮮花送給心
上的姑娘。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "south" : "/d/changan/huarui3",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/girl" : 1,
        ]));

        set("coor/x", -10730);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}