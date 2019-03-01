//snowman 28/02/98
#include <ansi.h>
inherit NPC;
string ask_huijia();
string ask_daojia();
int ask_rob();
void create()
{
        set_name(HIM"義士"NOR, ({ "yi shi", "yi", "shi" }) );
        set("gender", "男性" );
        set("age", 22+random(20));
        set("long",
                "這位志在反清復明的義士。\n");
        set("per", 35);
        set("str", 40);
        set("int", 47);
        set("con", 46);
        set("dex", 48);
        set("qi", 4500);
        set("max_qi", 4500);
        set("jing", 4600);
        set("max_jing", 4600);
        set("neili", 4000);
        set("max_neili", 4000);
        set("chat_chance", 0);
        set("chat_msg", ({
                (: random_move :),
        }) );
        set("inquiry", ([
        "護送" : (:ask_huijia:) ,
        "到了" : (:ask_daojia:) ,
         ]) );
        set("env/wimpy", 40);
        set_temp("apply/attack", 300);
        set_temp("apply/defense",300);
        set_temp("apply/armor", 300);
        set_temp("apply/damage", 100);
        setup();
        carry_object("/d/lingjiu/obj/qingyi")->wear();
        carry_object("/d/lingjiu/obj/doupeng")->wear();
}

void init()
{
        object ob = this_object();
        add_action("do_guard", "guard");
//        this_player()->start_busy(1);
if( query("lingsong", ob) == 0 )
{
        remove_call_out("leave");
        call_out("leave",240);
}
}

void leave()
{
        object ob = this_object();
        if( query("lingsong", ob) == 0){
                message_vision(HIG "反清義士見無人來接應,自己離開了。\n" NOR,this_object());
                destruct(this_object());
                }
        else call_out("leave",30);
}

string ask_huijia()
{
object me=this_player();
object ob = this_object();
if( query("kill_yunlong", me) == 0 )
return "我看你是清狗派來的那姦細吧。。。\n";
set_leader(me);
set("lingsong", 10, ob);
return "地振高岡，一派溪山千古秀,反清義士和你對上了喑號.\n";
}

string ask_daojia()
{
 object ob,me;
// int exp,pot,base_exp
 ob = this_object();
me = this_player();
if( query("kill_yunlong", me) == 0 )
return "我看你是清狗派來的那姦細吧。。。\n";
 if( query("short", environment(ob)) == "春來茶館" )
         {

          set_leader(0);
          write("門朝大海，三河合水萬年流.喑號對上了，\n");

             addn("combat_exp", 300+random(100), me);
             addn("family/gongji", 10+random(15), me);
             addn("potential", 100+random(60), me);
             delete("kill_yunlong", me);
         write("你的經驗和潛能提高了!!\n");
        call_out("leavet",1);
           return "我走了，大家保重.....\n";  
      }
        else {
                return "還沒到呢!你想不管了嗎?\n";
        }
}

int do_guard(string arg)
{
        write(query("name", this_player())+"，你現在不能用guard！\n");
        return 1;
}

void leavet()
{
        object ob = this_object();
        destruct(this_object());
}

void unconcious()
{            
        ::die();       
}        
