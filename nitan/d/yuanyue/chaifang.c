// This program is a part of NITAN MudLIB

inherit ROOM;
void create()
{
        set("short", "柴房"); 
        set("long", @LONG
圓月山莊的柴房好像並不是堆柴的，而是關人的。柴房裡有蜘蛛，
有老鼠，有狗屎貓尿，爛鍋破碗，有用剩下的煤屑(breeze)。幾乎什
麼都有，就是沒有柴連根柴都沒有。
LONG );
        set("type","house");
        set("indoors", "wansong");
        set("exits",([
                "south":__DIR__"grass4",
        ]) );

        set("item_desc", ([
                "煤屑": "柴房裡到處都是煤屑，你似乎可以打掃一下（ｄｉｇｈｔ）。\n",
                "breeze": "柴房裡到處都是煤屑，你似乎可以打掃一下（ｄｉｇｈｔ）。\n",
        ]) ); 
        set("coor/x",-590);
        set("coor/y",260);
        set("coor/z",80);
        setup();
        
} 
void init()
{
        add_action ("do_dight", "dight");
} 
int do_dight()
{               
        object mh,bo;
        int eff_qi;
        /*
        if (!present("sao ba",this_player())) 
                return notify_fail("你身上沒有掃把，怎麼打掃？\n");
        */
        eff_qi=query("qi", this_player());
        if( eff_qi<query("max_qi", this_player())/10 )
        {
                return notify_fail("你太累了，怎麼打掃？\n");
        }
        this_player()->receive_damage("qi",query("max_qi", this_player())/10);
        if( query("dighted", this_object()) )
        {       message_vision("$N拿著掃把二話不說打掃起來，\n頓時柴房裡揚起漫天的灰塵，簡直嗆得透不過氣，\n辛苦了一番，屋子總算幹凈了些。\n\n", this_player() );
                return 1;
        }
        else if (random(5)) 
        {
                message_vision("$N拿著掃把二話不說打掃起來，\n頓時柴房裡揚起漫天的灰塵，簡直嗆得透不過氣，\n辛苦了一番，屋子總算幹凈了些。\n\n", this_player());
                return 1;
        }
        else 
        {
                message_vision("$N拿著掃把辛辛苦苦地掃著，突然在一個黑暗的角落裡，似乎發現有一個小木盒子。\n", this_player());
                set("dighted", 1, this_object());
                mh=new(__DIR__"obj/muhe");
                bo=new("/clone/book/mojiao");
                bo->move(mh);
                mh->move(this_player());
                return 1;
        }
        return 0;
} 
void reset(){
        ::reset();
      
        if( query("dighted", this_object())){
                delete("dighted", this_object());
        }
        return;
}        
