// This program is a part of NT MudLIB
// jinshe.c 金蛇郎君

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

#define QUESTDIR "skybook_quest/金蛇劍法/"

void dest(object ob);
int ask_fuchou();
int ask_jinshe();
string ask_skill1(object me,string arg);
string ask_skill2(object me,string arg);
string ask_skill3(object me,string arg);
void create()
{
        set_name("夏雪宜", ({"xia xueyi", "xia", "xueyi"}));
        set("nickname", HIY"金蛇郎君"NOR);
        set("gender", "男性");
        set("age", 25);
        set("long", 
                "他就是人稱“金蛇郎君”的一代怪傑──夏雪宜。\n"
                "他做事全憑好惡，時正時邪，端地是獨來獨往，好不瀟洒！\n"
                "聽說他的身世很慘，人也變得偏激起來。\n"
                "看起來他好象受了點傷，臉色很難看。\n");
         set("attitude", "peaceful");
        
        set("str", 100);
        set("int", 20);
        set("con", 30);
        set("dex", 25);
        set("chat_chance", 15);
        set("chat_msg", ({
                "夏雪宜突然惡狠狠地說道：儀兒，你到底為什麼要害我！？\n",
                "夏雪宜眼中仿佛要噴出火來。\n",
                "突然，夏雪宜“哇”地一聲，吐出一大口帶黑的血。\n",
        }));
        set("inquiry", ([
                "溫儀": "她....她..... \n",
                "復仇" : (: ask_fuchou :),
                "鎖劍訣"  :        (: ask_skill1 :),
                "附骨纏身":        (: ask_skill2 :),
                "金蛇吐霧":        (: ask_skill3 :),
                "心得"    : (: ask_jinshe :),
                "金蛇劍法": (: ask_jinshe :),
                "秘訣"    : (: ask_jinshe :),
        ]));
        set("qi", 10000);
        set("max_qi", 10000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 9000);
        set("max_neili", 9000);
        set("jiali", 100);
        set("no_get",1);
        set(QUESTDIR+"pass", 1);
        
        set("combat_exp", 10000000);
         
        set_skill("force", 200);                // 基本內功
        set_skill("huntian-qigong", 200);       // 混天氣功
        set_skill("unarmed", 220);              // 基本拳腳
        set_skill("dodge", 200);                // 基本躲閃
        set_skill("parry", 200);                // 基本招架
        set_skill("sword", 200);                // 基本劍法
        set_skill("jinshe-jian",200);           // 金蛇劍法
        set_skill("strike", 200);
        set_skill("jinshe-zhang", 200);
        set_skill("throwing", 200);
        set_skill("jinshe-zhui", 200);
        set_skill("martial-cognize", 200);
        
        map_skill("force", "huntian-qigong");
        map_skill("sword", "jinshe-jian");
        map_skill("parry", "jinshe-jian");
        map_skill("strike", "jinshe-zhang");
        
        setup();
        
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

int accept_object(object who, object ob)
{
        object obn;
        if( !who || environment(who) != environment() ) return 0;
        if( !objectp(ob) ) return 0;
        if( !present(ob, who) ) return notify_fail("你沒有這件東西。\n");
        if( query("id", ob) != "wen shoupa" )
                return notify_fail("夏雪宜不需要這件東西。\n");
        write(HIY "夏雪宜接過手帕，呆呆地出神，突然間潸然淚下。 \n" NOR);
        write(HIR "夏雪宜喃喃道：儀兒啊，我知道你的心意，其實就算是真的，我也不在乎的。\n" NOR);         
        write(HIY "夏雪宜轉過頭來對你說：我該怎樣感謝你呢？\n" NOR);
        write(HIY "他背轉身去，沉默不語，好象在思考著什麼。\n" NOR);
        write(HIY "夏雪宜突然象下了很大決心似地對你說：我看\n" NOR);
        write(HIY "你也是武林中人，這裡有兩本我畢身心血的《金蛇秘芨》，\n" NOR);
        write(HIY "現在它對我來說已經沒有什麼用了，你就拿去吧。\n" NOR);
        write(HIY "夏雪宜嘆了口氣道：你是鋤惡揚善也好，我行我素也好，胡作非為也好，通通與我無關。\n" NOR);
        write(HIY "夏雪宜揮了揮手：好了，你可以走了。\n" NOR);
        /*
        obn = new("/clone/book/jinshe2");
        obn->move(who);
        */
        obn = new("/clone/book/jinshe2");
        obn->move(who);
        obn = new("/clone/book/jinshe3");
        obn->move(who);
        write(HIR "夏雪宜回首按了牆上的一個機關，只聽得隆隆幾聲巨響，石壁之上露出一個四方的洞口來。\n"NOR);
        set("exits/east","/d/shiliang/jinshedong1", get_object("/d/shiliang/jinshedong"));
        destruct(ob);
        return 1;
}
void dest(object ob)
{
        destruct(ob);
}
string ask_skill1(object me,string arg)
{
        return teach_perform(this_player(),this_object(),([
                "perform"        : "suo",        //pfm的代碼
                "name"                : "鎖劍訣",        //pfm的名稱
                "sk1"                : "jinshe-jian",//主要的武功的id
                "lv1"                : 100,                //主要的武功的等級
                "sk2"                : "sword",        //需要武功sk2的id
                "lv2"                : 100,                //需要武功sk2 的等級
                "neili"                : 300,                //需要基本內功等級
                "free"                : 1,                 //free=1不需要同一門派
                "msg1"                : "$N哈哈一笑：要學其實這招並不難，天下人都以常理出招。\n"+
                                "而我金蛇劍法反其道而行，劍訣要旨在于意境，不在招式。\n"+
                                "$n聽了$N的指導，恍然大悟。",
                "msg2"                : "好了，你自己繼續練習吧。",
                ]));
}
string ask_skill2(object me,string arg)
{
        return teach_perform(this_player(),this_object(),([
                "perform"        : "fugu",        //pfm的代碼
                "name"                : "附骨纏身",        //pfm的名稱
                "sk1"                : "jinshe-zhang",//主要的武功的id
                "lv1"                : 100,                //主要的武功的等級
                "sk2"                : "strike",        //需要武功sk2的id
                "lv2"                : 100,                //需要武功sk2 的等級
                "neili"                : 300,                //需要基本內功等級
                "free"                : 1,                 //free=1不需要同一門派
                ]));
}
string ask_skill3(object me,string arg)
{
        return teach_perform(this_player(),this_object(),([
                "perform"         : "tuwu",        //pfm的代碼
                "name"                : "金蛇吐霧",        //pfm的名稱
                "sk1"                : "jinshe-zhui",//主要的武功的id
                "lv1"                : 100,                //主要的武功的等級
                "sk2"                : "throwing",        //需要武功sk2的id
                "lv2"                : 100,                //需要武功sk2 的等級
                "force"                : 100,                //需要基本內功等級
                "neili"                : 300,                //需要最大內力多少
                "free"                : 1,                 //free=1不需要同一門派
                ]));
}

int ask_fuchou() 
{
        object me = this_player();

        if( me->query_skill("jinshe-jian",1) <200 )
                   return 1;

        if( me->query_condition("killer") )
        {
                command("fear "+query("id", me));
                command("say 小心官府通緝！");
                return 1;
        }

        if( query_temp(QUESTDIR+"start", me) )
        {
                command("shake "+query("id", me));
                command("say 你不是說要幫我復仇的嗎，怎麼還在這裡？");
                return 1;
        } 
        
        if( query(QUESTDIR+"over", me) )
        {
                command("thank "+query("id", me));
                command("say 你已經殺了溫家五老幫我復仇了，真是太感謝了！");
                return 1;
        } 
        //非vip玩家，只能失敗三次
        if( query(QUESTDIR+"fail", me) >= 3 && query("registered", me)<3 )
        {
                command("shake "+query("id", me));
                command("say 現在時間緊急，這復仇的事情還是以後再說吧。");
                return 1;
        }
        //需要間隔一天，經驗需要間隔500k

        if( query(QUESTDIR+"start/time", me) && time()-query(QUESTDIR+"start/time", me)<86400 )
        {
                command("shake "+query("id", me));
                command("say 今天先這裡吧，有什麼事情明天再說吧。");
                return 1;
        }
        if( query(QUESTDIR+"combat_exp", me) && query("combat_exp", me)-query(QUESTDIR+"combat_exp", me)<500000 )
        {
                command("look "+query("id", me));
                command("say 以你當前的經驗恐怕還是難以幫我復仇，還是抓緊去練功去吧。");
                return 1;
        }
        
        command("look "+query("id", me));
        command("say 好吧，你去幫我殺掉溫家五老，我定有重謝。");
        command("say 你只要和溫家五老的老大提起“金蛇郎君”即可。");

        set_temp(QUESTDIR+"start", 1, me);//開始標志
         //標記開始時間和經驗
        set(QUESTDIR+"time", time(), me);
        set(QUESTDIR+"combat_exp",query("combat_exp", me), me);
        return 1;
}

int ask_jinshe() 
{
        object me = this_player();      
        int exp, neili;
     
       //相關武功等級必須在250以上
        if( me->query_skill("jinshe-zhui",1) <250 )
                   return 1;
                   
        if( me->query_skill("jinshe-zhang",1) <250 )
                   return 1;
                   
          //必須殺死過溫家五老
        if( !query(QUESTDIR+"over", me) )
                   return 1;

        if( me->query_condition("killer"))
        {
                command("fear "+query("id", me));
                command("say 小心官府通緝！");
                return 1;
        }

        //非vip玩家，只能失敗三次
        if( query(QUESTDIR+"fail", me) >= 3 && query("registered", me)<3 )
        {
                command("shake "+query("id", me));
                command("say 我不是都告訴你了嗎，領悟不了可是你自己的事情了。");
                return 1;
        }
        //武功學習之間需要間隔一天，經驗需要間隔500k

        if( query(QUESTDIR+"time", me) && time()-query(QUESTDIR+"time", me)<86400 )
        {
                command("shake "+query("id", me));
                command("say 今天先這裡吧，有什麼事情明天再說吧。");
                return 1;
        }
        if( query(QUESTDIR+"combat_exp", me) && query("combat_exp", me)-query(QUESTDIR+"combat_exp", me)<500000 )
        {
                command("look "+query("id", me));
                command("say 以你當前的經驗恐怕還是難以領悟要訣，還是抓緊去練功去吧。");
                return 1;
        }
        exp=7000+random(3000);
        neili=200+random(300);
        command("look "+query("id", me));
        command("say 既然你幫我報了大仇，我就將我對金蛇秘籍的研究心得告訴你吧。");
        //標記武功的時間和標志
        set(QUESTDIR+"time", time(), me);
        set(QUESTDIR+"combat_exp",query("combat_exp",  me), me);
        if( random(query("kar", me)) > 22 )
        {
                set(QUESTDIR+"pass", 1, me);
                tell_object(me,HIG"\n你聽了夏雪宜的指點，再與金蛇秘笈中不解之處一加參照，登時豁然貫通，果然妙用無窮。\n\n"NOR);
                tell_object(me,HIC"\n你閉目冥思，《金蛇秘笈》中種種武功秘奧，有如一道澄澈的小溪，緩緩在心中流過，\n"NOR);
                tell_object(me,HIC"清可見底，更先半分渣滓，直到許久才醒覺。經此一陣苦思，不但通解了金蛇郎君的\n"NOR);
                tell_object(me,HIC"\n武學秘訣，對師父所授諸般上乘武功，也有更深一層體會。\n"NOR);
                command("wa "+query("id", me));
                tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"得到夏雪宜的指點，武學修為精進，獲得"+exp+"點經驗獎勵、"+neili+"點最大內力。\n"NOR);
                addn("combat_exp", exp, me);
                addn("max_neili", neili, me);
                me->improve_skill("jinshe-jian", 2000000);
                log_file("quest/jinshequest",sprintf("%s(%s)失敗%d次後得到夏雪宜的指點，武學修為精進。獎勵：%d點經驗，%d點最大內力。\n",me->name(1),query("id", me),query("quest/金蛇劍法/fail", me),exp,neili));

                return 1;
        }
        tell_object(me,HIR"\n苦思冥想，發現自己依然無法理解夏雪宜所傳秘訣。\n\n"NOR);
        command("sigh "+query("id", me));
        addn(QUESTDIR+"fail", 1, me);
        log_file("quest/jinshequest",sprintf("%s(%s)第%d次向夏雪宜求教，但是依然無法理解其中訣竅。\n",me->name(1),query("id", me),query("quest/金蛇劍法/fail", me)));

        return 1;
}
