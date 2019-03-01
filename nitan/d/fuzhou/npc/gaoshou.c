// gaoshou.c 劫匪
#include <ansi.h>
#include "init.h"
inherit NPC;
        string *xing=({"趙","錢","孫","李","周","吳","鄭","王","馮","陳","褚","衛","蔣","沈","韓","楊","朱","秦","尤","許","何","呂","施","張","孔","曹","嚴","華","金","魏","陶","姜","戚","謝","鄒","喻","柏","水","竇","章","雲","蘇","潘","葛","奚","范","彭","郎","魯","韋","昌","馬","苗","鳳","花","方","俞","任","袁","柳","酆","鮑","史","唐","費","廉","岑","薛","雷","賀","倪","湯","滕","殷","羅","畢","郝","鄔","安","常","樂","于","時","傅","皮","卞","齊","康","伍","余","元","卜","顧","孟","平","黃","和","穆","蕭","尹","姚","邵"}); 
        string *id=({"zhao","qian","sun","li","zhou","wu","zheng","wang","feng","chen","zhu","wei","jiang","shen","han","yang","zhu","qin","you","xu","he","lv","shi","zhang","kong","cao","yan","hua","jin","wei","tao","jiang","qi","xie","zou","yu","bai","shui","dou","zhang","yun","su","pan","ge","xi","fan","pen","lang","lu","wei","chang","ma","miao","feng","hua","fang","yu","ren","yuan","liu","feng","bao","shi","tang","fei","lian","cen","xue","lei","he","ni","tang","teng","yin","luo","bi","hao","wu","an","chang","le","yu","shi","fu","pi","bian","qi","kang","wu","yu","yuan","piao","gu","meng","ping","huang","he","mu","xiao","yin","yao","shao"}); 
        string *ming1=({"天","地","玄","黃","宇","宙","洪","荒","日","月","盈","昃","辰","宿","列","寒","來","暑","往","秋","冬","餘","成","律","陽","雲","騰","雨","露","霜","金","生","麗","水","玉","昆","岡","劍","巨","闕","珠","夜","光","珍","重","海","河","鱗","羽","翔","龍","師","火","帝","鳥","官","人","皇","文","裳","國","陶","民","周","發","殷","湯","朝","道","垂","拱","平","章","愛","育","黎","首","臣","伏","賓","王","鳴","鳳","竹","白","駒","化","草","木"}); 
        string *ming2=({"天","地","玄","黃","宇","宙","洪","荒","日","月","盈","昃","辰","宿","列","律","陽","雲","騰","雨","露","霜","金","生","麗","水","玉","昆","岡","劍","巨","闕","珠","夜","光","珍","重","海","河","鱗","羽","翔","龍","官","人","皇","文","裳","國","陶","民","周","發","殷","湯","朝","道","垂","拱","平","章","愛","育","黎","首","臣","伏","賓","長","信","器","詩","景","行","賢","克","聖","德","建","名","立","形","端","表","正","空","谷","傳","聲"}); 
        string *hhxm=({"沙通天","侯通海","沈青剛","吳青烈","馬青雄","錢青健"}); 
        string *hhid=({"sha","hou","shen","wu","ma","qian"}); 
        string *hhtitle=({"黃河幫幫主","黃河幫先鋒","黃河四鬼之一","黃河四鬼之二","黃河四鬼之三","黃河四鬼之四"});
        string *hhnick=({"鬼門龍王","三頭蛟","斷魂刀","追命槍","奪魄鞭","喪門斧"}); 
        string *tyxm=({"逍遙子","常長風","花劍影","蓋一鳴"});
        string *tyid=({"xiaoyao","chang","hua","gai"});
        string *tytitle=({"太岳四俠之一","太岳四俠之二","太岳四俠之三","太岳四俠之四"});
        string *tynick=({HIM"煙霞神龍",HIG"雙掌開碑",HIC"流星趕月",HIB"八步趕蟾、賽專諸、踏雪無痕、獨腳水上飛、雙刺蓋七省"});
void create()
{
        int i, j;
        switch (random(10))
        {
                case 0:
                        i = random(sizeof(tyxm));
                        set_name(tyxm[i], ({tyid[i]}));
                        set("title",HIG+tytitle[i]+NOR);
                        set("nickname",tynick[i]+NOR);
                        break;
                case 1:
                        i = random(sizeof(hhxm));
                        set_name(hhxm[i], ({hhid[i]}));
                        set("title",HIY+hhtitle[i]+NOR);
                        set("nickname",hhnick[i]+NOR);
                        break;
                default:
                        i = random(sizeof(xing));
                        set_name(xing[i]+ming1[random(sizeof(ming1))]+ming2[random(sizeof(ming2))], ({id[i]}));
                        set("title",HIY"黃河幫堂主"NOR);
                        set("long","一位彪悍的北方漢子，一身黃河幫的黑衣。\n");
                        break;
        }
        set("gender", "男性" );
        set("age", 30 + random(25) );
        set("max_qi",1200+random(300));
        set("max_jing",500+random(200));
        set("attitude", "heroism");
        set("str", 20 + random(11));        // 膂力
        set("per", 20 + random(11));        // 容貌
        set("int", 20 + random(11));        // 悟性
        set("con", 20 + random(11));        // 根骨
        set("dex", 100 + random(11));         // 身法
        set("kar", 20 + random(11));        // 福緣
        set("shen", -10);
        set("demogorgon",1);
        set("no_suck",1);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
   //   set_temp("apply/damage", 40);
        set_temp("apply/armor", 40);
        set_temp("apply/dodge", 40);
        setup();
        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chan" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "sword.sui" :),
                (: perform_action, "parry.ren" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
        carry_object(__DIR__"obj/ycloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        add_money("silver", 2);
}
