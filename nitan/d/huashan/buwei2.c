// buwei2.c

inherit ROOM;

void create()
{
        set("short", "寢室");
        set("long", @LONG
這裡是岳不群的寢室，岳不群在江湖上人稱「君子劍」，他雖為
一大派掌門，可他的臥室卻布置的很簡單。除了一張床，幾只箱子，
牆角有張化妝台，只有靠牆一張紅木書桌(desk)還顯得略有氣派。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "south" : __DIR__"buwei1",
        ]));
        set ("item_desc", ([
                "desk" : 
"這是一張很結實的紅木書桌，桌面上擺著幾只狼毫筆，磨了一半的墨，\n"
"還有一疊未用的白紙。\n"
        ])  ) ;

        set("no_clean_up", 0);
        setup();
}
void init()
{
        add_action("do_move", "move");
}

int do_move(string arg)
{
        object paper;

        if( !arg || arg=="" ) return 0;

        if( arg=="desk" )
        {
                if (!query("hs_trigger"))
                {
                        message_vision(
"$N輕輕的推了推書桌，沉重的書桌似乎根本沒動...，突然從書桌和\n"
"牆壁之間飄落出一張紙。\n", this_player());
                        paper = new(__DIR__"obj/paper");
                        paper->move(__FILE__);
                        set("hs_trigger", 1);
                        return 1;
                }
                message_vision(
"$N輕輕的推了推書桌，沉重的書桌紋絲不動。\n", this_player());
                return 1;
        }
        return 0;
}