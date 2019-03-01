// 離村前設置性格及天賦等數據

#include <ansi.h>

inherit NPC;

mixed ask_chucun();       //請求出村

void create()
{
        set_name(HIC "花伯" NOR, ({ "hua bo", "hua", "bo" }));
        set("long", @LONG
這是一個精幹的老者，看起來有八十多歲，他是老村長的徒弟，
如果你要出村，可以找他（ask hua about 出村）。
LONG);        
        set("gender", "男性" );
        set("title", HIR "古村守衛" NOR); 
        set("age", 88);
        set("attitude", "friendly");
        set("max_jing", 5000000);
        set("max_qi", 5000000);
        set("max_jingli", 5000000);
        set("jingli", 5000000);
        set("max_neili", 5000000);
        set("neili", 5000000);
        set("jiali", 600);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);
        set("combat_exp", 100000000);

        set("inquiry", ([
                "出村" : (: ask_chucun :),
        ]));

        set_skill("dodge", 800);
        set_skill("unarmed", 800);
        set_skill("force", 800);
        set_skill("parry", 800);
        set_skill("sword", 800);
        set_skill("poison", 800);
        set_skill("medical", 800);
        set_skill("hand", 800);
        set_skill("strike", 800);
        set_skill("staff", 800);
        set_skill("finger", 800);
        set_skill("claw", 800);
        set_skill("blade", 800);
        set_skill("pixie-jian", 800);
        set_skill("literate", 800);
        set_skill("taoism", 800);
        set_skill("buddhism", 800);
        set_skill("jiuyang-shengong", 800);
        set_skill("lingbo-weibu", 800);
        set_skill("qiankun-danuoyi", 800);
        set_skill("xuanming-zhang", 800);
        set_skill("jiuyin-baiguzhao", 800);
        set_skill("dugu-jiujian", 800);
        set_skill("qianzhu-wandushou", 800);
        set_skill("ranmu-daofa", 800);
        set_skill("dagou-bang", 800);
        set_skill("shaolin-yishu", 800);
        set_skill("wudu-qishu", 800);
        set_skill("throwing", 800);
        set_skill("mantian-xing", 800);
        set_skill("idle-force", 800);
        set_skill("sad-strike", 800);

        map_skill("unarmed", "sad-strike");
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("strike", "xuanming-zhang");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("sword", "dugu-jiujian");
        map_skill("blade", "ranmu-daofa");
        map_skill("staff", "dagou-bang");
        map_skill("throwing", "mantian-xing");
        map_skill("poison", "wudu-qishu");
        map_skill("medical", "shaolin-yishu");

        prepare_skill("unarmed", "sad-strike");

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.po" :),
                (: perform_action, "blade.zhenyan" :),
                (: perform_action, "blade.huo" :),
                (: perform_action, "staff.wugou" :),
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.ban" :),
                (: perform_action, "unarmed.xiao" :),
                (: perform_action, "parry.nuoyi" :),
                (: perform_action, "dodge.lingbo" :),
                (: perform_action, "throwing.shan" :),
                (: perform_action, "hand.zhugu" :),
                (: perform_action, "strike.wuji" :),
                (: perform_action, "finger.six" :),
                (: perform_action, "finger.zhongheng" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),
        }));

        setup();
        carry_object("d/city/obj/cloth")->wear();
}

int accept_fight(object me)
{
          tell_object(me, HIG "這位" + RANK_D->query_respect(me) +
                "，你還是到練武場找人比試吧！\n" NOR);
          return 0;
}

mixed ask_chucun()
{
        object me;
        string msg;

        me = this_player();

        if( !query("newbie_quest_completed/can_out", me) )
                return "沒有尊師的允許，我可不敢讓你出村！\n";

        if( query("combat_exp", me)>200000 )
        {
                return "對不起，你經驗太高了，恐怕我也幫不了你了（經驗不能超過20萬）！\n";
        }

        msg = HIG "好吧！你選擇你要去的地方吧：\n" NOR;
        msg+= HIW "--------------------------------------------\n" NOR;
        msg+= HIC "1. 直接出村（到揚州武廟）\n" NOR;
        msg+= HIC "2. 到郭府歷練（到郭府大門外）\n" NOR;
        msg+= HIC "3. 拜師（到門派入門師傅處）\n" NOR;
        msg+= HIC "4. 我還是先在古村四處逛逛吧。\n" NOR;
        msg+= HIW "--------------------------------------------\n" NOR;
        msg+= HIR "請輸入1─4編號。\n\n" NOR;

        tell_object(me, msg);

        input_to("get_select", me);
        
        return 1;
}

void get_select(string arg, object me)
{
        string msg;

        if (! arg || arg == "4")return;

        if (arg != "1" && arg != "2" && arg != "3")
        {
                tell_object(me, HIG "請輸入 1─4 中的數字！\n");
                input_to("get_select", me);
                return;
        }

        
        if (arg == "1")
        {
                me->move("/d/city/wumiao");
                set("startroom", "/d/city/wumiao", me);

                // 出村給予5萬經驗10萬潛能
                addn("combat_exp", 50000, me);
                addn("potential", 100000, me);
                tell_object(HIG "新手獎勵：你成功出古村，獲得5萬經驗和10萬潛能的獎勵！\n" NOR);
                        
                // 取消拜師標志
                delete("family", me);
                delete("title", me);
                set("title", "普通百姓", me);

                // 設置年齡
                set("mud_age", 0, me);
                me->save();
                return;
        }
        if (arg == "2")
        {
                me->move("/d/wuguan/guofu_gate");
                tell_object(me, BLINK + HIR "\n輸入指令 join 郭府 加入郭府！\n" NOR);
                set("startroom", "/d/wuguan/guofu_gate", me);

                // 出村給予5萬經驗10萬潛能
                addn("combat_exp", 50000, me);
                addn("potential", 100000, me);
                tell_object(HIG "新手獎勵：你成功出古村，獲得5萬經驗和10萬潛能的獎勵！\n" NOR);
                                
                // 取消拜師標志
                delete("family", me);
                delete("title", me);
                set("title", "普通百姓", me);
                // 設置年齡
                set("mud_age", 0, me);
                me->save();
                return;
        }
        if (arg == "3")
        {
                msg = HIC "請選擇你要去的門派（我將送你到門派拜師處）：\n" NOR;
                msg+= HIW "------------------------------------------\n" NOR;
                msg+= HIY "f1.  華山派            f15. 血刀門\n"
                          "f2.  嵩山派            f16. 大輪寺\n"
                          "f3.  衡山派            f17. 丐  幫\n"
                          "f4.  少林派            f18. 鐵掌幫\n"
                          "f5.  武當派            f19. 紅花會\n"
                          "f6.  峨嵋派            f20. 五毒教\n"
                          "f7.  逍遙派            f21. 明  教\n"
                          "f8.  靈鷲宮            f22. 玄冥谷\n"
                          "f9.  星宿派            f23. 梅  莊\n" 
                          "f10. 古墓派            f24. 雪山派\n"
                          "f11. 全真派            f25. 鎮遠鏢局\n"
                          "f12. 昆侖派            f26. 絕情谷\n"
                          "f13. 桃花島            f27. 日月神教\n"
                          "f14. 藥王谷\n\n"
                          "s1.  歐陽世家          s2.  中原苗家\n"
                          "s3.  慕容世家          s4.  八卦刀商家堡\n"
                          "s5.  關外胡家          s6.  大理段氏\n\n" NOR;
               msg+= HIW "--------------------------------------\n" NOR;
               msg+= HIR "請輸入f1─f15，s1─s6編號。\n\n" NOR;

               tell_object(me, msg);
               input_to("get_sel_fam", me);

               return;                
        }
        return;                
        
}

void get_sel_fam(string arg, object me)
{
        
        mapping path;
        string where;

        path = ([
            "f1"    :  "/d/huashan/laojun",
            "f2"    :  "/d/songshan/dadian",
            "f3"    :  "/d/henshan/zhurongdian",
            "f4"    :  "/d/shaolin/guangchang1",
            "f5"    :  "/d/wudang/sanqingdian",
            "f6"    :  "/d/emei/huayanding",
            "f7"    :  "/d/xiaoyao/xiaodao4",
            "f8"    :  "/d/lingjiu/damen",
            "f9"    :  "/d/xingxiu/xxh1",
            "f10"   :  "/d/gumu/mumen", 
            "f11"   :  "/d/quanzhen/jiaobei",
            "f12"   :  "/d/kunlun/guangchang",
            "f13"   :  "/d/taohua/jingshe",
            "f14"   :  "???",
            "f15"   :  "/d/xuedao/shandong2",
            "f16"   :  "/d/xueshan/shanmen",
            "f17"   :  "/d/gaibang/inhole",
            "f18"   :  "/d/tiezhang/guangchang",
            "f19"   :  "/d/huijiang/damen",
            "f20"   :  "/d/wudu/neijin",
            "f21"   :  "/d/mingjiao/shanmen",
            "f22"   :  "/d/xuanminggu/zulin2",
            "f23"   :  "/d/meizhuang/keting",
            "f24"   :  "/d/lingxiao/gate",
            "f25"   :  "/d/beijing/gate",
            "f26"   :  "/d/jueqing/shanzhuang",
            "f27"   :  "0",
            "s1"    :  "/d/city/beidajie1",
            "s2"    :  "/d/zhongzhou/miaojia_houting",
            "s3"    :  "/d/yanziwu/shuiyun",
            "s4"    :  "/d/shaolin/guangchang1",
            "s5"    :  "/d/guanwai/xiaowu",
            "s6"    :  "/d/dali/neitang",

        ]);

        
        if (! arg)return;

        if (arg == "f14")
        {
                tell_object(me, HIG "藥王谷暫時還沒開放！\n" NOR);
                get_select("3", me);
                return;
        }
        if (arg == "f25")
        {
                tell_object(me, HIG "鎮遠鏢局暫時還沒開放！\n" NOR);
                get_select("3", me);
                return;
        }
        // 日月神教分男女
        if (arg == "f27")
        {
                if( query("gender", me) == "男性" )
                {
                        where = "/d/heimuya/pingdingzhou";
                }
                else
                        where = "/d/heimuya/shenggu";

        }

        if (! stringp(where))where = path[arg];

        if (! stringp(where))
        {
                tell_object(me, HIR "輸入編號錯誤！\n" NOR);
                get_select("3", me);
                return;
        }


        // 出村給予5萬經驗10萬潛能
        addn("combat_exp", 50000, me);
        addn("potential", 100000, me);
        tell_object(HIG "新手獎勵：你成功出古村，獲得5萬經驗和10萬潛能的獎勵！\n"
                        "到揚州武廟(南賢)處輸入指令 ask nanxian 新手福利 還可領取新手福利!\n" NOR);
                
        // 取消拜師標志
        delete("family", me);
        delete("title", me);
                set("title", "普通百姓", me);
        // 設置年齡
        set("mud_age", 0, me);
        // 取消登陸地點
        set("startroom", where, me);

        //write("where = " + where +"\n");
        // 移動過去
        me->move(where);
        me->save();

        return;
}

void init()
{
        object me;

        me = this_player();

        tell_object(me, HIG "\n花伯對你說道：這位" + RANK_D->query_respect(me) +
                "，如果要出村輸入 " HIR "ask hua about 出村 \n\n" NOR);

        return;

}
