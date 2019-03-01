// cheng.c 程藥發
#include <ansi.h>
inherit NPC;

int ask_job();
int ask_fail();
string *yz_east = ({//這裡定義強盜的可能產生地
        "/d/taishan/yidao1",
        "/d/quanzhou/qzroad1",
        "/d/quanzhou/qzroad4",
        "/d/fuzhou/fzroad1",
        "/d/fuzhou/kedian",
        "/d/fuzhou/wuyishan3",
        "/d/taishan/taishanjiao",
        "/d/huanghe/huanghe4",
        "/d/huanghe/huanghe_1",
        "/d/huanghe/jingyuan",
        "/d/huanghe/wufosi",
        "/d/huanghe/xueguan",
        });

string *yz_south = ({//這裡定義強盜的可能產生地
        "/d/wudang/wdroad4",
        "/d/fuzhou/fzroad6",
        "/d/henshan/hsroad1",
        "/d/wudang/wdroad5",
        "/d/wudang/house",
        "/d/wudang/sanbuguan",
        "/d/emei/qsjie1",
        "/d/emei/caopeng",
        "/d/emei/cangjinglou",
        "/d/xiaoyao/muwu3",
        "/d/xiaoyao/muwu2",
        "/d/xiaoyao/shulin2",
        });

string *yz_north = ({//這裡定義強盜的可能產生地
        "/d/shaolin/hanshui1",
        "/d/shaolin/jiulou2",
        "/d/shaolin/shijie1",
        "/d/shaolin/shijie5",
        "/d/city2/haigang",
        "/d/city2/xiaotan",
        "/d/city2/road2",
        "/d/city2/yihongyu",
        "/d/city2/zhuang4",
        "/d/city2/zhuang9",
        });

string *yz_west = ({//這裡定義強盜的可能產生地
        "/d/xiangyang/northgate2",
        "/d/xiangyang/hutong2",
        "/d/xiangyang/westjie3",
        "/d/xiangyang/wallw8",
        "/d/xiangyang/shudian",
        "/d/xiangyang/walle7",
        "/d/xiangyang/minju2",
        "/d/city4/road4",
        "/d/city4/clubup",
        "/d/mingjiao/westroad1",
        "/d/mingjiao/westroad2",
        "/d/mingjiao/shanjiao",
        "/d/mingjiao/huangtulu2",
        "/d/mingjiao/mjtianmen",
        });

void create()
{
        set_name("程藥發", ({ "cheng yaofa", "cheng" }));
        set("title", "知府");
        set("gender", "男性");
        set("age", 43);
        set("str", 20);
        set("dex", 20);
        set("long", "他就是程藥發，現任知府。\n");
        set("combat_exp", 3000000);
        set("shen", 0);
        set("attitude", "heroism");

        set_skill("unarmed", 50);
        set_skill("force", 50);
        set_skill("sword", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);

        set("neili", 500); 
        set("max_neili", 500);
        set("inquiry", ([
                "job" : (:ask_job():),
                "任務" : (: ask_job() :),
                "失敗" : (: ask_fail() :),
          ])),

        set("env/important", 1);    

        setup();
        carry_object(__DIR__"obj/jinduan")->wear();
}

int ask_job()
{

        object me = this_player(), ob;
        mapping skl; 
        string *sname, place;
        int i, skill = 0;

        skl = me->query_skills();

        if (me->query("combat_exp") < 100000){
                command("say " + RANK_D->query_respect(me) + "你的本事還沒有到家呢，恐怕此去路途險惡，你還不能勝任！\n");
                return 1;
        }

        if ( !skl ) {
                tell_object(me, "你去學一些本事先吧！\n");
                return 1;
                }
        sname  = sort_array( keys(skl), (: strcmp :) );
        for(i=0; i<sizeof(skl); i++) 
                if (skl[sname[i]] >= skill && sname[i] != "literate" && sname[i] != "taoism")
                        skill = skl[sname[i]];
                        
        if (skill < 80) skill = 80;
       
        if (me->query("combat_exp") > 1000000) {
                command("say " + RANK_D->query_respect(me) + "乃是國之棟樑，我小小縣令，豈敢勞您大架！");
                return 1;
        }
        if (me->query("kill_qiangdao") == 1) {
                command("kick " + me->query("id"));
                command("say 我不是給了你任務了嗎？");
                return 1;
                }
        else {
                command("nod" + me->query("id"));
                command("say " + RANK_D->query_respect(me) + "能為江山社稷著想，真是太好了。");
                me->set("kill_qiangdao", 1);
                me->set("quest3/quest_type", "殺");
                me->set("quest3/quest", "強盜");
                me->set("task_time", time() + 300);
                switch(random(3)) {
                case 0 :
                        ob = new(__DIR__"qiangdao");
                        ob->set("long", "他是明教棄徒，專靠打劫營生，長了一臉橫肉，讓人望而生畏。\n"
                        "他是" + me->query("name") + "(" + me->query("id") + ")" + "的目標。\n");
                        ob->set_skill("jiuyang-shengong", skill);
                        ob->set_skill("blade", skill);
                        ob->set_skill("strike", skill);
                        ob->set_skill("lingxu-bu", skill);
                        ob->set_skill("sanhua-zhang", skill);
                        ob->set_skill("jinwu-daofa", skill);
                        ob->map_skill("force", "jiuyang-shengong");
                        ob->map_skill("strike", "sanhua-zhang");
                        ob->map_skill("dodge", "lingxu-bu");
                        ob->map_skill("parry", "jinwu-daofa");
                        ob->map_skill("blade","jinwu-daofa");
                        ob->prepare_skill("strike", "sanhua-zhang");
                        ob->set("chat_chance_combat", 100);
                        break;

                default : 
                        ob = new(__DIR__"qiangdao");                   
                        ob->set("long", "他是星宿弟子，常常下山打劫，尖尖的下巴上掛著幾屢胡須，一看就知道他是個邪魔外道之輩。\n"
                        "他是" + me->query("name") + "(" + me->query("id") + ")" + "的目標。\n");
                        ob->set_skill("zhaixinggong", random(skill));
                        ob->set_skill("huagong-dafa", random(skill));
                        ob->set_skill("chousui-zhang", random(skill));
                        ob->set_skill("strike", random(skill));
                        ob->set_skill("unarmed", random(skill));
                        ob->map_skill("force", "huagong-dafa");
                        ob->map_skill("dodge", "zhaixinggong");
                        ob->map_skill("parry", "chousui-zhang");
                        ob->map_skill("strike","chousui-zhang");
                        ob->prepare_skill("strike", "chousui-zhang");
                        ob->set("chat_chance_combat", 100);
                        break;
                  }

                                 
                switch(random(4)) {
                        case 0 :
                                place = yz_east[random(sizeof(yz_east))];
                                ob->move(place);
                                me->set("quest3/place", place);
                                command("whisper " + me->query("id") + " 有一個強盜在揚州城東為非作歹，你去降服他。");                           
                                break;
                        case 1 :
                                place = yz_south[random(sizeof(yz_south))];
                                ob->move(place);
                                me->set("quest3/place", place);
                                command("whisper " + me->query("id") + " 有一個強盜在揚州城南為非作歹，你去降服他。");                           
                                break;
                        case 2 :
                                place = yz_north[random(sizeof(yz_north))];
                                ob->move(place);
                                me->set("quest3/place", place);
                                command("whisper " + me->query("id") + " 有一個強盜在揚州城北為非作歹，你去降服他。");                           
                                break;
                        default :
                                place = yz_west[random(sizeof(yz_west))];
                                ob->move(place);
                                me->set("quest3/place", place);
                                command("whisper " + me->query("id") + " 有一個強盜在揚州城西為非作歹，你去降服他。");                           
                }               
                ob->set_temp("owner/id",me->query("id"));
                ob->set("combat_exp", me->query("combat_exp"));
                ob->set("max_neili", me->query("max_neili"));
                ob->set("eff_qi", me->query("max_qi") * 2);
                ob->set("max_qi", me->query("max_qi") * 2);
                ob->set("qi", me->query("max_qi") * 2);
                ob->set("jiali",me->query("jiali") * 2);
                ob->set_skill("dodge", skill);
                ob->set_skill("force", skill);
                ob->set_skill("parry", skill);

                ob->set("force_factor", random(10));   
                return 1;
                }
        return 1;
}

int ask_fail()
{
        object me = this_player();
        
        if (me->query("kill_qiangdao") == 1) {
                command("haha");
                command("say 你這身手也敢來懲姦除惡，都怪老夫當初看錯了人。");
                command("chat " + me->query("name") + "狂妄自大，致使強盜危害一方。來人啦，杖責三十，逐出堂外！");
                me->move("/d/city/yamen");
                me->add("qi",-300);
                call_out("delete", 300);
                return 1;
                }
        else return 0;
}

int delete()
{
        this_player()->delete("kill_qiangdao");
        return 1;
}

