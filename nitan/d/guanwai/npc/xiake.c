#include <ansi.h>
int do_copy(object me);
int do_back(object me);
inherit NPC;
string* names = ({
"趙","錢","孫","李","周","吳","鄭","王","馮","陳","褚","衞",
"蔣","沈","韓","楊","朱","秦","尤","許","何","呂","施","張",
"孔","曹","嚴","華","金","魏","陶","姜","戚","謝","鄒","喻",
"柏","水","竇","章","雲","蘇","潘","葛","奚","範","彭","郎",
"魯","韋","昌","馬","苗","鳳","花","方","傻","任","袁","柳",
"鄧","鮑","史","唐","費","廉","岑","薛","雷","賀","倪","湯",
"藤","殷","羅","華","郝","鄔","安","常","樂","呆","時","付",
"皮","卞","齊","康","伍","餘","元","卜","顧","盈","平","黃",
"和","穆","肖","尹","姚","邵","湛","汪","祁","毛","禹","狄",
"米","貝","明","藏","計","伏","成","戴","談","宋","茅","龐",
"熊","紀","舒","屈","項","祝","董","樑","樊","胡","凌","霍",
"虞","萬","支","柯","昝","管","盧","英","仇","候","嶽","帥",
"司馬","上官","歐陽","夏候","諸葛","聞人","東方","赫連","皇甫",
"尉遲","公羊","澹台","公治","宗政","濮陽","淳于","單于","太叔",
"申屠","公孫","仲孫","轅軒","令狐","鍾離","宇文","長孫","幕容",
"司徒","師空","顓孔","端木","巫馬","公西","漆雕","樂正","壤駟",
"公良","拓趾","夾谷","宰父","穀梁","楚晉","閻法","汝鄢","塗欽",
"段千","百里","東郭","南郭","呼延","歸海","羊舌","微生","樑丘",
"左丘","東門","西門","佰賞","南官",
"緱","亢","況","後","有","琴","商","牟","佘","耳","墨","哈",
"譙","年","愛","陽","佟","第","五","言","福","蒯","鍾","宗",
"林","石",
});

string* ids = ({
"zhao","qian","sun","li","zhou","wu","zhen","wang","feng","chen","zhu","wei",
"jiang","shen","han","yang","zhu","qing","you","xu","he","lu","shi","zhang",
"kong","cao","yan","hua","jin","wei","tao","jiang","qie","xie","zhou","yu",
"bo","shui","dou","zhang","yun","su","pan","ge","xi","fan","peng","lang",
"lu","wei","chang","ma","miao","feng","hua","fang","sha","ren","yuan","liu",
"deng","bao","shi","tang","fei","lian","chen","xue","lei","he","ni","tang",
"teng","yin","luo","hua","hao","wu","an","chang","le","dai","shi","fu",
"pi","bian","qi","kang","wu","yu","yuan","po","gu","ying","ping","huang",
"he","mu","xiao","yin","yao","shao","zhan","wang","qi","mao","yu","di",
"mi","bei","ming","zang","ji","fu","cheng","dai","tan","song","mao","pang",
"xiong","ji","su","qu","xiang","zhu","dong","liang","fan","hu","ling","ho",
"yu","wan","zhi","ke","jiu","guan","lu","ying","qiu","hou","yue","suai",
"sima","shangguan","ouyang","xiahou","zhuge","wenren","dongfang","helian","huangpu",
"weichi","gongyang","zhantai","gongye","zongzheng","puyang","chunyu","shanyu","taishu",
"shentu","gongshun","zhongshun","xuanyuan","linghu","zhongli","yuwen","changshun","murong",
"situ","shikong","zhuankong","duanmu","wuma","gongxi","qidiao","lezheng","xiangsi",
"gongliang","tuozhi","jiagu","zaifu","guliang","chujing","yanfa","ruye","tuqin",
"duanqian","baili","dongguo","nanguo","huyan","guihai","yangshe","weisheng","liangqiu",
"zuoqiu","dongmen","ximen","baishang","nangong",
"gou","kang","kuang","hou","you","qing","shang","mo","she","er","mo","ha",
"qiao","nian","ai","yang","dong","di","wu","yan","fu","kai","zong","zong",
"lin","shi",
});
//----以下歡迎添加，nm2需要一定的空字，以便產生出單名--------------
string* nm2 = ({
"忠","孝","禮","義","智","勇","仁","匡","憲","令","福","祿","大","小","曉",
"高","可","阿","金","世","克","叔","之","公","夫","時","若","慶","文","武",
"多","才","長","子","永","友","自","人","為","鐵","","","","","","","","",
"","","","","","","","","","","","","","",
});

string* nm3 = ({
"霸","白","班","斌","賓","昌","超","誠","川","鼎","定","鬥",
"法","飛","風","鋒","鋼","罡","貫","光","海","虎","華",
"浩","宏","濟","堅","健","劍","江","進","傑","俊","康",
"良","麟","民","明","鳴","寧","培","啟","強","榮","山",
"泰","濤","挺","偉","熙","祥","雄","旭",
"毅","瑜","羽","宇","嶽","舟",
});

#include <ansi.h>
void away();

void create()
{
   string weapon;
   int i = random(sizeof(names));
  set_name(names[i]+nm2[random(sizeof(nm2))]+nm3[random(sizeof(nm3))], ({"qingbing"}));
        set("nickname", HIG"大清官兵"NOR);
        set("gender", "男性");
        set("age", 22);
        set("long", 
                "他是一個大清官兵。\n");
        set("attitude", "peaceful");
        set("age", random(10) + 25);
        set("no_quest", 1);
        set("str", 33);
        set("con", 26);
        set("int", 20);
        set("dex", 23);
        set("combat_exp", 1080000 + random(4000000)); 
        set("attitude", "friendly");
        set_skill("force", 50);
        set_skill("sword", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
     set_skill("jiuyang-shengong", 100);
    set_skill("qiankun-danuoyi", 100);
    set_skill("qishang-quan", 100);
    set_skill("shenghuo-shengong", 100);
    set_skill("taiji-quan",150);
    set_skill("taiji-jian",150);
    set_skill("taiji-dao",150);
    set_skill("shenghuo-ling",300);

    map_skill("force", "shenghuo-shengong");
    map_skill("dodge", "qiankun-danuoyi");
    map_skill("unarmed", "qishang-quan");
    map_skill("cuff", "qishang-quan");
    map_skill("hand", "taiji-quan");
    map_skill("sword","shenghuo-ling");
    map_skill("parry","shenghuo-ling");
    map_skill("blade","taiji-dao");
        set("max_qi", 1450); 
        set("eff_jingli", 1400); 
        set("neili", 1700); 
        set("max_neili", 1700);
        set("jiali", 30);
        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: perform_action, "sword.can" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "sword.xi" :),
                (: perform_action, "sword.hua" :),                
                (: command("unwield jian") :),
                (: command("unwield jian") :),
                (: command("wield jian") :),
                (: command("wield jian") :),
                (: perform_action, "cuff.fei" :),                
                (: perform_action, "cuff.shang" :),                
                (: perform_action, "cuff.fei" :),                
                (: perform_action, "cuff.shang" :),                
                (: perform_action, "dodge.yi" :),                                
                (: perform_action, "dodge.yi" :),                                
        }) );
        weapon = "/clone/weapon/gangjian";
        setup();
        carry_object(weapon)->wield();
        carry_object("/clone/cloth/cloth")->wear();
        add_money("silver", 50);
}

int do_back(object me)
{
        destruct(me);
        return 1;
}

int checking(object ob, object me)
{
        if(!me || !present(me, environment())) do_back(ob);
        else call_out("checking", 2, ob, me);
        return 1;
}

int do_copy(object me)
{
        int i;
        object ob;
        ob = this_object();

      if( !query_temp("xx_rob", me)){
                 do_back(me);
                 return 0;
                 }
        message_vision(HIR"突然從附近竄出一個$N，二話不説就撲向了$n！\n"NOR, ob, me);
        addn_temp("biaoshi", 1, me);
        
        set("combat_exp",query("combat_exp",  me)*4/5, ob);
        set("max_qi",query("max_qi",  me), ob);
        set("eff_qi",query("max_qi",  me), ob);
        set("qi",query("max_qi",  me), ob);
        set("max_jingli",query("max_jingli",  me), ob);
        set("eff_jingli",query("max_jingli",  me), ob);
        set("jingli",query("max_jingli",  me), ob);
        set("max_neili",query("max_neili",  me), ob);
        set("neili",query("max_neili",  me), ob);
        ob->set_skill("force", me->query_skill("force"));
        ob->set_skill("jiuyang-shengong", me->query_skill("force")* 4 / 5);
        ob->set_skill("qiankun-danuoyi", me->query_skill("force")* 4 / 5);
        ob->set_skill("qishang-quan", me->query_skill("force")* 4 / 5);
        ob->set_skill("shenghuo-shengong",me->query_skill("force")* 4 / 5);
        ob->set_skill("dodge", me->query_skill("force")* 4 / 5); 
        ob->set_skill("sword", me->query_skill("force")* 4 / 5); 
        ob->set_skill("taiji-quan", me->query_skill("force")* 4 / 5); 
        ob->set_skill("parry",me->query_skill("force")* 4 / 5); 
        ob->set_skill("shenghuo-ling", me->query_skill("force")* 4 / 5);
        set("shen", -1000, ob);
        ob->kill_ob(me);
        me->kill_ob(ob);
        checking(ob, me);    
        call_out("do_back", 350,  ob);  
        return 1;
}
