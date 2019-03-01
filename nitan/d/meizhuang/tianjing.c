// tianjing.c
inherit ROOM;

void create()
{
        set("short", "大天井");
        set("long", @LONG
你走過一個大天井，天井左右各植一棵老梅，枝幹如鐵，極是蒼
勁。往南是梅莊大門，北面是大廳。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "north" : __DIR__"dating",
        ]));
        set("objects", ([ /* sizeof() == 2 */
            __DIR__"npc/huyuan" : 1,
        ]));
        set("outdoors", "meizhuang");
//        set("no_clean_up", 0);

        setup();
//        replace_program(ROOM);
}
void init()
{
        add_action("do_open", "open");
}
int do_open(string arg)
{
        object room;

        if (query("exits/south"))
                return notify_fail("大門已經是開着了。\n");

        if (!arg || (arg != "gate" && arg != "south"))
                return notify_fail("你要開什麼？\n");

        if(!( room = find_object(__DIR__"gate")) )
                room = load_object(__DIR__"gate");
        if(objectp(room))
        {
                set("exits/south", __DIR__"gate");
                message_vision("$N使勁把大門打了開來。\n", this_player());
                set("exits/north", __FILE__, room);
                message("vision", "吱地一聲，裏面有人把大門打開了。\n", room);
                remove_call_out("close_gate");
                call_out("close_gate", 10);
        }

        return 1;
}

void close_gate()
{
        object room;

        if(!( room = find_object(__DIR__"gate")) )
                room = load_object(__DIR__"gate");
        if(objectp(room))
        {
                delete("exits/south");
                        message("vision", "護院上前把大門關了起來。\n", this_object());
                delete("exits/north", room);
                message("vision", "乒地一聲，裏面有人把大門關上了。\n", room);
        }
}
