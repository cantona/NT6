inherit ROOM;

void create()
{
        set("short", "後院");
        set("long", @LONG
這是一個用籬笆圍成的簡易院落，遠處種著幾畦蔬菜。院子中間
一棵高大的柿樹上結滿了鮮紅的果實，旁邊的地上蓋著一張厚厚的草
席(xi)。 
LONG);
       set("outdoors", "wudujiao");

        set("exits", ([
                "north" : __DIR__"minju6",
        ]));
        set("item_desc", ([
                "xi" : "\n一張厚厚的草席蓋在洞口，下面似乎是一個地窖。\n" ,
        ]));
        setup();
}

void init()
{
        add_action("do_move", "pull");
}

int do_move(string arg)
{
        object me,hole;
        string dir;

        me = this_player();
        if (!arg || arg == "") return 0;

        if( arg=="xi" ) {
                message_vision("\n$N掀開蓋在洞口的草席走了下去。\n", this_player());
                me->move(__DIR__"dijiao");
                message_vision("\n蓋在洞口的草席一掀，$N從上面走了下來。\n",me);
        }
        else {
                message_vision("\n$N雙手在空中比劃了幾下，但似乎什麼也沒抓住。\n", this_player());
        }               
        return 1;
}