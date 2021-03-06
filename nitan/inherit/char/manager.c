// /inherit/char/manager.c

// last modified by sega 4/13/2000
// 修改叛徒的屬性為師傅的功夫,quest 的等級,呵呵
// Modified by Constant Jan 11 2001
// Modified by sir 4/12/2001
// 修改別派奸細,13個一輪,完成後附加pot,score獎勵
// Modified by Zeratul May 3 2001
// 修改叛徒任務，10個一輪，完成後可以向師父切磋升特殊skill 1級,附加score獎勵
// Modified by sir 5.1.2002

#include <dbase.h>
#include <login.h>
#include <ansi.h>
#include <quest1.h>
#define ONE_DAY                 (86400 / 365)
int is_manager() {return 1;}
///////開始祕籍任務
int party_quest_book(object me)
{
        object book, room, master = this_object();
        string *dir, *file, place;
        int i,j;

        me = this_player();
  if (!me->query("family/family_name"))
   {
                message_vision("$N對着$n説：這位"+RANK_D->query_respect(me)+"何不加入我"+master->query("family/family_name")+"？\n", master, me);
                return 1;
           }
        if (me->query("family/family_name") !=
                master->query("family/family_name"))
        {
                message_vision("$N對着$n説：我不是你的掌門人，你回你們" + me->query("family/family_name") + "去吧。\n", master, me);
                return 1;
        }

        // Modified by zeratul 2000-12-24
        if (me->query("combat_exp") <= 1000)
        {
                message_vision(WHT"$N對着$n説：你學藝未精，不宜下山。\n"NOR, master, me);
                return 1;
        }

        if ( me->query("quest/book") && !me->query( "quest/book/finished" ) )
        {
                if (time() < (int)me->query("quest/book/time") )
                {
                        message_vision("$N對着$n説：我不是叫你去取" + me->query("quest/book/book") + "，怎麼空手回來了！？\n", master, me);
                        return 1;
                }
                else
                {
                        message_vision( CYN"$N對着$n説：你跑到哪裏閒逛去了？這次可要小心在意些！\n"CYN, master, me );
                        quest_failed( me, "book" );
                }
        }

        dir = get_dir("/d/");
        i = random(sizeof(dir));
        file = get_dir("/d/"+dir[i]+"/");
        j = random(sizeof(file));
        if (
                sizeof(file[j]) < 2 ||
                file[j][sizeof(file[j])-2..sizeof(file[j])-1] != ".c" ||
                dir[i]=="gaibang" ||
                dir[i]=="gaochang" ||
    dir[i]=="gumu"        ||
    dir[i]=="taohua" ||
    dir[i]=="heizhao" ||
    dir[i]=="shenlong" ||
    dir[i]=="wanjiegu" ||
    dir[i]=="yanziwu" ||
                dir[i]=="death" ||
                dir[i]=="wizard" ||
                dir[i]=="working" ||
                dir[i]=="binghuo" ||
                dir[i]=="xiakedao" ||
                dir[i]=="npc")
        {
                message_vision("$N對着$n説：本門祕籍？不是好好的麼？\n", master, me);
                return 1;
        }
        if(!( room = find_object("/d/"+dir[i]+"/"+file[j]) ))
                room = load_object("/d/"+dir[i]+"/"+file[j]);
        if (room->query_max_encumbrance() < 10000000
        || !mapp(room->query("exits")) //add by qingyun
        || room->query("no_quest")                //add by qingyun
)
        {
                message_vision("$N對着$n説：等等吧，等我回頭清點一下看看。\n", master, me);
                return 1;
        }
        book = new("/clone/quest/questbook");
        book ->set("name", me->query("family/family_name")+"祕籍");
        book ->set("owner", me->query("id"));
        book->move(room);
        command("qst "+book->query("name")+"在"+room->query("short")+"(/d/"+dir[i]+"/"+file[j]+")。\n");

        message_vision("$N對着$n説：本門祕籍流落江湖，聽説最近在" + to_chinese(dir[i]) + "一帶出現。你去把它取回來吧？\n", master, me);
        me->set("quest/book/book", book->query("name"));
        me->set("quest/book/family", me->query("family/family_name"));
        me->set("quest/book/time", time() + 500 );
        me->set("quest/book/dest", to_chinese(dir[i]) );
        me->delete( "quest/book/finished" );
        return 1;
}
int accept_quest_book(object me, object obj)
{
        object master = this_object();
        int exp, pot, score, num, times, e_bonus, p_bonus, s_bonus;
        int cost;

        me = this_player();
        if (me->query("family/family_name") !=
                master->query("family/family_name"))
        {
                message_vision("$N對着$n説：我不是你的掌門人，你回你們" + me->query("family/family_name") + "去吧。\n", master, me);
                return 1;
        }
        if (obj->query("owner") != me->query("id"))
        {
                message_vision("$N對着$n説：這不是我要你找的書。\n",master,me);
                return 1;
        }
        if ( !me->query("quest/book") || me->query( "quest/book/finished" ) )
        {
                message_vision("$N對着$n説：我沒要這書，你去哪裏拿來的！\n", master, me);
                destruct(obj);
                return 1;
        }
        if (time() - (int)me->query("quest/book/time") > 1500 )
        {
                message_vision("$N對着$n説：你平時練功勤奮點，就不必去這麼久了！下次努力點！\n", master, me);
                destruct(obj);
                quest_failed( me, "book" );
                return 1;
        }
        destruct(obj);

        num=(int)me->query("perform/number")+1;
        if (num<4) times=num;
        else times=4;

        e_bonus = 100 + random( 50 );
        cost = time() - ((int)me->query("quest/book/time")-500); //花了多少時間完成

        e_bonus += e_bonus * cost /250; // cost 最高1500  也就是四倍
        p_bonus = 12 + random( e_bonus / 8 );
        s_bonus = random(10)+ 10 * times;

        me->add("combat_exp",e_bonus);
        me->add("potential",p_bonus);
        me->add("family/fealty",s_bonus);
        me->set_temp("prize_reason","祕籍");
        me->set_temp("can_give_prize",1);
        me->set_temp("prize_exp",e_bonus);
        me->set_temp("prize_pot",p_bonus);
        me->add("family/gongxian",1);


        message_vision("$N對着$n説：本門祕籍？不錯，你為本門立了一大功！\n", master, me);
        tell_object(me,HIW + "你這次行走江湖，獲得了" + chinese_number(e_bonus) + "點實戰經驗，" + chinese_number(p_bonus) + "點潛能，增長了" + chinese_number(s_bonus) + "點師門忠誠。\n"NOR);

        quest_finished( me, "book" );
        return 1;
}
//////////祕籍結束//////////
//////////開始叛徒任務 ////////////
object create_betrayer(object me)
{
        mapping name, hp_status, skill_status, map_status, prepare_status;
        string *sname, *mname, *pname;
        object room, obj, weapon, armor, master = this_object();
        object *inv;
        string weapon_type;
        mapping skl;
        string *skillname;
        int skilllvl;
  int i,j;

  seteuid(getuid());
        obj = new("/clone/quest/questman");
        obj ->set("owner", me->query("id"));
        obj ->set("quest", "betrayer");
        if (random(2) == 0)
        {
                name = NAME_D->woman_name();
                obj->set("gender", "女性");
        }
        else
        {
                name = NAME_D->man_name();
                obj->set("gender", "男性");
        }

//        obj->set("name", name["name"],({name["id"]}));
        obj->set_name(name["name"],({me->query("id")+"'s betrayer",name["id"],"betrayer"}));
        hp_status = me->query_entire_dbase();
        obj->set("str", hp_status["str"]);
        obj->set("int", hp_status["int"]);
        obj->set("con", hp_status["con"]);
        obj->set("dex", hp_status["dex"]+random(20));
        obj->set("age", hp_status["age"]+2);

        obj->set("max_jing",  hp_status["max_jing"]);
        obj->set("eff_jing",  hp_status["max_jing"]);
        obj->set("jing",      hp_status["max_jing"]);
        obj->set("max_qi",    hp_status["max_qi"]*3/2);
        obj->set("eff_qi",    hp_status["max_qi"]*3/2);
        obj->set("qi",              hp_status["max_qi"]*3/2);
        obj->set("max_neili", hp_status["max_neili"]);
        obj->set("neili",     hp_status["max_neili"]);
        obj->set("jiali",     hp_status["max_neili"]/20);
        obj->set("combat_exp",hp_status["combat_exp"]*5/4+100);
/* 1000萬以上玩家，在此長正氣或戾氣 */
        if(me->query("combat_exp") > 100000000)
                        obj->set("shen", -1 * master->query("shen_type") * obj->query("combat_exp") / 2000);
/* skill */
        skl = me->query_skills();
        skilllvl =10;
        if (sizeof(skl))
        {
                skillname = sort_array( keys(skl), (: strcmp :) );
                for (j=0; j<sizeof(skl); j++)
                {
                        if (skilllvl < skl[skillname[j]])
                                skilllvl = skl[skillname[j]];
                }
        }

        if ( mapp(skill_status = master->query_skills()) )
        {
                skill_status = master->query_skills();
                sname = keys(skill_status);

                for(i=0; i<sizeof(skill_status); i++)
                {
                        obj->set_skill(sname[i], skilllvl*11/10-20);
                }
        }
/* skill map*/
        if ( mapp(map_status = master->query_skill_map()) )
        {
                mname = keys(map_status);

                for(i=0; i<sizeof(map_status); i++)
        {
                        obj->map_skill(mname[i], map_status[mname[i]]);
                }
        }
/* skill prepare*/
        if ( mapp(prepare_status = master->query_skill_prepare()) )
        {
                pname = keys(prepare_status);

                for(i=0; i<sizeof(prepare_status); i++)
                {
                        obj->prepare_skill(pname[i], prepare_status[pname[i]]);
                }
        }
/* weapon */
        inv = all_inventory(master);
        for ( i = 0; i < sizeof(inv); i++ )
                if( inv[i]->query("equipped") && stringp(weapon_type = inv[i]->query("skill_type")) )
                {
                        weapon = new( "/clone/weapon/" + weapon_type );
                        weapon->set("value", 0);
                        weapon->move( obj );
                        weapon->wield();
                }
/* family */
        obj->set("family/family_name",master->query("family/family_name"));
        obj->set("family/master_name",master->query("name"));
        obj->set("family/generation",(int)master->query("family/generation")+1);
        obj->set("family/title",master->query("family/title"));
        obj->set("family/master_id",master->query("id"));
        obj->set("family/enter_time",time());
        obj->set("title",master->query("family/family_name") + "第" + chinese_number((int)master->query("family/generation") + 1) + "代叛徒");
  return obj;
}
////////詢問獲得叛徒任務//////////
int party_quest_betrayer(object me)
{
        string *dir, *file, place;
        int i, j ;
  object room;
  object obj;
  object master=this_object();
//        me = this_player();

  if (!me->query("family/family_name"))
   {
                message_vision("$N對着$n説：這位"+RANK_D->query_respect(me)+"何不加入我"+master->query("family/family_name")+"？\n", master, me);
                return 1;
           }
        if (me->query("family/family_name") !=
                master->query("family/family_name"))
        {
                message_vision("$N對着$n説：我不是你的掌門人，你回你們"+me->query("family/family_name")+"去吧。\n", master, me);
                return 1;
        }
        if (me->query("combat_exp") <= 10000)
        {
                message_vision(WHT"$N對着$n説：你學藝未精，不宜下山。\n"NOR, master, me);
                return 1;
        }
        if ( islocked( me, "betrayer" ) ) return 1;
        if ( me->query("quest/betrayer") &&
                !me->query( "quest/betrayer/finished" ) )
        {
                if (time() < (int)me->query("quest/betrayer/time") )
                {
                        message_vision("$N對着$n説：我不是叫你去殺" + me->query("quest/betrayer/name") + "，怎麼空手回來了！？\n", master, me);
                        return 1;
                }
                else
                {
                        message_vision( WHT"$N對着$n説：你跑到那裏閒逛去了？\n"NOR, master, me );
                        quest_failed( me, "betrayer" );
                        me->add("qi",-(int)(me->query("qi")/10));
                }
        }


/* Move to dest place */
//先選地方 減少系統開支
        dir = get_dir("/d/");
        i = random(sizeof(dir));
        file = get_dir("/d/"+dir[i]+"/");
        j = random(sizeof(file));

        if (//strsrch(file[j], ".c") == -1 ||
                file[j][sizeof(file[j])-2..sizeof(file[j])-1] != ".c" ||
                dir[i]=="gaibang" ||
                dir[i]=="gaochang" ||
    dir[i]=="gumu"        ||
    dir[i]=="taohua" ||
    dir[i]=="heizhao" ||
    dir[i]=="shenlong" ||
    dir[i]=="wanjiegu" ||
    dir[i]=="yanziwu" ||
                dir[i]=="death" ||
                dir[i]=="wizard" ||
                dir[i]=="working" ||
                dir[i]=="binghuo" ||
                dir[i]=="xiakedao" ||
                dir[i]=="lingjiu"||
                dir[i]=="gaibang"||
                dir[i]=="npc")
        {
                message_vision("$N對着$n説：等等吧，等下山弟子回山後你再來看看。\n", master, me);
                return 1;
        }
        if(!( room = find_object("/d/"+dir[i]+"/"+file[j]) ))
                room = load_object("/d/"+dir[i]+"/"+file[j]);
        if (room->query_max_encumbrance() < 10000000
        || !mapp(room->query("exits")) //add by qingyun
        || room->query("no_quest")                //add by qingyun
                || room->query("no_fight"))
        {
                message_vision("$N對着$n説：等等吧，等下山弟子回山再看看。\n", master, me);
                return 1;
        }

        if (!master->query_temp("betrayers")) master->set_temp("betrayers", 1);
        else master->add_temp("betrayers", 1);

  obj = create_betrayer(me);

        if (!objectp(obj) || !obj->move(room))
        {
                if (objectp(obj))        destruct(obj);
                message_vision("$N對着$n説：等等吧，等下山弟子回山再看看。\n", master, me);
           return 1;
        }
        command("qst "+obj->query("name")+"("+obj->query("id")+")"+"在"+room->query("short")+"(/d/"+dir[i]+"/"+file[j]+")。\n");
        message_vision("$N對着$n説：本門歸山弟子回報，本門叛徒" + obj->query("name") + "在" + to_chinese(dir[i]) + "一帶出沒。你敢去把這叛徒的人頭給我取回來麼？\n", master, me);
        me->set("quest/betrayer/name", obj->query("name"));
        me->set("quest/betrayer/family", obj->query("family/family_name"));
        me->set("quest/betrayer/time", time() + 500);
        me->set("quest/betrayer/dest", to_chinese(dir[i]));
        me->set("quest/betrayer/obj", obj );
        me->delete("quest/betrayer/finished");
        return 1;
}
///////完成叛徒任務、獎勵///////
int accept_quest_betrayer(object me, object obj)
{
        object master = this_object();
        int exp, pot, score, num, times, e_bonus, p_bonus, s_bonus;
        int cost;

        me = this_player();

        if (me->query("family/family_name") !=
                master->query("family/family_name"))
        {
                message_vision("$N對着$n説：我不是你的掌門人，你回你們" + me->query("family/family_name") + "去吧。\n", master, me);
                return 1;
        }
        if ( islocked( me, "betrayer" ) ) return 1;
        if ( !me->query( "quest/betrayer" ) ||
                me->query( "quest/betrayer/finished" ) )
                return 0;
        if (obj->query("userp") == 1)
        {
                message_vision(HIR "$N對着$n説：我叫你殺叛徒，你卻去殺玩家！去死吧你！\n"NOR, master, me);
                destruct(obj);
                quest_failed( me, "betrayer" );
                me->delete_temp("mebetrayernum");
                master->kill_ob(me);
                return 1;
        }
        if (obj->query("quest") != "betrayer" )
        {
                message_vision( HIR"$N對着$n説：我叫你殺叛徒，你卻濫殺無辜，矇蔽師長！去死吧你！\n"NOR, master, me);
                destruct(obj);
                quest_failed( me, "thief" );
                me->delete_temp("methiefnum");
                me->delete_temp("mebetrayernum");
                master->kill_ob(me);
                return 1;
        }
        master->add_temp("betrayers", -1);
        destruct(obj);

        num=(int)me->query("perform/number")+1;
        if (num<4) times=num;
        else times=4;

        cost = time() - ((int)me->query("quest/betrayer/time")-500); //花了多少時間完成

//  e_bonus = 200 + random( 200 );
                e_bonus = 200 + random( 100 );
    e_bonus += 50*me->query_temp("mebetrayernum");
    e_bonus += e_bonus * cost / 1200; // 叛徒1200秒就會自動跑走
//        p_bonus = (int)random(e_bonus/4)+35;
    p_bonus = (int)random(e_bonus/2)+35;
          s_bonus = random(10)+ 15* times;
    me->add("combat_exp",e_bonus);
    me->add("potential",p_bonus);
    me->add("family/fealty",s_bonus);
    me->add("family/gongxian",1);
        me->set_temp("prize_reason","叛徒");
        me->set_temp("can_give_prize",1);
        me->set_temp("prize_exp",e_bonus);
        me->set_temp("prize_pot",p_bonus);

        message_vision("$N對着$n説：叛徒的人頭？不錯，你為本門清理了門户！\n", master, me);
        tell_object(me,HIW + "你經過這次拼殺，獲得了" + chinese_number(e_bonus) + "點實戰經驗，" + chinese_number(p_bonus) + "點潛能，增長了" + chinese_number(s_bonus) + "點師門忠誠。\n"NOR);

        me->add_temp("mebetrayernum",1);

        if ((int)me->query_temp("mebetrayernum") == 10)
        {
                me->add("score", 3000);
                me->delete_temp("mebetrayernum");
                me->set_temp("family_can_qiecuo",1);

                message_vision(HIW "$N對着$n笑道：你在外遊歷期間，為師閉關參悟，近日出關，武學修為又有所突破！\n", master, me);
                tell_object(me,HIM +"你現在有機會與"+ master->query("name")+"切磋 ( qiecuo )武學。\n"NOR);
        }

        quest_finished( me, "betrayer" );

        return 1;
}


//取消任務
int cancle_quest_betrayer( object me )
{
        object master = this_object();

        if ( !me->query( "quest/betrayer" ) || me->query( "quest/betrayer/finished" ) )
                return 0;
        if ( me->query( "quest/betrayer/lock" ) )
        {
                tell_object( me, "你已經取消任務了！\n" );
                return 1;
        }
        lock_quest( me, "betrayer", "book" );
        message_vision( "$N對$n説道：那你就幫我找找祕籍吧。\n", master, me );
        return 1;
}
/////叛徒結束//////////////

/////////開始奸細任務////////
object create_thief( object me )
{
        mapping name, hp_status, skill_status, map_status, prepare_status;
        string *sname, *mname, *pname;
        object obj, thief_master, weapon;
        mapping skl;
        string *skillname;
        int skilllvl,topexp;
        int inc_exp,inc_lvl,i,j,k;
        object *inv;
        string *family, weapon_type;
        string *masters = ({
        "baituo/ouyangfeng",        //lingshe-zhangfa        shexing-diaoshou hamagong
        "dali/duanzc",        //duanyun-fu                sun-finger
        "dali/daobaifeng",        //feifeng-whip                jinyu-quan         wuluo-zhang
        "dali/yideng",        //duanjia-sword                six-finger
        "emei/miejue",        //huifeng-jian                jinding-zhang         tiangang-zhi
        "emei/feng",         //yanxing-dao                jinding-zhang         tiangang-zhi
        "gaibang/hong",                //dagou-bang                xianglong-zhang        suohou-hand
        "gaibang/jian",                //fengmo-staff                jianlong-zaitian
        "gumu/longnv",        //yunv-jian                meinv-quan
        "gumu/limochou",        //qiufeng-chenfa        meinv-quan
        "gumu/yangguo",        //xuantie-sword                anran-zhang
        "heimuya/dongfang",        //bixie-jian                xuantian-zhi
        "heimuya/ren",                //wuyun-jian                xuantian-zhi
        "heimuya/weng",                //shigu-bifa                xuantian-zhi
        "hengshan/xian",                //hengshan-jian                tianchang-zhang        chuanyun-shou
        "henshan/moda",                //hengshan-sword        biluo-zhang        luoyan-hand
        "honghua/chen-jialuo",        //luohua-jian                benlei-shou        baihua-cuoquan
        "honghua/wu-chen",        //zhuihun-jian                benlei-shou
        "huashan/yue-buqun",        //huashan-sword                huashan-ken
        "huashan/feng-buping",        //kuangfeng-jian        poyu-quan        hunyuan-zhang
        "huashan/feng",                //lonely-sword                poyu-quan        hunyuan-zhang
        "kunlun/hezudao",        //liangyi-sword                kunlun-strike
        "kunlun/hetaichong",        //xunlei-sword                zhentian-cuff        chuanyun-leg
        "lingjiu/tonglao",        //tianyu-qijian                liuyang-zhang        zhemei-shou
        "lingxiao/bai",                //xueshan-sword                snow-strike
        "lingxiao/shipopo",        //jinwu-blade                snow-strike
        "mingjiao/zhangwuji",        //shenghuo-ling                qishang-quan
        "mingjiao/yintianzheng",        //lieyan-dao                sougu
        "mingjiao/weiyixiao",        //liehuo-jian                hanbing-mianzhang
        "murong/murong-fu",        //murong-sword                canhe-finger        xingyi-strike
        "nanshaolin/tianhong",        //weituo-chu                jingang-cuff
        "nanshaolin/tianjing",        //riyue-whip                wuxiang-finger
        "qingcheng/yu",                //songfeng-jian                wuying-leg        cuixin-strike
        "quanzhen/wang",                //quanzhen-jian                chunyang-quan        haotian-zhang
        "quanzhen/ma",                //duanyun-bian                chunyang-quan        haotian-zhang
        "shaolin/da-mo",        //                        nianhua-zhi        sanhua-zhang
        "shaolin/xuan-nan",        //wuchang-zhang                yizhi-chan  banruo-zhang
        "shaolin/du-nan",        //riyue-bian                jingang-quan
        "shenlong/hong",                //ruyi-hook                yingxiong-sanzhao        shenlong-bashi
        "shenlong/su",                //meiren-sanzhao        jueming-leg        huagu-mianzhang
        "shenlong/pang",                //shenlong-staff        huagu-mianzhang        jueming-leg
        "songshan/zuo",                //songshan-sword        songyang-strike        poyun-hand
        "taishan/tianmen",        //taishan-sword                kuaihuo-strike
        "taohua/huang",        //yuxiao-jian                tanzhi-shentong        lanhua-shou
        "taohua/lu",                //luoying-shenjian        xuanfeng-leg        luoying-zhang
        "tiezhang/qqren",        //                        tiezhang-zhangfa
        "tiezhang/qqzhang",        //tiexue-qiang                zhusha-zhang
        "wudang/zhang",        //taiji-jian                taiji-quan
        "wudang/yu",                //liangyi-jian                taiji-quan
        "wudujiao/hetieshou",        //wudu-goufa                wudu-zhang        qianzhu-wandushou
        "xiaoyao/xiaoyaozi",        //ruyi-dao                zhemei-shou        liuyang-zhang
        "xingxiu/ding",                //                        chousui-zhang        sanyin-wugongzhao
        "xingxiu/chuchen",        //tianshan-zhang        chousui-zhang        sanyin-wugongzhao
        "xueshan/jiumozhi",        //                        huoyan-dao
        "xueshan/fawang",        //riyue-lun                dashou-yin        yujiamu-quan
        "xueshan/xuedao",        //xue-dao                dashou-yin
        "yunlong/chen",                //yunlong-jian                yunlong-zhua        yunlong-shou
                });

        seteuid(getuid());
        obj = new("/clone/quest/questjianxi");
        obj ->set("owner", me->query("id"));
        obj ->set("quest", "thief");
        if (random(2) == 0)
        {
                name = NAME_D->woman_name();
                obj->set("gender", "女性");
        }
        else
        {
                name = NAME_D->man_name();
                obj->set("gender", "男性");
        }

        hp_status = me->query_entire_dbase();
        obj->set("fname", name["name"]);
        obj->set("str", hp_status["str"]);
        if (obj->query("str")<me->query_str()-20)
                obj->set("str",me->query_str()-20);
        obj->set("int", hp_status["int"]);
        obj->set("con", hp_status["con"]);
        obj->set("dex", hp_status["dex"]+ 10);
        if (obj->query("dex")<me->query_dex()-20)
                obj->set("dex",me->query_dex()-20);
        obj->set("age", hp_status["age"]+2);

        if ((hp_status["max_qi"]*2)<1500)
        {
                obj->set("max_qi", 1500);
                obj->set("eff_qi", 1500);
                obj->set("qi",     1500);
        }
        else
        {
                obj->set("max_qi", hp_status["max_qi"]*2);
                obj->set("eff_qi", hp_status["max_qi"]*2);
                obj->set("qi",     hp_status["max_qi"]*2);
        }
        if (hp_status["max_jing"]*3/2 < obj->query("max_qi")/4)
        {
                obj->set("max_jing",  obj->query("max_qi")/4*3/2);
                obj->set("eff_jing",  obj->query("max_qi")/4*3/2);
                obj->set("jing",      obj->query("max_qi")/4*3/2);
        }
        else {
                obj->set("max_jing",  hp_status["max_jing"]*3/2);
                obj->set("eff_jing",  hp_status["max_jing"]*3/2);
                obj->set("jing",      hp_status["max_jing"]*3/2);
        }


        if ((hp_status["max_neili"])<1500)
                obj->set("max_neili",1500);
        else
                obj->set("max_neili", hp_status["max_neili"]);

        if((hp_status["neili"]) < hp_status["max_neili"])
                obj->set("neili", hp_status["max_neili"]);
        else  obj->set("neili", hp_status["neili"]);
        if (obj->query("neili") < 1500) obj->set("neili",1500);
        obj->set("jiali",     hp_status["neili"]/20);

        topexp = (int) me->query("combat_exp");
        inc_exp = ( topexp*2 - topexp ) / 11;
        topexp = topexp + inc_exp * ((int) me->query_temp("methiefnum")-1);
        obj->set("combat_exp", topexp + 100);

/* skill */
        skl = me->query_skills();
        skilllvl=100;
        if (sizeof(skl))
        {
                skillname = sort_array( keys(skl), (: strcmp :) );
                for (j=0; j<sizeof(skl); j++)
                {
                        if (skilllvl < skl[skillname[j]])
//                                skilllvl = skl[skillname[j]]*4/5 + skl[skillname[j]]*((int) me->query_temp("methiefnum")-1)*2/55;
                                skilllvl = skl[skillname[j]];
                }
                inc_lvl = ( skilllvl - skilllvl * 4/5 ) / 11;
                skilllvl = skilllvl - inc_lvl *((int) me->query_temp("methiefnum")-1);
        }

        i = random( sizeof(masters) );
        thief_master = new ( "/kungfu/class/"+masters[i] );

        if ( mapp(skill_status = thief_master->query_skills()) )
        {
                skill_status = thief_master->query_skills();
                sname = keys(skill_status);

                for(i=0; i<sizeof(skill_status); i++)
                {
                        obj->set_skill(sname[i], skilllvl);
                }
        }
/* skill map*/
        if ( mapp(map_status = thief_master->query_skill_map()) )
        {
                mname = keys(map_status);

                for(i=0; i<sizeof(map_status); i++)
                {
                        obj->map_skill(mname[i], map_status[mname[i]]);
                }
        }
/* skill prepare*/
        if ( mapp(prepare_status = thief_master->query_skill_prepare()) )
        {
                pname = keys(prepare_status);

                for(i=0; i<sizeof(prepare_status); i++)
                {
                        obj->prepare_skill(pname[i], prepare_status[pname[i]]);
                }
        }

        inv = all_inventory(thief_master);
        for ( i = 0; i < sizeof(inv); i++ )
                if( inv[i]->query("equipped") && stringp(weapon_type = inv[i]->query("skill_type")) )
                {
                        weapon = new( "/clone/weapon/" + weapon_type );
                        weapon->set("value", 0);
                        weapon->move( obj );
                        weapon->wield();
                }
        obj->set( "family_name", thief_master->query("family/family_name") );
/* 1000萬以上玩家，在此長正氣或戾氣 */
        if(me->query("combat_exp") > 100000000)
                        obj->set("shen", -1 * thief_master->query("shen_type") * obj->query("combat_exp") / 2000);
         destruct( thief_master );
        return obj;
}

int party_quest_thief(object me)
{
        string *dir, *file, place;
        int i, j, k;
        string err;
        object room, obj, master = this_object();

        me = this_player();
  if (!me->query("family/family_name"))
   {
                message_vision("$N對着$n説：這位"+RANK_D->query_respect(me)+"何不加入我"+master->query("family/family_name")+"？\n", master, me);
                return 1;
           }
        if (me->query("family/family_name") !=
                master->query("family/family_name"))
        {
                message_vision("$N對着$n説：我不是你的掌門人，你回你們"+me->query("family/family_name")+"去吧。\n", master, me);
                return 1;
        }

        if (me->query("combat_exp") <= 100000)
        {
                message_vision(WHT"$N對着$n説：你學藝未精，無能鋤奸。\n"NOR, master, me);
                return 1;
        }

        if ( islocked( me, "thief" ) )
        {
                return 1;
        }

        if ( me->query("quest/thief") && !me->query( "quest/thief/finished" ) )
        {
                if (time() < (int)me->query("quest/thief/time") )
                {
                        message_vision("$N對着$n説：怎麼樣，奸細"+ me->query("quest/thief/name")+"的人頭呢！？\n", master, me);
                        return 1;
                }
                else
                {
                        message_vision( CYN"$N對着$n説：你跑到哪裏閒逛去了？這次可要小心在意些！\n"NOR, master, me );
                        quest_failed( me, "thief" );
                        if ((int)me->query_temp("methiefnum")>1)
                                me->add_temp("methiefnum",-1);
                        else
                                me->delete_temp("methiefnum");
                        me->add("qi",-(int)(me->query("qi")/10));
                }
        }

/* Move to dest place */
        dir = get_dir("/d/");
//        for (i = 0; i < sizeof(dir); i++)
// 為了照顧南少林(shaolin是nanshaolin字符串的子集)，所以從後讀起
        for (i = sizeof(dir)-1; i >= 0; i--)
        {
                if (strsrch(master->query("startroom"), dir[i]) >= 0)
                        k = i;
        }
        file = get_dir("/d/"+dir[k]+"/");
        j = random(sizeof(file));

        if (sizeof(file[j]) < 2 ||
                file[j][sizeof(file[j])-2..sizeof(file[j])-1] != ".c" )
        {
                message_vision("$N對着$n説：等等吧，等下山弟子回山後你再來看看。\n", master, me);
                return 1;
        }
        if(!( room = find_object("/d/"+dir[k]+"/"+file[j]) ))
                room = load_object("/d/"+dir[k]+"/"+file[j]);

        if (room->query_max_encumbrance() < 10000000
                || !mapp(room->query("exits")) //add by qingyun
        || room->query("no_quest")                //add by qingyun
)
        {
                message_vision("$N對着$n説：等等吧，等下山弟子回山再看看。\n", master, me);
                return 1;
        }
        err = catch(obj = create_thief( me ));
        if (stringp(err))
        {
                tell_object(find_player("qingyun"),"出錯。\nerr="+err);
                return 1;
        }
  if (!obj ||
   obj->query("family_name") == me->query("family/family_name") ||
  !obj->move(room))
   {
           if (objectp(obj)) destruct(obj);
           message_vision("$N對着$n説：我這裏有點事要忙，等會兒我再看看吧。\n", master, me);
    return 1;
   }
        if (!master->query_temp("thiefs")) master->set_temp("thiefs", 1);
        else master->add_temp("thiefs", 1);
        if (!me->query_temp("methiefnum"))
                me->set_temp("methiefnum",1);


        me->set("quest/thief/name", obj->query("fname"));
        me->set("quest/thief/family", obj->query("family/family_name"));
        me->set("quest/thief/time", time() + 300 );
        message_vision("$N對着$n説：本門弟子回報，我派周圍有陌生人出現。你去查看一下是不是別派的奸細？\n", master, me);
        me->set( "quest/thief/obj", obj );
        me->delete( "quest/thief/finished" );
        command("qst "+obj->query("name")+"在"+room->query("short")+"(/d/"+dir[k]+"/"+file[j]+")。\n");
//        obj->move(room);
        return 1;
}

int accept_quest_thief(object me, object obj)
{
        object master = this_object();
        int num, times, e_bonus, p_bonus, s_bonus, lastfealty;
        int cost;

        me = this_player();
        if (me->query("family/family_name") !=
                master->query("family/family_name"))
        {
                message_vision("$N對着$n説：我不是你的掌門人，你回你們"+me->query("family/family_name")+"去吧。\n", master, me);
                return 1;
        }
        if ( islocked( me, "thief" ) )
                return 1;

        if ( !me->query( "quest/thief" ) || me->query( "quest/thief/finished" ))
                return 0;

        if (obj->query("userp") == 1)
        {
                message_vision( HIR"$N對着$n説：我叫你殺奸細，你卻去殺玩家！去死吧你！\n"NOR, master, me);
                destruct(obj);
                quest_failed( me, "thief" );
                me->delete_temp("methiefnum");
                master->kill_ob(me);
                return 1;
        }

        if (obj->query("quest") != "thief" )
        {
                message_vision( HIR"$N對着$n説：我叫你殺奸細，你卻濫殺無辜，矇蔽師長！去死吧你！\n"NOR, master, me);
                destruct(obj);
                quest_failed( me, "thief" );
                me->delete_temp("methiefnum");
                master->kill_ob(me);
                return 1;
        }

        master->add_temp("thiefs", -1);
        destruct(obj);

        num=(int)me->query("perform/number")+1;
        if (num<4) times = num;
        else times = 4;

        cost = time() - ((int)me->query("quest/thief/time")-300); //花了多少時間完成

        e_bonus = (int)me->query_temp("methiefnum");
        e_bonus = e_bonus*100 + 200 + random(50);
        if (e_bonus > 1500)
                e_bonus = 1250+random(250);
  e_bonus += e_bonus* cost / 1200;
  e_bonus -= e_bonus/3;

        p_bonus = (int)random(e_bonus/10)+100;
        s_bonus = random(10) + 15 * times;

        me->add("combat_exp", e_bonus);
        me->add("potential", p_bonus);
        me->add("family/fealty", s_bonus);
        me->add("family/gongxian",1);
        me->set_temp("prize_reason","奸細");
        me->set_temp("can_give_prize",1);
        me->set_temp("prize_exp",e_bonus);
        me->set_temp("prize_pot",p_bonus);

        message_vision("$N對着$n説：奸細的人頭？不錯，你為本門立一大功！\n", master, me);
        tell_object(me, HIW + "經過這番歷練，你獲得了" + chinese_number(e_bonus) + "點實戰經驗，" + chinese_number(p_bonus) + "點潛能，增長" + chinese_number(s_bonus) + "點師門忠誠。\n"NOR);

        me->add_temp("methiefnum",1);

        if ((int)me->query_temp("methiefnum") == 13)
        {
                me->delete_temp("methiefnum");
                p_bonus = 1300+ random(100);

                me->add("potential",p_bonus);
                me->add("score", 4000);
                message_vision(HIW "$N對着$n笑道：哈哈哈！真乃可塑之才也，為本門屢立奇功呀！\n"NOR, master, me);
                tell_object(me,HIM + master->query("name")+"嘉獎了你："        + chinese_number(p_bonus) + "點潛能，\n"NOR);
        }

        quest_finished( me, "thief" );

        return 1;
}

int cancle_quest_thief( object me )
{
        object master = this_object();

        if( !me->query( "quest/thief" ) || me->query( "quest/thief/finished" ) )
                return 0;
        if( me->query( "quest/thief/lock" ) )
        {
                tell_object( me, "你已經取消任務了！\n" );
                return 1;
        }
        lock_quest( me, "thief", "betrayer" );
        message_vision( "$N對着$n説：還是先把本門叛徒剷除乾淨再管別的事吧。\n", master, me );
        me->delete_temp("methiefnum");

        return 1;
}
/////////奸細任務結束////////////
int party_quest_kill(object me)
{
        object killer, room, master = this_object();
        string place;
        int i,j;
        int level;
        int t;

        me = this_player();

        if (master->query("eff_qi") * 2 < master->query("max_qi") ||
                master->query("qi") * 2 < master->query("max_qi"))
        {
                message_vision(HIC "$N" HIC "捂着胸口，一副非常痛苦的樣子，對你的"
                               "話顯然沒有聽進去。\n" NOR, me);
                return 1;
        }

  if (!me->query("family/family_name"))
  {
                message_vision("$N對着$n説：這位"+RANK_D->query_respect(me)+"何不加入我"+master->query("family/family_name")+"？\n", master, me);
                return 1;
         }

        if (me->query("family/family_name") !=
                master->query("family/family_name"))
        {
                message_vision("$N對着$n説：我不是你的掌門人，你回你們" + me->query("family/family_name") + "去吧。\n", master, me);
                return 1;
        }

        if (me->query("combat_exp") <= 1000)
        {
                message_vision(WHT"$N對着$n説：你學藝未精，不宜下山。\n"NOR, master, me);
                return 1;
        }

        if ( me->query("quest/kill") && !me->query( "quest/kill/finished" ) )
        {
                        message_vision("$N對着$n説：我不是叫你在"HIY+CHINESE_D->chinese_monthday(((me->query("quest/kill/time")-1270000000)*365))+NOR"之前殺了" + me->query("quest/kill/name") + "，現在是"HIY+CHINESE_D->chinese_monthday(((time()-1270000000)*365))+NOR"，我要的人頭呢！？\n", master, me);
                        return 1;
        }

        if (me->query("shen")>0 && master->query("shen")<0)
        {
                message_vision(CYN "$N" CYN "大怒道：豈有此理！才幾天不見，"
                  "你居然也學起假仁假義來了，快給我滾！\n"
                   NOR, master, me);
    return 1;
        }

        if (me->query("shen")<0 && master->query("shen")>0)
        {
                message_vision(CYN "$N" CYN "大怒道：豈有此理！你居然已經誤"
                  "入歧途，還敢來見我！\n" NOR, master, me);
    return 1;
        }

        level = me->query_temp("quest/next_level");
        if (level < 0 || level > 3)        level = 0;

        killer = new("/clone/quest/killer");
        killer ->set("owner", me->query("id"));
        killer ->set("level", level);
        NPC_D->copy_skill(killer); //無參數則隨機取門派
        NPC_D->init_npc_skill(killer,NPC_D->check_level(me));//按經驗拷貝等級
        NPC_D->copy_status(killer,me,100); //拷貝狀態百分率

        if (killer->query("combat_exp")<1000000)
                killer->set("neili",killer->query("max_neili"));
        else if (killer->query("combat_exp")<3000000)
                killer->set("neili",killer->query("max_neili")*3/2);
        else
                killer->set("neili",killer->query("max_neili")*2);

        killer->add_temp("apply/attack", killer->query_skill("force") * (level - 1) * 2 / 15);
        killer->add_temp("apply/dodge",  killer->query_skill("force") * (level - 1) * 2 / 15);
        killer->add_temp("apply/parry",  killer->query_skill("force") * (level - 1) * 2 / 15);
        killer->add_temp("apply/damage", 5 + level * 7);
        killer->add_temp("apply/unarmed_damage", 5 + level * 7);
        killer->add_temp("apply/armor", 10 + level * 15);

        if (me->query("combat_exp") > 1000000)
                NPC_D->set_perform(killer);
        if (me->query("combat_exp")<2000000)
                NPC_D->place_npc(killer,0);
        else
                NPC_D->place_npc(killer,1);

        room = environment(killer);
        place = to_chinese(killer->query("place"));
        command("qst "+killer->query("name")+"("+killer->query("id") +")"+"在"+room->query("short")+"("+file_name(room)+")。\n");

                message("vision", WHT + master->name() + WHT "小聲的對" + me->name() +
                                  WHT "吩咐着什麼，" + me->name() +
                                  WHT "一邊聽，一邊不住的點頭。\n" NOR,
                                          environment(me), ({ me }));
                if (master->query("shen")>0)
                {
                        killer->set("shen", -killer->query("combat_exp") / 2000);
                        if (master->query("family/family_name") == "少林派")
                                tell_object(me, CYN + master->name() + CYN "對你道：雖"
                                                 "然我們出家人以慈悲為懷，但是對於大"
                                                 "兇大惡之徒也不能放過。\n最近" NOR +
                                                 HIR + killer->name() +"("+killer->query("id") +")"+NOR + CYN "在" +
                                                 place + "作惡多端，你去把他除了，提頭來見。\n" NOR);
                        else
                                tell_object(me, CYN + master->name() + CYN"對你道：" NOR
                                                 + HIR + killer->name() +"("+killer->query("id") +")"+ NOR + CYN "這個"
                                                 "敗類打家劫舍，無惡不作，\n聽説他最近"
                                                 "在" + place +        "，你去除掉他，提頭來見我。\n" NOR);
                } else
                if (master->query("shen")<0)
                {
                        killer->set("shen", killer->query("combat_exp") / 2000);
                        tell_object(me, CYN + master->name() + CYN "對你道：" NOR + HIR
                                         + killer->name() +"("+killer->query("id") +")"+ NOR + CYN "這個所謂大俠屢次"
                                         "和我派作對，\n聽説他最近在" + place + "，你"
                                         "去宰了他，提頭來見！\n" NOR);
                } else
                {
                        killer->set("shen_type", 0);
                        killer->set("shen", 0);
                        tell_object(me, CYN + master->name() + CYN "對你説道：我早就看"
                                         NOR + HIR + killer->name() +"("+killer->query("id") +")"+ NOR + CYN "不順眼"
                                         "，\n聽説他最近在" + place + "，你去做了他，帶他的人頭來交差！\n" NOR);
                }
                switch (level)
                {
                case 0:
                        message_vision(CYN "$N" CYN "頓了頓，又對$n" CYN "道：這個"
                                       "事情容易辦得很，你要是還辦不成那可不象話。"
                                       "\n" NOR, master, me);
                        break;
                case 1:
                        break;
                case 2:
                        message_vision(CYN "$N" CYN "看了看$n" CYN "又道：這個事情"
                                       "很是有些難辦，你要是不行我就另找人吧。\n"
                                       NOR, master, me);
                        break;
                case 3:
                        message_vision(CYN "$N" CYN "歎了口氣，鄭重的對$n" CYN "道"
                                       "：這次任務兇險得緊，你不要勉強自己，不行就"
                                       "算了。\n" NOR, master, me);
                        break;
                }
        me->set("quest/kill/level", level);
        me->set("quest/kill/master_name", master->name());
        me->set("quest/kill/master_id", master->query("id"));
        me->set("quest/kill/id", killer->query("id"));
        me->set("quest/kill/name", killer->name());
        me->set("quest/kill/place", place);
        t = time() +4 * ONE_DAY - 1; // 三分鐘一個 one day
        me->set("quest/kill/time", t );
        message("vision", WHT + master->name() + WHT "在你耳邊悄聲説道：你務必要在"
                          NOR + HIY + CHINESE_D->chinese_monthday(((t-1270000000)*365)) + NOR + WHT
                                  "之前完成！\n" NOR, me);
        me->delete( "quest/kill/finished" );
        return 1;
}
int cancle_quest_kill(object who)
{
        mapping dbase;
        mapping q;
        object ob;
        string msg;
        int n;
        int g;

        object me = this_object();
        dbase = who->query_entire_dbase();

        if (! mapp(q = dbase["quest"]["kill"]) ||
            q["master_name"] != me->name())
                {
                        message_vision("$N説道：我沒給你什麼任務啊？mapp(q)="+mapp(q)+"\n",me,who);
                        return 1;
                }

                if (q["notice"] == "die")
                {
                        message_vision(CYN "$N" CYN "點點頭，對$n" CYN "道：算了，聽説這人"
                                       "已經被殺了，你不用再辛苦了。\n" NOR, me, who);
                } else
                {
                        message_vision(CYN "$N" CYN "擺擺手，對$n" CYN "道：你幹不了就算了"
                                       "，讓別人做吧！\n" NOR, me, who);
                        who->delete("quest_num/kill");
                }

                    who->delete_temp("quest/next_level");
                n = (40 + random(40) + NPC_D->check_level(who) * 5);
                g = (10 + random(10) + NPC_D->check_level(who));

                switch (q["level"])
                {
                case 0:
                        n *= 2;
                        break;
                case 1:
                        break;
                case 2:
                        n = 0;
                        break;
                case 3:
                        n = 0;
                        break;
                default:
                                                n = 0;
                                                break;
                }
//                if (! n) break;

                // adjust weiwang
                dbase["weiwang"] -= n;
                if (dbase["weiwang"] < 0)
                        dbase["weiwang"] = 0;
                msg = HIR "你的江湖威望受到了損失";

                // adjust gongxian
                dbase["family/gongxian"] -= g;
                if (dbase["family/gongxian"] < 0)
                        dbase["family/gongxian"] = 0;
                msg += HIR "，師門對你的信任降低了";

                // notice place
                message("vision", msg + "。\n" NOR, who);

        who->start_busy(2);

        who->delete("quest/kill");
        ob = find_living(q["id"]);
        if (! ob || ob->query_temp("owner") != who->query("id"))
                return 1;

        if (environment(ob))
                message_vision(HIC "$N" HIC "看了看四周，急急忙忙的走掉了。\n" NOR, ob);

        destruct(ob);
        return 1;
}
int accept_quest_kill(object me, object obj)
{
        object master = this_object();
        int num, times, exp ,pot ,score, fealty , gongxian;
        object *helper;
        string msg;
        int t;
        mapping q;
        int timeover;
        int bonus;
        int quest_count;
        int special;
        int type;

        me = this_player();
        if (me->query("family/family_name") !=
                master->query("family/family_name"))
        {
                message_vision("$N對着$n説：我不是你的掌門人，你回你們"+me->query("family/family_name")+"去吧。\n", master, me);
                return 1;
        }

        if ( !me->query( "quest/kill" ) || me->query( "quest/kill/finished" ))
                return 0;

        if (obj->query("userp") == 1)
        {
                message_vision( HIR"$N對着$n説：我叫你殺人，你卻去殺玩家！去死吧你！\n"NOR, master, me);
                destruct(obj);
//                quest_failed( me, "thief" );
                me->delete_temp("quest_num/kill");
                master->kill_ob(me);
                return 1;
        }

        if (obj->query("quest") != "kill" )
        {
                message_vision( HIR"$N對着$n説：我叫你殺人，你卻濫殺無辜，矇蔽師長！去死吧你！\n"NOR, master, me);
                destruct(obj);
                quest_failed( me, "kill" );
//                me->delete_temp("quest_num/kill");
                master->kill_ob(me);
                return 1;
        }

///        master->add_temp("kill", -1);
//        destruct(obj);
                q = me->query("quest/kill");
                if (! mapp(q) || ! obj->is_corpse() && ! obj->is_head())
                        return 0;

                if (! stringp(obj->query("owner")))
                {
                        message_vision(CYN "$N" CYN "捂着鼻子看了看" + obj->name()
                                       + NOR + CYN "，道：什麼臭烘烘的？快給我"
                                       "拿走。\n" NOR, master);
                        return 0;
                }

                if (obj->query("owner") != me->query("id"))
                        return 0;

                msg = CYN "$N" CYN "接過" + obj->name() + NOR + CYN "，呵呵大笑"
                      "，對$n" CYN "道：";

                if (me->query("shen")>0)
                        msg += CYN "又除了一害，很好！";
                else
                if (me->query("shen")<0)
                        msg += CYN "好極了！什麼大俠，不堪一擊！";
                else
                        msg += CYN "幹得好，漂亮！";
                msg += "\n" NOR;
                t = time();
                if (me->query_temp("quest/escape_times"))
                {
                        msg += CYN "$N" CYN "讚許道：這次沒想到敵人這麼強悍，實"
                               "在未曾料到，辛苦，辛苦！\n" NOR;
                        timeover = 0;
                } else
                if (t > q["time"])
                {
                        msg += CYN "$N" CYN "搖搖頭，又道：可惜，不是讓你" +
                               CHINESE_D->chinese_monthday(t*60) + "前做完嗎？算"
                               "了，將功補過，你先退下吧。\n" NOR;
                        timeover = 1;
                } else
                {
                        if (t - q["time"] < ONE_DAY)
                        {
                                msg += CYN "$N" CYN "點點頭道：幹得不錯，這麼"
                                       "快就完成了，好好幹！\n" NOR ;
                        } else
                                msg += CYN "$N" CYN "點點頭道：這次不錯，辛苦"
                                       "了。\n" NOR;

                        timeover = 0;
                }
                bonus = 1;
                helper = q["helper"];

                      if (!arrayp(helper) || member_array(me,helper) < 0)
                       {
                        msg += CYN "$N" CYN "又對$n" CYN "道：可惜這次"
                                "對方被人先下手殺死，努力一點，就能自己完成了！\n" NOR;
                                                type = 1;
                                               }
                                               else
                {
                        helper -= ({ me });
                        helper -= ({ 0 });
                        if (sizeof(helper)>0)
                        {
                        msg += CYN "$N" CYN "欣慰的對$n" CYN "道：這次你能夠"
                               "得到" + helper[0]->name() +
                               NOR + CYN "的幫忙，也屬不易！以後彼此要多加照"
                               "應！\n" NOR;
                                bonus = 2;
                        }
                }
                destruct(obj);

                                               exp = me->query_temp("quest_kill/combat_exp");
                                               pot = me->query_temp("quest_kill/potential");
                                               score = me->query_temp("quest_kill/score");
                                               me->delete_temp("quest_kill");

                                               exp /= bonus;
                                               pot /= bonus;
                                               score /= bonus;

                                               quest_count = me->query("quest_num/kill");
                                               if (type!=1 && (!exp || !pot || !score))
                                               {
                                                        msg += CYN "$N" CYN "又對$n" CYN "道：只可惜關鍵時刻，你"
                                                               "心存膽怯，沒有手刃對方，甚是可惜。\n"NOR;
                   bonus = 2;
                                               }
                if (quest_count == 100)
                {
                        msg += CYN "$N" CYN "哈哈大笑兩聲道：真有你的，連着上"
                               "百次任務都完成的漂漂亮亮，很好，很好。\n" NOR;
                        special = 1;
                } else
                if (quest_count == 200)
                {
                        msg += CYN "$N" CYN "大喜道：不錯不錯，真是不錯，兩百"
                               "次任務乾得很好。\n" NOR;
                        special = 1;
                } else
                if (quest_count == 300)
                {
                        msg += CYN "$N" CYN "大喜道：不錯不錯，連續三百個任務"
                               "都絲毫不出差錯，真是漂亮。\n" NOR;
                        special = 1;
                } else
                if (quest_count == 400)
                {
                        msg += CYN "$N" CYN "大喜道：真是不錯，竟然連續四百個"
                               "任務絲毫不出差錯，幹得好。\n" NOR;
                        special = 1;
                } else
                if (quest_count == 500)
                {
                        msg += CYN "$N" CYN "歎道：真是長江後浪推前浪，想不到"
                               "你接連五百次任務都無一疏漏，真是不錯！\n" NOR;
                        special = 1;
                } else
                if (quest_count == 600)
                {
                        msg += CYN "$N" CYN "歎道：真是長江後浪推前浪，想不到"
                               "你接連六百次任務都無一疏漏，漂亮之極！\n" NOR;
                        special = 1;
                } else
                if (quest_count == 700)
                {
                        msg += CYN "$N" CYN "歎道：真是長江後浪推前浪，想不到"
                               "你七百次任務竟無一疏漏，不易，不易！\n" NOR;
                        special = 1;
                } else
                if (quest_count == 800)
                {
                        msg += CYN "$N" CYN "歎道：真是長江後浪推前浪，想不到"
                               "你接連八百次任務都無一疏漏，不易之極！\n" NOR;
                        special = 1;
                } else
                if (quest_count == 900)
                {
                        msg += CYN "$N" CYN "深深地歎道：想不到你接連九百次任"
                               "務都無一疏漏，不易之極！不易之極！\n" NOR;
                        special = 1;
                } else
                if (quest_count == 1000)
                {
                        msg += CYN "$N" CYN "深深歎了口氣，道：想不到你連着一"
                               "千次任務無一失手，看來我們" +
                               me->query("family/family_name") +
                               "真是後繼有人啊！\n" NOR;
                        special = 1;
                } else
                if (quest_count > 1000)
                {
                        me->set("quest_num/kill",1);
                } else
                if ((quest_count % 10) == 0)
                {
                        msg += CYN "$N" CYN "喜道：真是不賴，居然連着" +
                               chinese_number(quest_count) +
                               "次都沒有失手，乾的好！\n" NOR;
                }
                message_vision(msg, master, me);
                me->delete_temp("quest/escape_times");
                me->delete("quest/kill");
                fealty = 10;
                gongxian = 1;
        if (timeover)
        {
                exp /= 2;
                pot /= 3;
                score /= 4;
                fealty /= 2;
                gongxian /= 2;
        } else
        {
                // 百分之一的機率直接贈送物品獎勵
//                if ((quest_count >= 100 && random(200) == 1) || special)
                if ( special)
                {
                  "/quest/weixiaobao"->special_bonus(master, me,"gongxian");
                }
        }
        if (type==1 || (exp==0 &&pot==0 && score==0))
          return 1;
        message("vision", sprintf(HIC "通過這次鍛鍊你獲得了%s點經驗，"
                                  "%s點潛能。\n同時還增"
                                  "長了%s點江湖閲歷，及%s點門"
                                  "派忠誠度。\n" NOR,
                                  chinese_number(exp),
                                  chinese_number(pot),
                                  chinese_number(score),
                                  chinese_number(fealty)), me);
        me->add("combat_exp", exp);
        me->add("potential", pot);
        me->add("score", score);
        me->add("family/gongxian", gongxian);
        me->add("family/fealty",fealty);
        return 1;
}
int accept_reply(object me,object ob,string arg)
{
        return "/quest/weixiaobao"->accept_reply(me,ob,arg);
}
/////其它部分： 叛師、俠客島、qiecuo///////
////下面這段幹嘛的 ？？  不知道//
int accept_betrayer(object ob)
{
        if (ob->query("shen") > 0)
        {
                if (ob->query("betrayer") > 0)
                        return 1;
        } else {
                if (ob->query("betrayer") > 5)
                        return 1;
        }
}
// 向掌門要求叛師
// Added by Constant Jan 12 2001
int betray(object ob, int depth)
{
        string *base_skill = ({
                "array",             "axe",             "blade",
                "claw",              "club",            "cuff",
                "dagger",            "dodge",           "force",
                "finger",            "gambling"         "hammer",
                "hand",              "hook",                  "leg",
          "literate",         "parry",             "spear",
                "staff",            "stick",             "strike",
                "sword",             "throwing",          "unarmed",
                "whip"
        });

        object master = this_object();
        mapping ob_skills = ob->query_skills();
        string skill_name;
        int skill_level, i;

        if (ob->query("family/family_name") !=
                master->query("family/family_name"))
        {
                message_vision("$N説道：“貴派之事自有貴派掌門處置，與我無關。”\n", master, ob);
                return 1;
        }
        if (ob->query("combat_exp") < 1000000)
        {
                message_vision("$N冷笑道：“就憑你這點微末道行，也想到江湖上去闖蕩，還不叫人笑掉大牙？”\n", master, ob);
                return 1;
        }

        if (depth == 0)
        {
                message_vision(HIR "\n$N眉頭一皺，緊緊盯着$n，目光如箭，$n不禁打了個寒戰。\n"NOR, master, ob);
                ob->start_busy(10);
                call_out("betray", 5, ob, depth + 1);
        }
        else
        {
                message_vision(HIR "\n半晌，$N歎道：“既然你執意離去，我也不便強留。只是你的一身武功，哪裏來就還哪裏去吧。”\n"NOR, master, ob);
                message_vision(HIR "説罷，揮掌在$n額頭輕輕一擊，$n只覺全身勁力被綿綿不絕抽去，大駭之下，暈了過去。\n"NOR, master, ob);
                for (i = 0; i < sizeof(ob_skills); )
                {
                        skill_name = keys(ob_skills)[i];
                        skill_level = ob_skills[skill_name];
                        if (member_array(skill_name, base_skill) != -1)
                        {
                                skill_level = skill_level / 2;
                                if (skill_level == 0)
                                        map_delete(ob_skills, skill_name);
                                else
                                {
                                        ob_skills[skill_name] = skill_level;
                                        i ++;
                                }
                        }
                        else
                        {
                                map_delete(ob_skills, skill_name);
                        }
                }
//                ob->set("betrayer", ob->query("betrayer") + 1);
                ob->add("expell",1);
                ob->set("detach/"+ob->query("family/family_name"),1);
                ob->set("title", "普通百姓");
                ob->set("class", "0");
                ob->delete("family");
                ob->save();
                ob->unconcious();
        }
        return 1;
}
// 掌門弟子可以向掌門人要牌上俠客島

int xkd(object me)
{
        object master = this_object();
        object ob = this_player();
        object ling;
        object first;
        string first_dir;
        string *dir;
        string c_player;
        int i;

  if (!me->query("family/family_name"))
   {
                message_vision("$N對着$n説：這位"+RANK_D->query_respect(me)+"何不加入我"+master->query("family/family_name")+"？\n", master, me);
                return 1;
           }
        if (ob->query("family/family_name") !=
                master->query("family/family_name"))
        {
                message_vision("$N對着$n説：我不是你的掌門人，你回你們"+me->query("family/family_name")+"去吧。\n", master, me);
                return 1;
        }

        if (!ob->query("xkd/ling"))
        {
                message_vision("$N對着$n説：你還不是掌門大弟子，擔不起如此重任。\n", master, me);
                return 1;
        }
        dir = explode(base_name(master),"/");
        first_dir = dir[sizeof(dir)-2];
        if (objectp(first = NPC_D->create_first(first_dir)))
        {
                c_player=first->query("current_player");
                destruct(first);
                if (ob->query("id")!= c_player)
                {
                        message_vision("$N對着$n説：你不是掌門大弟子，擔不起如此重任。\n", master, me);
                        return 1;
                }
        }
        if ( ob->query("xkd/ling") && !ob->query_temp("xkd/ask") )
        {
                ling = new( "/d/xiakedao/obj/tongpai1" );
                ling->set( "own", ob->query("id") );
                ling->move( ob );
                ling = new( "/d/xiakedao/obj/tongpai2" );
                ling->set( "own", ob->query("id") );
                ling->move( ob );
                message_vision( HIY"$N對$n説道：俠客島昨日送來賞善罰惡令，邀請為師上島。\n你是本門掌門弟子，就代為師走一趟吧。\n"NOR, master, ob );
                message_vision( HIC"説完，$N把兩塊令牌交到$n手裏。\n"NOR, master, ob );
                ob->set_temp("xkd/ask",1);
        }
        else
        {
                message_vision("$N對着$n説：你不是已經拿了令牌了嗎，還不速速起程。\n", master, me);
                return 1;
        }
        return 1;
}

//切磋武學包括師父獎勵和特殊perform
int do_qiecuo(string arg)
{
        object master = this_object();
        object me = this_player();
        object weapon;
        string special;
        string *sskl,pfskill,pfmartial,pfarg,pfmsg;
        mapping skl, map_status;
        mixed perform_actions = ({});
        int bl,sl,i,j,num,learn_b,fealty_b;

        fealty_b=(int)me->query("family/fealty");

        num=(int)me->query("perform/number")+1;
        if (num<4) learn_b= num * num * 100;
        else learn_b=1600;

        if (!living(me)||!living(master)) return 0;
        if (me->query("family/family_name") !=master->query("family/family_name"))
        {
                message_vision("$N對着$n説：我不是你的掌門人，你回你們"+me->query("family/family_name")+"去吧。\n", master, me);
                return 1;
        }
        if (me->is_busy() || me->is_fighting())
        {
                message_vision("$N對着$n説：你忙完了再來吧！\n", master, me);
                return 1;
        }
        if (master->is_fighting())
        {
                message_vision("$N對着$n説：我現在正忙着呢！\n", master, me);
                return 1;
        }
      //family_can_qiecuo作為師父獎勵和特殊perform切磋的區別
              if( !me->query_temp("family_can_qiecuo"))
              {
                if (!arg)
                {
                             message_vision("$N對着$n説：你要切磋什麼？\n", master, me);
                             return 1;
                }
                if( sscanf(arg, "%s.%s", pfmartial, pfarg)!=2 )
                {
                        message_vision("$N對着$n説：你要切磋什麼？\n", master, me);
                             return 1;
                }
                if (fealty_b<learn_b)
                {
                        message_vision("$N對着$n説：你還是多為本門做點貢獻再來吧！\n",master,me);
                        return 1;
                }

                if( stringp(pfskill = me->query_skill_mapped(pfmartial)))
                {
                        if (!master->query_skill(pfskill,1))
                        {
                                message_vision("$N對着$n説：這個武功我沒練過，你去找其他人吧。\n", master, me);
                                return 1;
                        }
                        perform_actions = get_dir( SKILL_D(pfskill) + "/" );
                        for ( j = 0; j < sizeof( perform_actions ); j++ )
                        {
                                sscanf( perform_actions[j], "%s.c", perform_actions[j] );
                                if ( perform_actions[j] == pfarg )
                                {
                                        bl=me->query_skill(pfmartial,1);
                                        sl=me->query_skill(pfskill,1);
                                        pfmsg="perform/"+pfarg;
                                        if(sl<10 || bl<10)
                                        {
                                                message_vision("$N對着$n説：你先打好基礎，再來切磋吧！\n", master, me);
                                                return 1;
                                        }
                                        else if(me->query(pfmsg,1)==1)
                                        {
                                                message_vision("$N對着$n説：你已經領會了這招，還要切磋麼？\n", master, me);
                                                return 1;
                                        }
                                        else
                                        {
                                                message_vision(HIW"$N哈哈笑道：“好吧，為師就傳授你些心得！”。\n"NOR, master, me);
                                                write(HIC"你聽了指導，瞑思苦想，對"+to_chinese(pfskill)+"的體會又深了一層。\n"NOR);
                                                me->set(pfmsg,1);
                                                me->add("perform/number",1);
                                                fealty_b=fealty_b - learn_b;
                                                me->set("family/fealty",fealty_b);
                                                me->start_busy(3);
                                                return 1;
                                        }
                                }
                         }
                        me->start_busy(1);
                        message_vision("$N對着$n説：你要切磋什麼？\n", master, me);
                             return 1;
                }
                else
                {
                        me->start_busy(1);
                        message_vision("$N對着$n説：你要切磋什麼？\n", master, me);
                             return 1;
                }
        }
        else
        {
                      if (!arg)
                {
                        message_vision("$N對着$n説：你要切磋什麼？\n", master, me);
                             return 1;
                }
                      if (!(special=me->query_skill_mapped(arg)))
                {
                        message_vision("$N對着$n説：你只能從基本技能中請教特殊技能。\n", master, me);
                             return 1;
                }
                  if(arg=="force")
                {
                        message_vision("$N對着$n説：內功修為，不是靠切磋能提高的。\n", master, me);
                             return 1;
                }
                  else if(special=="bixie-jian"
                          ||special=="jinshe-jian"
                          ||special=="jiuyin-baiguzhao"
                          ||special=="liangyi-jian"
                          ||special=="lonely-sword"
                          ||special=="shenzhao-jing"
                          ||special=="taixuan-gong"
                          ||special=="shenxing-baibian"
        ||special=="xianglong-zhang"
        ||(special=="hamagong" && arg=="strike")
                          )
                {
                        message_vision("$N對着$n説：此項技能無法通過切磋來提高！\n", master, me);
                             return 1;
                }
                  else
                {
                           bl=me->query_skill(arg,1);
                           sl=me->query_skill(special,1);
                           if(sl>=bl*3/2)
                           {
                                message_vision("$N對着$n説：你先打好基礎，再來切磋吧！\n", master, me);
                                return 1;
                        }
                           else
                        {       //chinese_number(p_bonus)
//                                tell_object(me,HIM + master->query("name")+"取走了你："        + chinese_number(learn_b) + "點忠誠度。\n"NOR);
                                message_vision(HIW"$N哈哈笑道：“好吧，為師就傳授你些心得！”。\n"NOR, master, me);
                                   write(HIC"你聽了指導，瞑思苦想，對"+to_chinese(special)+"的體會又深了一層。\n"NOR);
                                   me->set_skill(special,sl+1);
                                   me->delete_temp("family_can_qiecuo");
                                   me->start_busy(3);
                                   return 1;
                        }
                }
        }
}
