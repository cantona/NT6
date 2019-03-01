//ROOM neishi.c
inherit ROOM;
void init();
int do_move(string);
void create()
{
        set("short", "成德殿後廳");
        set("long", @LONG
這裡是日月神教的後廳。看上去滿是灰塵，但中間有一個瓷碗 (
wan)，似乎有古怪。
LONG );
        set("exits", ([
                "east" : __DIR__"house1",
                "west" : __DIR__"restroom",
                "south":__DIR__"chengdedian",
        ]));
        set("objects" , ([
             __DIR__"npc/zish" : 4,
        ]));
        set("item_desc", ([
            "wan" : "這是一個自漢代流傳下的古董，很別致。\n",
        ]));
//        set("no_clean_up", 0);
        setup();
}
void init()
{
        add_action("do_circle", "circle");
        add_action("do_circle", "zhuan");
}

int do_circle(string arg)
{

        object me = this_player();
        object room;

        if ((arg != "wan") || !arg)
          return notify_fail("你要旋什麼？\n");
        if( query("str", me)<12 )
          return notify_fail("你臂力連旋不開什麼！\n");
        if(!( room = find_object(__DIR__"didao1")) )
           room = load_object(__DIR__"didao1");
        if(!objectp(room))  return notify_fail("ERROR:not found 'didao1.c' \n");
        if (!query("exits/down"))
          {
          set("exits/down", __DIR__"didao1");
          message_vision("$N將碗旋開，見側牆打開露，出一個黑幽幽的洞口.\n",me);                    
         set("exits/out", __DIR__"huoting", room);
         return notify_fail("一定要抓緊時間，走後將它關上。\n");
        }
        if(!( room = find_object(__DIR__"didao1")) )
           room = load_object(__DIR__"didao1");
        if(!objectp(room))  return notify_fail("ERROR:not found 'didao1.c' \n");
        if (!query("exits/down"))
          {
          set("exits/down", __DIR__"didao1");
          message_vision("$N旋動了碗，只見側牆打開，露出一個黑幽幽
              的洞口。\n",me);
          set("exits/out", __DIR__"huoting", room);
          message("vision", "外面傳來一陣搬動碗的聲音，一束光線射了進來。
          \n", room);
          }
         else
          {
          delete("exits/down");
          message_vision("很快碗又搬回了原位。側牆上的洞口又被封住了。\n",me);
          delete("exits/out", room);
          message("vision", "外面傳來一陣搬動碗的聲音，洞口被封住了。\n", room);
          }
       return 1;
}