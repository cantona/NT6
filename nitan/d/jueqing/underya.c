#include <ansi.h>

inherit ROOM;

int out_water(object me);

void create()
{
        set("short", "絕情谷底");
        set("long", @LONG
這裏便是絕情谷底，情景一瞥之間，四下削壁環列， 宛似
身處一口大井之底， 常言道：“坐井觀天”，但坐在此處，望
上去盡是白雲濃霧。不遠處是一寒潭(tan)，潭中瀰漫着陣陣寒
氣。 寒潭西側有幾塊大石(stone)。 四下一望，峭壁上垂一根
長藤(teng)， 看來可以借這跟樹藤攀上懸崖。

LONG);
        set("item_desc",([
                "tan"    : HIC "寒潭看去平靜如鏡，陣陣寒氣從中透出。\n" NOR,
                "stone"  : NOR + WHT "石頭有半人多高，看似非常沉重。\n" NOR,
                "teng"   : NOR + YEL "這根樹藤看上去很結實，可作攀爬之用。\n" NOR,
 
        ]));
        set("no_clean_up", 0);

        setup();
}

void init()
{       
        add_action("do_jump", ({ "tiao", "jump" }));
        add_action("do_climb", ({ "climb", "pa" }));
        add_action("do_bao", ({ "bao" }));
}

int do_bao(string arg)
{
        object me = this_player();

        if (! arg || arg != "stone")
                return notify_fail("你要抱什麼？\n");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢！\n");

        if (me->is_fighting())
                return notify_fail("你還是先把你面前這個傢伙解決了再説。\n");     

        if( query_temp("marks/抱", me) )
                return notify_fail("你已經抱了一塊石頭了。\n"); 

        write(HIC "你將大石抱起，頓感異常沉重。\n" NOR);
        
        // 將石頭抱住才可沉入寒潭中
        set_temp("marks/抱", 1, me);

        return 1;
}

int do_climb(string arg)
{
        object me = this_player();
        object ob;


        if (! arg || arg != "teng")
                return notify_fail("你要做什麼？\n");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢！\n");

        if (me->is_fighting())
                return notify_fail("你還是先把你面前這個傢伙解決了再説。\n");
        
        write(HIG "\n你拉着樹藤向上爬去…\n" NOR);
        write(HIC "\n爬了許久，你感覺疲憊之極，但終於達到了山峯。\n\n" NOR);

        if (! ob = find_object(__DIR__"jueqing"))
               ob = load_object(__DIR__"jueqing");

        me->move(ob);
       
        return 1;

}
int do_jump(string arg)
{
        object me = this_player();
        object ob;


        if (! arg || arg != "tan")
                return notify_fail("你要往哪兒跳？\n");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢！\n");

        if (me->is_fighting())
                return notify_fail("你還是先把你面前這個傢伙解決了再説。\n");
       
        if( query("tiao", me) )
                return 1;

        if( !query_temp("marks/抱", me) )
        {                    
                write(HIW "你長吸一口氣，縱身入潭，直往深處潛去，那潭底越深越"
                      "寒，潛\n了一會，四周藍森森的都是玄冰。由於深處浮力太強"
                      "，你用力衝\n了數次，也不過再潛下數丈，始終無法到底……\n" NOR);

                call_out("out_water", 6, me);
                set("tiao", 1, me);

                return 1;
        }
         
        // 抱住大石，能夠潛入潭底
        write(HIG "你縱身入潭，由於抱有大石頭，身體急沉而下，猛地裏眼前一\n"
                  "亮，你心念一動，忙向光亮處游去，只覺一股急流卷着你的身\n"
                  "子衝了過去，光亮處竟是一洞。你拋下大石，手腳齊劃，那洞\n"
                  "內卻是一道斜斜向上的冰窖。你順勢而上，過不多時， “波”\n"
                  "的一響，躍出了水面。\n" NOR);

        if (! ob = find_object(__DIR__"underya2"))
               ob = load_object(__DIR__"underya2");

        me->move(ob);
        delete_temp("marks/抱", me);
        delete("tiao", me);
       
        return 1;

}

int out_water(object me)
{      
       write(HIY "此時你氣息漸促，只好回到岸邊。\n" NOR);
       me->move(__DIR__"underya");
       delete("tiao", me);
       return 1;
}