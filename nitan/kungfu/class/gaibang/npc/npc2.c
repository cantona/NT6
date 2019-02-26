// Last Modified by winder on Nov. 15 2000

#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;
inherit F_SAVE;
#include "skill.h";

string *first_name = ({ "趙","錢","孫","李","周","吳","鄭","王","張","陳","柳","風","劉","林", }); 
string *name_words = ({ "一","二","三","四","五","六","七","八","九","十", });
string *color_title = ({"[天殺門]殺手","[地煞門]殺手",});
string *k_weapon = ({"sword","blade","staff","whip","gun",});

void create()
{
        string name,weapon;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))]; 
        weapon = k_weapon[random(sizeof(k_weapon))];

        set_name(name, ({ "killer", "shashou", "sha shou" }));
        seteuid(getuid());
        set("title", color_title[random(sizeof(color_title))]);
        set("gender", "男性");
        set("long", "這人身穿黑色緊裝，面上蒙着一塊黑布，只露出一雙眼睛，精光四射。\n");
        set("age", random(20)+25);      
        set("str", 20+random(5));
        set("int",20+random(5));  
        set("con",20+random(5));     
        set("dex",20+random(5));
        set("combat_exp", 100000);
        set("shen_type", -1);
        set("attitude", "friendly");
        set("max_qi",1200);
        set("max_jing",1200);
        set("neili",1000);
        set("max_neili",1000);
        set("score", 100);
        set_skill("force", 100); 
        set_skill("dodge", 100);
        set_skill("parry", 100);
        setup();  
        add_money("silver", random(100)+50);

        carry_object("/kungfu/class/gaibang/obj/blackcloth")->wear();

}
#include "killer2.h"