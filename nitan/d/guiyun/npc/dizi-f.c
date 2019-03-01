// Npc: /d/guiyun/npc/dizi-f.c
// Last Modified by winder on Jul. 9 2001

inherit NPC;

void create()
{
        int no = random(3); 
        string *name_string = ({"慕容小雪","文玉燕","李三姑","石二翠"});
        set_name("女弟子", ({"nv dizi", "nv", "dizi"}) );
        set("long", "她正在專心致志地練習功夫。\n");
        set("gender", "女性" );
        set("age", 23);
        set("attitude", "peaceful");
        set("str",18);
        set("int",28);
        set("con",19);
        set("dex",22);
        set("max_qi", 650);
        set("max_jing", 250);
        set("neili", 500);
        set("max_neili", 320);
        set("jiali", 10);
        set("combat_exp", 15000);

        set_skill("force", 30);
        set_skill("bibo-shengong", 27);
        set_skill("dodge", 30);
        set_skill("anying-fuxiang", 28);
        set_skill("parry", 32);
        set_skill("strike", 22);
        set_skill("luoying-shenzhang", 18);
        set_skill("leg", 20);
        set_skill("xuanfeng-tui", 15);
        set_skill("sword", 30);
        set_skill("yuxiao-jianfa", 25);
        set_skill("taoism", 20);
        set_skill("literate", 35);
        set_skill("qimen-wuxing", 40);

        map_skill("force", "bibo-shengong");
        map_skill("dodge", "anying-fuxiang");
        map_skill("strike", "luoying-shenzhang");
        map_skill("leg", "xuanfeng-tui");
        map_skill("parry", "luoying-shenzhang");
        map_skill("sword", "yuxiao-jianfa");
        prepare_skill("strike", "luoying-shenzhang");
        prepare_skill("leg", "xuanfeng-tui");
        set("shen_type", 0);
        create_family("桃花島", 3, "弟子");
        set("class", "fighter");

        set("inquiry", ([
                "name"  :"小女子"+name_string[no]+"，打十五歲起便在這裡學藝。",
                "rumors":"聽說師祖收徒很重視悟性和文化，我得多讀些書了。",
                "here"  :"這裡是歸雲莊，你隨便轉轉吧，累了請到客房休息。",
                "東邪"  :"那是師祖呀，蒙他老人家恩準，我才能跟陸莊主學藝。",
                "黃藥師":"那是師祖呀，蒙他老人家恩準，我才能跟陸莊主學藝。",
                "桃花島":"聽說是師祖住的地方，可惜沒有去看過。",
                "陸乘風":"是我的師父，這裡的莊主，你找他老人家有什麼事嗎？",
                "歸雲莊":"聽說這裡是花了莊主無數心血才建起來的，與別的莊院相比如何？",
                "太湖"  :"就在莊前不遠，是一個煙波浩淼的大湖。",
        ]) );
        setup();
        carry_object("/clone/cloth/female-cloth")->wear();
}
