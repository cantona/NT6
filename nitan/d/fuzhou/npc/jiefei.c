// jiefei.c 黃河幫劫匪
#include <ansi.h>
#include "jinit.h"
inherit NPC;
string *xing=({"趙","錢","孫","李","周","吳","鄭","王","馮","陳","褚","衞","蔣","沈","韓","楊","朱","秦","尤","許","何","呂","施","張","孔","曹","嚴","華","金","魏","陶","姜","戚","謝","鄒","喻","柏","水","竇","章","雲","蘇","潘","葛","奚","範","彭","郎","魯","韋","昌","馬","苗","鳳","花","方","俞","任","袁","柳","酆","鮑","史","唐","費","廉","岑","薛","雷","賀","倪","湯","滕","殷","羅","畢","郝","鄔","安","常","樂","於","時","傅","皮","卞","齊","康","伍","餘","元","卜","顧","孟","平","黃","和","穆","蕭","尹","姚","邵"}); 
        string *id=({"zhao","qian","sun","li","zhou","wu","zheng","wang","feng","chen","zhu","wei","jiang","shen","han","yang","zhu","qin","you","xu","he","lv","shi","zhang","kong","cao","yan","hua","jin","wei","tao","jiang","qi","xie","zou","yu","bai","shui","dou","zhang","yun","su","pan","ge","xi","fan","pen","lang","lu","wei","chang","ma","miao","feng","hua","fang","yu","ren","yuan","liu","feng","bao","shi","tang","fei","lian","cen","xue","lei","he","ni","tang","teng","yin","luo","bi","hao","wu","an","chang","le","yu","shi","fu","pi","bian","qi","kang","wu","yu","yuan","piao","gu","meng","ping","huang","he","mu","xiao","yin","yao","shao"}); 
        string *ming1=({"天","地","玄","黃","宇","宙","洪","荒","日","月","盈","昃","辰","宿","列","寒","來","暑","往","秋","冬","餘","成","律","陽","雲","騰","雨","露","霜","金","生","麗","水","玉","昆","岡","劍","巨","闕","珠","夜","光","珍","重","海","河","鱗","羽","翔","龍","師","火","帝","鳥","官","人","皇","文","裳","國","陶","民","周","發","殷","湯","朝","道","垂","拱","平","章","愛","育","黎","首","臣","伏","賓","王","鳴","鳳","竹","白","駒","化","草","木"}); 
        string *ming2=({"天","地","玄","黃","宇","宙","洪","荒","日","月","盈","昃","辰","宿","列","律","陽","雲","騰","雨","露","霜","金","生","麗","水","玉","昆","岡","劍","巨","闕","珠","夜","光","珍","重","海","河","鱗","羽","翔","龍","官","人","皇","文","裳","國","陶","民","周","發","殷","湯","朝","道","垂","拱","平","章","愛","育","黎","首","臣","伏","賓","長","信","器","詩","景","行","賢","克","聖","德","建","名","立","形","端","表","正","空","谷","傳","聲"}); 

void create()
{
        int i;
        i = random(sizeof(xing));
        set_name(xing[i]+ming1[random(sizeof(ming1))]+ming2[random(sizeof(ming2))], ({id[i]}));
        set("title","黃河幫劫匪");
        set("long",
                "這是一位彪悍的北方漢子，一身黃河幫的黃衣。\n");
        set("gender", "男性" );
        set("age", 20 + random(25) );
        set("attitude", "heroism");
        set("str", 20 + random(11));        // 膂力
        set("per", 20 + random(11));        // 容貌
        set("int", 20 + random(11));        // 悟性
        set("con", 20 + random(11));        // 根骨
        set("dex", 20 + random(11));         // 身法
        set("kar", 20 + random(11));        // 福緣
        set("shen", -10);
        set("demogorgon",1);
        set("no_suck",1);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set_temp("apply/damage", 40);
        set_temp("apply/armor", 40);
        set_temp("apply/dodge", 40);
        setup();
        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.sanqing" :),
                (: perform_action, "sword.chan" :),
                (: perform_action, "parry.ju" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
        carry_object(__DIR__"obj/ycloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        add_money("silver", 2);
}
