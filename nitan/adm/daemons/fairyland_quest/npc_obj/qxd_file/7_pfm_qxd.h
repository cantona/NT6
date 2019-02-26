// for all_cmds_qxd_hj.h
// naihe 21:42 03-10-17
// 給各個技能都加上 pfm  05-9-3 21:25

mapping can_use_pfm( string pfm_id, object me, object target )
{

    // 成功時，返回如下信息，給戰鬥函數中的 "pfm_info" 變量接收。
    // "name": "技能中文名"
    // "damages": 攻擊力
    // "me_busy": 自身忙時
    // "msg_all": 給房子裏其他人看的描述
    // "msg_me": 給自己看的描述
    // "msg_target": 給被攻擊房看的描述
    // "lost_hp": 自己消耗氣息
    mapping pfm_list;
    string *pfm_msg;
    string pfm_skills, pfm_name, pfm_limit;
    int LostHP_pfm = 10, Me_busy = 3+random(3);
    // PFM_LvNeed 在七星燈 1 號文件內以 #define 定義，至少有該等級的技能才能使用 pfm.
    // 以上2個帶大寫字母的以及 PFM_LvNeed 變量，即唯一判定 pfm 在什麼等級能夠使用、
    // 自己消耗氣息的量、自身的busy 的依據。
    string msg_all, msg_me, msg_target, find_name;
    int damages, damages_skills;
    if( !pfm_id || !me )
        return 0;
    // 絕技列表
    pfm_list = ([
        "kf": ({ "hfzj", "狂風", "feng", }),
        "by": ({ "hyzj", "暴雨", "yu",   }),
        "jl": ({ "llzj", "驚雷", "lei",  }),
        "xd": ({ "ydzj", "迅電", "dian", }),
        "dh": ({ "dhzj", "奪魂", 0,      }),
        "hy": ({ "fhzj", "火焰", 0,      }),
        "js": ({ "gszj", "巨石", 0,      }),
        //"cs": ({ "heal", "重生", 0,      }),  // 取消這個。感覺總是很不好
    ]);
    // 無此絕技存在，返回不可用
    if( undefinedp( pfm_list[ pfm_id ] ) )
        return ([ "err_msg": "你設定的絕技不存在" ]);
    // 那麼有此絕技存在，判斷玩家自身的條件是否符合
    // 是否懂得對應技能，以及技能等級是否足夠
    pfm_msg = pfm_list[ pfm_id ];
    pfm_skills = pfm_msg[0];
    pfm_name = pfm_msg[1];
    pfm_limit = pfm_msg[2];
    // 不懂該技能，返回不可用
    if( !query_temp("hj_game_skills/"+pfm_skills, me )
      || !query_temp("hj_game_damages/"+pfm_skills, me) )
        return ([ "err_msg": "你並不懂得「"+pfm_name+"」絕技的技能" ]);
    // 國度技能本國使用
    if( pfm_limit && query_temp("hj_game_find", me) != pfm_limit )
        return ([ "err_msg": "「"+pfm_name+"」絕技只能由本國度子民使用" ]);
    damages_skills=query_temp("hj_game_damages/"+pfm_skills, me);
    // 等級是否足夠、氣息是否足夠
    if( damages_skills < PFM_LvNeed )
        return ([ "err_msg":"你的技能等級不夠，無法使用「"+pfm_name+"」絕技" ]);
    if( query_temp("hj_hp", me)<(LostHP_pfm*5) )
        return ([ "err_msg":"你的氣息太弱，無法使用「"+pfm_name+"」絕技" ]);
    /*
    // 好了！一切OK，可以使用絕技！
    // 如果是恢復技，直接在這裏處理。
    if( pfm_id == "cs" )
    {
        int hp_add;
        message_vision( CYN"\n只見$N"NOR+CYN"深深地吸了一口氣，看起來精神好多了。\n\n"NOR, me );
        hp_add=query_temp("hj_game_damages/"+pfm_skills, me);
        hp_add = hp_add*2 + random(hp_add);
        addn_temp("hj_hp", hp_add, me);
        if( query_temp("hj_hp", me)>query_temp("hj_hp_max", me) )
            set_temp("hj_hp",query_temp("hj_hp_max",  me), me);
        me->start_busy( 3+random(8) );
        return 0;  // return 0 時那邊就不再處理了。
    }
    */
    if( pfm_id == "dh" )
    {
        // me 無論如何都不 busy
        int target_busy;
        if( target->query_busy() > 3 )
            return (["err_msg":query("name", target)+"還忙得很呢，還是趁機攻擊吧"]);
        if( query_temp("hj_hp", me)<(50+damages_skills) )
            return ([ "err_msg" : "你氣息虛弱，無法施展「"+pfm_name+"」絕技" ]);
        message_vision( HIB"\n只見$N"HIB"忽地身形一閃，快速無倫地貼近$n"HIB"，右掌對着$n"HIB"急拍而出！\n"NOR, me, target );
        addn_temp("hj_hp", -(damages_skills/3+random(damages_skills/5)), me);//99lv=33+19,40lv=16+8
        // 失敗
        // 奪魂技能特殊運用效果  有效抵抗各類奪魂攻擊
        if( query_temp("hj_special/sh", target) )
        {
            message_vision( HIB"只聽得$N"HIB"四周忽地響起一陣淒厲之聲，似是把$N"HIB"保護起來了一般。\n", target );
        }
        else if( !random(10) || random( 100 )+1 > damages_skills )
        {
            message_vision( CYN"$N"NOR+CYN"一驚之下急忙一閃，躲開了$n"NOR+CYN"的攻擊。\n\n"NOR, target, me );
        }
        else
        {
            target_busy = 5+random( damages_skills/10 );  // lv40:5+random(4)  lv99:5+random(9)
            tell_object( target, HIR"你一下子被拍個正中，突然全身僵硬，無法動彈！ (造成忙時 "+target_busy+" 秒)\n\n"NOR );
            tell_object(me,HIR+query("name", target)+HIR"被拍個正中，突然兩眼發直，整個人呆住了似的。(造成忙時"+target_busy+"秒)\n\n"NOR);
            tell_room(environment(target),HIR+query("name", target)+HIR"被拍個正中，突然兩眼發直，整個人呆住了似的。\n\n"NOR,({me,target}));
            target->start_busy( target_busy );
        }
        return 0;
    }
    // 確定絕技攻擊力
    damages = (damages_skills * 2) + random( damages_skills / 5 );
    // lv40 = 80 + random(8)
    // lv99 = 198 + random( 19 )
    // 效果描述及攻擊加成
    find_name=query_temp("hj_game_find", me);

    switch( pfm_name )
    {
      case "狂風":
        if( find_name == "feng" )
            damages += damages/4;   // lv40 = 100 +, lv99 = 250+
        // 描述
        msg_all = HIW"\n只見$N"HIW"忽地怒目一睜，挺身而立，兩手握起咒訣置於胸前，大聲叫道：“狂風速來！！！”\n霎時間落葉紛飛，狂風怒吼，從四面八方向着$n"HIW"直撲而至！！！\n\n"NOR;
        msg_me = HIW"\n你雙目一睜，挺身而立，兩手握起咒訣置於胸前，大聲叫道：“狂風速來！！！”\n霎時間落葉紛飛，狂風怒吼，從四面八方向着$n"HIW"直撲而至！！！\n造成了 "HIG+damages+HIW" 點傷害。\n\n"NOR;
        msg_target = HIW"\n只見$N"HIW"忽地雙目一睜，挺身而立，兩手握起咒訣置於胸前，大聲叫道：“狂風速來！！！”\n霎時間落葉紛飛，狂風怒吼，從四面八方向着你直撲而至！！！\n造成了 "HIR+damages+HIW" 點傷害。\n\n"NOR;
        break;
      case "暴雨":
        if( find_name == "yu" )
            damages += damages/4;
        msg_all = HIM"\n只見$N"NOR+HIM"忽地浮身離地，雙目微閉，兩手往外一分，柔聲念道：“密密之雨，請澆灑而下吧！”\n晴朗碧空頓時烏雲遍蓋，豆大雨點帶起劈空之聲，一顆顆都對準了$n"NOR+HIM"呼嘯而去！！！\n\n"NOR;
        msg_me = HIM"\n你浮身離地，雙目閉起，兩手往外一分，柔聲念道：“密密之雨，請澆灑而下吧！”\n晴朗碧空頓時烏雲遍蓋，豆大雨點帶起劈空之聲，一顆顆都對準了$n"NOR+HIM"呼嘯而去！！！\n造成了 "HIG+ damages + NOR+HIM" 點傷害。\n\n"NOR;
        msg_target = HIM"\n只見$N"NOR+HIM"忽地浮身離地，雙目微閉，兩手往外一分，柔聲念道：“密密之雨，請澆灑而下吧！”\n晴朗碧空頓時烏雲遍蓋，豆大雨點帶起劈空之聲，一顆顆都對準了你呼嘯而來！！！\n造成了 "HIR+ damages +NOR+HIM" 點傷害。\n\n"NOR;
        break;
      case "驚雷":
        if( find_name == "lei" )
            damages += damages/4;
        msg_all = HIC"\n忽然只見$N"NOR+HIC"雙掌往前一推，暴然喝道：“驚心之雷，響徹四方！！！”\n四處毫無預兆地雷聲炸起，聲聲巨響震人心魄，似有千軍萬馬盡皆朝$n"NOR+HIC"奔襲而去！！！\n\n"NOR;
        msg_me = HIC"\n你雙掌往前一推，暴然喝道：“驚心之雷，響徹四方！！！”\n四處毫無預兆地雷聲炸起，聲聲巨響震人心魄，似有千軍萬馬盡皆朝$n"NOR+HIC"奔襲而去！！！\n造成了 "HIG+ damages + NOR+HIC" 點傷害。\n\n"NOR;
        msg_target = HIC"\n忽然只見$N"NOR+HIC"雙掌往前一推，暴然喝道：“驚心之雷，響徹四方！！！”\n四處毫無預兆地雷聲炸起，聲聲巨響震人心魄，似有千軍萬馬盡皆朝你奔襲而來！！！\n造成了 "HIR+ damages +NOR+HIC" 點傷害。\n\n"NOR;
        break;
      case "迅電":
        if( find_name == "dian" )
            damages += damages/4;
        msg_all = HIG"\n忽然只見$N"NOR+HIG"右手抬起，一指向天，接着虛畫半圓，猛地指向$n"NOR+HIG"！\n隨着這一指，天空裏竟然劈起一道閃電，夾着沉悶雷聲，直打$n"NOR+HIG"而去！！！\n\n"NOR;
        msg_me = HIG"\n你抬起右手，一指向天，接着虛畫半圓，暗念咒文，隨即指向$n"NOR+HIG"！\n你一指方向，天空裏即刻劈起一道閃電，夾着沉悶雷聲，直向$n"NOR+HIG"打去！！！\n造成了 "HIG+damages+NOR+HIG" 點傷害。\n\n"NOR;
        msg_target = HIG"\n忽然只見$N"NOR+HIG"右手抬起，一指向天，接着虛畫半圓，猛地指向了你！\n隨着這一指，天空裏竟然劈起一道閃電，夾着沉悶雷聲，直向你打了過來！！！\n造成了 "HIR+damages+NOR+HIR" 點傷害。\n\n"NOR;
        break;
      case "火焰":
        msg_all = WHT"\n只聽得$N"NOR+WHT"哈哈大笑一聲，單掌在身前虛畫一圓，一團團"HIR"火焰"NOR+WHT"竟憑空生成，熱氣逼人！\n緊跟着，$N"NOR+WHT"喝道：“着！”雙手連甩，團團火焰立時向着$n"NOR+WHT"激射而去！！！\n\n"NOR;
        msg_me = WHT"\n你哈哈大笑一聲，單掌在身前虛畫一圓，一團團"HIR"火焰"NOR+WHT"就此憑空生成，熱氣逼人！\n緊跟着，你大喝了一聲“着！”雙手連甩，團團火焰立時向着$n"NOR+WHT"激射而去！！！\n造成了 "HIG+damages+NOR+WHT" 點傷害。\n\n"NOR;
        msg_target = WHT"\n只聽得$N"NOR+WHT"哈哈大笑一聲，單掌在身前虛畫一圓，一團團"HIR"火焰"NOR+WHT"竟憑空生成，熱氣逼人！\n緊跟着，$N"NOR+WHT"喝道：“着！”雙手連甩，團團火焰立時向着你激射而來！！！\n造成了 "HIR+damages+NOR+WHT" 點傷害。\n\n"NOR;
        break;
      case "巨石":
        msg_all = WHT"\n只聽得$N"NOR+WHT"哈哈大笑一聲，單掌在身前虛畫一圓，一塊"YEL"巨石"WHT"竟憑空生成！\n隨着$N"NOR+WHT"一聲斷喝“着！”，石塊帶起巨大壓迫之感，向着$n"NOR+WHT"砸去！！！\n\n"NOR;
        msg_me = WHT"\n你哈哈大笑一聲，單掌在身前虛畫一圓，一塊"YEL"巨石"WHT"就此憑空生成！\n你大喝一聲“着！”，唸咒運勁，石塊帶起巨大壓迫之感，向着$n"NOR+WHT"砸去！！！\n造成了 "HIG+damages+NOR+WHT" 點傷害。\n\n"NOR;
        msg_target = WHT"\n只聽得$N"NOR+WHT"哈哈大笑一聲，單掌在身前虛畫一圓，一塊"YEL"巨石"WHT"竟憑空生成！\n隨着$N"NOR+WHT"一聲斷喝“着！”，石塊帶起巨大壓迫之感，向着你砸了過來！！！\n造成了 "HIR+damages+NOR+WHT" 點傷害。\n\n"NOR;
        break;
    }
    return ([ "name": pfm_name, "damages": damages, "me_busy": Me_busy,"lost_hp": LostHP_pfm+random(LostHP_pfm),
          "msg_all": msg_all, "msg_me": msg_me, "msg_target": msg_target ]);
}