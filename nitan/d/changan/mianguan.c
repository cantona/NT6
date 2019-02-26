//Room: mianguan.c

inherit ROOM;

void create ()
{
        set ("short", "麪館");
        set("long", @LONG
據説這麪館十幾年前就在這裏了，而且不論颳風下雨，不論過年
過節，這麪館從未休息過一天。所以城裏的夜遊神都放心得很，因為
就算回家老婆不開門，至少還可以在老張的麪館裏吃上一碗熱氣騰騰
的牛肉麪。
LONG );
        //set("item_desc", ([" *** " : " *** ", ]));
        set("exits", 
        ([ //sizeof() == 1
                "south" : "/d/changan/huarui2",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/laozhang" : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -10740);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}