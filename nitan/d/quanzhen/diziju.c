// diziju.c 弟子居
// Winder Oct.10 1998

inherit ROOM;
int do_pull(string arg);

void create()
{
        set("short", "弟子居");
        set("long", @LONG
這裏是全真教弟子居住的房間。房間很大，整齊地鋪着一排一排
的牀，牀上被褥都摺疊得整整齊齊，但是一個人都沒有，也許所有的
弟子都去練功去了。靠牆的地方有一個櫃子(cabinet)。
LONG
        );
        set("sleep_room",1);
        set("exits", ([
                "north" : __DIR__"jingxiushi",
        ]));
        set("item_desc", ([
            "cabinet": "一個櫃子，也許是堆放衣物用的。\n"
        ]) );
        set("no_clean_up", 0);
        set("coor/x", -2730);
        set("coor/y", 100);
        set("coor/z", 170);
        setup();
        //replace_program(ROOM);
}

void init()
{
        add_action("do_pull","pull");
}

int do_pull(string arg)
{
        object me=this_player();

        if( !arg || arg != "cabinet" ) {
                return notify_fail("你要拉開什麼？\n");
        }

        message_vision("$N使勁把櫃子拉開，現出一個洞口。原來這裏是密室的入口。\n", this_player());
        set("exits/down", __DIR__"mishi");
        remove_call_out("close");
        call_out("close", 8, this_object());

        return 1;
}

void close(object room)
{
        message("vision","櫃子又吱吱地回到原地，把入口擋住了。\n", room);
        delete("exits/down", room);
}