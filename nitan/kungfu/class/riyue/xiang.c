// xiang.c
//Update by haiyan

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

#define CHILONG    "/clone/lonely/chilongsuo"
#define XINGLV     "/clone/item/xiaoao/xinglvtu"
#define SHUAIYI     "/clone/item/xiaoao/shuaiyitie"
int ask_kill();
mixed ask_pfm();

void create()
{
        object ob1, ob2;
    set_name("向問天", ({ "xiang wentian", "xiang"}));
    set("nickname", HIR "天王老子" NOR );
    set("gender", "男性");
    set("title", "日月神教光明右使");
    set("long", "他就是日月神教的光明右使。為人極為豪爽。\n");
    set("age", 56);
    set("shen_type", -1);
    set("attitude", "peaceful"); 

    set("str", 21);
    set("per", 28);
    set("int", 30);
    set("con", 26);
    set("dex", 30);
    set("chat_chance", 1);
    set("inquiry", ([
      "楊蓮亭"     : "這種人，該殺！\n",
      "東方不敗"   : "篡位叛徒，我非殺了他不可！\n",
      "任我行"     : "教主被困，已歷十年......\n",
      "殺東方不敗" : (: ask_kill :),
      "望斷秋水"   : (: ask_pfm :),
      "絕招"       : (: ask_pfm :),
    ]));
    set("qi", 4000);
    set("max_qi", 4000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 3500);
    set("max_neili", 3500);
    set("jiali", 350);

    set("combat_exp", 2500000);
    set("score", 0);

    set_skill("force", 150);
    set_skill("riyue-xinfa", 150);
    set_skill("dodge", 150);
    set_skill("piaomiao-shenfa", 150);
    set_skill("hand", 150);
    set_skill("huanmo-longtianwu", 150);
    set_skill("cuff", 150);
    set_skill("xuwu-piaomiao", 150);
    set_skill("parry", 150);
    set_skill("whip", 180);
    set_skill("liushui-bian", 180);
    set_skill("literate", 110);

    set_skill("sword", 150);
    set_skill("riyue-jian", 150);
    map_skill("sword", "riyue-jian");
    map_skill("force", "riyue-xinfa");
    map_skill("dodge", "piaomiao-shenfa");
    map_skill("hand", "huanmo-longtianwu");
    map_skill("cuff", "xuwu-piaomiao");
    map_skill("parry", "liushui-bian");
    map_skill("whip", "liushui-bian");

    prepare_skill("hand", "huanmo-longtianwu");
    prepare_skill("cuff", "xuwu-piaomiao");

    create_family("日月神教", 2, "光明右使");
    set("have_ling",1);
    set("master_ob",3);
        setup();
        if (clonep())
        {
                ob1 = find_object(XINGLV);
                if (! ob1) ob1 = load_object(XINGLV);
                if (! environment(ob1)) ob1->move(this_object());

                ob1 = find_object(SHUAIYI);
                if (! ob1) ob1 = load_object(SHUAIYI);
                if (! environment(ob1)) ob1->move(this_object());

                ob2 = find_object(CHILONG);
                if (! ob2) ob2 = load_object(CHILONG);
                if (! environment(ob2))
                {
                        ob2->move(this_object());
                        ob2->wield();
                } else
                {
                        ob2 = new("/clone/weapon/changbian");
                        ob2->move(this_object());
                        ob2->wield();
                }
        }
    carry_object("/d/heimuya/npc/obj/cloth")->wear();
}

void attempt_apprentice(object ob)
{
    if( query("family/family_name", ob) == "日月神教" )
        command("say 老夫已不收弟子，不過我這裏有一套鞭法，你若想學，我可以教你。");
    else
        command("say 我不收弟子。");
    return;
}

int recognize_apprentice(object ob, string skill)
{
     if( query("family/family_name", ob) == "日月神教" )
     {
         if (skill != "whip" && skill != "liushui-bian")
         {
             command("say 我只會點鞭法，其他的找你師傅去學！");
             return -1;
         }

         if( query("character", ob) == "光明磊落" && skill == "liushui-bian" )
         {
             command("say 你不適合學我這門絕技！");
             return -1;
         }

         if( query("shen", ob)>0 )
         {
             command("heng");
             command("say 你既然自命正派君子，來學我這種雕蟲小技做什麼？");
             return -1;
         }

         if (skill == "liushui-bian" && ob->query_skill("whip", 1) < 150)
         {
             command("say 你對基本鞭法的理解也未免太差了點。");
             return -1;
         }

         if (skill == "whip")
         {
             if( !query("can_learn/xiang/whip", ob) )
             {
                  command("say 好吧，我就教你一點關於鞭法的基本知識。");
                  set("can_learn/xiang/whip", 1, ob);
             }
             return 1;
         }

         if (skill == "liushui-bian")
         {
             if( !query("can_learn/xiang/liushui-bian", ob) )
             {
                  command("say 很好，我這就傳你流水鞭法！");
                  set("can_learn/xiang/liushui-bian", 1, ob);
             }
             return 1;
         }
     }
     return 0;
}

mixed ask_pfm()
{
      object me = this_player();

      if( query("can_perform/liushui-bian/wang", me) )
              return "你要跟老夫切磋一下嗎？";

      if( query("family/family_name", me) != query("family/family_name") )
              return "我神教武功獨步武林，這位" + RANK_D->query_respect(me) +
                     "既然想學，不如入我神教如何？";

      if (me->query_skill("liushui-bian", 1) < 180)
              return "你的流水鞭法還練不到家，讓我怎麼教你呢！";

      message_vision(HIY "$n" HIY "對$N" HIY "點了點頭：你看那塊巨石。\n" HIY
                     "只見$n" HIY "手中長鞭一蕩，驟然向上揮出，只見長鞭" HIY
                     "劃出一道弧線，直向巨石擊去。\n" HIW
                     "“叭”的一聲，巨石已被打成碎片，四下飛散。\n" NOR,
                     me, this_object());
      command("say 你看懂了沒有？");
      tell_object(me, HIY "你學會了「望斷秋水」這一招。\n" NOR);
      if (me->can_improve_skill("whip"))
            me->improve_skill("whip", 160000);
      set("can_perform/liushui-bian/wang", 1, me);
      return 1;
}

int ask_kill()
{
      object ob, me = this_player();
      if (!query("have_ling"))
            command("say 我的天香堂令牌已經給別人了，怎麼還不去？");
      else
      {
            command("tell"+query("id", me)+"你要去殺東方不敗？\n");
            message_vision(HIC "向問天對$N點了點頭説：我助你一臂之力。\n" NOR, me);
            ob=new("/d/heimuya/npc/obj/card4");
            ob->move(me);
            delete("have_ling");
            tell_object(me, "向問天從懷裏摸出一塊令牌塞到你的手上。\n");
      }
      return 1;
}

void reset()
{
      set("have_ling",1);
}
