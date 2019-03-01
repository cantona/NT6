//room: didao1.c
inherit ROOM;

void create()
{
  set("short","秘道");
        set("long", @LONG
這是一條異常幽靜的走廊，四周漆黑一團，你好象什麼都看不見
似的走在裡面，你不覺想到這似乎在每個角落都藏著無限殺機，太恐
怖了，四周毫無聲息，好象掉下一根針都可能聽到。牆上有一個凸起，
象是一個機關(button)。
LONG );

  set("exits",([
      "east" : __DIR__"didao2",
      "west" : __DIR__"didao1",
      "south" : __DIR__"didao5",
  ]));
        set("item_desc", ([
            "button" : "這是一個石頭上雕刻出來的圖像，凸起著令人感覺有點異樣，似乎可以按動(push)。\n",
        ]));

  set("no_clean_up", 0);
  setup();
}
void init()
{
        add_action("do_push","push");
        add_action("do_push","an");
}

int do_push(string arg)
{

        object me = this_player();
        object room;

        if ((arg != "button") || !arg)
        {
                write("你要按什麼？\n");
                return 1;
        }

        if( query("str", me)<12 )
        {
                write("你臂力還按不動什麼！\n");
                return 1;
        }

        if(!( room = find_object(__DIR__"huoting")) )
                room = load_object(__DIR__"huoting");

        if (!query("exits/out"))
        {
                set("exits/out", __DIR__"huoting");
                message_vision("$N按下了機關，只見側牆打開，幾線亮光透射進來。\n",me);
                set("exits/down", __DIR__"didao1", room);
                message("vision", "側牆傳來一陣嘎嘎聲響，露出一個黑黝黝的洞口。\n", room);
        }
        else
        {
                delete("exits/out");
                message_vision("很快機關又變回了原樣。洞口又被封住了。\n",me);
                delete("exits/down", room);
                message("vision", "側牆傳來一陣嘎嘎聲響，洞口被封住了。\n", room);
        }
        return 1;
}
