// Npc: /d/guiyun/npc/dizi-m.c
// Last Modified by winder on Jul. 9 2001

inherit NPC;

void create()
{
        int name_no = random(4); 
        string *name_string = ({"伯","仲","叔","季"});

        set_name("男弟子", ({"nan dizi", "nan", "dizi"}) );
        set("long", "他正在專心致志地練習功夫。\n");
        set("gender", "男性" );
        set("age", 26);
        set("attitude", "peaceful");
        set("str",22);
        set("int",28);
        set("con",18);
        set("dex",20);
        set("max_qi", 700);
        set("max_jing", 270);
        set("neili", 500);
        set("max_neili", 340);
        set("jiali", 12);
        set("combat_exp", 20000);

        set_skill("force", 35);
        set_skill("bibo-shengong", 30);
        set_skill("dodge", 35);
        set_skill("anying-fuxiang", 30);
        set_skill("parry", 40);
        set_skill("strike", 30);
        set_skill("luoying-shenzhang", 28);
        set_skill("leg", 30);
        set_skill("xuanfeng-tui", 25);
        set_skill("sword", 40);
        set_skill("yuxiao-jianfa", 35);
        set_skill("taoism", 20);
        set_skill("literate", 40);
        set_skill("qimen-wuxing", 40);

        map_skill("force", "bibo-shengong");
        map_skill("dodge", "anying-fuxiang");
        map_skill("strike", "luoying-shenzhang");
        map_skill("leg", "xuanfeng-tui");
        map_skill("parry", "luoying-shenzhang");
        map_skill("sword", "yuxiao-jianfa");
        prepare_skill("strike", "luoying-shenzhang");

        set("shen_type", 0);
        create_family("桃花島", 3, "弟子");
        set("class", "fighter");

        set("inquiry", ([
                "name"  :"在下復姓司馬，名喚"+name_string[name_no]+ "雄，從十六歲起便投在這裡學藝。",
                "rumors":"聽說師祖收徒很重視悟性和文化，我得多讀些書了。",
                "here"  :"這裡是歸雲莊，你隨便轉轉吧，累了請到客房休息。",
                "東邪"  :"那是師祖呀，，蒙他老人家恩準，我才能跟陸莊主學藝。",
                "黃藥師":"那是師祖呀，，蒙他老人家恩準，我才能跟陸莊主學藝。",
                "桃花島":"聽說是師祖住的地方，可惜沒有去看過。",
                "陸乘風":"是我的師父，這裡的莊主，你找他老人家有什麼事嗎？",
                "歸雲莊":"聽說這裡是花了莊主無數心血才建起來的，與別的莊院相比如何？",
                "太湖"  :"就在莊前不遠，是一個煙波浩淼的大湖。",
        ]) );
        setup();
        carry_object("/clone/cloth/male-cloth")->wear();
}
