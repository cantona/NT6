//biaotou.c
//鏢頭.c 

inherit NPC;

#include <ansi.h>
void init();
int ask_start();
int ask_arrived();

mapping default_dirs = ([ //root:在此定義移動方向。
        "north":                "北",
        "south":                "南",
        "east":                 "東",
        "west":                 "西",
        "northup":              "北邊",
        "southup":              "南邊",
        "eastup":               "東邊",
        "westup":               "西邊",
        "northdown":            "北邊",
        "southdown":            "南邊",
        "eastdown":             "東邊",
        "westdown":             "西邊",
        "northeast":            "東北",
        "northwest":            "西北",
        "southeast":            "東南",
        "southwest":            "西南",
        "up":                   "上",
        "down":                 "下",
        "enter":                "裏",
        "out":                  "外",
]);

void create()
{
        set("title","運鏢天下");
        set_name(HIC "鏢頭" NOR, ({ "biao tou", "tou" }));
        set("nickname",HIW "一招畢命" NOR);
        set("long","他是一個馳騁江湖數十年的老鏢師。\n");
        set("gender", "男性");
        set("age", 54);
        
        set("food",250);
        set("water",250);

        set("no_get",1);

        set("inquiry", ([
                "出發" : (: ask_start :),
                "抵達" : (: ask_arrived :),
        ]));
        set("chat_chance_combat", 60);

        setup();

        carry_object(__DIR__"obj/pixue")->wear();
        carry_object(__DIR__"obj/tiejia")->wear();
        carry_object(__DIR__"obj/gangjian")->wield();
}
int accept_hit(object ob)
{
        command("say 毛都沒長齊學人劫鏢？去死吧！");
        command("perform sword.lian");
        kill_ob(ob);
        return 1;
}
int accept_kill(object ob)
{
        command("say 毛都沒長齊學人劫鏢？去死吧！");
        command("yun recover");
        return 1;
}


void init()
{
        add_action("do_move","move");
}

int do_move(string arg)
{
        object me, ob, env;
        mapping exit;
        int busy, kar, i;
        me = this_player();
        ob = this_object();
        env = environment(me);
        kar = 20 + random(10);

        if( !living(ob) )
              return notify_fail("嗯....你得先把" + ob->name() + "弄醒再説。\n");

        if (ob->query_temp("owner/id") != me->query("id")) {
                command("? " + me->query("id"));
                return notify_fail("\n");
                }
        
        if (!arg) {
                command("kick " + me->query("id"));
                command("say 你要我趕到哪兒去？");
                return notify_fail("\n");
                }

        if( !mapp(exit = env->query("exits")) || undefinedp(exit[arg]) ) {
                command("?");
                command("say 這個方向沒有路呃。");
                return notify_fail("\n");
                }

        if (ob->is_busy()) {
                command("say 我這兒正忙着呢！");
                return notify_fail("\n");
                }

        if (me->is_busy()) {
                command("say 你自己都忙不過來，還催我幹什麼？");
                return notify_fail("\n");
                }

        if (ob->is_fighting()) {
                command("say 請你先把我的對手料理了吧！\n");
                return notify_fail("\n");
                }

        command("go " + arg); 
        ob->start_busy(2 + random(2));
        me->move(environment(ob));
        message_vision(HIC "鏢頭用警惕的眼光觀察着四周。\n" NOR,me);
        busy = 2 + random(30 - kar);
        if (busy > 3) busy = 3;
        me->start_busy(busy);
//        i = 30;
//        if ( random(i) < 15){
        ob = new(__DIR__"robber");
        ob->invocation(me);
        
        call_out("robber", 1);

        message_vision(HIR "突然，一個劫匪從暗處竄了出來！！！\n\n" NOR,me);

        ob->move(environment(me));
                 
        return 1;
        } 


int ask_start()
{
        object ob = this_object(), me = this_player();

        if (ob->query_temp("started")) {
                command("say 不是已經在路上了嗎？");
                return 1;
                }

        if (me->query("quest/yunbiao") ==1) {
                ob->set_temp("started",1);
                ob->set_temp("owner/id",me->query("id"));
                command("say 好吧，我們出發！");
                return 1;
                }
        
        if (ob->query_temp("owner/id") != me->query("id")) {
                command("slap " + me->query("id"));
                command("say 又沒有讓你護鏢，來瞎鬧什麼？");
                return 1;
                }
        call_out("leave", 600);
        me->set("task_time", 600);
        return 1;
}

int ask_arrived()
{
        object me, ob;
        int exp, pot, ww;
        
        me = this_player();
        ob = this_object();

        if (ob->query_temp("owner/id") != me->query("id")) {
                command("say " + me->query("name") + "你並沒有護這趟鏢，憑什麼來領取獎勵？");
                command("grin " + me->query("id"));
                return 1;
                }

        if (ob->is_busy()) {
                command("say 我這兒正忙着呢！");
                return notify_fail("\n");
                }

        if (ob->is_fighting()) {
                command("say 請你先把我的對手料理了吧！\n");
                return notify_fail("\n");
                }

        if (ob->query_temp("fuzhou") ==1){
                 if (file_name(environment(ob)) !="/d/fuzhou/biaojuzt") {
                         command("say 你想半途而廢？");
                       return 1;
                       }

                if (!present("lin zhennan", environment(ob))) {
                       command("say 總鏢頭不在，不好交差啊！");
                       return 1;
                       }

   }
   else {
                if (file_name(environment(ob)) !="/d/city/qianzhuang") {
                command("say 你想半途而廢？");
                return 1;
                }

                if (!present("qian yankai", environment(ob))) {
                        command("say 錢老闆不在，不好交差啊！");
                        return 1;
                           }
        }
        me->set("quest2/yunbiao",0);
        ww = (50 + random(50));
        exp = (100 + random(30)) * 10;
        pot = (500 + random(exp)) * 6 / 10;
        message_vision(HIW "$N被獎勵了：\n"
                + HIG + chinese_number(exp) + "點實戰經驗，\n"  
                + HIC + chinese_number(pot) + "點潛能，\n"
                + HIY + chinese_number(exp * pot / 500000) + "兩黃金，\n" 
                + HIW + chinese_number(ww) + "點江湖威望，\n"NOR,me); 

        me->add("combat_exp",exp);
        me->add("potential",pot);
        me->add("balance",(exp * pot/50));
        me->add("weiwang",ww);

        message_vision(CYN "鏢師往錢莊裏間離去了。\n" NOR,me);
        destruct(ob);

        return 1;
}

