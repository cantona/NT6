// xiaozhao.c
#include <ansi.h>

inherit NPC;

int ask_wuji();
int ask_jian();
int ask_gold();
int ask_ge();
int ask_qiankun();

void create()
{
        set_name("小昭", ({ "xiao zhao", "xiao", "zhao" }));
        set("nickname", HIC "天涯思君不可忘" NOR);
        set("long",
            "她雙目湛湛有神，修眉端鼻，頰邊微現梨渦，真是秀美無倫，只是年紀幼\n"
            "小，身材尚未長成，雖然容貌絕麗，卻掩不住容顏中的稚氣。\n");
        set("gender", "女性");
        set("age", 15);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 30);
        set("str", 15);
        set("int", 25);
        set("con", 25);
        set("dex", 30);

        set("max_qi", 500);
        set("max_jing", 200);
        set("max_neili", 500);
        set("jiali", 50);
        set("combat_exp", 50000+random(10000));
        set("score", 20000);

        set_skill("force", 80);
        set_skill("dodge", 80);
        set_skill("unarmed", 80);
        set_skill("sword", 80);
        set_skill("taiji-jian", 70);
        set_skill("taiji-quan", 70);
        set_skill("tiyunzong",50);
        map_skill("dodge", "tiyunzong");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");
        map_skill("unarmed", "taiji-quan");

        set_temp("apply/attack", 15);
        set_temp("apply/damage", 15);
        set("party/party_name", HIG "明教" NOR);
        set("party/rank", HIG "波斯聖教主" NOR);
        set("party/level", 1);
        set("inquiry", ([
            "張無忌" :  (: ask_wuji :),
            "倚天劍" :  (: ask_jian :),
            "黃金" :    (: ask_gold :),
            "歌" :      (: ask_ge :),
            "乾坤大挪移": (: ask_qiankun :),
            "乾坤大挪移心法": (: ask_qiankun :),
            "wuji" :    (: ask_wuji :),
            "jian" :    (: ask_jian :),
            "gold" :    (: ask_gold :),
            "ge" :      (: ask_ge :),
        ]));

        set("chat_chance", 3);
        set("chat_msg", ({
                    "小昭低聲吟道：天涯思君不可忘 武當山頂松柏長\n",
                    "小昭低聲吟道：寶刀百鍊生玄光 字作喪亂意彷徨\n",
                    "小昭低聲吟道：皓臂似玉梅花粧 浮槎北溟海茫茫\n",
                    "小昭低聲吟道：誰送冰舸來仙鄉 窮髮十載泛歸航\n",
                    "小昭低聲吟道：七俠聚會樂未央 百歲壽宴摧肝腸\n",
                    "小昭低聲吟道：有女長舌如利槍 針其膏兮藥其肓\n",
                    "小昭低聲吟道：不悔仲子逾我牆 當道時見中山狼\n",
                    "小昭低聲吟道：奇謀妙計夢一場 剝極而復參九陽\n",
                    "小昭低聲吟道：青翼出沒一笑揚 倚天長劍飛寒芒\n",
                    "小昭低聲吟道：禍起蕭牆破金湯 與子共穴相扶將\n",
                    "小昭低聲吟道：排難解紛當六強 羣雄歸心約三章\n",
                    "小昭低聲吟道：靈芙醉客綠柳莊 太極初傳柔克剛\n",
                    "小昭低聲吟道：舉火燎天何煌煌 俊貌玉面甘損傷\n",
                    "小昭低聲吟道：百尺高塔任迴翔 恩斷義絕紫衫王\n",
                    "小昭低聲吟道：四女同舟何所望 東西永隔如參商\n",
                    "小昭低聲吟道：刀劍齊失人云亡 冤蒙不白愁欲狂\n",
                    "小昭低聲吟道：簫長琴短衣流黃 新婦素手裂紅裳\n",
                    "小昭低聲吟道：屠獅有會孰為殃 夭矯三鬆鬱青蒼\n",
                    "小昭低聲吟道：天下英雄莫能當 君子可欺之以方\n",
                    "小昭低聲吟道：祕笈兵書此中藏 不識張郎是張郎\n",
        }) );

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

int ask_wuji()
{
        command("sigh"+query("id", this_player()));
        say("小昭幽幽地説：天涯思君不可忘，東西永隔如參商。\n");
        return 1;
}

int ask_jian()
{
        command("say 我不知道在哪裏...別問我。");
        return 1;
}

int ask_gold()
{
        command("say 不行啊，這不能隨便給人。");
        return 1;
}

int ask_ge()
{
        command("nod"+query("id", this_player()));
        say("小昭曼聲唱道：\n\n" +
        "世情推物理  人生貴適意\n\n"+
        "想人間造物搬興廢  吉藏兇 兇藏吉  富貴那能長富貴\n\n"+
        "日盈昃  月滿虧蝕  地下東南  天高西北  天地尚無完體\n\n"+
        "展放愁眉  休爭閒氣  今日容顏  老於昨日  古往今來  盡須如此\n\n"+
        "管他賢的愚的  貧的和富的  到頭這一身  難逃那一日\n\n"+
        "受用了一朝  一朝便宜\n\n"+
        "百歲光陰  七十者稀  急急流年  滔滔逝水\n\n");
        return 1;
}

int ask_qiankun()
{
        object me = this_player();
        if( query_temp("mark/qiankun", me) && 
                query("party/party_name", me) == HIG"明教"NOR )
        {
                message_vision( CYN"小昭莞爾一笑，對$N説道：乾坤大挪移心法在本教密道里，我們去取吧。\n"NOR,me);
                set_leader(me);
                delete_temp("mark/qiankun", me);
        }
        else
        {
                command("say 自上代教主陽頂天離奇失蹤，乾坤大挪移心法已經失落很久了。\n");
                set_temp("mark/qiankun", 1, me);
                set_leader(0);
        }
        return 1;
}
