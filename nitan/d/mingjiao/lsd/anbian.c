// anbian.c 岸邊
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;

void home( object ob );
void create()
{
        set("short", GRN"岸邊"NOR);
        set("long", @LONG
只見岸邊數裏之外樹木葱翠，奇峯挺拔，聳立着好幾座高山。島
東端山石直降人入海，並無淺灘，帆船吃水較深，卻可以泊在岸邊。
這時你看見不遠的有一塊頗為平整的巖石，上面被人用利器刻着『靈
蛇島』三個大字，其側還有幾個看不太清的小字(zi)。往東而上是一
個很高的山崗，再上面是一座山峯。海灘上有幾隻海船，看來可以推
(tui)下海去。
LONG );
        set("exits", ([ 
                "eastup" : __DIR__"shanguang",
        ]));
        set("item_desc", ([
                "zi" :HIR"\t\t踏足靈蛇島，必死！\n"NOR
        ]));
        set("boat", 1);
        set("outdoors", "靈蛇島");
        setup();
}

void init()
{
        // add_action("do_push","tui");
        add_action("do_enter","enter");
}

/*
int do_enter()
{
        object me, sea, *inv;
        int i;
        me = this_player();        
        if(!query("boat_on_sea")) return 0;
        if(!(sea = find_object("/clone/misc/sea")))
             sea = load_object("/clone/misc/sea");
        if(sea = find_object("/clone/misc/sea")){
             inv = all_inventory(sea);
             for(i= 0;i< sizeof(inv);i++){
                   if(inv[i]->query("boat_of") == base_name(this_object())){
                          message_vision("$N象猴子一樣蹦得老高，兩下就竄上了海船。\n\n", me);
                          me->move(inv[i]);
                          message("vision",me->name()+"象猴子一樣蹦了上來。\n",environment(me), ({me}) );
                          return 1;
                   }
             }
        }
        else write("sea boat error, please call wizard. \n");
        return 1;
}       

int do_push(string arg)
{
        object me, ob;
        me = this_player();
        
        if( arg=="chuan" || arg=="船" ) {
            if(me->is_busy()) return notify_fail("你正忙着呢。\n");
            if(!query("boat")) return notify_fail("岸上已經沒有海船了。\n");
            if(query("boat_on_sea")) return notify_fail("岸邊有艘海船呢，你再推下去一艘，它們會相撞的。\n");
            me->start_busy(5);
            add("boat", -1);
            message_vision("$N使出吃奶的勁，將海船推進了大海，現在總算可以上船(enter)了。\n", me);
            EMOTE_D->do_emote(me,"touch", me->query("id"));
            me->add("jingli", -50);
            ob=new("/clone/misc/boat2");
            ob->set("boat_of", "/d/mingjiao/lsd/anbian");
            ob->set_temp("stepe", 98);
            ob->set_temp("steps", 5);
            ob->move("/clone/misc/sea");
            set("boat_on_sea", 1);
            return 1;
        }
}       

void reset()
{
        set("boat", 1);
        ::reset();
}
*/
int do_enter ( string arg )
{
        object ob ;
        string dir;
        if (! arg || arg != "chuan")
        {
                tell_object(this_player() , "你要 enter 哪兒？\n" ) ;
                return 1 ;
        }
        ob = this_player () ;
        message_vision("船伕一見有人上船，忙叫了一聲：開船嘍！\n", ob);
        message_vision("船伕升起帆，船就向西方航行。\n", ob);
        ob->move("/d/mingjiao/lsd/dahai") ;
        tell_object(ob, BLU "你在海上航行了三天三夜.......\n" NOR ) ;
        call_out("home", 10 , ob );
        return 1 ;
}
void home( object ob )
{
        tell_object(ob , "大船終於抵達了南海岸邊。你走下船來。\n" ) ;
        ob->move("/d/beijing/haigang") ;
}


