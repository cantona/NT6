#include <ansi.h>
inherit NPC;

mixed teach_hunting();
string ask_chushengdao();

void create()
{
        set_name("獵人", ({"hunter"}));
        set("gender", "男性" );
        set("class", "swordman");
        set("age", 45);
        set("str", 200);
        set("con", 26);
        set("int", 28);
        set("dex", 200);
        set("combat_exp", 12000000);
        set("attitude", "peaceful");

        set_skill("unarmed", 300);
        set_skill("dodge", 300);
        set_skill("hunting", 2000);

        set("max_qi", 4500);
        set("max_jing", 2000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 150);

        set("inquiry", ([
                "hunting" : ( :teach_hunting: ),
                "捕獵"    : ( :teach_hunting: ),
                "畜生道"  : (: ask_chushengdao :),
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();

 }

int accept_object(object me, object ob)
{
        if( !me || environment(me) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, me) ) return notify_fail("你沒有這件東西。");
        if( query("id", ob) == "bushou jia" )
        {
                command("nod");
                command("say 這個我正用得著，在下無以為報，如果你願意，我\n可以"
                        "教你一些捕獵的技巧。");
                 set_temp("marks/hunter", 1, me);
                return 1;
        }
        else
        {
                 command("shake");
                 command("say 這是什麼東西，我不需要！");
        }

           return 1;
}



mixed teach_hunting()
{
        object me = this_player();
        int jing, add;

        jing=query("jing", me);
        add = me->query_int() + random(me->query_int() / 2 );

        if( !query_temp("marks/hunter", me) )
                return "你我素無往來，何出此言？\n";

        if (me->is_busy() || me->is_fighting())
        {
                write("你現在正忙著。\n");
                return 1;
        }

        if (jing < 20)
        {
                write("你的精神無法集中。\n");
                return 1;
        }

        if( (query("potential", me)-query("learned_points", me))<1 )
        {
                write("你的潛能不夠，無法繼續學習。\n");
                return 1;
        }
        write(HIW "獵人給你講解了有關捕獵的一些技巧。\n" NOR);
        write(HIY "你聽了獵人的指導，似乎有所心得。\n" NOR);

        addn("learned_points", 1, me);

        me->improve_skill("hunting", add);

        addn("jing", -(5+random(6)), me);

        return 1;

}

string ask_chushengdao()
{
        object me;
        
        me = this_player();
        
        if( query("int", me)<32 || 
            query("con", me)<32 || 
            query("str", me)<32 || 
            query("dex", me)<32 )
            return "你的先天屬性還不足以修煉畜生道，我看你還是先回去吧。\n";


        if( query("reborn/times", me)<3 )
                return "走開，走開，沒看我正忙嗎？\n";
        
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me)<4 )
                return "閣下武功已經獨步天下，何必如此貪心?\n";
                        
        if (me->query_skill("lunhui-sword",1))
                return "哼，凡夫俗子，竟然如此貪心！\n";
                                        
        // 已經完成任務
        if( query("lunhui-sword_quest/chushengdao/finish", me) )
                return "呵呵，閣下武功非凡，世間罕有，令在下佩服、佩服。\n";

        // 分配任務
        // 殺黃金白玉虎
        if( !query("lunhui-sword_quest/chushengdao/give_quest", me) )
        {
                command("look"+query("id", me));
                command("say 閣下看來並非泛泛之輩，既然你有求于我，那你得先幫我一個忙！");
                command("tan");
                command("say 前方不遠處有一片樹林，在下三代在此狩獵，一直風平浪靜，也算落得個豐衣足食，自在快活！");
                command("say 前不久，樹林裡出現一只猛獸，將樹林裡的其他動物全都趕跑了，不少獵人也慘糟其毒手。");
                command("say 據說，那是一只存活千年的黃金白玉虎，兇猛非常，不少武林高手前去都無一生還 ……");
                command("look"+query("id", me));
                command("say 閣下如果有本事收拾那畜生，我這祖傳絕學便可傾囊相受。");
                tell_object(me, this_object()->name() + HIG "讓你幫他解決掉黃金白玉虎！\n" NOR);
                set("lunhui-sword_quest/chushengdao/give_quest", 1, me);
                me->save();
                return "怎麼樣，敢去嗎？";
        }
        
        // 完成任務
        if( !query("lunhui-sword_quest/chushengdao/killed", me) )
                return "怎麼樣，解決掉黃金白玉虎了嗎？\n";

        command("hehe");
        command("nod"+query("id", me));
        command("say 好！好！好！閣下武功非凡，在下佩服，這就傳你「畜生道」……");

        message_sort(HIC "\n$N" HIC "走上前去，在$n" HIC "耳邊悄悄說了幾句，然後又拿出一本書，指指點點，"
                     "$n" HIC "不住地點頭，忽而眉頭深鎖，忽而低頭沉思 ……\n良久，$n" HIC "大笑一聲，似乎"
                     "對剛才的疑慮有所頓悟。\n", this_object(), me);

        tell_object(me, HIG "恭喜你領悟了「畜生道」劍法，目前等級為10級。\n");
        me->set_skill("chusheng-dao", 10);
        set("lunhui-sword_quest/chushengdao/finish", 1, me);
        
        return "保重！";
        
                
}
