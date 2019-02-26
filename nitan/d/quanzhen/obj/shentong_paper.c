// Code of ShenZhou
// shentong_paper.c
//Can't use it in no_fight rooms By Sure
//5.2001

#include <ansi.h>
inherit ITEM;

string long_desc();

mapping default_dirs = ([
                  "north":        "北",
                  "south":        "南",
                  "east":         "東",
                  "west":         "西",
                  "northup":      "北邊",
                  "southup":      "南邊",
                  "eastup":       "東邊",
                  "westup":       "西邊",
                  "northdown":    "北邊",
                  "southdown":    "南邊",
                  "eastdown":     "東邊",
                  "westdown":     "西邊",
                  "northeast":    "東北",
                  "northwest":    "西北",
                  "southeast":    "東南",
                  "southwest":    "西南",
                  "up":           "上",
                  "down":         "下",
                  "out":          "外",
                  "enter":        "裏",
]);

void create()
{
                  set_name("純陽神通功祕訣", ({"shentong mijue", "mijue"}));
                  set_weight(100);
                  if( clonep() )
                                         set_default_object(__FILE__);
                  else {
                                         set("unit", "卷");
                                         set("long", (: long_desc :));
                                         set("value", 10000000);
                                         set("material", "paper");
                                         set("no_drop","這樣東西不能離開你。\n");
                  }
}

string long_desc()
{
        string desc;

        if( random(2) )
        {
          desc ="

純陽神通功祕訣

純陽神通功系本山人晚年悟得。吾青壯年獻身於抗金大業，大小百餘戰，
殺金賊無數。無奈朝廷奸賊當道，忠義之士俱被殺戳，有功之臣慘遭滅門。
餘雖有心迴天，奈我朝氣數已盡，非人力所能為。為免我華夏遭滅門之厄，
餘慨歎之餘，網羅天下同道之士，修活死人墓，集數萬金，以為日後東山
再起之備。餘手創全真教，廣傳門徒，授防身之術，盼我教眾徒能成為我
大宋之中流砥拄。我大宋中興，全繫於諸人。餘閉關多年，並與諍友林氏
朝英切磋多次，兼參讀九陰真經，終大徹大悟，得成大道。餘戎馬生涯，
行走江湖多年，身受巨創多次，又與西毒歐陽鋒大戰數次，雖破其哈蟆功，
餘亦深受劇毒，元氣大傷，恐不日就要歸天。惜眾徒皆資質一般，無人能
授予奇功。師弟伯通雖資質奇佳，但已非純陽之身，且不通事理。餘去之
後，恐重陽宮不日就要遭厄運，此也是天數。餘特留此祕訣，藏於極密之
處，日後有緣者自能獲得此訣。爾既能得此訣，當是極為有緣。中興華夏，
全賴於汝，望汝不負吾望。汝若能習成此功，可進列為吾徒，日後須行俠
仗義，替天行道。

終南山王重陽
\n";
        }
        else desc="
練功祕訣：須於無人僻靜之處，持此祕訣，靜讀潛心修練(xiulian)。
已婚者須當心走火入魔。此功光練無用，須常常和高手切磋(qiecuo)。\n";


return desc;
}


void init()
{
        add_action("do_xiulian","xiulian");
        add_action("do_xiulian","xiu");
        add_action("do_qiecuo","qiecuo");
}

int do_xiulian(string arg)
{
        object me = this_player();
        object here=environment(me);
                object where;

                seteuid(getuid());
        where = environment(me);

        if(me->is_busy())return notify_fail("你正忙着呢。\n");
                if( query("no_fight", where) )
                return notify_fail("你只覺渾身懶懶地，無法凝神聚氣。\n");
        if( query("neili", me)<1000)return notify_fail("你內力不足，無法修練。\n");
        if( query("jingli", me)<1000)return notify_fail("你精力不足，無法修練。\n");
        if(me->query_skill("xiantian-gong",1)<300)return notify_fail("你先天功基礎太差，無法修練。\n");
        if(me->query_skill("force",1)<300)return notify_fail("你內功基礎太差，無法修練。\n");
        if(me->query_skill("taoism",1)<300)return notify_fail("你道學基礎太差，無法修練。\n");
        if( query("shen", me)<3500000)return notify_fail("你行俠仗義之事做得不夠，正氣不足，無法修練。\n");

        if( query("quanzhen/shentong_times", me)>20 )
        {
                set("can_perform/xiantian-gong/shen", 1, me);
                return notify_fail("你修練已久，該去實戰應用一下了。\n");
        }

        message_vision(
HIG"$N按照純陽神通功祕訣，運起玄門先天功，聚天地之精氣，過紫宮，入泥丸，
透十二重樓，開玄關，通任督，勁隨意到，勁到力至。\n"NOR,me);

        me->start_busy( 1+random(5) );

        call_out("done",1+random(10) );

        return 1;
}

void done()
{
        object me = this_player();
        object here=environment(me);
        int marries=query("married/times", me);
        object where;


        if( random(marries) > 0 )
        {
                message_vision(
HIY"$N只覺元氣不足，想要打通的督脈只差一絲絲，可是偏偏就是過不去。累得出了一身大汗。\n"NOR,me);
                addn("neili", -query("neili", me)/2, me);
                addn("jingli", -1000, me);
                me->improve_skill("force",100+random(400));
        }
        else
        {
                if( random(query("neili", me))>8000 )
                {
                        message_vision(
HIG"$N只覺得真氣直通任督，越運真氣越是充沛，靈台一片清涼光明，偏體舒暢無比。\n"NOR,me);
                        me->improve_skill("force",200+random(400));
                        addn("neili", -1000-random(2000), me);
                        addn("shentong", random(2), me);
                }
                else if( random(query("neili", me))>3000 )
                {
                        message_vision(
HIG"$N只覺得真氣通過任督，真氣充沛，偏體舒暢無比。\n"NOR,me);
                        if( query("potential", me) )
                        {
                                addn("potential", -1, me);
                                addn("neili", -random(50), me);
                        }
                        else addn("neili", -100-random(50), me);

                        me->improve_skill("force",100+random(100));
                }
                else
                {
                        message_vision(
HIY"$N只覺內力不足，想要打通的任脈只差一絲絲，可是偏偏就是過不去。累得出了一身大汗。\n"NOR,me);
                        addn("neili", -100, me);
                        addn("jingli", -500, me);
                }
        }

        addn("quanzhen/shentong_times", 1, me);
}


int do_qiecuo(string arg)
{
        object me = this_player();
        object target;
        object here=environment(me);
        int skill, value;
                object where;

                seteuid(getuid());
        where = environment(me);

        if(me->is_busy())return notify_fail("你正忙着呢。\n");
                if( query("no_fight", where) )
                return notify_fail("比試的念頭剛在腦中一閃，四周就凝結了一層殺氣。\n");
        if(!arg)return notify_fail("你想和誰切磋？\n");
        target = present(arg,here);
        if(!target)return notify_fail("你想和誰切磋？\n");

        if( query("race", target) != "人類")return notify_fail("可惜它不懂人事。\n");
        if( query("combat_exp", target)*3<query("combat_exp", me)*2 )
                return notify_fail("此人武功太差，無法和你切磋。\n");

        if(!living(target)) return notify_fail("你得等人家醒了才行。\n");
        if(target->is_busy())return notify_fail("人家正忙着呢。\n");

        if( query("neili", me)<1000)return notify_fail("你內力不足，無法切磋。\n");
        if( query("jingli", me)<1000)return notify_fail("你精力不足，無法切磋。\n");
        if(me->query_skill("xiantian-gong",1)<300)return notify_fail("你先天功基礎太差，無法切磋。\n");
        if(me->query_skill("force",1)<300)return notify_fail("你內功基礎太差，無法切磋。\n");
        if(me->query_skill("taoism",1)<300)return notify_fail("你道學基礎太差，無法切磋。\n");

        if( query("quanzhen/shentong_times", me)<1)return notify_fail("你純陽神通未練已久，該去修練一下了。\n");

        message_vision(
HIG"$N按照純陽神通功祕訣，運起玄門先天功，聚天地之精氣，過紫宮，入泥丸，
透十二重樓，開玄關，通任督，勁隨意到，勁到力至。\n"NOR,me);
        message_vision(
HIW"$N緊跟着將內力偏布全身，只見白氣逐漸籠罩全身，雙眼精光四射，與平時判若兩人。\n" NOR, me);

        message_vision(
HIR"$N接着突然出掌攻向$n，當真是無聲無息，卻迅如閃電。\n" NOR, me,target);

                  skill = me->query_skill("force");
                  addn("neili", -skill*2, me);
                  set("jiali", 0, me);
                  value=skill*(5+random(query("shentong", me)*5));
                  if( value > 90000 ) value = 90000;
                  if( value < 30000 ) value = 30000;
                  addn("jingli", value, me);
                  addn_temp("apply/attack", value/200, me);
                  COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                  me->start_busy(1+random(2));
                  addn("jingli", -value, me);
                  addn_temp("apply/attack", -value/200, me);
                  me->improve_skill("force",50+random(100));

                  if( random(10)==1 ) call_out("run_away",0,target);

                  set("quanzhen/shentong_times",query("quanzhen/shentong_times",  me)-4, me);

        return 1;
}

void destroy_me(object ob)
{
        message_vision(HIR"$N被純陽神通功驚人內力所驚，不由得向後連連退步，口道：“佩服！佩服！”。
説完轉身撒腿就跑，比兔子還快，轉眼就不見了。\n"NOR,ob);
        destruct(ob);
}

void run_away(object ob)
{
        object obj;
        object here = environment(ob);
        string *dirs,dir,dest,target_dir;
        mapping exit;

        if(!ob)return;
        if(!here || !objectp(here) )return;

        if( !userp(ob) && random(100)==1 )
        {
                call_out("destroy_me",1,ob);
                return;
        }

        if(random(5) != 0) call_out("run_away",0,ob);

        message_vision(HIR"$N被純陽神通功驚人內力所逼，不由得向後連連退步。\n"NOR,ob);

        exit=query("exits", here);
        if( !exit ) return;
        dirs = keys(exit);
        if (sizeof(dirs) > 0)
        dir = dirs[random(sizeof(dirs))];
        if(!dir)return;
        dest = exit[dir];
        if( !dest )return;

        if( !(obj = find_object(dest)) )
                call_other(dest, "???");
        if( !(obj = find_object(dest)) )
                return;
        if( !wizardp(ob) && query("short", obj) == "巫師休息室" )
                return;

        if( !undefinedp(default_dirs[dir]) )
                                         target_dir = default_dirs[dir];
                  else
                                         target_dir = dir;


        if( ob->move(obj) ) {
                        message_vision(HIY"只見$N踉踉蹌嗆跑了過來。\n" NOR, ob);
        }
}
