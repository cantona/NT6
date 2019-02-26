// hspb.c 事件：衡山水簾洞瀑布

#include <ansi.h>

// 獎勵
private void do_bonus(object room)
{
        object *obs;
        object ob;
        string msg;
        int lvl,p_bonus,s_bonus;
        int r,i;

        obs = all_inventory(room);
        if (sizeof(obs) < 1)
                return;

        r = random(365);
        if (r == 0)
        { 
                msg = HIY "【自然奇觀】衡山水簾洞激流\n"NOR;
                msg += HIG "只聽轟隆隆聲音大做，振聾發聵，令人心懼神搖！你抬頭看去，只見\n"
                          "黃昏中水簾洞籠罩在層層霧氣之中，分外妖嬈。洞外水流飛瀉，氣勢驚人！\n" NOR;
                msg += HIG "你望着湍急的瀑布飛練，為這世間美景驚歎不已，從"
                           "中不禁領悟到了武學的道理。\n" NOR; 
                for ( i = 0 ; i < sizeof(obs); i++)  // 增加潛能基本內功及潛能
                {
                        if( !living(obs[i]) || !userp(obs[i]) ) continue;
                        p_bonus = 5000 + random( 5000 );
                        s_bonus = 1000 + random( 500 );
                        addn("potential", p_bonus, obs[i]);
                        addn("score", s_bonus, obs[i]);
                        
                        lvl = obs[i]->query_skill("force", 1);
                        if (lvl >= 50 && lvl< 300 )
                                       obs[i]->set_skill("force", lvl + 10);
                        else if ( lvl >= 300 )
                                       obs[i]->set_skill("force", lvl + 1);

                }

                message("vision", msg, obs);
                message("channel:rumor", HIM"【謠言】"+"聽説衡山水簾洞瀑布激流澎湃，奇景非凡，無數遊人歎羨不已。\n"NOR, users());
               
        } else 
        if (r < 250) 
        {        
                msg = HIY "【自然奇觀】衡山水簾洞瀑流\n"NOR;
                msg += HIY "一陣轟隆轟隆的聲音傳來，你抬頭一看，只見黃昏中瀑布騰起層層霧氣。\n" NOR;
                switch (random(3)) 
                { 
                case 0: 
                        msg += HIY "看着這壯麗的瀑流，你不禁感歎，正所謂「飛流直"
                                    "下三千尺，疑是銀河落九天」啊。\n" NOR; 
                        break; 
                case 1: 
                        msg += HIY "瀑流就像一席倒掛的白簾，氣勢如虹，天地都不禁為之失色。\n" NOR; 
                        break; 
                default: 

                        msg += HIY "瀑流直如水銀泄地一般，水花四濺。\n" NOR; 
                        break; 
                } 
                msg += HIG "觀賞着飛流直下的水瀑，你不由得感歎自然造化的奇妙，隱"
                           "隱對武學也有了一點領會。\n" NOR; 
                           
                for ( i = 0 ; i < sizeof(obs); i++)
                {
                        if( !living(obs[i]) || !userp(obs[i]) ) continue;
                        p_bonus = 500 + random( 500 );
                        s_bonus = 200 + random( 200 );                        
                        addn("potential", p_bonus, obs[i]);
                        addn("score", s_bonus, obs[i]);
                }               
 
                message("vision", msg, obs);

        } else
        {
                switch (random(3))
                {
                case 0:
                        msg = WHT "瀑流漸漸緩了下來。\n" NOR;
                        break;
                case 1:
                        msg = WHT "瀑流總是不見有增強的趨勢。\n" NOR;
                        break;
                default:
                        msg = WHT "瀑流有如小橋流水，叮叮咚咚，離你所期望的相差甚遠。\n" NOR;
                        break;
                }
                msg += HIG "你心中大感失望。\n" NOR;

                message("vision", msg, obs);
        }
} 
 
// 事件觸發 
void trigger_event() 
{ 
        object room; 
        // 衡山水簾洞瀑布 
        if (objectp(room = find_object("/d/henshan/shuiliandong"))) 
                do_bonus(room); 
} 

void create() 
{ 
        seteuid(getuid()); 
        message("channel:sys", HIR"【自然奇觀】衡山水簾洞瀑布。\n"NOR, users());
        trigger_event();
}
