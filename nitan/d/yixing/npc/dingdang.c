// /d/yixing/npc/dingdang.c 叮叮噹噹
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void init();

string ask_wine();
string ask_tian();

void create()
{
        set_name("丁當" , ({"ding dang", "ding"}));
        set("long",
                "只見你眼前出現了一張清麗白膩的臉龐，小嘴邊帶着俏皮的微笑。\n"
                "她身上散發着少女的悠香，讓人聞了不由心中一蕩。\n");
        set("nickname", HIC"叮叮噹噹"NOR);
        set("gender", "女性");
        set("attitude", "friendly");
        set("age", 18);
        set("per", 27);
        
        set("str", 18);
        set("int", 26);
        set("con", 20);
        set("dex", 19);
        
        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 700);
        set("max_jing", 700);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 10);

        set("combat_exp", 70000);
        set("score", 70000);

        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("dodge", 80);
        set_skill("hand", 85);
/*
        set_skill("taixuan-gong", 70);
        set_skill("ding-dodge", 70);
        set_skill("dingjia-qinnashou", 80);
        set_skill("literate", 60);
        
        map_skill("force", "taixuan-gong");
        map_skill("parry", "dingjia-qinnashou");
        map_skill("hand", "dingjia-qinnashou");
        map_skill("dodge", "ding-dodge");
        prepare_skill("hand", "dingjia-qinnashou");
*/        
        set("inquiry", ([
                "玄冰碧火酒" : (:ask_wine:),
                "wine" : (:ask_wine:),
                "丁不三" : "丁不三是我爺爺啊，你找他有事？我爺爺很兇的，你還是別找他了。\n",
                "天哥" : (:ask_tian:),
                "石破天" : (:ask_tian:),
                "雪山派" : "爺爺最討厭雪山派的人了，你千萬不要在他面前提起。\n",
                "xueshan" : "爺爺最討厭雪山派的人了，你千萬不要在他面前提起。\n",
                "name" : "我姓丁名當，大家都叫我叮叮噹噹。\n",
                "名字" : "我姓丁名當，大家都叫我叮叮噹噹。\n",
        ]));
        
        setup();
        carry_object(CLOTH_DIR"female-cloth")->wear();

}

void init()
{
        object ob, me;
        me=this_player();
        
        if ( environment(me)==find_object("/d/forest/clbajiaoting.c")) {
        if( query_temp("find/dddd", me) )
        {
        command("say 天哥的傷不知道什麼時候才全愈，真教人擔心。");
        command("sigh");
        return;
                }
        }
}

string ask_tian()
{
        object me=this_player();
        
        if( query_temp("find/dddd", me) )
        {
        command("sigh");
        return "天哥受了重傷，我剛餵了點「玄冰碧火酒」給他服用，希望他沒事。";
        }
        else {
        return "你也認識天哥嗎？噢，對了，你是他的屬下吧。";
        }
}

string ask_wine()
{
        object me=this_player();
        
        if( query("combat_exp", me)<100000 )
        {
        command("look"+query("id", me));
        command("sneer"+query("id", me));
        return "憑你這點本事配來管本姑娘的閒事？！";
        }
        if( query_temp("find/dddd", me) )
        {
        command("ah"+query("id", me));
        add_action("do_pretty", "pretty");
        command("say 一定是爺爺派你來勸我回去的是不是？原來他已經知道我偷了他的寶貝。");
        command("sigh");
        command("say 天哥以前風流涕淌，對人家老是油腔滑調的，可是最近不知道怎麼變傻了，連哄人家的話也不會説了。");
        command("disapp");
        set_temp("pretty/ding", 1, me);
        return "我真寧願他是以前那個會哄人家開心的天哥。";
        }
        else {
                return "這酒是我爺爺的，你自己問他要吧。";
                }
}

int do_pretty(string arg)
{
        object me, ob, *obs;
        me=this_player();
        
        if ( !arg ) return 0;

        ob = present(arg, environment());
        
        if (!objectp(ob)) return 0;
        
        if( query_temp("pretty/ding", me) )
        {
        command("giggle");
        command("happy2"+query("id", me));
        command("blush");
        command("say 謝謝你啦，不過我要留在這裏陪天哥，你幫我把這剩下的「玄冰碧火酒」帶回去給爺爺吧。");
        ob=new("/clone/unique/jiu.c");
        message_vision("丁當將一瓶「玄冰碧火酒」交了給$N。\n", me);
        ob->move(this_player());
        set("got/wine", 1, me);
        delete_temp("find/dddd", me);
        delete_temp("pretty/ding", me);
        delete_temp("first/ask", me);
        return 1;
        } 
}
