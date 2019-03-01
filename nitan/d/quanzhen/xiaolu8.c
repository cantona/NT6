// xiaolu8.c 後山小路
// xiaolu8.c 後山小路

inherit ROOM;
string l_pattern();

void create()
{
        set("short", "後山小路");
        set("long", @LONG
這裡是後山上的小路。這條小路好象不是人工刻意修出來的，
也許只是以前的採藥人踩多了，現出這樣一條小路來。山壁上好象
刻著一些什麼字跡(pattern)。走到這裡，你好象迷路了。
LONG
        );
        set("outdoors", "chongyang");
        set("exits", ([
                "east" : __FILE__,
                "west" : __DIR__"xiaolu7",
                "north" : __DIR__"xiaolu4",
                "south" : __FILE__,
        ]));
        set("item_desc",([
          "pattern" : (:l_pattern():),
        ]));
        set("no_clean_up", 0);

        set("coor/x", -2680);
        set("coor/y", 120);
        set("coor/z", 170);
        setup();
        //replace_program(ROOM);
}

string l_pattern()
{
        object me=this_player();
        if( query_temp("tmark/指", me) == 1){
                addn_temp("tmark/指", 1, me);
                return("好象是被人用大力金剛指力之類的功夫在山石上刻下一首詩，這
人的指力可真了得。\n");
        }
        else {
                set_temp("tmark/指", 1, me);
                return("山壁上刻著一首詩，不知道是怎麼刻上去的。\n");
        }
}