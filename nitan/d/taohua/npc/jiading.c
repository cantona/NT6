//Cracked by Kafei
//指認yapu_npc的家丁
//maco

inherit NPC;
#include <ansi.h>
string ask_yapu();

void create()
{
        set_name("家丁", ({ "jia ding", "ding" }));
        set("long", "一個二十出頭的小夥子，身板結實，雙目有神，似乎練過幾年功夫。\n");
        set("gender", "男性");
        set("age", 25);

        set_skill("unarmed", 30);
        set_skill("dodge", 30);
        set_skill("parry", 30);
        set_skill("stick", 30);
        set_skill("staff", 30);
        set_skill("sword", 30);
        set_skill("blade", 30);
        set("combat_exp", 10000);
        set("shen_type", 1);
        set("inquiry", ([
                "啞僕" : (:ask_yapu:),
                "yapu" : (:ask_yapu:),
        ]));
        create_family("桃花島", 4, "家丁");
        delete("title");
        setup();
}

int start_check(object me)
{
                call_out("leave", 1200, me);
                call_out("check", 1, me);
}

void init()
{
        ::init();

        add_action("do_recognize", "ren");
        add_action("do_recognize", "recognize");
        add_action("do_bring", "bring");
        add_action("do_bring", "dai");
        add_action("do_order", "order");

}
void leave(object me)
{
        string killer=query_temp("my_killer", me);
        object jiading = this_object();

        if (query("recognized") && objectp(present(me, environment(jiading)))) {
        command("addoil"+query("job_master", jiading));
        call_out("leave", 60, me);
        }

        else if(objectp(present(me, environment(jiading)))){
        message_vision(CYN"$N説道：這麼久還捉不到那"+query("find_yapu_real")+"裝成的"+query("find_yapu")+"，我看今天是逮不到他了，不如先回歸雲莊吧。\n"NOR,jiading);
        command("sigh");
        message_vision("$N快步離開了。\n"NOR,jiading);
        destruct(jiading);
        }

        else {
        message_vision("$N快步離開了。\n"NOR,jiading);
        destruct(jiading);
        }

        return;
}

void check(object me)
{
        string killer=query_temp("my_killer", me);
        object jiading = this_object();

        if( !query("find_yapu", me) )
        {
        command("bye"+query("id", me));
        message_vision("$N快步離開了。\n"NOR,jiading);
        destruct(jiading);
        }

        else if(me->is_ghost() )
        {
        command("ah");
        command("cry corpse");
        command("grpfight"+query_temp("my_killer", me));
        command("kill"+query_temp("my_killer", me));
        }
        else call_out("check", 1, me);
}

int do_recognize(string arg)
{
        object me, ob, jiading, where, weapon, huwei;
        mapping skill_status;
        string *sname;
        int i ,num, level = 0, s_level, j, gain, exp, ob_exp, rate;

        me = this_player();
        exp=query("combat_exp", me);

        jiading = this_object();
        if( query("job_master") != query("id", me) )
                return 0;
        if( query("recognized"))
                return notify_fail("家丁已經指認出來對方了！\n");
        if( !living(jiading) )
                return notify_fail("嗯....你得先把家丁弄醒再説。\n");
        if( !arg )
                return notify_fail("你要家丁指認誰？\n");
        if(!objectp(ob = present(arg, environment(this_player()))))
                return notify_fail("這裏沒有這個人。\n");
        if( query("th_victim", ob) )
                return notify_fail(ob->name()+"已經被指認出來了！\n");
        if(ob == me)
                return notify_fail("指認你自己？有意義嗎？\n");
        if(ob == jiading)
                return notify_fail("要家丁指認家丁？\n");
        if( query("family/family_name", ob) == "桃花島" )
                return notify_fail("你連桃花島的人物也認不出來？\n");
        if( me->is_busy() || me->is_fighting() )
                return notify_fail("你正忙着呢。\n");
        if( jiading->is_busy() || jiading->is_fighting() )
                return notify_fail( "家丁正忙着呢。\n");
        if( query("no_fight", environment(me)) )
                return notify_fail("這裏不能戰鬥，認出來也沒用。\n");


        me->start_busy(1);

        message_vision("$N低聲在家丁耳邊説道：是不是這個"+ob->name()+"？\n",me,ob);
        where = environment(ob);

        if( query("yapu_target", ob) == query("id", me )
         && query("name", ob) == query("find_yapu") )
        {
        if( !living(ob) )
        ob->revive();
        command("ah");
        command("points"+query("id", ob));
        ob->interrupt_me();
        set("real_face", 1, ob);
        set("recognized",1);

        //yapu_npc的身分改換
        {
        set("long",query("real_long",  ob), ob);
        if( query("real_title", ob) )
        set("title",query("real_title",  ob), ob);
        ob->clear_condition();
        set("shen_type", -1, ob);
        
        if ( mapp(skill_status = me->query_skills()) ) {
                skill_status = me->query_skills();
                sname = keys(skill_status);

                for(i=0; i<sizeof(skill_status); i++) {
                        if ( skill_status[sname[i]] > level ) level = skill_status[sname[i]];
                }
                
                level = (int)level*4/5 + 1;
                s_level = (int)level*21/20;

                rate = random(3)+9;

                set("combat_exp", exp*rate/10+random(exp/100), ob);
                ob_exp=query("combat_exp", ob);

                set("th_victim",query("id",  me), ob);
                //此npc的reward
                
                set("gain", 50+level, ob);
                gain=query("gain", ob);
                if(gain>300) gain=300;

                if(exp <  100000) //100k
                        gain = gain + random(level/2);
                else if(exp <  500000) //500k
                        gain = gain + random(level/3);
                else if(exp < 1000000) //1m
                        gain = gain + random(level/4);
                else if(exp < 3000000) //3m
                        gain = gain + random(level/5);
                else gain = gain + random(level/8);

                set("gain_exp", gain, ob);
                set("gain_pot", gain/4+random(gain/10), ob);
                set("shen", -ob_exp/10, ob);
                
                if(ob_exp < 1000000) {
                addn("gain_exp", random(5)+10, ob);
                addn("gain_pot", random(5)+1, ob);
                }
                else if(ob_exp < 2000000) {
                addn("gain_exp", random(5)+15, ob);
                addn("gain_pot", random(5)+5, ob);
                }
                else if(ob_exp < 3000000) {
                addn("gain_exp", random(5)+20, ob);
                addn("gain_pot", random(5)+10, ob);
                }
                else {
                addn("gain_exp", random(5)+25, ob);
                addn("gain_pot", random(5)+15, ob);
                }


                set("max_qi",query("max_qi",  me)*9/10, ob);
                set("eff_qi",query("max_qi",  me)*9/10, ob);
                set("max_jing",query("max_jing",  me)*9/10, ob);
                set("eff_jing",query("max_jing",  me)*9/10, ob);
                set("qi",query("max_qi",  ob), ob);
                set("jing",query("max_jing",  ob)*9/10, ob);
                set("jiali",query("jiali",  me)/2, ob);
                if( query("max_neili", me)>0){
                        set("max_neili", level*30, ob);
                        if( query("max_neili", ob)>query("max_neili", me) )
                                set("max_neili",query("max_neili",  me)+level, ob);
                }
                else set("max_neili", 500, ob);
                
                if( query("max_jingli", me)>0){
                        set("max_jingli",query("max_jingli",  me)*9/10, ob);
                }
                else set("max_jingli", 500, ob);
                set("neili",query("max_neili",  ob), ob);
                set("jingli",query("max_jingli",  ob), ob);
                set("no_sing", 1, ob);
                ob->set_skill("dodge", level);
                ob->set_skill("parry", level );
                ob->set_skill("force", level);
                
        switch(query("real_menpai", ob)){
        case "huashan" :
        ob->set_name("大盜", ({"da dao", "dao" ,"robber"}) );
        ob->set_skill("blade", s_level);
        ob->set_skill("sword", s_level);
        ob->set_skill("cuff", s_level);
        ob->set_skill("strike", s_level);
        ob->set_skill("huashan-jianfa", level);
        ob->set_skill("liangyi-dao", level);
        ob->set_skill("ding-dodge", s_level);
        ob->set_skill("zixia-gong", level);
        ob->set_skill("pishi-poyu", level);
        ob->set_skill("hunyuan-zhang", level);
        ob->set_skill("ziyin-yin", level);
        ob->set_skill("zhengqi-jue", level);

        ob->map_skill("force", "zixia-gong");
        ob->map_skill("dodge", "ding-dodge");
        ob->map_skill("parry", "huashan-jianfa");
        ob->map_skill("strike", "hunyuan-zhang");
        ob->map_skill("cuff", "pishi-poyu");
        ob->map_skill("sword", "huashan-jianfa");
        ob->map_skill("blade", "liangyi-dao");
        ob->prepare_skill("cuff", "pishi-poyu");
        ob->prepare_skill("strike", "hunyuan-zhang");
        set("real_message", HIR"小販臉色一變，喝道："+RANK_D->query_rude(me)+"原來是黃老邪門下？想捉"+RANK_D->query_self_rude(ob)+"，可沒那麼容易！\n"NOR, ob);
        addn("gain_exp", random(10)+30, ob);
        addn("gain_pot", random(5)+20, ob);
        ob->add_money("silver", 20+random(31));
        if(random(3) == 1)  weapon=new("/clone/weapon/gangdao");
        else if(random(3) == 1) weapon=new("/clone/weapon/changjian");
        
                break;
                
        case "dajin" :
        ob->set_name("殺手", ({"shashou", "shou", "killer"}) );
        ob->set_skill("sword", s_level);
        ob->set_skill("cuff", s_level);
        ob->set_skill("taiji-shengong", s_level);
        ob->set_skill("taiji-jian", s_level);
        ob->set_skill("tiyunzong", level);
        ob->set_skill("taiji-quan", s_level);
        ob->set_skill("taoism", level);
        ob->set_skill("literate", level);
        ob->map_skill("force", "taiji-shengong");
        ob->map_skill("parry", "taiji-jian");
        ob->map_skill("cuff", "taiji-quan");
        ob->map_skill("dodge", "tiyunzong");
        ob->map_skill("sword", "taiji-jian");
        ob->prepare_skill("cuff", "taiji-quan");
        set("real_message", HIR"書生冷笑一聲，道："+RANK_D->query_rude(me)+"，特地前來送死嗎？\n"NOR, ob);
        set("jiali", 0, ob);
        set("str", 27+random(4), ob);
        ob->carry_object("/clone/anqi/feibiao")->set_amount(2+random(3));
        if(random(3) != 0) weapon=new("/clone/weapon/changjian");
                break;
                
        case "tiezhang" :
        ob->set_name("惡霸", ({"e ba", "ba"}) );
        ob->set_skill("strike", s_level+20);
        ob->set_skill("blade", s_level);
        ob->set_skill("taixuan-gong", level);
        ob->set_skill("tie-zhang", s_level+20);
        ob->set_skill("ding-dodge", s_level);
        ob->set_skill("wuhu-duanmen", s_level);
        ob->map_skill("blade","wuhu-duanmen");
        ob->map_skill("dodge","ding-dodge");
        ob->map_skill("strike","tie-zhang");
        ob->map_skill("force", "taixuan-gong");
        ob->map_skill("parry", "tie-zhang");
        ob->prepare_skill("strike", "tie-zhang");
        addn("gain_exp", -20, ob);
        addn("gain_pot", -20, ob);
        set("real_message", HIR"趟子手吃了一驚，臉上陡現殺氣，朝$N衝了過來！\n"NOR, ob);
                break;
                
        case "shaolin" :
        ob->set_name("破戒僧", ({"pojie seng", "seng"}) );
        ob->set_skill("blade", s_level);
        ob->set_skill("sword", s_level);
        ob->set_skill("club", s_level);

        ob->set_skill("buddhism", level);
        ob->set_skill("damo-jian", s_level);
        ob->set_skill("xiuluo-dao", s_level);
        ob->set_skill("zui-gun", s_level);
        ob->set_skill("jingang-quan", s_level);
        ob->set_skill("shaolin-shenfa", level);
        ob->set_skill("hunyuan-yiqi", level);
        ob->set_skill("yizhi-chan", level);
        ob->set_skill("banruo-zhang", level);
        ob->map_skill("force", "hunyuan-yiqi");
        ob->map_skill("dodge", "shaolin-shenfa");
        ob->map_skill("parry", "damo-jian");
        ob->map_skill("cuff","jingang-quan");
        ob->map_skill("sword", "damo-jian");
        ob->map_skill("blade", "xiuluo-dao");
        ob->map_skill("club", "zui-gun");
        set("real_message", HIR"僧人臉色一變，獰笑道：好哇，你居然認出了"+RANK_D->query_self_rude(ob)+"來，需容你不得！\n"NOR, ob);
                switch (random(3)) {
                case 0 :
                        ob->set_skill("finger", s_level);
                        ob->set_skill("yizhi-chan", s_level);
                        ob->set_skill("strike", s_level);
                        ob->set_skill("banruo-zhang", s_level);
                        ob->map_skill("finger","yizhi-chan");
                        ob->map_skill("strike","banruo-zhang");
                        ob->prepare_skill("finger","yizhi-chan");
                        ob->prepare_skill("strike","banruo-zhang");
                        if(random(3) == 0) weapon=new("/d/shaolin/npc/obj/jiedao");
                        break;
                case 1 :
                        ob->set_skill("cuff", s_level);
                        ob->set_skill("jingang-quan", s_level);
                        ob->map_skill("cuff","jingang-quan");
                        ob->prepare_skill("cuff","jingang-quan");
                        if(random(3) == 0) {
                        ob->apply_condition("drunk",query("con", ob)+query("max_neili", ob)/100+3);
                        weapon=new("/d/shaolin/npc/obj/qimeigun");
                                }
                        break;
                case 2 :
                        ob->set_skill("claw", s_level);
                        ob->set_skill("longzhua-gong", s_level);
                        ob->map_skill("claw","longzhua-gong");
                        ob->prepare_skill("claw","longzhua-gong");
                        break;
                }
                break;
                
        case "xiyu" :
        ob->set_name("蒙古武將", ({"menggu wujiang", "wujiang", "jiang"}) );
        set("class", "officer", ob);
        set("dali/rank", 3, ob);
        set("rank_info/rude", "狗韃子", ob);
        ob->set_skill("hamagong", s_level+10);
        ob->set_skill("lingshe-zhang", s_level);
        ob->set_skill("wuxingbu", s_level);
        ob->set_skill("luan-blade", s_level);
        ob->set_skill("blade", s_level);
        ob->set_skill("strike", s_level);
        ob->set_skill("parry", s_level);
        ob->set_skill("shentuo-zhang", s_level);
        ob->set_skill("lingshe-quan", s_level);

        ob->map_skill("force", "hamagong");
        ob->map_skill("blade", "luan-blade");
        ob->map_skill("dodge", "wuxingbu");
        ob->map_skill("parry", "luan-blade");
        
        set("real_message", "", ob);
        message_vision(HIR"胡人雙眼一噔，冷笑道：就憑你這"+RANK_D->query_rude(me)+"，也想跟"+RANK_D->query_self_rude(ob)+"作對？\n"NOR, me, ob);

        {
        num = 1+random(3);
        message_vision(HIR"胡人拍了拍手，身後突然躍出"+chinese_number(num)+"個鐵甲護衞，"+chinese_number(num+1)+"人向$N左右包抄！\n"NOR, me, ob);
                    for (i=0; i<num; i++) {
                huwei = new("/d/taohua/npc/mg_huwei");
                set("combat_exp", exp/2+random(exp/1000), huwei);
                set("rank_info/rude", "狗韃子", huwei);
                set("max_qi",query("max_qi",  ob)/2, huwei);
                set("eff_qi",query("max_qi",  ob)/2, huwei);
                set("max_jing",query("max_jing",  ob)/2, huwei);
                set("eff_jing",query("max_jing",  ob)/2, huwei);
                set("qi",query("max_qi",  huwei), huwei);
                set("jing",query("max_jing",  huwei), huwei);
                set("jiali",query("jiali",  ob)/2, huwei);
                set("max_neili",query("max_neili",  ob)/2, huwei);
                set("max_jingli",query("max_jingli",  ob)/2, huwei);
                set("neili",query("max_neili",  huwei), huwei);
                set("jingli",query("max_jingli",  huwei), huwei);

                huwei->set_skill("ding-force", level*3/4);
                huwei->set_skill("san-sword", level*3/4);
                huwei->set_skill("ding-dodge", level*3/4);
                huwei->set_skill("luan-blade", level*3/4);
                huwei->set_skill("wrestling", level*3/4);
                huwei->set_skill("hand", level*3/4);
                huwei->set_skill("force", level*3/4);
                huwei->set_skill("parry", level*3/4);
                huwei->set_skill("dodge", level*3/4);
                huwei->set_skill("sword", level*3/4);

                huwei->map_skill("force", "ding-force");
                huwei->map_skill("sword", "san-sword");
                huwei->map_skill("dodge", "ding-dodge");
                huwei->map_skill("parry", "san-sword");
                huwei->map_skill("hand", "wrestling");
                huwei->prepare_skill("hand", "wrestling");

                huwei->move(environment(me));
                
                huwei->kill_ob(me);
                huwei->start_check(ob);
                huwei->set_leader(ob);
                me->fight_ob(huwei);
                addn("gain_exp", random(10)+20, ob);
                addn("gain_pot", random(5)+5, ob);
                }
        }
        ob->add_money("silver", 20+random(31));
        if( query_temp("armor/cloth", ob) )
        destruct(query_temp("armor/cloth", ob));
        ob->carry_object("/clone/armor/tiejia")->wear();
        if(random(3) == 0) weapon=new("/clone/weapon/gangdao");
        if( random(query("combat_exp", me))>2000000){
        ob->map_skill("strike", "hamagong");
        ob->prepare_skill("strike", "hamagong");
        addn("gain_exp", random(10)+40, ob);
        addn("gain_pot", random(5)+10, ob);
        }
        else {
        ob->map_skill("cuff","lingshe-quan");
        ob->map_skill("strike","shentuo-zhang");
        ob->prepare_skill("cuff","lingshe-quan");
        ob->prepare_skill("strike","shentuo-zhang");
        }

                break;
                
        case "mizong" :
        ob->set_name("護法喇嘛", ({"hufa lama", "hufa", "lama"}) );
        set("class", "lama", ob);
        ob->set_skill("longxiang-banruo", level);
        ob->set_skill("shenkongxing", level);
        ob->set_skill("huoyan-dao", s_level);
        ob->set_skill("yujiamu-quan", level);
        ob->set_skill("dashou-yin", s_level);
        ob->set_skill("lamaism", level);
        ob->set_skill("xue-dao", s_level);
        ob->set_skill("mingwang-jian", s_level);
        ob->set_skill("jingang-chu", level);
        ob->set_skill("staff", level);
        ob->set_skill("sword", s_level);
        ob->set_skill("blade", s_level);
        ob->set_skill("cuff", s_level);
        ob->set_skill("hand", s_level);
        ob->set_skill("strike", s_level);
        ob->map_skill("force", "longxiang-banruo");
        ob->map_skill("dodge", "shenkongxing");
        ob->map_skill("parry", "xue-dao");
        ob->map_skill("blade", "xue-dao");
        ob->map_skill("sword", "mingwang-jian");
        ob->map_skill("staff", "jingang-chu");
        set("real_message", HIR"窮漢見$N目光瞧來，臉上忽然變得猙獰可怖，叫道："+RANK_D->query_rude(me)+"是桃花島來的？\n"NOR, ob);
        
        if( query_temp("armor/cloth", ob) )
        destruct(query_temp("armor/cloth", ob));
        
        ob->carry_object("/d/qilian/obj/lamajiasha")->wear();
        if(random(6) == 0) weapon=new("/clone/weapon/changjian");
        else if(random(5) == 1)        weapon=new("/d/xueshan/obj/miandao");
        else if(random(4) == 2) weapon=new("/d/xueshan/obj/fachu");

        if( random(query("combat_exp", me))>2000000){
        ob->map_skill("strike", "huoyan-dao");
        ob->prepare_skill("strike", "huoyan-dao");
        addn("gain_exp", random(20)+50, ob);
        addn("gain_pot", random(10)+20, ob);
        }
        else {
        ob->map_skill("hand", "dashou-yin");
        ob->map_skill("cuff", "yujiamu-quan");
        ob->prepare_skill("hand", "dashou-yin");
        ob->prepare_skill("cuff", "yujiamu-quan");
        }
                break;
        case "miaojiang" :
        ob->set_name("苗疆巫女", ({"miaojiang wunu", "wunu", "nu"}) );
        ob->set_skill("claw", s_level);
        ob->set_skill("strike", s_level);
        ob->set_skill("huagong-dafa", level);
        ob->set_skill("zhaixinggong", level);
        ob->set_skill("chousui-zhang", s_level);
        ob->set_skill("sanyin-zhua", s_level);
        ob->set_skill("feixing-shu", s_level);
        ob->set_skill("poison", level);
        ob->set_skill("dodge", s_level);

        ob->map_skill("force", "huagong-dafa");
        ob->map_skill("strike", "chousui-zhang");
        ob->map_skill("claw", "sanyin-zhua");
        ob->map_skill("dodge", "zhaixinggong");
        ob->map_skill("parry", "sanyin-zhua");
        ob->prepare_skill("strike", "chousui-zhang");
        ob->prepare_skill("claw", "sanyin-zhua");

        set("real_message", "", ob);
        message_vision(HIR"女孩眼珠一轉，微笑道：這位"+RANK_D->query_respect(me)+"，你該不是要捉我吧？那……我可要先下手。\n"NOR, me);
        
        ob->carry_object("/clone/drug/xxqingxin-san");
        ob->carry_object("/d/xingxiu/obj/lianxin");
        ob->carry_object("/d/xingxiu/obj/blzhen")->set_amount(1+random(3));

        if( query_temp("armor/cloth", ob) )
        destruct(query_temp("armor/cloth", ob));
        ob->carry_object("/d/city/obj/jin_ao")->wear();
        //has poison,add reward
        addn("gain_exp", random(10)+30, ob);
        addn("gain_pot", random(5)+10, ob);

        if( random(query("combat_exp", me))>2000000 && ob->query_skill("strike")>250 && query("neili", ob)>1000 && random(2) == 1){
        message_vision("$N把玉笛放到口邊，輕輕一吹，只聽一陣極尖極細的哨子聲遠遠傳了出去。\n", ob);
        message_vision(HIR"隨着哨子聲，玉笛裏突然飛出藍印印的一點火星，火星陡地熄滅，隨即大亮，蓬的一聲響，騰向半空，升起有丈許，這才緩緩降落。\n"NOR, me);
        new("/d/xingxiu/obj/flute_fire")->move(environment(me));
        addn("gain_exp", random(20)+50, ob);
        addn("gain_pot", random(10)+30, ob);
        }

                break;

        }
                if(weapon != 0) {
                weapon->move(ob);
                weapon->wield();
                }
                //設定完成
                message_vision(""+query("real_message", ob)+"",me,ob);
                ob->kill_ob(me);
                me->fight_ob(ob);

        }

        }
        //改換完成
        }
        else if( query("name", ob) == query("find_yapu") )
        {
        command("shake");
        command("say 打扮差不多，不過不是。");
        }

        else if( query("race", ob) != "人類" )
        {
        command("consider");
        command("say 就算那"+query("find_yapu_real")+"作惡多端，禽獸不如，好歹也還是個人哪……。");
        }

        else if( query("gender", ob) == "女性" && query("per", ob) >= 30 && query("age", ob)<30 )
        {
        message_vision("家丁呆呆地看著$n……\n",me,ob);
        command("shake");
        command("say 這位"+ RANK_D->query_respect(me) +"神仙一般的人物，怎麼會是那個"+query("find_yapu_real")+"？");
        }
        else if( query("gender", ob) == "男性" && query("per", ob) >= 30 )
        {
        command("shake");
        command("say 這位"+ RANK_D->query_respect(me) +"儀表堂堂，豈是那"+query("find_yapu_real")+"可以比擬？");
        }
        else
        {
        command("shake");
        command("say 不是不是。");
        }
        return 1;

}

int do_bring(string arg)
{
        object me, ob, jiading, where, weapon;
        int yapu_exp, yapu_pot;
        string lu;
        me = this_player();
        jiading = this_object();

        if( query("job_master") != query("id", me) )
                return 0;
        if( !living(jiading) )
                return notify_fail("嗯....你得先把家丁弄醒再説。\n");
        if( !arg )
                return notify_fail("你要家丁帶走誰？\n");
        if(!objectp(ob = present(arg, environment(this_player()))))
                return notify_fail("這裏沒有這個人。\n");
        if(ob == me)
                return notify_fail("帶走自己？你到底在想什麼？\n");
        if(ob == jiading)
                return notify_fail("要家丁帶走家丁？\n");
        if( query("th_victim", ob) != query("id", me) )
                return notify_fail("你無法確定"+ob->name()+"是不是你要捉的對象。\n");
        if( me->is_busy() || me->is_fighting() )
                return notify_fail("你正忙着呢。\n");
        if( jiading->is_busy() || jiading->is_fighting() )
                return notify_fail( "家丁正忙着呢。\n");

        switch(query("family/master_name", me)){
        case "黃藥師" :
        lu = "我陸師兄";
        break;
        default:
        lu = "陸莊主";
        }

        yapu_exp=query("gain_exp", ob);
        yapu_pot=query("gain_pot", ob);

        if(yapu_exp > 500) yapu_exp = 500+random(40);
        if(yapu_pot > 250) yapu_exp = 240+random(30);

        if (arg == "corpse" && (ob = present(arg, environment(me))) 
         && query("yapu_fail", ob) == query("id", me) )
        {
        command("shrug");
        command("say 怎麼把人打死了？……算了，還是先把它帶回去交差吧。");
        message_vision("家丁將"+ob->name()+"扶了起來背在背上，走掉了。\n",me,ob);
        delete("find_yapu", me);
        me->apply_condition("th_yapu_fail", 5);
        destruct(ob);
        destruct(jiading);
        }
        else if( query("th_victim", ob) == query("id", me) && !living(ob)){
                message_vision(CYN"$N説道：把這"+ob->name()+"處理了！\n"NOR,me,ob);
                command("nod "+getuid(me));
                
                if( query_temp("last_damage_from", ob) == me && query("age", ob)<20 && query("shen", me)>1000){
                message_vision(HIR"家丁掏出一把細長的鐵柄小刀，扳開$n的嘴巴，正要斬去$n的舌頭……\n"NOR,me,ob);
                message_vision(CYN"$N忽然説道：且慢！這"+ob->name()+"年紀尚輕，雖然誤入歧途，但是未始不能改過。\n"NOR,me,ob);
                message_vision(CYN"$N説道：你先別動手，直接把$p帶回歸雲莊，交給"+lu+"，由他處理便是。\n"NOR,me,ob);
                command("ok");
                addn("th_exp", yapu_exp, me);
                addn("th_pot", yapu_pot, me);
                set("th_help_yapu", 1, me);
                }
                else if( query_temp("last_damage_from", ob) == me){
                message_vision(HIR"家丁掏出一把細長的鐵柄小刀，扳開$n的嘴巴，飛快地斬去了$n的舌頭，跟着轉過刀鋒，在$p雙耳各刺一刀，立時鮮血泉湧！\n"NOR,me,ob);
                message_vision(HIR"家丁收起小刀，取出一個瓷瓶，挑出傷藥彈在$p斷舌和雙耳傷處，流血立緩，可是從此也已成聾啞之人。\n"NOR,me,ob);
                addn("th_exp", yapu_exp, me);
                addn("th_pot", yapu_pot, me);
                }
                else {
                command("say 雖然不是"+ RANK_D->query_respect(me) +"親手擺平的，不過總算是逮到這"+RANK_D->query_rude(ob)+"了！");
                set_temp("not_me", 1, me);
                //算成功，不過沒reward。
                }
        command("say 我現在就把這"+RANK_D->query_rude(ob)+"帶回歸雲莊上。");
        message_vision("家丁將"+ob->name()+"扶了起來背在背上，走掉了。\n",me,ob);
        set("th_yapu_ok", 1, me);

                if( query_temp("not_me", me)){
                tell_object(me,"此次工作本來可獲得"+yapu_exp+"點桃花exp，"+yapu_pot+"點桃花pot，不過因為不是你自己完成的，所以不算。\n");
                log_file("test/yapu_job",
                sprintf("%s(%s) failed to get %d th_exp and %d th_pot from %s on %s\n", 
                me->name(),query("id", me),yapu_exp,yapu_pot,ob->name(),ctime(time())));
                delete_temp("not_me", me);
                }
                else {
                tell_object(me,"此次工作獲得"+yapu_exp+"點桃花exp，"+yapu_pot+"點桃花pot。\n");
                log_file("test/yapu_job",
                sprintf("%s(%s) got %d th_exp and %d th_pot from %s on %s\n", 
                me->name(),query("id", me),yapu_exp,yapu_pot,ob->name(),ctime(time())));

                }
                if( query("th_exp", me)>10000){
                set("th_exp", 10000, me);
                tell_object(me,"你的桃花經驗已經達到10000點的滿點，不能再累積了。\n");
                }

                if( query("th_pot", me)>query("max_potential", me)*10){
                set("th_pot",query("max_potential",  me)*10, me);
                tell_object(me,"你的桃花潛能已經達到"+(query("max_potential", me)*10)+"點的滿點，不能再累積了。\n");
                }
                
        destruct(ob);
        destruct(jiading);
        }
        else tell_object(me,"你得先打昏"+ob->name()+"才行！\n");

        return 1;
}

string ask_yapu()
{
        object me;
        me = this_player();

        if( query("job_master") == query("id", me)){
        return "我在"+query("yapu_region")+""+query("yapu_room")+CYN"見到那"+query("find_yapu_real")+"時，看來是個尋常"+query("find_yapu")+"模樣。";        
        }
        else return 0;
}

int do_order(string arg)
{
        object me, jiading;
        me = this_player();
        jiading = this_object();

        if( query("job_master") != query("id", me) )
                return 0;
        if( !living(jiading) )
                return notify_fail("嗯....你得先把家丁弄醒再説。\n");
        if( me->is_busy() )
                return notify_fail("你正忙着呢。\n");
        if( jiading->is_busy() || jiading->is_fighting() )
                return notify_fail( "家丁正忙着呢。\n");

        if( arg == "follow" ) {
        message_vision("$N向家丁招了招手，要他跟上來。\n",me);
        command("follow"+query("id", me));
        }
        if( arg == "stay" ) {
        message_vision("$N命令家丁留在原地。\n",me);
        command("nod"+query("id", me));
        command("follow none");
        }
        if( arg == "leave" ) {
        message_vision("$N向家丁一揮手，説道：你先離開這兒！\n",me);
        command("nod");
        jiading->random_move();
        }

        return 1;
}
