inherit NPC;
string *first_name = ({
"趙","錢","孫","李","周","吳","鄭","王","張","陳", "劉","林" }); 
string *name_words = ({
"順","昌","振","發","財","俊","彥","良","志","忠", "孝","雄","益","添","金",
"輝","長","盛","勝","進","安","福","同","滿", "富","萬","龍","隆","祥","棟","國","億","壽","楊" });
string *color_title = ({
"青帶男教眾","紅帶男教眾","白帶男教眾","藍帶男教眾","紫帶男教眾","綠帶男教眾",
"黃帶男教眾","金帶男教眾","銀帶男教眾","黑帶男教眾", });

void create()
{
        string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))]; 
        if( random(10) > 4 ) 
        name += name_words[random(sizeof(name_words))];
        set_name(name, ({"nan jiaozhong", "jiaozhong", "nan"}) );
        set("title", color_title[random(sizeof(color_title))]);
        set("long","這是一名"+query("title", this_object())+"，他正在專心致志地練習功夫。\n");
        set("gender", "男性" );
        set("age", 16+random(20));
        set("attitude", "peaceful");
        set("str",15+random(13));
        set("int",20);
        set("con",15+random(12));
        set("dex",15+random(10));
        set("max_qi", 300+random(200));
        set("max_jing", 200)+random(200);
        set("neili", 250+random(200));
        set("max_neili", 250+random(200));
        set("combat_exp", random(6000)+6000);
        set_skill("force", 25+random(15));
        set_skill("shenghuo-shengong", 30);
        set_skill("dodge", 25+random(15));
        set_skill("piaoyi-shenfa", 30);
        set_skill("hand", 25+random(15));
        set_skill("sougu-yingzhua", 30);
        set_skill("parry", 25+random(15));
        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("parry", "sougu-yingzhua");
        map_skill("hand", "sougu-yingzhua");
        prepare_skill("hand", "sougu-yingzhua");
        set("inquiry", ([
                "name": "在下明尊座下末進弟子，從十六歲起便投在這裡學藝。",
                "rumors": "聽說故教主一身渾厚的內力都是得自昆侖山的一次奇遇。",
                "here": "這裡是明教總壇，你沒事還是不要隨便亂轉的好。",
                "明教": "問什麼問，不懂用help mingjiao嗎？！",
        ]));
        setup();
        carry_object("/d/mingjiao/obj/black-cloth")->wear();
}
