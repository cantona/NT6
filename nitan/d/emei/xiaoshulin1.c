inherit ROOM;

void create()
{
        set("short","小樹林");
        set("long", @LONG
這是峨嵋山金頂華藏庵外的一片小樹林。林中沒有路，但地上依
稀有些足跡，似乎剛有人走過。北面有一扇小窗。
LONG );
        set("outdoors", "emei");
        set("exits", ([
                "south"   : __DIR__"xiaoshulin2", 
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me = this_player();

        if (! arg || arg != "chuang")
                return 0;

        message_vision("$N趁人不注意，跳進窗裏。\n", me);
        me->move(__DIR__"hcawest");
        message_vision("$N從華藏庵外跳窗進來。\n", me);
        return 1;
}