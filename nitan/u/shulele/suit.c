// suit.c

#include <mudlib.h>
#include <ansi.h>
#include <armor.h>
#include <command.h>
#define NULL_VALUE 0
inherit CLOTH;
inherit F_SAVE;
inherit F_AUTOLOAD;
inherit F_DAMAGE;
//inherit F_CLEAN_UP;
inherit F_COMMAND;
string replace_color(string,int);
int help(object);
int wiz_set(string,string,string,int);
string inputstr,verb;
int main(object me, string arg);

void create()
{
       seteuid(getuid());
       set_name(HIW"巫師工作服"NOR,({"wizard suit","suit" }));
       set("long",@LONG
※※※※※※※※※※※※※※※※※※※※※※※※※※※※
※  命  令  ※    用       法   ※    説        明    ※
※※※※※※※※※※※※※※※※※※※※※※※※※※※※
※yao       ※yao <genre><valu> ※可以憑空取錢        ※
※bianxing  ※bianxing <id>     ※給人做變性手術      ※
※xing      ※xing <id>         ※讓某人甦醒          ※
※hun       ※hun  <id>         ※讓某人暈倒          ※
※feng      ※feng <id>         ※封凍某人            ※
※jiefeng   ※jiefeng <id>      ※解封某人            ※
※age       ※age <id> <s>      ※修改年齡            ※
※skill     ※skill <id><msg><s>※修改人物的武功等級  ※
※exp       ※exp <id> <s>      ※修改人物的武功等級  ※
※※※※※※※※※※※※※※※※※※※※※※※※※※※※
LONG
       );
       if(clonep())
           set_default_object(__FILE__);
       else{
           set("unit","件");
           seteuid(geteuid());
           set("material", "cloth");
           set("armor_prop/armor", 10000);
           set("no_get",1);
           set("no_drop",1);
           }
       setup();
}
// 命令直待
void init()
{
       if( wizardp(environment()) ) {
       add_action("quanjia","quanjia");
       add_action("yao","yao");
       add_action("xing","xing");
       add_action("combat_exp","exp");       
       add_action("hun","hun");
       add_action("bx","bianxing");
       add_action("fengplayer","feng");
       add_action("jiefengplayer","jiefeng");
       add_action("office_number","office_number");
       add_action("str","str");
       add_action("cor","cor");
add_action("wuxing","wuxing");
       add_action("int","int");
       add_action("spi","spi");
       add_action("cps","cps");
       add_action("per","per");
       add_action("con","con");
       add_action("kar","kar");
       add_action("balance","balance");
       add_action ("skill", "skill");
       add_action("daoxing","dh");
       add_action ("age", "age");   
add_action ("faith", "faith");                
       add_action("letdie","letdie");
       add_action("potential","qn");
       add_action("max_mana","mana");
       add_action("detect", "level");       
       add_action("max_force","neili");
       this_player()->set_temp("heat",1);
      }
}

// COMBAT_EXP 修改經驗
int combat_exp(string str)
{
        object me,target;
        string name;
        int i;
        if(!str)        return notify_fail("combat sb. exp\n");
        me=this_player();
        if(sscanf(str,"%s %d",name,i)==2)       {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->add("combat_exp",i);
             log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s增加combat_exp:%12d。\n",ctime(time()),name, i));
        write("修改"+WHT+target->query("name")+NOR"的經驗值增加了"+HIR+(string)i+NOR"點。\n",this_object());
        return 1;
        }
        else return notify_fail("combat sb. exp\n");
}
int max_force(string str)
{
        object me,target;
        string name;
        int i;
        if(!str)        return notify_fail("max sb. force\n");
        me=this_player();
        if(sscanf(str,"%s %d",name,i)==2)       {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->add("max_force",i);
     log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s修改max_force:%12d。\n",ctime(time()),name, i));

        write("修改"+WHT+target->query("name")+NOR"的內力增加了"+HIR+(string)i+NOR"點。\n",this_object());
        return 1;
        }
        else return notify_fail("max sb. force\n");
}
int str(string str)
{
        object me,target;
        string name;
        int i;
        if(!str)        return notify_fail("str sb. str\n");
        me=this_player();
        if(sscanf(str,"%s %d",name,i)==2)       {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->add("str",i);
        log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s增加strength:%12d。\n",ctime(time()),name, i));

        write("修改"+WHT+target->query("name")+NOR"的經驗值增加了"+HIR+(string)i+NOR"點。\n",this_object());
        return 1;
        }
        else return notify_fail("str sb. str\n");
}
int cor(string str)
{
        object me,target;
        string name;
        int i;
        if(!str)        return notify_fail("cor sb. cor\n");
        me=this_player();
        if(sscanf(str,"%s %d",name,i)==2)       {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->add("cor",i);
   target->add("str",i);
        log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s增加cor:%12d。\n",ctime(time()),name, i));


        write("修改"+WHT+target->query("name")+NOR"的經驗值增加了"+HIR+(string)i+NOR"點。\n",this_object());
        return 1;
        }
        else return notify_fail("cor sb. cor\n");
}
int wuxing(string str)
{
        object me,target;
        string name;
        int i;
        if(!str)        return notify_fail("wuxing sb. wuxing\n");
        me=this_player();
        if(sscanf(str,"%s %d",name,i)==2)       {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->add("int",i);
        target->add("str",i);
        log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s增加strength:%12d。\n",ctime(time()),name, i));
        write("修改"+WHT+target->query("name")+NOR"的經驗值增加了"+HIR+(string)i+NOR"點。\n",this_object());
        return 1;
        }
        else return notify_fail("wuxing sb. wuxing\n");
}
int spi(string str)
{
        object me,target;
        string name;
        int i;
        if(!str)        return notify_fail("spi sb. spi\n");
        me=this_player();
        if(sscanf(str,"%s %d",name,i)==2)       {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->add("spi",i);
 log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s增加spi:%12d。\n",ctime(time()),name, i));

        write("修改"+WHT+target->query("name")+NOR"的經驗值增加了"+HIR+(string)i+NOR"點。\n",this_object());
        return 1;
        }
        else return notify_fail("spi sb. spi\n");
}
int cps(string str)
{
        object me,target;
        string name;
        int i;
        if(!str)        return notify_fail("cps sb. cps\n");
        me=this_player();
        if(sscanf(str,"%s %d",name,i)==2)       {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->add("cps",i);
 log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s增加cps:%12d。\n",ctime(time()),name, i));

        write("修改"+WHT+target->query("name")+NOR"的經驗值增加了"+HIR+(string)i+NOR"點。\n",this_object());
        return 1;
        }
        else return notify_fail("cps sb. cps\n");
}
int per(string str)
{
        object me,target;
        string name;
        int i;
        if(!str)        return notify_fail("per sb. per\n");
        me=this_player();
        if(sscanf(str,"%s %d",name,i)==2)       {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->add("per",i);
        log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s增加per:%12d。\n",ctime(time()),name, i));

        write("修改"+WHT+target->query("name")+NOR"的經驗值增加了"+HIR+(string)i+NOR"點。\n",this_object());
        return 1;
        }
        else return notify_fail("per sb. per\n");
}
int kar(string str)
{
        object me,target;
        string name;
        int i;
        if(!str)        return notify_fail("kar sb. kar\n");
        me=this_player();
        if(sscanf(str,"%s %d",name,i)==2)       {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->add("kar",i);
 log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s增加kar:%12d。\n",ctime(time()),name, i));
        write("修改"+WHT+target->query("name")+NOR"的經驗值增加了"+HIR+(string)i+NOR"點。\n",this_object());
        return 1;
        }
        else return notify_fail("kar sb. kar\n");
}
int con(string str)
{
        object me,target;
        string name;
        int i;
        if(!str)        return notify_fail("con sb. con\n");
        me=this_player();
        if(sscanf(str,"%s %d",name,i)==2)       {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->add("con",i);
 log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s增加con:%12d。\n",ctime(time()),name, i));
        write("修改"+WHT+target->query("name")+NOR"的經驗值增加了"+HIR+(string)i+NOR"點。\n",this_object());
        return 1;
        }
        else return notify_fail("con sb. con\n");
}
int balance(string str)
{
        object me,target;
        string name;
        int i;
        if(!str)        return notify_fail("balance sb. balance\n");
        me=this_player();
        if(sscanf(str,"%s %d",name,i)==2)       {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->add("balance",i);
        log_file("cmds/file/"+geteuid(me),
                    sprintf("[%s] %s增加balance:%12d。\n",ctime(time()),name, i));

        write("修改"+WHT+target->query("name")+NOR"的經驗值增加了"+HIR+(string)i+NOR"點。\n",this_object());
        return 1;
        }
        else return notify_fail("balance sb. balance\n");
}
int max_mana(string str)
{
        object me,target;
        string name;
        int i;
        if(!str)        return notify_fail("max sb. mana\n");
        me=this_player();
        if(sscanf(str,"%s %d",name,i)==2)       {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->add("max_mana",i);
 log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s增加max_mana:%12d。\n",ctime(time()),name, i));

        write("修改"+WHT+target->query("name")+NOR"的法力增加了"+HIR+(string)i+NOR"點。\n",this_object());
        return 1;
        }
        else return notify_fail("max sb. mana\n");
}
int potential(string str)
{
        object me,target;
        string name;
        int i;
        if(!str)        return notify_fail("potential sb. qn\n");
        me=this_player();
        if(sscanf(str,"%s %d",name,i)==2)       {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->add("potential",i);
 log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s增加potential:%12d。\n",ctime(time()),name, i));

        write("修改"+WHT+target->query("name")+NOR"的潛能增加了"+HIR+(string)i+NOR"點。\n",this_object());
        return 1;
        }
        else return notify_fail("potential sb. qn\n");
}
int office_number(string str)
{
        object me,target;
        string name;
        int i;
        if(!str)        return notify_fail("office_number sb. office_number\n");
        me=this_player();
        if(sscanf(str,"%s %d",name,i)==2)       {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->add("office_number",i);
 log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s增加office_number:%12d。\n",ctime(time()),name, i));

        write("修改"+WHT+target->query("name")+NOR"的官職增加了"+HIR+(string)i+NOR"點。\n",this_object());
        return 1;
        }
        else return notify_fail("office_number sb. office_number\n");
}
int daoxing(string str)
{
        object me,target;
        string name;
        int i;
        if(!str)        return notify_fail("daoxing sb. dh\n");
        me=this_player();
        if(sscanf(str,"%s %d",name,i)==2)       {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->add("daoxing",i);
 log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s增加daoxing:%12d。\n",ctime(time()),name, i));

        write("修改"+WHT+target->query("name")+NOR"的道行增加了"+HIR+(string)i+NOR"點。\n",this_object());
        return 1;
        }
        else return notify_fail("daoxing sb. dh\n");
}
// AGE 年齡
int age(string str)
{
        object me,target;
        string name;
        int level;
        me=this_player();
        if(!str) return notify_fail("age sb 增加的年紀.\n");
        if(sscanf(str,"%s %d",name,level)==2)   {
        if(!(target=present(name,environment(me))))
                return notify_fail("沒兒沒有這麼個人。\n");
        target->add("mud_age",86400*level);
        target->add("age",level);
       log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s增加age:%12d。\n",ctime(time()),name, level));

        write("修改"+WHT+target->query("name")+NOR+"，年紀增加"+HIR+(string)level+NOR+"歲。\n",this_object());
        return 1;
        }
        else
        return notify_fail("age sb. 增加的年紀。\n");
}
int faith(string str)
{
        object me,target;
        string name;
        int i;
        if(!str)        return notify_fail("faith sb. faith\n");
        me=this_player();
        if(sscanf(str,"%s %d",name,i)==2)       {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->add("faith",i);
       log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s增加faith:%12d。\n",ctime(time()),name, i));
        write("修改"+WHT+target->query("name")+NOR"的門派忠誠度增加了"+HIR+(string)i+NOR"點。\n",this_object());
        return 1;
        }
        else return notify_fail("faith sb. faith\n");
}
//  SKILL 武功
int skill(string str)
{
        object me;
        object target;
        string name,skills;
        int level;
        if(!str)        return notify_fail("skill 某人 技術 等級\n");
        me=this_player();
        if(sscanf(str,"%s %s %d",name,skills,level)==3)         {
        if(!(target=present(name,environment(me))))
                return notify_fail("這兒沒有這麼個人。\n");
        target->set_skill(skills,level);
         log_file("cmds/file/"+geteuid(me),
                     sprintf("[%s] %s增加%s:%12d。\n",ctime(time()),name,skills,level));

        write("修改"+WHT+target->query("name")+NOR"的"+YEL+to_chinese(skills)+NOR+"武功為"+HIR+(string)level+NOR"級。\n",this_object());
        return 1;
        }
        else
        return notify_fail("skill 某人 技術 等級\n");
}
// 把人封住
int fengplayer (string str)
{
  object ob;
  if(str=="kittt") return notify_fail("你是不是想死啊！\n");
  if (!str) return notify_fail("feng <id>\n");
       ob = LOGIN_D->find_body(str);
  if (!ob) return notify_fail("有這個人嗎?\n");
  tell_object(ob,"你的眼睛突然一片模糊，好像有人矇住你了...\n");
  ob->set_temp("block_msg/all",1);
  ob->disable_player(HIR "<失去知覺中>" NOR);      
  return 1;    
}
// 把人解封
int jiefengplayer (string str)
{
  object ob;
  if (!str) return notify_fail("jiefeng <id>\n");
       ob = LOGIN_D->find_body(str);
  if (!ob) return notify_fail("有這個人嗎?\n");   
  ob->set_temp("block_msg/all",0);
  ob->enable_player(); 
  tell_object(ob,"有人很你説道：“恭喜發財”，你終於可以...\n");
  return 1;
}
//  XING 使人甦醒
int xing (string str)
{
  object who;
  if (!str) return notify_fail ("xing <id>\n");
  who = LOGIN_D->find_body(str);
  if (!who){ 
  if (!(who=present (lower_case(str), environment(this_player()))) )
    return notify_fail ("沒有"+str+"呀？\n");}
  who->remove_call_out("revive");
  who->revive();
  who->reincarnate();
  return 1;
}
// HUN 使人昏倒

int hun (string str)
{
  object who;
  if (!str) return notify_fail ("你瘋了，把自己弄暈！\n");
  who = LOGIN_D->find_body(str);
  if (!who){ 
  if (!(who=present (lower_case(str), environment(this_player()))) )
    return notify_fail ("沒有"+str+"呀？\n");}
  who->remove_call_out("unconcious");
  who->unconcious();
  who->announce();
  return 1;
}
//  BX 變性手術
int bx(string arg)
{
  object bxid,me;
  me=this_player();
  if(arg=="kittt") return notify_fail("你奶奶的想死啊！\n");
  if (arg!=NULL_VALUE){
    bxid = LOGIN_D->find_body(arg);
    if (!bxid) return notify_fail("在網上好像沒這個人呀！\n");
    }
  if (arg) {
    if(arg=="kittt") return notify_fail("你想死啊！\n");
    if(bxid->query("gender")=="女性") bxid->set( "gender", "男性" );
    else bxid->set( "gender", "女性" );
    message("shout", HIM "【謠言】某人：聽説"+me->query("name")+"成功的對" 
    +bxid->query("name")+"進行了一次變性手術。\n" NOR,users());
    bxid->save();
    return 1;
  }
}
//  YAO 取錢
int yao (string arg)
{
        string kind;
        int amount;
        object n_money;
        if( !arg || sscanf(arg, "%d %s", amount, kind)!=2 )
          return notify_fail("usage: yao <多少錢> <錢幣種類>\n");
        n_money = present(kind + "_money", this_player());
        if( !n_money && file_size("/clone/money/" + kind + ".c") < 0 )
                return notify_fail("好像沒有這種錢呀？搖個屁呀！\n");
        if( amount < 1 )
                return notify_fail("呵呵，還是沒有。\n");
        if( !n_money ) {
                n_money = new("/clone/money/" + kind);
                n_money->move(this_player());
                n_money->set_amount(amount);
        } else
                n_money->add_amount(amount);
 message_vision( sprintf(HIY "$N使勁的掏自己的口袋，突然從袋子裏掏出%s%s%s。\n" NOR,
        chinese_number(amount),n_money->query("base_unit"),n_money->query("name")),
        this_player());return 1;
}
string replace_color(string arg,int flag)
{
        arg = replace_string(arg, "$BLK$", flag?BLK:"");
        arg = replace_string(arg, "$RED$", flag?RED:"");
        arg = replace_string(arg, "$GRN$", flag?GRN:"");
        arg = replace_string(arg, "$YEL$", flag?YEL:"");
        arg = replace_string(arg, "$BLU$", flag?BLU:"");
        arg = replace_string(arg, "$MAG$", flag?MAG:"");
        arg = replace_string(arg, "$CYN$", flag?CYN:"");
        arg = replace_string(arg, "$WHT$", flag?WHT:"");
        arg = replace_string(arg, "$HIR$", flag?HIR:"");
        arg = replace_string(arg, "$HIG$", flag?HIG:"");
        arg = replace_string(arg, "$HIY$", flag?HIY:"");
        arg = replace_string(arg, "$HIB$", flag?HIB:"");
        arg = replace_string(arg, "$HIM$", flag?HIM:"");
        arg = replace_string(arg, "$HIC$", flag?HIC:"");
        arg = replace_string(arg, "$HIW$", flag?HIW:"");
        arg = replace_string(arg, "$NOR$", flag?NOR:"");
        arg = replace_string(arg, "$BLINK$", flag?BLINK:"");
        if(flag) arg+=NOR;
        return arg;
}
int query_autoload()
{
   if (wizardp(environment())) return 1;
   else return 0;
  }
