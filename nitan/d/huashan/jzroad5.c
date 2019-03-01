// Room: /d/huashan/jzroad5.c

inherit ROOM;
void create()
{
        set("short", "中條山密林");
        set("long", @LONG
山路越來越小，周圍茂密森林裡和腳下的茅草封住了路，上不見
天光，後不見歸路(road)，你簡直絕望了。
LONG );
        set("exits", ([
                "northdown" : __DIR__"jzroad4",
        ]));
        set("item_desc", ([
                "road" : "路邊模模糊糊，好象有個碑。可是太暗了實在看不見。\n",
        ]));
        set("no_clean_up", 0);
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
"你點燃了火折，發現是一圍大樹，被削去樹皮的樹幹上書“中條山”三字。
側邊一個樹洞，似乎可以鑽(zuan)過去。\n");
             set_temp("marks/鑽1", 1, this_player());
             return 1;
       }
}

int do_zuan(string arg)
{
        object me;
        me = this_player();

        if( query_temp("marks/鑽1", me)){
             message("vision", me->name() + "側身滋溜一下鑽進樹洞不見了。\n",
                    environment(me), ({me}) );
             me->move(__DIR__"jzroad6");
             message("vision", me->name() + "從樹裡鑽了出來。\n",
                     environment(me), ({me}) );
             delete_temp("marks/鑽1", this_player());
             return 1;
        }
        else {
             write("你想往哪兒鑽?!\n");
             return 1;
        }
}