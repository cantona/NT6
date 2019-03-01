#include <ansi.h>
inherit NPC;
int ask_me();
string* goods = ({
       __DIR__"obj/shoujuan",
       __DIR__"obj/yangpi",
       __DIR__"obj/madao",
       __DIR__"obj/shoujuan",
       __DIR__"obj/shoujuan",
       __DIR__"obj/shoujuan",
       __DIR__"obj/jiunang",
       __DIR__"obj/shoujuan",
});
void destob(object ob);
void create()
{
        set_name("蘇普", ({ "supu"}));
        set("gender", "男性");
        set("age", 21);
        set("long", "一個年輕的哈薩克牧羊人, 哈薩克第一勇士蘇魯克的兒子。\n");
        set("attitude", "heroism");
        set("combat_exp", 70000);
        set("shen", 3000);
        set("str", 32);
        set("int", 20);
        set("con", 24);
        set("dex", 20);
        set("max_qi", 600);
        set("max_jing", 600);
        set("neili", 400);
        set("max_neili", 400);
        set_skill("unarmed", 30);
        set_skill("blade", 40);
        set_skill("parry", 40);
        set_skill("dodge", 40);
        set("inquiry", ([
            "阿曼" : "阿曼是我的心上人，我每次殺了野狼都會送她狼皮。\n",
            "李文秀" : "她的歌唱得最好聽的了，有人說她比天鈴鳥唱得還好。
但這幾年來，我一直沒聽到她唱歌，一直沒在見到她。\n",
            "摔跤" : (: ask_me :),
            "比試" : (: ask_me :),
            "計爺爺" : "就是計老人啊，他會釀又香又烈的美酒，會醫牛羊馬匹的疾病。\n",
            "蘇魯克" : "那是我阿爹，是哈薩克族的第一勇士！哈哈！\n",
        ]) );
        setup();
        set("chat_chance", 10);
        set("chat_msg", ({
"蘇普自豪地嚷道: 我也要學我阿爹成為哈薩克第一勇士。\n",
"蘇普自言自語: 從哪兒去弄一張上等的狼皮，送給阿曼呢? \n",
        }) );
        carry_object(__DIR__"obj/wandao")->wield();
        carry_object(__DIR__"obj/yangao")->wear();
        carry_object(__DIR__"obj/jiunang");
}

int ask_me()
{
        if( query_temp("supu_fight", this_player())){
            command("say 我們不是比試過了嗎？");
            return 1;
            } 
        if( !query_temp("supu_accept", this_player())){
            command("say 我是草原未來第一勇士，你憑什麼和我比試呢？");
            return 1;
            } 
        else {
        message_vision("$N看了$n一眼，用不太標準的漢話說道：
我是未來的草原第一勇士，這位漢族"+RANK_D->query_respect(this_player())+"你就和我切搓(fight)幾下吧？\n", this_object(), this_player());
        set_temp("supu1", 1, this_player());
        return 1;
        }
}

int accept_fight(object ob)
{
        object me;
        me = this_object();
        if( query("eff_qi", me)<query("max_qi", me) || 
           query("qi", me)<query("eff_qi", me) || 
           query("neili", me)<query("max_neili", me)){
           message_vision(CYN"$N對$n說：我還沒有休息好，你等一會兒吧。\n"NOR, ob, me);
           return 0;
           }
        if( query_temp("supu1", ob)){
        message_vision(CYN"$N對$n說：好吧，那我就同你切搓幾招吧，點到為止。\n"NOR, ob, me);
        remove_call_out("checking");
        call_out("checking", 1, me, ob);
        delete_temp("supu1", ob);
        delete_temp("supu_accept", ob);
        return 1;
        }
        else return 0;
}

int checking(object me, object ob)
{
        object good;
        int my_max_qi, his_max_qi;
           seteuid(getuid());
        my_max_qi=query("max_qi", me);
        his_max_qi=query("max_qi", ob);
        if (me->is_fighting()){
                call_out("checking",1, me, ob);
                return 1;
                }
        if ( !present(ob, environment()) ) return 1; 
        if( (query("qi", me)*100/my_max_qi) <= 50){
            message_vision(CYN"$N對$n不住地讚嘆：你們漢人果然不一般，我服輸了，送你一些禮物。\n"NOR, me, ob);
             good = new(goods[random(sizeof(goods))]); 
            set("owner",query("id",  ob), good);
            good->move(ob);
            set_temp("supu_fight", 1, ob);
            message_vision("$N交給$n一件禮物。\n", me, ob);
            message_vision(CYN"$N說道：我要回去陪阿曼了，有緣再相見吧。\n"NOR, me);            
            message_vision("$N帶著灰狼皮離開了"+query("short", environment(me))+"。\n",me);
            destruct(this_object());
            return 1;
            }
        if( (query("qi", ob)*100/his_max_qi)<50){
                message_vision(CYN"$N沖著$n一撇嘴，說道：你們漢人的武學不過如此。\n"NOR, me,ob);
                message_vision("$N對$n行了個禮，垂頭喪氣地離開了這裡。\n",ob, me);
//                ob->move("/u/snowman/hj/road");
//                message_vision("$N垂頭喪氣地走回來。\n", ob);
                return 1;
               }
        return 1;
}

int accept_object(object who, object ob)
{
        if( !who || environment(who) != environment() ) {return 0;}
        if ( !objectp(ob) ) {return 0; }
        if ( !present(ob, who) ) return 0;
        if (userp(ob)) {
               command("?"+query("id", who));
               command("say 你這漢人強盜，把人打暈想幹什麼？");
               this_object()->kill_ob(who);    
               return notify_fail("糟糕，穿邦了！\n");
               }
        if( query("name", ob) == "灰狼皮"){
                command("ah"+query("id", who));
                command("say 你殺死了大灰狼！看來你也是個勇士，要不要和我比試一下？\n");                
                set_temp("supu_accept", 1, who);
        message_vision("$N看了$n一眼，用不太標準的漢話說道：
我是未來的草原第一勇士，這位漢族"+RANK_D->query_respect(this_player())+"你就和我切搓(fight)幾下吧？\n", this_object(), this_player());
        set_temp("supu1", 1, this_player());
                call_out("destob",0,ob);                         
            return 1;
        }        
        command("smile"+query("id", who));
        command("say 謝謝你啦。");
        call_out("destob",0,ob);  
        return 0;
}
void destob(object ob)
{
        destruct(ob);
}
