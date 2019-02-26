//shiwei.c

#include <ansi.h>

inherit NPC;

string *first_name = ({ "趙","錢","孫","李","周","吳","鄭","王","樊","陳","祝","魏","蔣","沈",
                        "韓","楊", "劉","張","林","朱","歐陽","司馬","慕容","諸葛" });
string *name_words = ({ "順","昌","振","發","財","俊","彥","良","志","忠","孝","雄","益","添",
                        "金","輝","長","盛","勝","進","安","福","同","滿","富","萬","龍","隆",
                        "祥","棟","國","億","壽","思","霖","雷","鵬","平","軾","甫","維","齡",
                        "橋","溪","聲","谷","山","舟","巖","泉","遊","遜", });
        
void create()
{
        string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))];
        if (random(10) > 2) name += name_words[random(sizeof(name_words))];
        set_name(name, ({"shi wei","shi","wei"}));
        set("long",
                "這是位守護皇宮的帶刀侍衞，身穿勁裝，手持鋼"
                "刀。他雙目精光炯炯，警惕地巡視着四周的情形。\n");
        set("title", HIR"二品帶刀侍衞"NOR);
        set("age", 25);
        set("combat_exp", 200000);
        set("attitude", "heroism");
        set("str", 25);
        set("max_qi", 1000);
        set("max_jing", 1000);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 30);
        set_skill("blade", 100);
        set_skill("unarmed", 100);
        set_skill("parry", 100);
        set_skill("dodge", 100);
        set_skill("force", 100);
        setup();

        carry_object("/d/changan/npc/obj/blade")->wield();
        carry_object("/d/changan/npc/obj/jinzhuang")->wear();
}