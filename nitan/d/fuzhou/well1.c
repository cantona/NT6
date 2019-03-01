// room: well1.c

inherit ROOM;

int do_use(string arg);
int do_zuan(string arg);

void create()
{
        set("short", "井底");
        set("long", @LONG
這是在一口枯井的井底。光線極暗，什麼也看不清。
LONG );
        set("exits", ([
                "up" : __DIR__"well",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1820);
        set("coor/y", -6310);
        set("coor/z", -20);
        setup();
}

void init()
{
        add_action("do_use", "use");
        add_action("do_zuan", "zuan");
}

int do_use(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("fire", me))  return 0;
        if( arg=="fire" ) {
             write(
             "你點燃了火折，發現井底什麼也沒有。\n"
             );
             return 1;
       }
}

int do_zuan(string arg)
{
      object me;
      me = this_player();

      message_vision(
      "$N像沒頭蒼蠅一樣在黑洞洞的井底瞎鑽，結果一頭撞在井壁的石頭上。\n", this_player());
      if (random(2)==1) {
         write("你覺得你暈乎乎的，似乎撞傻了。\n");
/*
         if (me->query_skill("literate", 1) )
             me->set_skill("literate", me->query_skill("literate", 1)-1);
*/
      }
      else {
         set("qi", 10, me);
         me->unconcious();
      }
      return 1;
}