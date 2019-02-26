// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "富貴如意廳"); 
        set("long", @LONG
這是圓月山莊的正廳『富貴如意廳』，房子很大，建築也很堂皇，
如果擺酒席可以放下十幾張桌子，但令人奇怪的是，偌大一間屋子，
除了一張偌大的牀以外，便什麼也沒有了，而那張牀簡直比廚房裏的
鍋子還油膩，似乎無論往什麼地方隨手一摸，總會摸出一兩塊吃剩的
肉，三四根還沒啃完的肉骨頭，更為惱人的是，只見時不時有幾隻老
鼠上躥下跳，整間屋子散發着一種夾雜着濃郁酒氣的怪味。
LONG );
        set("type","house");
        set("valid_startroom", 1);
        set("indoors", "wansong");
        set("exits",([
                "east":__DIR__"shibanlu2",
                "west":__DIR__"suishilu2",
                "south":__DIR__"suishilu1",
                "north":__DIR__"shibanlu4",
        ]) );
        set("objects",([
                CLASS_D("mojiao") + "/liuruosong" : 1,
        ]) );
/*
        set("item_desc", ([
                "牀": "一張偌大的牀，又髒又亂，搖搖晃晃的似乎一推就會散架（ｍｏｖｅ）。\n",
                "bed": "一張偌大的牀，又髒又亂，搖搖晃晃的似乎一推就會散架（ｍｏｖｅ）。\n",
                "偌大的牀": "一張偌大的牀，又髒又亂，搖搖晃晃的似乎一推就會散架（ｍｏｖｅ）。\n"
        ]) );
*/
        set("coor/x",-590);
        set("coor/y",220);
        set("coor/z",80);
        setup();
} 

/*
void init()
{
        add_action("do_move", "move");
} 

int do_move(string arg)
{
        object mice;
        if ( !arg && arg != "bed" && arg != "牀" && arg != "偌大的牀")
                return 0;
        if( query("amount") > 5 )
                return 0;
        message_vision("$N晃了下牀，一隻小老鼠飛塊地躥了出來．\n", this_player());
        mice = new(__DIR__"obj/mouse");
        if(mice) 
                mice->move(this_object());
        addn("amount",1);
        return 1;
} 

void reset()
{
        ::reset();
        set("amount", 0);
}
*/
