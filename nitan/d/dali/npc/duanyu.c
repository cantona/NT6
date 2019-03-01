// duanyu.c 段譽

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("段譽", ({"duan yu", "duan", "yu"}));
        set("nickname", GRN"大理王子"NOR);
        set("gender", "男性");
        set("age", 20);
        set("long", 
                "他是一個身穿青衫的年輕男子。臉孔略尖，自有一股書生的呆氣。\n");
        set("attitude", "peaceful");
        
        set("str", 12);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("chat_chance", 1);
        set("chat_msg", ({
                "段譽歎了口氣道：“唉……何時能再見到語嫣啊……”\n",
                (: random_move :),
        }));

        set("inquiry", ([
                "大理" : "大理是個好地方，山清水秀，風景宜人。\n",
                "王語嫣" : "唉，她心裏只有她表哥，從來就沒把我放在眼裏。\n",
                "拜師" : "嗯....，我的師傅是老子、孔子和莊子，他們的學問我還沒學全呢。\n",
        ]));

        set("jing", 2000);
        set("max_jing", 2000);
        set("jingli", 2000);
        set("max_jingli", 2000);
        set("qi", 2000);
        set("max_qi", 2000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali",200);
        
        set("combat_exp", 500000);
        set("score", 20000);
         
        set_skill("force", 180);                // 基本內功
        set_skill("beiming-shengong", 180);        // 北冥神功
        set_skill("finger", 120);                // 基本指法
        set_skill("six-finger", 120);                // 六脈神劍
        set_skill("dodge", 150);                // 基本躲閃
        set_skill("lingbo-weibu", 150);                // 凌波微步
        set_skill("parry", 80);                        // 基本招架
        
        map_skill("force", "beiming-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("parry", "six-finger");
        map_skill("finger", "six-finger");
        prepare_skill("finger","six-finger");
        
        setup();
        
        carry_object("/d/city/obj/gangjian");
        carry_object("/clone/misc/cloth")->wear();
}
