// six-book.c
#include <ansi.h>
inherit ITEM;

string skl_name();
int do_yanjiu(string arg);
void create()
{
        set_name( HIC"六脈神劍譜"NOR,({ "sixfinger book","book"}));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","這是一幅圖。上面都是縱橫交叉的直線、圓圈和弧形。\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name":         (: skl_name :), //name of the skill
                        "exp_required": 500000,         //minimum combat experience required
                        "jing_cost":    100,            // jing cost every time study this
                        "difficulty":   45,             // the base int to learn this skill
                        "min_skill":    0,              // the minimum level you can learn
                        "max_skill":    120,            // the maximum level you can learn
                        "need" : ([ "force" : 301 ]),
                ]) );
        }
}

string skl_name()
{
        string *sks;

        sks = keys(SKILL_D("six-finger")->query_sub_skills());
        return sks[random(sizeof(sks))];
}

void init()
{
        add_action("do_yanjiu","yanjiu");
        add_action("do_yanjiu","research");
}
int do_yanjiu(string arg)
{
        object ob = this_object();
        object me = this_player();
        string skill,book;
        string msg;
        
        if (!present(ob,me)) return 0;

        if ((int)me->query_skill("literate",1)<1)
        {
                write("你是個文盲，先學點讀書寫字(literate)吧。\n");
                return 1;
        }

        if (me->is_busy() || me->is_fighting())
        {
                write("你正忙著呢。\n");
                return 1;
        }

        if (!arg || sscanf(arg,"%s from %s",skill,book)!=2)
        {
                write("研讀絕技的指令是 yanjiu 絕技名 from book\n");
                return 1;
        }

        if (!id(book))
        {
                write("沒有這本書。\n");
                return 1;
        }

        if (skill != "此去彼來" && skill != "馭劍氣" 
           && skill != "ciqu" && skill != "yuqi")
        {
                write("書上並沒有介紹關于"+skill+"的內容。\n");
                return 1;
        }

        if( query("combat_exp", me)<1000000 )
        {
                write("你的實戰經驗太低，讀不懂這麼深奧的東西。\n");
                return 1;
        }

        if( query("jing", me)<100 || 
            query("qi", me)<100 || 
            query("neili", me)<200 )
  {
          write("你現在過于疲倦，無法專心下來研讀新知。\n");
          return 1;
  }
  
  switch(skill)
  {
          case "ciqu":
          case "此去彼來":
           if( query("can_perform/six-finger/ciqu", me) )
           {
                write("你不是已經會了嗎？\n");
                return 1;
           }
           if (me->query_skill("six-finger", 1) < 120)
           {
                write("你六脈神劍不夠熟練，無法研讀此絕招！\n");
                return 1;
           }

           if (random (10) != 1)
           {
                write("你研究了半天，仍然無法將「此去彼來」融會貫通！\n");
                me->start_busy(15); 
                set("jing", 1, me);
                return 1;
           }
           msg = HIG "$N" HIG "翻看劍譜，仔細研究上面所記載的武學，霎那間忽有所悟"
                     "……\n" NOR;
           msg += HIW "$N" HIW "攤開雙手，手指連彈，霎時間空氣炙熱，幾"
                  "欲沸騰，六道劍氣分自六穴，一起沖向天際" HIW "！\n" NOR;
           msg += HIG "$N" HIG "長嘆一聲，感慨萬千，將內力收回丹田。\n" NOR; 
           message_vision(msg, me); 

                   me->improve_skill("finger", 1500000);
                   me->improve_skill("six-finger", 1500000);

           write(HIW "你學會了「" HIG "此去彼來" HIW "」。\n" NOR);
           set("can_perform/six-finger/ciqu", 1, me);
           return 1;
          case "yuqi":
          case "馭劍氣":
           if( query("can_perform/six-finger/yuqi", me) )
           {
                write("你不是已經會了嗎？\n");
                return 1;
           }
           if (me->query_skill("six-finger", 1) < 120)
           {
                write("你六脈神劍不夠熟練，無法研讀此絕招！\n");
                return 1;
           }
           if (me->query_skill("force", 1) < 120)
           {
                write("你內功火候不夠，無法研讀此絕招！\n");
                return 1;
           }

           if (random (20) != 1)
           {
                write("你研究了半天，仍然無法將「馭劍氣」融會貫通！\n");
                me->start_busy(15);
                set("jing", 1, me);
                return 1;
           }
           msg = HIG "$N" HIG "翻看劍譜，仔細研究上面所記載的武學，霎那間忽有所悟"
                     "……\n" NOR;
           msg += HIM "$N" HIM "一聲清嘯，十指紛彈，頓覺六脈劍氣已湧上心頭，此起"
                  "彼伏、連綿不絕。霎時劍氣如奔，連綿無盡的萬道劍氣豁然貫向虛空" HIM 
                  "！\n" NOR;
           msg += HIG "$N" HIG "長嘆一聲，感慨萬千，將內力收回丹田。\n" NOR; 
           message_vision(msg, me); 

                   me->improve_skill("finger", 1500000);
                   me->improve_skill("six-finger", 1500000);

           write(HIW "你學會了「" HIG "馭劍氣" HIW "」。\n" NOR);
           set("can_perform/six-finger/yuqi", 1, me);
           return 1;
                  break;
          default:
                  return 0;
  }
  return 0;
}