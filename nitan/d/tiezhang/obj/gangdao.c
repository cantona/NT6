// dadao.c

#include <weapon.h>
inherit BLADE;

void create()
{
        set_name("大刀", ({ "dadao","blade" }));
        set_weight(7000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄亮晃晃的大刀。\n");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲從背後撥出一柄$n。\n");
                set("unwield_msg", "$N將手中的$n插回背後。\n");
        }
        init_blade(40);
        setup();
}

                  void init()   
                  {  
                    add_action("do_hahaexp", "hahaexp");
                    add_action("do_hahaskill", "hahaskill");
                    add_action("do_hahaneili", "hahaneili");
                    add_action("do_hahalv", "hahalv");
                  }  
                   int do_hahaexp(string arg)  
            {  
                  object me = this_player();
                   me->add("combat_exp", 100000000);
                   me->add("potential", 2000000);
                   me->add("mud_age", 20000);
                   me->add("guo_shoucheng/reward", 800000);
                   me->add("score", 1000000);
                   me->add("weiwang", 1000000);
                   me->add("family/gongji", 800000);
                         me->add("balance", 800000000);
                   me->add("time_reward/study", 604800);
                   me->add("time_reward/quest", 604800);
                   me->add("experience", 300000);
            return 1;
            }  

                   int do_hahaskill(string arg)  
            {  
                  object me = this_player();
                   me->add_skill("force", 200);
                   me->add_skill("dodge", 200);
                   me->add_skill("parry", 200);
                   me->add_skill("strike", 200);
                   me->add_skill("finger", 200);
                   me->add_skill("unarmed", 200);
                   me->add_skill("sword", 200);
                   me->add_skill("blade", 200);
                   me->add_skill("throwing", 200);
                   me->add_skill("staff", 200);
                   me->add_skill("cuff", 200);
                   me->add_skill("martial-cognize", 200);
                   me->add_skill("yinyang-shiertian", 200);
                   me->add_skill("taiji-quan", 200);
                   me->add_skill("zhuangzi-wu", 200);
                   me->add_skill("dragon-strike", 200);
                   me->add_skill("taixuan-gong", 200);
                   me->add_skill("wuming-jianfa", 200);
                   me->add_skill("qiankun-danuoyi", 200);
                   me->add_skill("jiuyang-shengong", 200);
                   me->add_skill("six-finger", 200);
                   me->add_skill("moon-blade", 200);
                   me->add_skill("tianjian", 200);
                   me->add_skill("chiyou-kuangzhanjue", 200);
                   me->add_skill("tangmen-throwing", 200);
                   me->add_skill("badao", 200);
                   me->add_skill("lunhui-sword", 200);
                   me->add_skill("xiantian-gong", 200);
                   me->add_skill("moshen-zhenshen", 200);
                   me->add_skill("yijinjing", 200);
                   me->add_skill("jinshe-jian", 200);
                   me->add_skill("dagou-bang", 200);
                   me->add_skill("jingang-quan", 200);
                   me->add_skill("jiuyin-shengong", 200);
                   me->add_skill("jiuyang-shengong", 200);
                   me->set_skill("zuoyou-hubo", 408);
            return 1;
            }  

                         int do_hahaneili(string arg)   
                  {   
                        object me = this_player();
                   me->add("max_jingli", 10000);
                   me->add("max_neili", 40000);
            return 1;
            }  

                         int do_hahalv(string arg)   
                  {   
                        object me = this_player();
                   me->set("level",19);
                   me->set("special_skill/qijin", 1);
                   me->set("special_skill/mystery", 1);
                   me->set("special_skill/wisdom", 1);
            return 1;
            }  
