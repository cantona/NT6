//fujiang.c

inherit NPC;

string weapon_file, skill, special_skill;
string *first_name = ({ "趙","錢","孫","李","周","吳","鄭","王","樊","陳","祝",
                        "魏","蔣","沈","韓","楊", "劉","張","林","朱","歐陽",
                        "司馬","慕容","諸葛" });
string *name_words = ({ "順","昌","振","發","財","俊","彥","良","志","忠",
        "孝","雄","益","添","金","輝","長","盛","勝","進","安","福","同","滿",
        "富","萬","龍","隆","祥","棟","國","億","壽","思","霖","雷","鵬","平",
        "軾","甫","維","齡","橋","溪","聲","谷","山","舟","巖","泉","遊","遜", });

void determine_data()
{
        switch(random(5))
        {
        case 0:
                weapon_file="changjian";
                skill="sword";
                break;
        case 1:
                weapon_file="gangdao";
                skill="blade";
                break;
        case 2:
                weapon_file="gangzhang";
                skill="staff";
                break;
        case 3:
                weapon_file="changbian";
                skill="whip";
                break;
        case 4:
                weapon_file="axe";
                skill="axe";
                break;
        }
}

void create()
{
        string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))];
        if (random(10) > 2) name += name_words[random(sizeof(name_words))];
        set_name(name, ({"fu jiang","fu","jiang", "general", "fujiang"}));
        set ("long", @LONG
一名戰功累累的副將。如今太平了，便練練兵，以防邊疆有變。
LONG);
        determine_data();
        set("title", "副將");
        set("gender", "男性");
        set("age", 20 + random(30));
        set("combat_exp", 300000 + random(100000));
        set_skill(skill, 120);
        set_skill("dodge", 120);
        set_skill("parry", 120);
        set_skill("unarmed", 120);
        set_skill("force", 120);
        set("max_qi", 700);
        set("max_jing", 700);
        set("max_neli", 800);
        set("force", 1000);
        set("jiali", 25);

        setup();
        carry_object("/d/changan/npc/obj/" + weapon_file)->wield();
        carry_object("/d/changan/npc/obj/zhanjia")->wear();
}