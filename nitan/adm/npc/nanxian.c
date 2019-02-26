// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit NPC;
inherit F_DEALER;
inherit F_NOCLONE;

#define CONTRACT        "/d/reborn/obj/contract"

mixed ask_me1();
mixed ask_me2();
mixed ask_me3();
mixed ask_me4();
mixed ask_me5();
mixed ask_me6();
mixed ask_reborn();
mixed ask_buchang();
mixed ask_duanwu();
int full_all();

void create()
{
        set_name("南賢", ({ "nan xian", "nan", "xian" }));
        set("long", @LONG
此人衣著青杉，須發皆白。看似其貌不揚，實
卻為世上頭號人物。這便是武林中號稱「南賢
北醜」的南賢。其為人亦正亦邪，年輕時曾幹
下了無數轟天動地的大舉。生平決戰無數，僅
在北醜手下失過手。
LONG);
        set("nickname", HIW "天下至賢" NOR);
        set("title", HIC "武林泰鬥" NOR);
        set("gender", "男性" );
        set("age", 74);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 12000000);
        set("level", 100);

        set_skill("force", 500);
        set_skill("huntian-baojian", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("unarmed", 500);
        set_skill("sword", 500);
        set_skill("lunhui-jian", 500);
        set_skill("poison", 500);
        set_skill("medical", 500);
        set_skill("lingbo-weibu", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("buddhism", 500);
        set_skill("taoism", 500);
        set_skill("literate", 500);
        set_skill("martial-cognize", 500);

        map_skill("force", "huntian-baojian");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("unarmed", "huntian-baojian");
        map_skill("dodge", "lingbo-weibu");
        map_skill("sword", "lunhui-jian");

        prepare_skill("unarmed", "huntian-baojian");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.hui" :),
                (: exert_function, "sword" :),
                (: exert_function, "sword" :),
                (: exert_function, "sword" :),
                (: exert_function, "recover" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "powerup" :),
        }));

        set("inquiry", ([
                "name" : "姓名不過是一種代號而已，問它有何意義？",
                "北醜" : "你盡提那個齷齪的傢伙做甚？",
                "狀態回復": (: full_all :),
                "狀態恢復": (: full_all :),
/*
                "泥潭" : (: ask_me1 :),
                "禮物" : (: ask_me1 :),
                "gift" : (: ask_me1 :),
*/
                "高效練功": (: ask_me2 :),
                "雙倍經驗": (: ask_me3 :),
                "比武"    : (: ask_me4 :),
                "比武大會": (: ask_me4 :),
                "華山絕頂": (: ask_me4 :),
                "參加比武": (: ask_me4 :),
                "鑒定會員": (: ask_me5 :),
                "鑒定會員級別": (: ask_me5 :),
                "鑒定會員等級": (: ask_me5 :),
                //"新手導師評價票": (: ask_me6 :),
                "轉世重生" : (: ask_reborn :),
                "轉世" : (: ask_reborn :),
                "重生" : (: ask_reborn :),
                "轉生" : (: ask_reborn :),
                //"補償" : (: ask_buchang :),
  		//"端午節" : (: ask_duanwu :),

        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

        /*
        if (! clonep(this_object()))
        {
                move("/d/city/wumiao");
                message_vision(WHT "\n突然間你眼前一花，身後似乎多了個"
                               "人影。\n" NOR, this_object());
                set("startroom", "/d/city/wumiao");
        }
        */
        set("startroom", "/d/city/wumiao");
        check_clone();
}

void init()
{
/*
        object ob; 
        ::init();

        if (interactive(ob = this_player()) && ! is_fighting()) 
        if (interactive(ob = this_player()) && ! is_fighting() && ! query("welcomegift", ob)) 
        {
                remove_call_out("greeting"); 
                call_out("greeting", 1, ob); 
        }
*/
}

void greeting(object ob) 
{
        if ( ! ob || environment(ob) != environment() ) return; 
        say( CYN "南賢微微一笑道：這位" + RANK_D->query_respect(ob) + CYN + "是新人吧，我這裡有個禮物送給你(ask nan xian about 禮物)。\n" NOR); 
}

// 接受詢問
mixed accept_ask(object who, string topic)
{
        object me;
        object ob_hlp;
        int i;

        me = this_player();

        if (topic == "尋找帝王符圖")
        {
                //if (! me->query("reborn/times")) return "你還沒有經過轉世重生，無法領取任務！\n";
/*
                if( !MEMBER_D->is_valid_member(query("id", me)) )
                        return "對不起，帝王符圖任務只針對有效會員開放！\n";
*/
                if( query("quest_tuteng/end", me) )
                        return "不錯，不錯，閣下了卻了南賢的心願，多謝！\n";
                if( query("quest_tuteng/start", me) )
                        return "你已經領取了該任務，請盡快搜集七張帝王符圖交給我吧！\n";
                if( query("balance", me)<100000000 )
                        return "你的銀庫(bank)存款不足，領取該任務需要支付1萬兩黃金。\n";

                addn("balance", -100000000, me);
                set("quest_tuteng/start", 1, me);

                return "好吧，你就去尋找帝王符圖吧。\n";
        }

        if (topic == "任務完成")
        {
                string *spks = ({
                        "zhuque",
                        "tianshen",
                        "qijin",
                        "taxue",
                });
                int n;
                string mapsk;

                // 檢查是否是有效會員
                if( !MEMBER_D->is_valid_member(query("id", me)) )
                        return "對不起，帝王符圖任務只針對有效會員開放！\n";
                // 檢查是否領取過任務
                if( !query("quest_tuteng/start", me) )
                        return "我好像沒有交給你任務吧。\n";
                // 檢查任務是否已完成
                if( query("quest_tuteng/end", me) )
                        return "不錯，不錯，閣下了卻了南賢的心願，多謝！\n";

                if (me->query_skill("badao", 1) > 0 && me->query_skill("badao", 1) < 600)
                        return "閣下既會霸刀，但修習不深，不如等你再修習一段時間再來吧，以免錯失良機。\n";

                // 檢查是否存在7張帝王圖
                for (i = 1; i <= 7; i ++)
                {
                        if (! objectp(ob_hlp = present("diwang futu" + sprintf("%d", i), me)))
                                return "怎麼樣，我要的7張帝王圖蒐集齊了嗎\n";

                        if (base_name(ob_hlp) != "/clone/tuteng/futu" + sprintf("%d", i))
                                return "怎麼樣，我要的7張帝王圖蒐集齊了嗎？\n";
                }

                // 齊全：摧毀7張圖
                for (i = 1; i <= 7; i ++)
                {
                        ob_hlp = present("diwang futu" + sprintf("%d", i), me);
                        destruct(ob_hlp);
                }

                // 1、給予獎勵--隨機SP2（五種）
                //    如果已經購買過SP2了，則不獲得該SP2，但可獲得經驗獎勵
                if( !query("quest_tuteng/end3", me) )
                {
                        set("special_skill/"+spks[random(sizeof(spks))], 1, me);
                        write("獲取隨機圖騰技能！ \n");
                }

                // 2、exp 150萬  pot 200 萬 weiwang 100萬 閲歷 100萬
                GIFT_D->delay_bonus(me,
                                    ([ "exp"      : 1500000,
                                       "pot"      : 2000000,
                                       "weiwang"  : 1000000,
                                       "score"    : 1000000,
                                       "prompt"   : "你完成帝王符圖任務之後"]), 999);

                // 3、所有基本技能及激發在基本技能之上的技能熟練度大幅度提升（最多提升一級）
                mapsk = me->query_skill_mapped("force");
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("dodge");
                if (me->can_improve_skill("dodge"))
                        me->improve_skill("dodge", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("parry");
                if (me->can_improve_skill("parry"))
                        me->improve_skill("parry", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("staff");
                if (me->can_improve_skill("staff"))
                        me->improve_skill("staff", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("unarmed");
                if (me->can_improve_skill("unarmed"))
                        me->improve_skill("unarmed", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("sword");
                if (me->can_improve_skill("sword"))
                        me->improve_skill("sword", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("blade");
                if (me->can_improve_skill("blade"))
                        me->improve_skill("blade", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("finger");
                if (me->can_improve_skill("finger"))
                        me->improve_skill("finger", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("claw");
                if (me->can_improve_skill("claw"))
                        me->improve_skill("claw", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("hand");
                if (me->can_improve_skill("hand"))
                        me->improve_skill("hand", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("strike");
                if (me->can_improve_skill("strike"))
                        me->improve_skill("strike", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("cuff");
                if (me->can_improve_skill("cuff"))
                        me->improve_skill("cuff", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("whip");
                if (me->can_improve_skill("whip"))
                        me->improve_skill("whip", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                if (me->can_improve_skill("riding"))
                        me->improve_skill("riding", 15000000);

                if (me->can_improve_skill("martial-cognize"))
                        me->improve_skill("martial-cognize", 15000000);

                // 4、如霸刀等級超過600lv，則傳授絕招且霸刀提升5個等級的熟練度，至多可提升5級。
                if (me->query_skill("badao",1) >= 600)
                {
                        message_sort(HIC "\n南賢繼續對$N説道：閣下既會霸刀，南賢不才，也略知一二，如謀不棄，"
                                         "就由在下將所知與你講解一番 ……\n" NOR, me);

                        tell_object(me, HIW "你聽了南賢的講解後，對霸刀有了新的體會！\n" NOR);
                        tell_object(me, HIW "恭喜你，學會了「雄霸天下」及「阿鼻道第一刀」。\n" NOR);
                        set("can_perform/badao/xiong", 1, me);
                        set("can_perform/badao/san-1", 1, me);
                        for (i = 0; i < 5; i ++)
                        {
                                if (me->can_improve_skill("badao"))
                                        me->improve_skill("badao", 15000000);
                        }
                        tell_object(me, HIM "南賢悄悄對你説道：據説，只要你霸刀達到800級，這阿鼻道第二刀可找陰長生學習。\n" NOR);
                        tell_object(me, HIM "南賢又對你説道：可是陰長生不會白教你，需要找到天下第一神酒--天乙神酒與他交換。\n" NOR);
                }
                // 設置任務完成標志
                set("quest_tuteng/end", 1, me);

                me->save();
                log_file("diwang-quest",query("id", me)+"於"+ctime(time())+"完成帝王符圖任務！\n");

                return 1;
        }
        if (topic == "修羅道")
        {

                if( query("int", me)<32 || 
                    query("con", me)<32 || 
                    query("str", me)<32 || 
                    query("dex", me)<32 )
                    return "你的先天屬性還不足以修煉修羅道，我看你還是先回去吧。\n";
        
                if( query("reborn/times", me)<3 )
                        return "哼，沒事別來煩我，走開！\n";
                
                if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me)<4 )
                        return "閣下武功已經獨步天下，恭喜恭喜！\n";                    

                if (me->query_skill("lunhui-sword",1))
                        return "哼，凡夫俗子，竟然如此貪心！\n";
                                
                // 已經完成任務
                if( query("lunhui-sword_quest/xiuluodao/finish", me) && 
                    me->query_skill("xiuluodao", 1))
                        return "呵呵，多虧你上次幫我，這無敵劍氣我已經修煉成功了。\n";
        
                // 分配任務
                if( !query("lunhui-sword_quest/xiuluodao/give_quest", me) )
                {
                        command("hehe");
                        command("say 我正在修煉渾天寶鑒之無敵劍氣，急需1把青罡劍練功！");
                        command("ke");
                        command("say 能幫我這個忙嗎？");
                        tell_object(me, this_object()->name() + HIG "讓你幫他蒐集1把青罡劍把，趕快去吧！\n" NOR);
                        set("lunhui-sword_quest/xiuluodao/give_quest", 1, me);
                        me->save();
                        return "事成之後，我會傳你幾招武功防身！";
                }
                
                // 完成任務
                
                if (! objectp(ob_hlp = present("qinggang jian", me)))
                        return "怎麼樣，1把青罡劍蒐集夠了嗎？\n";
                        
                if (base_name(ob_hlp) != "/clone/weapon/qinggang-jian")
                        return "怎麼樣，1把青罡劍蒐集夠了嗎？\n";

                destruct(ob_hlp);
                
                command("hehe");
                command("nod");
                command("say 既然你幫我了這個忙，我就順便傳你一招，相信你以後用得著 ...");
                
                message_sort(HIC "\n$N" HIC "走上前去，在$n" HIC "耳邊悄悄説了幾句，然後又拿出一本書，指指點點，"
                             "$n" HIC "不住地點頭，忽而眉頭深鎖，忽而低頭沉思 ……\n良久，$n" HIC "大笑一聲，似乎"
                             "對剛才的疑慮有所頓悟。\n", this_object(), me);
                                        
                tell_object(me, HIG "恭喜你領悟了「修羅道」劍法，目前等級為10級。\n");
                me->set_skill("xiuluodao", 10);
                set("lunhui-sword_quest/xiuluodao/finish", 1, me);
                
                return "明白了？";              
        }
        


        return ULTRA_QUEST_D->accept_ask(this_object(), who, topic);
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        command("say 哼！不知死活。");
        command("exert powerup");
        command("exert sword");
        ::fight_ob(ob);
}

int accept_fight(object who)
{
        command("say 沒興趣。");
        return 0;
}

int accept_ansuan(object who)
{
        return notify_fail("你剛想暗算，可是眼前一花，看不太清楚。\n");
}

mixed ask_me1()
{
        object me = this_player();
        object ob;

        if( query("welcomegift", me) )
        {
                command("say 呵呵～這就是您的不是了！老夫已經給過您禮物了！");
                return 1;
        }
        else
        {
                set("welcomegift", 1, me);
                addn("food", 5000, me);
                addn("water", 10000, me);
                addn("score", 1000, me);
                addn("weiwang", 100, me);
                set("tianfu", 4, me);
                // me->add("potential", 1000);
                me->add_skill("training", 200);

                ob = new("/adm/npc/obj/gift");
                ob->move(me, 1);
                ob = new("/clone/fam/max/zhenyu");
                ob->move(me, 1);
                set("bindable", 3, ob);
                set("bind_owner",query("id",  me), ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);
                ob = new("/clone/fam/max/longjia");
                ob->move(me, 1);
                set("bindable", 3, ob);
                set("bind_owner",query("id",  me), ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);
                ob = new("/clone/fam/max/xuanhuang");
                ob->move(me, 1);
                set("bindable", 3, ob);
                set("bind_owner",query("id",  me), ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);

                // ob->move(this_object());
                // command("give gift to " + me->query("id"));

                /*
                CHANNEL_D->do_channel(me, "es", sprintf("在下%s今日光臨□泥潭□（61.128.162.81 : 2001）\n            現已得到南賢的幫助和獎勵！即日起開始玩泥巴了！",
                                      me->name(1)));
                */

                message_vision(HIW "$N" HIW "凌空一指，突然天空中一道" HIM "七" HIY "彩" HIR "霞" HIC "光" HIW "籠罩$n，轉瞬即逝！\n" NOR,
                               this_object(), me);

                tell_object(me, HIG "南賢送給了你一個禮物（gift），你可以 look gift 來看看是什麼禮物。\n" NOR);
                return 1;
        }
}

mixed ask_me2()
{
        int td;
        object me = this_player();

        td = time() / 86400;

        if( query("time_reward/which_day1", me) == td )
                return "你今天已經領過高效練功獎勵時間了。";

        if (! MEMBER_D->is_valid_member(me))
        // || (int)MEMBER_D->db_query_member(me, "endtime") < 1888888888)
                return "你不是會員，想要高效練功獎勵還是先購買會員卡吧。\n";

/*
        message("member", HIM "\n【泥潭會員】" + me->query_idname() + HIM " 領取二小時的高效練功時間\n" NOR,
                all_interactive(), 0);
*/

        tell_object(me, HIR "\n你領取二小時的高效練功時間開始計時，輸入指令istat可以查看剩餘時間。\n" NOR);

        addn("time_reward/study", 7200, me);
        set("time_reward/which_day1", td, me);
        return 1;
}

mixed ask_me3()
{
        // int t;
        int td;
        object me = this_player();

        td = time() / 86400;

        if( query("time_reward/which_day2", me) != td )
                delete("time_reward/times", me);

        if( query("time_reward/which_day2", me) == td &&
            query("time_reward/times", me) >= 3 )
                return "你今天已經領完所有的雙倍經驗獎勵時間了。";

        if (! MEMBER_D->is_valid_member(me))
                return "你不是會員，想要雙倍經驗獎勵還是先購買會員卡吧。\n";

        /*
        t = localtime(time())[2];
        if (t >= 20 && t < 24)
                return "每天20~24點均為雙倍經驗時間，現在正處於雙倍經驗時間段你還是過一會再來領吧。\n";

        message("member", HIM "\n【泥潭會員】" + me->query_idname() + HIM " 領取二小時的雙倍獎勵時間開始計時。\n" NOR,
                all_interactive(), 0);
        */

        tell_object(me, HIR "\n你領取二小時的雙倍經驗時間開始計時，輸入指令istat可以查看剩餘時間。\n" NOR);

        set("time_reward/which_day2", td, me);
        addn("time_reward/quest", 7200, me);
        addn("time_reward/times", 1, me);
        return 1;
}

mixed ask_me4()
{
        object me = this_player();

        tell_object(me, HIY "南賢説道：既然你要參加比武，那麼老夫就送你一程！\n" NOR);
        message_vision(HIY "只見南賢伸手一招，一道紅光照向$N，$N騰空飛去！\n" NOR, me);
        me->move("/d/huashan/houzhiwangyu");
        return 1;
}

mixed ask_duanwu()
{
	object me = this_player();
	object ob;

	if (query_temp("duanwu_time", me) > time())
		tell_object(me, HIY "南賢説道：" + query("name", me)  + "你剛剛已經拿過了，再拿需要等待10秒，每個人每天只能吃一次喲！\n"NOR);
	else {
		tell_object(me, HIY "南賢説道：" + query("name", me)  + "端午節快樂！\n"NOR);
 		message_vision(HIY "南賢從懷裡拿出一個粽子送給了 " + query("name", me) + "！\n" NOR);
		ob = new("/u/luoyun/zongzi");
		ob->move(me);
		set_temp("duanwu_time", time() +10, me);
	}
	 return 1;
}


int full_all()
{
        object me, ob;
        int max;

        me = this_object();
        ob = this_player();

        //只開放申請帳號至今不足30天且年齡小於18歲的的ID
        if( time()-query("birthday", ob)>86400*19 )
        {
                command("say 你已經不是新手了，還要我來照顧你的呀？\n");
                return 1;
        }

        max=query("max_jing", ob);
        ob->receive_curing("jing", max);
        ob->receive_heal("jing", max);
        max=query("max_qi", ob);
        ob->receive_curing("qi", max);
        ob->receive_heal("qi", max);
        max=query("max_neili", ob);
        set("neili", max, ob);
        max=query("max_jingli", ob);
        set("jingli", max, ob);
        set("food", ob->max_food_capacity(), ob);
        set("water", ob->max_water_capacity(), ob);
        ob->start_busy(2);
        message_vision(CYN "$N微笑著伸手朝$n一拂道聲：“好了！”\n" NOR,me, ob);
        tell_object(ob, HIC "你頓感如沫春風，神清意爽，疲憊盡去。\n" NOR);
        return 1;
}

mixed ask_me5()
{
        int value, trans, t;
        object me = this_player();

        t = time();
        if( !wizardp(me) && t-query_temp("identify_member", me)<10 )
                return "你剛剛才鑒定過，還是等會再來吧。\n";

        if (! MEMBER_D->is_member(me))
                return "你不是會員，想要鑒定會員等級還是先購買會員卡吧。\n";

        if (MEMBER_D->db_query_member(me, "vip") == 3)
                return "恭喜你，你已經是白金會員了！\n";

        set_temp("identify_member", t, me);

        value = MEMBER_D->db_query_member(me, "payvalue");
        trans = MEMBER_D->db_query_member(me, "transfervalue");
        value -= trans;

        if (value >= 2000)
        {
                MEMBER_D->db_set_member(me, "vip", 3);
                tell_object(me, HIY "\n你目前的會員等級為★★★白金會員★★★，會員商店購物品享受 8 折！\n\n" NOR);
                return 1;
        }
        else
        if  (value >= 1000)
        {
                MEMBER_D->db_set_member(me, "vip", 2);
                tell_object(me, HIY "\n你目前的會員等級為★★黃金會員★★，會員商店購物品享受 8.8 折！\n\n" NOR);
                return 1;
        }
        else
        if  (value >= 500 && MEMBER_D->db_query_member(me, "vip") < 2)
        {
                MEMBER_D->db_set_member(me, "vip", 1);
                tell_object(me, HIY "\n你目前的會員等級為★白銀會員★，會員商店購物品享受 9.5 折！\n\n" NOR);
                return 1;
        }
        else
        {
                if (MEMBER_D->db_query_member(me, "vip") == 2)
                        return "你目前的會員等級為黃金會員！\n";

                if (MEMBER_D->db_query_member(me, "vip") == 1)
                        return "你目前的會員等級為白銀會員！\n";

                tell_object(me, HIY "\n你目前的會員等級為普通會員。\n" NOR);
                return 1;
        }
}

mixed ask_me6()
{
        int wd;
        object me = this_player();

        wd = time() / 604800;

        if( query("flowers/which_week", me) == wd )
                return "你本週已經領過新手導師評價票了。";

        if (! MEMBER_D->is_valid_member(me))
                return "你不是會員，想要領取新手導師評價票還是先購買會員卡吧。\n";

        tell_object(me, HIR "\n你領取了一張新手導師評價票，輸入指令flowers可以查看你擁有的新手導師評價票數。\n" NOR);

        set("flowers/amount", 1, me);
        set("flowers/which_week", wd, me);
        return 1;
}

mixed ask_buchang()
{
        string id, sql;
        int    jointime, endtime, day;
        object me = this_player();
        object ob;


        if( query("gifter/buchang", me) )
                return "你已經領過補償了,不要太貪心哦。";

        id=query("id", me);

        if( !MEMBER_D->is_member(id) ) // 非沖值用户肯定不是會員
        {
                day = time() + 15724800; // 補償半年的會員
                sql = sprintf("INSERT INTO %s SET id = \"%s\", jointime = %d, endtime = %d",
                              "members", id, time(), day);
                DATABASE_D->db_query(sql);
                me->set_srv("quit_save", 86400*365); // 1年的離線物品不掉
                ob = new("/clone/goods/washgift");
                ob->move(me, 1);
                set("no_sell", 1, ob);
                set("bindable", 3, ob);
                set("bind_owner", id, ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);
                ob = new("/clone/goods/mask");
                ob->move(me, 1);
                set("no_sell", 1, ob);
                set("bindable", 3, ob);
                set("bind_owner", id, ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);
        } else
        {
                jointime = (int)MEMBER_D->db_query_member(id, "jointime");
                if( jointime < 1 ) jointime = time();

                endtime  = (int)MEMBER_D->db_query_member(id, "endtime");
                if( endtime < 1 )  // 非會員
                {
                        day = time() + 15724800;  // 半年的會員
                        me->set_srv("quit_save", 86400*365);
                        ob = new("/clone/goods/washgift");
                        ob->move(me, 1);
                        set("no_sell", 1, ob);
                        set("bindable", 3, ob);
                        set("bind_owner", id, ob);
                        set("auto_load", 1, ob);
                        set("set_data", 1, ob);
                        ob = new("/clone/goods/mask");
                        ob->move(me, 1);
                        set("no_sell", 1, ob);
                        set("bindable", 3, ob);
                        set("bind_owner", id, ob);
                        set("auto_load", 1, ob);
                        set("set_data", 1, ob);
                }
                else
                {
                        // 是否小於年度
                        if( endtime - jointime < 31536000 ||
                            query("online_time", me)<86400*3)//防止刷nt
                        {
                                if( endtime >= time() + 7948800 )
                                {
                                        log_file("buchang", sprintf("%s %s get buchang but the endtime is %d\n",
                                                                    TIME_D->replace_ctime(time()), id, endtime));
                                        endtime = time() + 7948800;
                                }

                                if( endtime > time() )
                                        day = endtime + 15724800; // 半年的會員時間
                                else
                                        day = time() + 15724800;

                                me->set_srv("quit_save", 86400*365);
                                ob = new("/clone/goods/washgift");
                                ob->move(me, 1);
                                set("no_sell", 1, ob);
                                set("bindable", 3, ob);
                                set("bind_owner", id, ob);
                                set("auto_load", 1, ob);
                                set("set_data", 1, ob);
                                ob = new("/clone/goods/mask");
                                ob->move(me, 1);
                                set("no_sell", 1, ob);
                                set("bindable", 3, ob);
                                set("bind_owner", id, ob);
                                set("auto_load", 1, ob);
                                set("set_data", 1, ob);
                        }
                        else
                        {
                                // 是否終身
                                if( endtime - jointime >= 63072000 )
                                {
                                        day = endtime;
                                        MEMBER_D->db_pay_member(id, 200); // 補償200nt
                                        me->set_srv("quit_save", 86400*365);
                                }
                                else // 是否年度
                                {
                                        if( endtime > time() )
                                                day = endtime + 7948800; // 1個季度的會員時間
                                        else
                                                day = time() + 7948800;

                                        MEMBER_D->db_pay_member(id, 70); // 補償70nt
                                        me->set_srv("quit_save", 86400*365);
                                        ob = new("/clone/goods/washgift");
                                        ob->move(me, 1);
                                        set("no_sell", 1, ob);
                                        set("bindable", 3, ob);
                                        set("bind_owner", id, ob);
                                        set("auto_load", 1, ob);
                                        set("set_data", 1, ob);
                                }
                        }
                }
                sql = sprintf("UPDATE %s SET jointime = %d, endtime = %d WHERE id = \"%s\"",
                              "members", jointime, day, id);

                DATABASE_D->db_query(sql);
        }

        set("gifter/buchang", 1, me);
        me->save();
        tell_object(me, HIY "\n你領取了(" HIM "當機補償" NOR + HIY ")，祝你在王者之戰裡玩的愉快！\n" NOR);
        return 1;
}

mixed ask_reborn()
{
        object ob, who, weapon;
        string map_skill, type;

        who = this_player();

        if( query("reborn/times", who) >= 3 )
        {
                message_vision("$N對$n一拱手，道：你已經歷過三世輪回了，我看就不用了吧！\n",
                               this_object(), who);
                return 1;
        }

        if( query("reborn_offer", who) )
        {
                message_vision("$N對$n怒道：老夫已經給過你一份閻王契(Contract)，為何還來找我！\n",
                               this_object(), who);
                return 1;
        }

        if( (!query("reborn/times", who) && query("combat_exp", who)<6000000000) ||
            (query("reborn/times", who) == 1 && query("combat_exp", who)<10000000000) ||
            (query("reborn/times", who) == 2 && query("combat_exp", who)<20000000000) )
        {
                message_vision("$N對$n一拱手，道：經驗不夠，強求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        if( query("betrayer", who) )
        {
                message_vision("$N對$n怒道：你還是先把與判師門派中的糾葛解決了再來！\n",
                               this_object(), who);
                return 1;
        }

        map_skill = who->query_skill_mapped("force");
        if (who->query_skillo("force", 1) < 3600 ||
            who->query_skillo(map_skill, 1) < 3600)
        {
                message_vision("$N對$n一拱手，道：內功不夠，強求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        map_skill = who->query_skill_mapped("dodge");
        if (who->query_skillo("dodge", 1) < 3600 ||
            who->query_skillo(map_skill, 1) < 3600)
        {
                message_vision("$N對$n一拱手，道：輕功不夠，強求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        map_skill = who->query_skill_mapped("parry");
        if (who->query_skillo("parry", 1) < 3600 ||
            who->query_skillo(map_skill, 1) < 3600)
        {
                message_vision("$N對$n一拱手，道：招架不夠，強求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        if (who->query_skillo("martial-cognize", 1) < 3600)
        {
                message_vision("$N對$n一拱手，道：武學修養不夠，強求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        weapon=query_temp("weapon", who);
        if( !objectp(weapon) ) weapon = query_temp("armor/hands", who);
        if( !objectp(weapon) ) weapon = query_temp("armor/finger", who);
        if( !weapon || /*!weapon->is_ultimate()*/ query("status", weapon) < 6 ||
            query("id", who) != weapon->item_owner() )
        {
                message_vision("$N對$n一拱手，道：你必須擁有一把品質完美的兵器，才能轉世重生。\n",
                               this_object(), who);
                return 1;
        }

        type=query("skill_type", weapon);
        if( type )
        {
                map_skill = who->query_skill_mapped(type);
                if (! map_skill)
                {
                        message_vision("$N對$n一拱手，道：你必須先激發和你裝備的兵器對應的兵器技能。\n",
                                        this_object(), who);
                        return 1;
                }
        }
        else
        {
                type = "unarmed";
                map_skill = who->query_skill_mapped(type);
                if( !map_skill ) { type = "strike"; map_skill = who->query_skill_mapped(type); }
                if( !map_skill ) { type = "hand"; map_skill = who->query_skill_mapped(type); }
                if( !map_skill ) { type = "cuff"; map_skill = who->query_skill_mapped(type); }
                if( !map_skill ) { type = "finger"; map_skill = who->query_skill_mapped(type); }
                if( !map_skill ) { type = "claw"; map_skill = who->query_skill_mapped(type); }
                if( !map_skill ) {
                        message_vision("$N對$n一拱手，道：你必須先激發和你裝備的兵器對應的兵器技能。\n",
                                       this_object(), who);
                        return 1;
                }
        }

        if (who->query_skillo(type, 1) < 3600 ||
            who->query_skillo(map_skill, 1) < 3600)
        {
                message_vision("$N對$n一拱手，道：" + to_chinese(map_skill) + "不夠，強求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        if (! ultrap(who))
        {
                message_vision("你還沒有到大宗師的境界，還是好好學習鍛煉吧。\n",
                               this_object(), who);
                return 1;
        }

        if( !query("breakup", who) )
        {
                message_vision("$N對$n一拱手，道：你還沒有打通過任督二脈呢。\n",
                               this_object(), who);
                return 1;
        }

        if( query("reborn/times", who) && !query("animaout", who) )
        {
                message_vision("$N對$n一拱手，道：你還沒有修煉元嬰出世呢。\n",
                               this_object(), who);
                return 1;
        }

        if( query("reborn/times", who) && !query("death", who) )
        {
                message_vision("$N對$n一拱手，道：你還沒有打通過生死玄關呢。\n",
                               this_object(), who);
                return 1;
        }

        if( query("couple/couple_id", who) )
        {
                message_vision("$N對$n一拱手，道：你還是先和你的家庭做個交代再轉世吧。\n",
                               this_object(), who);
                return 1;
        }

        if( query("bunch", who) )
        {
                message_vision("$N對$n一拱手，道：你還是先和你的幫派做個交代再轉世吧。\n",
                               this_object(), who);
                return 1;
        }

        if( query("brothers", who) )
        {
                message_vision("$N對$n一拱手，道：你還是先和你的結義兄弟做個交代再轉世吧。\n",
                               this_object(), who);
                return 1;
        }

        if( query("league", who) )
        {
                message_vision("$N對$n一拱手，道：你還是先和你的同盟做個交代再轉世吧。\n",
                               this_object(), who);
                return 1;
        }

        if( query("private_room", who) )
        {
                message_vision("$N對$n一拱手，道：你還是先把你的住房拆毀掉再轉世吧。\n",
                               this_object(), who);
                return 1;
        }

        message_vision(CYN "$N歎道：「人間本是百樁磨，既然是有心之士相詢，老夫也不藏拙，這物事你便收下吧。」\n" NOR,
                       this_object(), who);

        ob = new(CONTRACT);
        ob->move(who, 1);
        set("bindable", 3, ob);
        set("bind_owner",query("id",  who), ob);
        set("owner",query("id",  who), ob);
        set("no_store", 1, ob);
        set("auto_load", 1, ob);
        set("set_data", 1, ob);

        message_vision(HIC "$N拿出一份閻王契(Contract)給$n。\n" NOR
                       CYN "$N續道：「欲成轉世奇緣，需向五嶽山君獻祭，你這便前往泰山、華山、衡山、恆山與嵩山一行吧。」\n" NOR,
                       this_object(), who);

        message("channel:rumor",HBRED"【轉世重生】人間："+query("name", who)+"("+query("id", who)+")"
                HBRED "拿到閻王契，開始前往五嶽獻祭，欲成轉世奇緣！\n\n" NOR, users());

        set("reborn_offer", "start", who);

        return 1;
}

int accept_object(object who, object ob)
{
        int r;

        if (r = ULTRA_QUEST_D->accept_object(this_object(), who, ob))
                return r;

        if (base_name(ob) != CONTRACT ||
            query("owner", ob) != query("id", who) )
                return 0;

        if( sizeof(query("offer", ob))<5 )
                return notify_fail(CYN "南賢搖搖頭道：「五嶽獻祭未成，為時尚早。」\n" NOR);

        delete("bindable", ob);
        delete("bind_owner", ob);
        call_out("to_return", 1, who, ob);
        return 1;
}

int to_return(object who, object ob)
{
        if (! ob || ! who) return 0;

        message_vision(CYN "$N點了點頭道：「果真是有心人，竟能捱過五嶽山君那般挑剔折磨，來，在這裡蓋個血指印。」\n" NOR
                       HIC "$n依從$N指示，咬破拇指，在閻王契上蓋上血指印。\n" NOR
                       HIM "只見閻王契(Contract)突生紫光，血指印旁憑空現出了$n的名字。\n" NOR
                       CYN "$N續道：「速去昆侖之巔尋那昆侖鏡，將閻王契投入其中，方可獲得肉身入地獄面見閻王之資格。路程險惡，務必小心。」\n" NOR,
                       this_object(), who);

        set("name", MAG"閻王契"NOR, ob);
        ob->set_name(MAG "閻王契" NOR, ({ "contract" }));
        set("long", MAG"這是一份閻王契，上面血指印旁有"+who->query_idname()+"的名字。\n"NOR, ob);
        ob->move(who, 1);
        set("bindable", 3, ob);
        set("bind_owner",query("id",  who), ob);
        set("reborn_offer", "finish", who);
        tell_object(who, HIC "南賢將泛紫光的閻王契(Contract)還給你。\n" NOR);

        return 1;
}

void unconcious()
{
        die();
}
