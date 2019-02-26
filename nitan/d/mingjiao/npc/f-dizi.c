inherit NPC;
string *first_name = ({
 "趙","何","謝","李","蘇","吳","鄭","文","張","陳", "劉","林","樊" }); 
string *name_words = ({ 
"可","小","靈","燕","若","花","蓉","若","雲","翠","麗","馨","雲","香",
"凝","美","香","蘭","玉","環",});
string *color_title = ({
"青帶女教眾","紅帶女教眾","白帶女教眾","藍帶女教眾","紫帶女教眾","綠帶女教眾",
"黃帶女教眾","金帶女教眾","銀帶女教眾","黑帶女教眾", });
void create()
{
        string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))]; 
        if( random(10) > 4 ) 
        name += name_words[random(sizeof(name_words))];
        set_name(name, ({"nu jiaozhong", "jiaozhong", "nu"}));
        set("title", color_title[random(sizeof(color_title))]);
        set("long","這是一名"+query("title", this_object())+"，她正在專心致志地練習功夫。\n");
        set("gender", "女性" );
        set("age", 15+random(20));
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
        set_skill("strike", 25+random(15));
        set_skill("hanbing-mianzhang", 30);
        set_skill("parry", 25+random(15));
        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("parry", "hanbing-mianzhang");
        map_skill("strike", "hanbing-mianzhang");
        prepare_skill("strike", "hanbing-mianzhang");
        set("shen_type", 0);
        set("inquiry", ([
                "name": "奴家叫做"+this_object()->name()+"，從十五歲起便投在這裏學藝。",
                "rumors": "聽説故教主一身渾厚的內力都是得自崑崙山的一次奇遇。",
                "here": "這裏是明教總壇，你沒事還是不要隨便亂轉的好。",
                "明教": "問什麼問，不懂用help mingjiao嗎？！",
        ]));
        setup();
        carry_object("/d/mingjiao/obj/black-cloth")->wear();
}
