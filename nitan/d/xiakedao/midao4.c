// midao4.c 密道

inherit ROOM;

int do_break(string arg);
void create()
{
        set("short", "密道");
        set("long", @LONG
這是一條很長的祕密通道，四周是堅硬的石壁，你什麼也看不
見，只能摸索前進。突然你走到了路的盡頭，這是個死路，你還是
回去吧。
LONG );
        set("item_desc",([
            "shibi" : "唉!石壁有什麼可看的，不過這側的石壁和其他的不同卻是真的。
呀，它是一個石門(men)哇!\n",
        ]));
        set("exits", ([
                "east" : __DIR__"midao3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3090);
        set("coor/y", -25000);
        set("coor/z", -20);
        setup();

}
void init()
{
        add_action("do_break","break");
}
int do_break(string arg)
{
        int n;
        n=query("neili", this_player());
        if( !arg || arg!="men")
        {
            write("不要隨意打破別人的東西。\n");
            return 1;
        }
        message_vision("$N在石門前站定，深吸一口氣，兩掌同時拍出。\n", this_player());
        if (n >200)
        {
            message_vision("$N丹田一運氣，猛的一拍，石門慢慢的開了。\n", this_player());
            set("exits/west",__DIR__"midao5");
            set("neili", n-200, this_player());
            remove_call_out("close");
            call_out("close",5, this_object());
        }
        else
        {
            message_vision("$N丹田一運氣，猛的一拍，石門卻絲毫沒動。\n", this_player());
            set("neili", 0, this_player());
        }
        return 1;
}

void close(object room)
{
        message("vision","石門自動的合上了。\n", room);
        delete("exits/west", room);
}