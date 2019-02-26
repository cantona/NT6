// yanshi.c 巖石
// snowman 16.12.98
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
string sea();
void create()
{
	set("short", HIW"巖石"NOR);
        set("long", @LONG
這是一塊露出水面的巖石。但見那火柱的周圍一片青綠，原來這
裏是一個極大的島嶼。島嶼西部都是尖石嶙峋的山峯，奇開怪樣，莫
可名狀，島東卻是一片望不到盡頭的平野，乃火山灰傾入大海而成。
此處雖處北極，但火山萬年不滅，島上氣侯便和長白山、黑龍江一帶
相似。島的西部有一山頂有一山頂正在帽出黑煙。往北便是一片片大
綠野。巖石的南部是海邊(sea），有幾塊浮基正向南漂流。
LONG );
        set("item_desc", ([
		"sea" : (: sea :),
        ]) );
	set("exits",([
		"north" : __DIR__"pingyan1",
	]));
	set("outdoors", "冰火島");
	setup();
}

void init()
{
     if(!this_player()->query_condition("cold_wind") && !wizardp(this_player()))
        this_player()->apply_condition("cold_wind", 1);
	add_action("do_make","make");
        add_action("do_push","tui");
        add_action("do_enter","enter");
}

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
                          message_vision("$N象猴子一樣蹦得老高，兩下就竄上了帆船。\n\n", me);
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

        if(!query("boat")) return notify_fail("推什麼？\n");
        if( arg=="chuan" || arg=="船" ) {
            if(me->is_busy()) return notify_fail("你正忙着呢。\n");
            if(query("boat_on_sea")) return notify_fail("岸邊有艘帆船呢，你再推下去一艘，它們會相撞的。\n");
            me->start_busy(5);
            add("boat", -1);
            message_vision("$N使出吃奶的勁，將用樹幹製成的帆船推進了大海。\n\n", me);
            EMOTE_D->do_emote(me,"touch", me->query("id"));
            me->add("jingli", -50);
            ob=new("/clone/misc/boat");
            ob->set("boat_of", base_name(this_object()));
            ob->set_temp("stepe", 200);
            ob->set_temp("stepn", 945);
            ob->move("/clone/misc/sea");
            set("boat_on_sea", 1);
            return 1;
        }
}       

int do_make(string arg)
{
        object me, ob, weapon;
        int i;
        string msg;
        me = this_player();
        weapon = me->query_temp("weapon");
        i = query("make_times");

        if( arg=="chuan" || arg=="船" ) {
            if(me->is_busy()) return notify_fail("你正忙着呢。\n");
            me->start_busy(5);
            if(!objectp(ob = present("shu gan", environment(me)))
               && !objectp(ob = present("shu gan", me)))
                     return notify_fail("你要用什麼材料造船？\n");
            switch(i){
                case 0: if(!weapon || weapon->query("flag")!=4) return notify_fail("你需要一件鋒利的工具，才能剖開樹幹。\n");
                        msg = "$N將樹幹剖開，並排，再用藤條將它們牢牢地困緊。\n"; 
                        add("make_times", 1); break;
                case 1: msg = "$N將樹幹上的樹皮撥下來，打緊，再用騰條穿孔做成了帆。\n"; 
                        add("make_times", 1); break;
                case 2: msg = "$N將樹幹掏空，打磨了一翻，然後用掏出的木頭做成了漿，舵等用具。\n"; 
                        add("make_times", 1); break;
                case 3: msg = "$N將一根樹幹削圓削細，仔細量了尺寸，做成了主桅杆。\n"; 
                        add("make_times", 1); break;
                case 4: msg = "$N將帆支起，又加固了主桅，一條船總算是做好了。\n";
                        delete("make_times");
                        add("boat", 1);
                        break;
                default: break;
            }
            me->add("jingli", -100);
            destruct(ob);
            message_vision(msg, me);
            return 1;
        }
        else return notify_fail("你要做什麼？\n");
}       

string sea()
{   
       string msg;
       int boat;
       boat=query("boat_on_sea");
    
       msg = "\n那是一片汪洋，一望無際，海中有無數的浮冰。\n";
       if(boat)
          msg += "岸邊停放着一隻簡陋的帆船，正隨波左右搖動。從這裏就可以上去(enter)。\n";        
          msg += "這裏寬闊平坦，看來可以是個很好的工場。\n";
       if(query("make_times") >= 1){ 
            if(query("make_times") >= 4) msg += "有一隻用巨樹樹幹製成的簡陋帆船的船體，看來是快要完成了。\n";
            else msg += "一旁放有幾根巨樹的樹幹，已經被剖開成了兩半。\n";  
       }
       if(query("boat")) msg += "岸邊放有用巨樹樹幹製成的簡陋帆船，如果使勁推，可以把它推(tui)下水去。\n";
       return msg;       
}
