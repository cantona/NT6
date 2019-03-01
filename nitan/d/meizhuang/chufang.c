inherit ROOM;

void create()
{
        set("short", "廚房");
        set("long", @LONG
你順著香味走到了梅莊的廚房，一位廚師正站在灶台後面笑眯眯
的看著你，他手上拿著一柄鐵勺，用力的把鍋裡煮著的一大堆食物攪
勻，梅莊的弟子們如果餓了，就到這裡來問這位廚師能不能吃飯，一
般來說，他們都不會遭到拒絕的。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "east" : __DIR__"zoulang3",
        ]));
        set("objects", ([ /* sizeof() == 1 */
            __DIR__"npc/chushi" : 1,
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}

